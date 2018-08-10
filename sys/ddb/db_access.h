/*	$OpenBSD: db_access.h,v 1.9 2018/05/07 15:52:46 visa Exp $	*/
/*	$NetBSD: db_access.h,v 1.6 1994/10/09 08:29:57 mycroft Exp $	*/

/*
 * Mach Operating System
 * Copyright (c) 1993,1992,1991,1990 Carnegie Mellon University
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 *
 *	Author: David B. Golub, Carnegie Mellon University
 *	Date:	7/90
 */

/*
 * Data access functions for debugger.
 */
db_expr_t db_get_value(db_addr_t, size_t, int);
void db_put_value(db_addr_t, size_t, db_expr_t);

void db_read_bytes(db_addr_t, size_t, char *);
void db_write_bytes(db_addr_t, size_t, char *);

#define DB_STACK_TRACE_MAX	19

struct db_stack_trace {
	unsigned int	st_count;
	db_addr_t	st_pc[DB_STACK_TRACE_MAX];
};

void db_print_stack_trace(struct db_stack_trace *, int (*)(const char *, ...));
void db_save_stack_trace(struct db_stack_trace *);
