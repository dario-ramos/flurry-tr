/*
 * scamper_traceb.h
 *
 * $Id: scamper_traceb.h,v 1.138 2021/09/18 14:21:11 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2008      Alistair King
 * Copyright (C) 2015      The Regents of the University of California
 * Copyright (C) 2015      The University of Waikato
 * Copyright (C) 2019      Matthew Luckie
 * Copyright (C) 2021-2023 Dario Ramos
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

#ifndef __SCAMPER_TRACEB_H
#define __SCAMPER_TRACEB_H

/* forward declare some important structures */
struct scamper_addr;

typedef struct scamper_traceb
{
  /* the current list, cycle, and defaults */
  // TODO Add these back in later on
  // struct scamper_list   *list;
  // struct scamper_cycle  *cycle;
  // uint32_t               userid;
  struct scamper_addr *src;
  struct scamper_addr *dst;
} scamper_traceb_t;

scamper_traceb_t* scamper_traceb_alloc(void);
void scamper_traceb_free(scamper_traceb_t *trace);

#endif /* __SCAMPER_TRACEB_H */
