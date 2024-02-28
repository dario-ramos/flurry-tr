/*
 * scamper_traceb_text.c
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2014      The Regents of the University of California
 * Copyright (C) 2021-2023 Dario Ramos
 * Authors: Matthew Luckie, Dario Ramos
 *
 * $Id: scamper_traceb_text.c,v 1.30 2023/01/15 16:21:51 dario-ramos Exp $
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

#ifndef lint
static const char rcsid[] =
    "$Id: scamper_traceb_text.c,v 1.30 2023/01/15 16:21:51 dario-ramos Exp $";
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "internal.h"

#include "scamper_traceb.h"
#include "scamper_file.h"
#include "scamper_traceb_text.h"
#include "utils.h"

/*
 * scamper_file_text_traceb_write
 *
 * return 0 on successful write, -1 otherwise.
 */
int scamper_file_text_traceb_write(const scamper_file_t *sf,
                                   const scamper_traceb_t *trace)
{
  /* current return code */
  int rc = -1;
  /* variables for writing to the file */
  int fd;
  off_t foff = 0;
  size_t wc;

  fd = scamper_file_getfd (sf);
  if (fd != STDOUT_FILENO && (foff = lseek (fd, 0, SEEK_CUR)) == -1)
  {
    goto cleanup;
  }

  // TODO Write actual traceb results instead
  if (write_wrap (fd, "placeholder response from traceb\n", &wc, 33) != 0)
  {
    goto cleanup;
  }

  rc = 0; /* we succeeded */

cleanup:

  return rc;
}
