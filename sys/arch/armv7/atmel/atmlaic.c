/*
 * Copyright (c) 2015 Gregory P. Czerniak <gregczrk@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Device driver for the Atmel Advanced Interrupt Controller (AIC).
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/device.h>
#include <sys/evcount.h>

#include <machine/bus.h>
#include <machine/fdt.h>
#include <machine/intr.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/fdt.h>

#define AIC_NIRQ		128   /* Number of IRQs. */
#define AIC_SSR			0x000 /* Source Select Register */
#define AIC_SMR			0x004 /* Source Mode Register */
#define  AIC_SMR_INT_LEVEL_SENSITIVE	0x0000
#define  AIC_SMR_INT_EDGE_TRIGGERED	0x0020
#define  AIC_SMR_EXT_HIGH_LEVEL		0x0040
#define  AIC_SMR_EXT_POSITIVE_EDGE   	0x0060
#define AIC_SVR			0x008 /* Source Vector Register */
#define AIC_ISR			0x018 /* Interrupt Status Register */
#define AIC_EOICR		0x038 /* End of Interrupt Command Register*/
#define AIC_SPU			0x03C /* Spurious Interrupt Vector Register */
#define AIC_IECR		0x040 /* Interrupt Enable Command Register */
#define AIC_IDCR		0x044 /* Interrupt Disable Command Register */
#define AIC_ICCR		0x048 /* Interrupt Clear Command Register */
/******************************************************************************/

struct atmlaic_softc {
	struct device			  sc_dev;
	bus_space_tag_t			  sc_iot;
	bus_space_handle_t		  sc_ioh;
	int				  sc_node;
	struct evcount		 	  sc_spur;
	struct interrupt_controller 	  sc_intc;
	struct intrhand			**sc_handlers;
};
struct atmlaic_softc *atml_intc = NULL;

struct intrhand {
	int (*ih_func)(void *);		/* Interrupt handler function. */
	void *ih_arg;			/* Interrupt handler arguments. */
	int ih_ipl;			/* OpenBSD IPL. */
	int ih_irq;			/* IRQ number. */
	struct evcount ih_count;	/* Event counter for this interrupt. */
	char *ih_name;			/* Interrupt name. */
};

int		 atmlaic_match(struct device *, void *, void*);
void		 atmlaic_attach(struct device *, struct device *, void*);
void		 atmlaic_intr_enable(struct atmlaic_softc *, int);
void		 atmlaic_intr_enable(struct atmlaic_softc *, int);
void		*atmlaic_intr_establish(void *, int *, int,
		    int (*)(void *), void *, char *);
void		 atmlaic_intr_disestablish(void *cookie);
void		 atmlaic_intr(void);
void		 atmlaic_spur_intr(void);

struct cfattach atmlaic_ca = {
	sizeof (struct atmlaic_softc), atmlaic_match, atmlaic_attach
};

struct cfdriver atmlaic_cd = {
	NULL, "atmlaic", DV_DULL
};

int
atmlaic_match(struct device *parent, void *cfdata, void *aux)
{
	struct fdt_attach_args *faa = aux;

	return OF_is_compatible(faa->fa_node, "atmel,sama5d3-aic");
}

void
atmlaic_attach(struct device *parent, struct device *self, void *args)
{
	struct atmlaic_softc *sc = (struct atmlaic_softc *)self;
	struct fdt_attach_args *faa = args;
	int i;

	atml_intc = sc;

	/*
	 * There is only one region of memory-mapped register space for
	 * this device.  If there's zero or more than one in the device
	 * tree file, something is wrong.
	 */
	if (faa->fa_nreg != 1)
		panic("%s: number of atmlaic registers != 1!", __func__);
	sc->sc_node = faa->fa_node;
	sc->sc_iot = faa->fa_iot;

	/* Get access to the SoC's memory-mapped space for this device. */
	if (bus_space_map(sc->sc_iot, faa->fa_reg[0].addr,
	    faa->fa_reg[0].size, 0, &sc->sc_ioh))
		panic("%s: bus_space_map failed!", __func__);

	/* Disable all interrupts. */
	for (i = 0; i < AIC_NIRQ; i++)
		atmlaic_intr_disable(sc, i);

	/*
	 * Set up the spurious interrupt service routine and make an
	 * evcount to track how often spurious interrupts happen.
	 */
	evcount_attach(&sc->sc_spur, "spur", NULL);
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SPU,
	    (u_int32_t)atmlaic_spur_intr);

	/* Prepare all interrupt handle pointers and set them to NULL. */
	sc->sc_handlers = mallocarray(AIC_NIRQ,
	    sizeof(*sc->sc_handlers), M_DEVBUF, M_ZERO | M_NOWAIT);

	/* Register this driver as an interrupt controller to the OS. */
	sc->sc_intc.ic_node = faa->fa_node;
	sc->sc_intc.ic_cookie = sc;
	sc->sc_intc.ic_establish = atmlaic_intr_establish;
	sc->sc_intc.ic_disestablish = atmlaic_intr_disestablish;
	arm_intr_register_fdt(&sc->sc_intc);
}

void
atmlaic_intr_enable(struct atmlaic_softc *sc, int irq)
{
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SSR, irq);
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_IECR, 1);
}

void
atmlaic_intr_disable(struct atmlaic_softc *sc, int irq)
{
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SSR, irq);
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_IDCR, 1);
}

/*
 *  Atmel AIC supports eight interrupt priority levels. OpenBSD ARM
 *  specifies 13 different IPLs. This function converts the generic
 *  ARM IPLs to an approximation that Atmel AIC can use.
 */
int
atmlaic_ipl_to_priority(int ipl)
{
	switch (ipl)
	{
	case IPL_NONE:
		return 0;
		break;
	case IPL_SOFT:
		return 1;
		break;
	case IPL_SOFTCLOCK:
	case IPL_SOFTNET:
	case IPL_SOFTTTY:
		return 2;
		break;
	case IPL_BIO:
		return 3;
		break;
	case IPL_NET:
		return 4;
		break;
	case IPL_TTY:
	case IPL_VM:
		return 5;
		break;
	case IPL_AUDIO:
		return 6;
		break;
	case IPL_CLOCK:
	case IPL_STATCLOCK:
	case IPL_SCHED:
	case IPL_HIGH:
		return 7;
		break;
	}
	return 0;
}

/*
 *  Converts an interrupt trigger value from the device tree
 *  specification to one used by the Source Mode Register.
 */
u_int32_t
atmlaic_convert_trigger(int trigger_val)
{
}

void *
atmlaic_intr_establish(void *cookie, int *cells, int level,
    int (*func)(void *), void *arg, char *name)
{
	struct atmlaic_softc	*sc = cookie;
	struct intrhand		*ih = NULL;
	int			 irqno = cells[0];
	int			 psw;

	if (irqno < 0 || irqno >= AIC_NIRQ)
		panic("%s: bogus irqnumber %d: %s", __func__,
		    irqno, name);

	if (sc->sc_handlers[irqno] != NULL)
		panic("%s: irq %d already registered" , __func__,
		    irqno);

	ih = malloc(sizeof(*ih), M_DEVBUF, M_WAITOK);
	ih->ih_func = func;
	ih->ih_arg = arg;
	ih->ih_ipl = level;
	ih->ih_irq = irqno;
	ih->ih_name = name;

	psw = disable_interrupts(PSR_I);

	sc->sc_handlers[irqno] = ih;

	if (name != NULL)
		evcount_attach(&ih->ih_count, name, &ih->ih_irq);

	/* Select the interrupt to set up. */
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SSR, ih->ih_irq);
	/* Set ISR to atmlaic_intr(). */
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SPU,
	    (u_int32_t)atmlaic_intr);
	/* TODO: Set priority and trigger. */
	/* Clear the interrupt. */
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_ICCR, 1);

	atmlaic_intr_enable(sc, irqno);
	
	restore_interrupts(psw);
	return ih;
}

void
atmlaic_intr_disestablish(void *cookie)
{
	struct intrhand		*ih = cookie;
	struct atmlaic_softc	*sc = atml_intc;
	int			 psw;

	psw = disable_interrupts(PSR_I);

	atmlaic_intr_disable(sc, ih->ih_irq);
	sc->sc_handlers[ih->ih_irq] = NULL;
	if (ih->ih_name != NULL)
		evcount_detach(&ih->ih_count);
	free(ih, M_DEVBUF, sizeof(*ih));

	restore_interrupts(psw);
}

void
atmlaic_intr(void)
{
	unsigned int		 irq;
	int			 s;
	struct intrhand		*ih;
	struct atmlaic_softc 	*sc = atml_intc;

	/* Get the IRQ number for the current interrupt. */
	irq = bus_space_read_4(sc->sc_iot, sc->sc_ioh, AIC_ISR) & 0x7F;

	/* Get the interrupt information from the array. */
	/* Call the interrupt function and increment evcount if return > 0. */
	if ((ih = sc->sc_handlers[irq]) != NULL) {
		s = splraise(ih->ih_ipl);
		if (ih->ih_func(ih->ih_arg))
			ih->ih_count.ec_count++;
		splx(s);
	}

	/*
	 * Set the End of Interrupt register.  This jumps us back to what we
	 * were doing.
	 */
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_EOICR, i);
}

void
atmlaic_spur_intr(void)
{
	/* Increment the spurious interrupt counter. */
	sc->sc_spur.ec_count++;
	
	/*
	 * Set the End of Interrupt register.  This jumps us back to what we
	 * were doing.
	 */
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_EOICR, i);
}
