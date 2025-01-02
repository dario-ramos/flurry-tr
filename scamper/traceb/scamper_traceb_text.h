/*
 * scamper_traceb_text.h
 *
 * $Id: scamper_traceb_text.h,v 0.1 2024/04/09 17:09:16 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2010 The University of Waikato
 * Copyright (C) 2022      Matthew Luckie
 * Copyright (C) 2021-2024 Dario Ramos
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

#ifndef __SCAMPER_TRACEB_TEXT_H
#define __SCAMPER_TRACEB_TEXT_H

int scamper_file_text_traceb_write(const scamper_file_t *sf,
                                   const struct scamper_traceb *trace, void *p);

#endif /* __SCAMPER_TRACEB_TEXT_H */
