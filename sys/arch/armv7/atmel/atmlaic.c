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

#include <dev/ofw/openfirm.h>
#include <dev/ofw/fdt.h>

#define AIC_SSR			0x000 /* Source Select Register */
#define AIC_SMR			0x004 /* Source Mode Register */
#define AIC_SVR			0x008 /* Source Vector Register */
#define AIC_EOICR		0x038 /* End of Interrupt Command Register*/
#define AIC_SPU			0x03C /* Spurious Interrupt Vector Register */
#define AIC_IDCR		0x044 /* Interrupt Disable Command Register */
/******************************************************************************/

struct atmlaic_softc {
	struct device			sc_dev;
	bus_space_tag_t			sc_iot;
	bus_space_handle_t		sc_ioh;
	int				sc_node;
	struct evcount		 	sc_spur;
	struct interrupt_controller 	sc_intc;
};

int		 atmlaic_match(struct device *, void *, void*);
void		 atmlaic_attach(struct device *, struct device *, void*);
void		*atmlaic_intr_establish(void *, int *, int,
		    int (*)(void *), void *, char *);
void		 atmlaic_intr(void);

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

	/*
	 * Set up the spurious interrupt service routine and make an
	 * evcount to track how often spurious interrupts happen.
	 */
	evcount_attach(&sc->sc_spur, "spur", NULL);
	bus_space_write_4(sc->sc_iot, sc->sc_ioh, AIC_SPU,
	    (u_int32_t)atmlaic_spur_intr);

	/* Register this driver as an interrupt controller to the OS. */
	sc->sc_intc.ic_node = faa->fa_node;
	sc->sc_intc.ic_cookie = sc;
	sc->sc_intc.ic_establish = atmlaic_intr_establish;
	sc->sc_intc.ic_disestablish = atmlaic_intr_disestablish;
	arm_intr_register_fdt(&sc->sc_intc);
}

void *
atmlaic_intr_establish(void *cookie, int *cells, int level,
    int (*func)(void *), void *arg, char *name)
{
	struct intrhand		*ih = NULL;
	return ih;
}

void
atmlaic_intr_disestablish(void *cookie)
{
}

void
atmlaic_intr(void)
{
	/* Get the IRQ number from the AIC. */
	/* Get the interrupt information from the array. */
	/* Call the interrupt function and increment evcount if return > 0. */
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
