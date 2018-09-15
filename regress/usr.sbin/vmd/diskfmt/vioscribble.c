/*	$OpenBSD: vioscribble.c,v 1.1 2018/09/09 04:25:32 ccardenas Exp $	*/

/*
 * Copyright (c) 2018 Ori Bernstein <ori@eigenstate.org>
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
 * Quick hack of a program to try to test vioqcow2.c against
 * vioraw.c.
 *
 * Compile with:
 *
 *     cc -pthread -o scribble vioscribble.c vioqcow2.c vioraw.c
 */
#include <sys/param.h>	/* PAGE_SIZE */
#include <sys/socket.h>
#include <sys/stat.h>

#include <machine/vmmvar.h>
#include <dev/pci/pcireg.h>
#include <dev/pci/pcidevs.h>
#include <dev/pv/virtioreg.h>
#include <dev/pv/vioblkreg.h>
#include <dev/pv/vioscsireg.h>

#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

#include <errno.h>
#include <event.h>
#include <poll.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <err.h>

#include "pci.h"
#include "vmd.h"
#include "vmm.h"
#include "virtio.h"

#define CLUSTERSZ 65536

int verbose;
struct virtio_backing qcowfile;
struct virtio_backing rawfile;

/* We expect the scribble disks to be 4g in size */
#define DISKSZ	(4ull*1024ull*1024ull*1024ull)

/* functions that io code depends on */

void
log_debug(const char *emsg, ...)
{
	if (verbose) {
		va_list ap;

		va_start(ap, emsg);
		vfprintf(stdout, emsg, ap);
		fprintf(stdout, "\n");
		va_end(ap);
	}
}

void
log_warnx(const char *emsg, ...)
{
	va_list ap;

	va_start(ap, emsg);
	vfprintf(stdout, emsg, ap);
	fprintf(stdout, "\n");
	va_end(ap);
}

void
log_warn(const char *emsg, ...)
{
	va_list ap;

	va_start(ap, emsg);
	vfprintf(stdout, emsg, ap);
	fprintf(stdout, "\n");
	va_end(ap);
}

static void
fill(size_t off, char *buf, size_t len)
{
	size_t i;

	/* use the top bits of off, since we can guess at where we went wrong. */
	for (i = 0; i < len; i++)
		buf[i] = (off >> 8);
}

int
main(int argc, char **argv)
{
	int qcfd, rawfd, i;
	char buf[64*1024], cmp[64*1024];
	off_t len, off, qcsz, rawsz;

	verbose = !!getenv("VERBOSE");
	qcfd = open("scribble.qc2", O_RDWR);
	rawfd = open("scribble.raw", O_RDWR);
	if (qcfd == -1 || virtio_init_qcow2(&qcowfile, &qcsz, qcfd) == -1)
		err(1, "unable to open qcow");
	if (rawfd == -1 || virtio_init_raw(&rawfile, &rawsz, rawfd) == -1)
		err(1, "unable to open raw");

	srandom_deterministic(123);

	/* scribble to both disks */
	printf("scribbling...\n");
	for (i = 0; i < 16; i++) {
		off = (random() % DISKSZ);
		len = random() % sizeof buf + 1;
		fill(off, buf, sizeof buf);
		if (qcowfile.pwrite(qcowfile.p, buf, len, off) == -1)
			printf("iter %d: unable to write at %llx\n", i, off);
		rawfile.pwrite(rawfile.p, buf, len, off);

		if (qcowfile.pread(qcowfile.p, buf, len, off) == -1)
			printf("unable to read at %llx\n", off);
		rawfile.pread(rawfile.p, cmp, len, off);
		if (memcmp(buf, cmp, len) != 0) {
			printf("iter %d: mismatch at 0x%llx (espected val: %d)\n",
			    i, off, (char)(off  >> 8));
			break;
		}
	}

	/* validate that both disks match */
	printf("validating...\n");
	for (off = 0; off < DISKSZ; off += sizeof buf) {
		if (qcowfile.pread(qcowfile.p, buf, sizeof buf, off) == -1)
			printf("unable to read at %llx\n", off);
		rawfile.pread(rawfile.p, cmp, sizeof buf, off);
		if (memcmp(buf, cmp, sizeof buf) != 0) {
			printf("mismatch at 0x%llx (espected val: %d)\n",
			    off, (char)(off  >> 8));
			break;
		}
	}
	return 0;
}
