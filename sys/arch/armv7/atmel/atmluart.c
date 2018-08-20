/*
 * Copyright (c) 2018 Gregory P. Czerniak <gregczrk@gmail.com>
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
#include <sys/uio.h>
#include <sys/device.h>
#include <sys/conf.h>

#include <dev/cons.h>

#include <machine/fdt.h>

#include <dev/ofw/openfirm.h>

struct atmluart_softc {
};

int     atmluartprobe(struct device *parent, void *self, void *aux);           
void atmluartattach(struct device *parent, struct device *self, void *aux);

cdev_decl(atmluart);

struct cfdriver atmluart_cd = {
	NULL, "atmluart", DV_TTY
};

struct cfattach atmluart_ca = {
	sizeof(struct atmluart_softc), atmluartprobe, atmluartattach
};

void atmluart_init_cons(void) {
}

int atmluartprobe(struct device *parent, void *self, void *aux) {
	struct fdt_attach_args *faa = aux;

	return OF_is_compatible(faa->fa_node, "atmel,at91sam9260-usart");
}

void atmluartattach(struct device *parent, struct device *self, void *aux) {
}
