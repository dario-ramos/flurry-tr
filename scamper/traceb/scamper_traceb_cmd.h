/*
 * scamper_traceb_cmd.h
 *
 * $Id: scamper_traceb_cmd.h,v 0.1 2024/04/09 16:43:36 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2010 The University of Waikato
 * Author: Matthew Luckie, Dario Ramos
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

#ifndef __SCAMPER_TRACEB_CMD_H
#define __SCAMPER_TRACEB_CMD_H

void* scamper_do_traceb_alloc(char *str, char *errbuf, size_t errlen);
int scamper_do_traceb_arg_validate(int argc, char *argv[], int *stop,
                                   char *errbuf, size_t errlen);
const char* scamper_do_traceb_usage(void);

#endif /* __SCAMPERB_TRACEB_CMD_H */
