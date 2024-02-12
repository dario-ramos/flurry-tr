/*
 * scamper_traceb.c
 *
 * $Id: scamper_traceb.c,v 1.138 2021/10/08 12:55:30 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2008      Alistair King
 * Copyright (C) 2015      The Regents of the University of California
 * Copyright (C) 2015      The University of Waikato
 * Copyright (C) 2019      Matthew Luckie
 * Copyright (C) 2021-2022 Dario Ramos
 * Authors: Matthew Luckie
 *          Doubletree implementation by Alistair King
 *          baires traceroute implementation by Dario Ramos
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "internal.h"

#include "scamper_traceb.h"
#include "../utils.h"

/*
 * scamper_traceb_alloc
 *
 * allocate the trace and all the possibly necessary data fields
 */
scamper_traceb_t* scamper_traceb_alloc()
{
  return (struct scamper_traceb*) malloc_zero(sizeof(struct scamper_traceb));
}

/*
 * scamper_traceb_free
 *
 */
void scamper_traceb_free(scamper_traceb_t *trace)
{
  if (trace == NULL)
    return;
  free (trace);
}
