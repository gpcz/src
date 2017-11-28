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

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <machine/bus.h>
#include <machine/fdt.h>

#include <dev/ofw/openfirm.h>
#include <dev/ofw/fdt.h>

#define AIC_SSR			0x000 /* Source Select Register */
#define AIC_SMR			0x004 /* Source Mode Register */
#define AIC_SVR			0x008 /* Source Vector Register */
#define AIC_IDCR		0x044 /* Interrupt Disable Command Register */
/******************************************************************************/

struct atmlaic_softc {
	struct device			sc_dev;
	bus_space_tag_t			sc_iot;
	bus_space_handle_t		sc_ioh;
	int				sc_node;
	struct interrupt_controller 	sc_intc;
};

int		 atmlaic_match(struct device *, void *, void*);
void		 atmlaic_attach(struct device *, struct device *, void*);
void		*atmlaic_intr_establish(void *, int *, int,
		    int (*)(void *), void *, char *);

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

	if (faa->nreg != 1)
		panic("%s: number of atmlaic registers != 1!", __func__);
	sc->sc_node = faa->fa_node;
	sc->sc_iot = faa->fa_iot;
	
	if (bus_space_map(sc->sc_iot, faa->fa_reg[0].addr,
	    faa->fa_reg[0].size, 0, &sc->sc_ioh))
		panic("%s: bus_space_map failed!", __func__);

	sc->sc_intc.ic_node = faa->fa_node;
	sc->sc_intc.ic_cookie = sc;
	sc->sc_intc.ic_establish = atmlaic_intr_establish;
	arm_intr_register_fdt(&sc->sc_intc);
}

void *
atmlaic_intr_establish(void *cookie, int *cells, int level,
    int (*func)(void *), void *arg, char *name)
{
}
