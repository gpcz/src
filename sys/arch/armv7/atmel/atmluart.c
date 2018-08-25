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
#include <sys/tty.h>

#include <dev/cons.h>

#include <machine/fdt.h>

#include <dev/ofw/openfirm.h>

#define AUART_STATUS	0x0014
#define  AUART_RXRDY	0x0001
#define  AUART_TXRDY	0x0002
#define AUART_RXHLD	0x0018
#define AUART_TXHLD	0x001C

struct atmluart_softc {
};

int	atmluartprobe(struct device *parent, void *self, void *aux);           
void	atmluartattach(struct device *parent, struct device *self, void *aux);
int	atmluartcnattach(bus_space_tag_t iot, bus_addr_t iobase, int rate,
    tcflag_t cflag);
int	atmluartcngetc(dev_t dev);
void	atmluartcnputc(dev_t dev, int c);
void	atmluartcnpollc(dev_t dev, int on);

cdev_decl(atmluart);

struct cfdriver atmluart_cd = {
	NULL, "atmluart", DV_TTY
};

struct cfattach atmluart_ca = {
	sizeof(struct atmluart_softc), atmluartprobe, atmluartattach
};

bus_space_tag_t		atmluartconsiot;
bus_space_handle_t	atmluartconsioh;
bus_addr_t		atmluartconsaddr;
tcflag_t		atmluartconscflag = TTYDEF_CFLAG;

void atmluart_init_cons(void) {
	struct fdt_reg reg;
	void *node;

	if ((node = fdt_find_cons("atmel,at91sam9260-dbgu")) == NULL)
		return;

	if (fdt_get_reg(node, 0, &reg))
		return;

	atmluartcnattach(fdt_cons_bs_tag, reg.addr, B115200, TTYDEF_CFLAG);
}

int atmluartprobe(struct device *parent, void *self, void *aux) {
	struct fdt_attach_args *faa = aux;

	return OF_is_compatible(faa->fa_node, "atmel,at91sam9260-usart");
}

int atmluartcnattach(bus_space_tag_t iot, bus_addr_t iobase, int rate, tcflag_t cflag) {
	static struct consdev atmluartcons = {
		NULL, NULL, atmluartcngetc, atmluartcnputc, atmluartcnpollc, NULL,
		NODEV, CN_MIDPRI
	};

	if (bus_space_map(iot, iobase, 0x100, 0, &atmluartconsioh))
			return ENOMEM;

	cn_tab = &atmluartcons;
	cn_tab->cn_dev = makedev(12, 0);

	atmluartconsiot = iot;
	atmluartconsaddr = iobase;
	atmluartconscflag = cflag;

	return 0;
}

int atmluartcngetc(dev_t dev) {
	int character;
	int s;
	s = splhigh();
	splx(s);
	return character;
}

void atmluartcnputc(dev_t dev, int c) {
	int s;
	s = splhigh();
	splx(s);
}

void atmluartcnpollc(dev_t dev, int on) {
}

/*void atmluartattach(struct device *parent, struct device *self, void *aux) {
  }*/


