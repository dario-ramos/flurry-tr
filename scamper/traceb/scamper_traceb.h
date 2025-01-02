/*
 * scamper_traceb.h
 *
 * $Id: scamper_traceb.h,v 0.1 2024/04/09 17:01:23 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2008      Alistair King
 * Copyright (C) 2015      The Regents of the University of California
 * Copyright (C) 2015      The University of Waikato
 * Copyright (C) 2019-2023 Matthew Luckie
 *
 * Authors: Matthew Luckie
 *          Doubletree implementation by Alistair King
 *          Traceb implementation by Dario Ramos
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

/*
 * the structures underlying the following typedefs are defined and allocated
 * in scamper_traceb_int.h
 *
 * there are get functions below for obtaining values held in those structs.
 * only internal scamper components should include scamper_traceb_int.h
 */
typedef struct scamper_traceb scamper_traceb_t;

#define SCAMPER_TRACEB_FLAG_DL           0x04 /* datalink for TX timestamps */
#define SCAMPER_TRACEB_FLAG_CONSTPAYLOAD 0x40 /* do not hack payload for csum */
#define SCAMPER_TRACEB_FLAG_PTR          0x100 /* do ptr lookups */
#define SCAMPER_TRACEB_FLAG_RAW          0x200 /* use raw socket */

#define SCAMPER_TRACEB_TYPE_ICMP_ECHO       0x01 /* ICMP echo requests */
#define SCAMPER_TRACEB_TYPE_UDP             0x02 /* UDP to unused ports */
#define SCAMPER_TRACEB_TYPE_TCP             0x03 /* TCP SYN packets */
#define SCAMPER_TRACEB_TYPE_ICMP_ECHO_PARIS 0x04 /* paris traceroute */
#define SCAMPER_TRACEB_TYPE_UDP_PARIS       0x05 /* paris traceroute */
#define SCAMPER_TRACEB_TYPE_TCP_ACK         0x06 /* TCP ACK packets */

/*
 * scamper hop flags:
 * these flags give extra meaning to fields found in the hop structure
 * by default.
 */
#define SCAMPER_TRACEB_DTREE_FLAG_NOBACK 0x01

#endif /* __SCAMPER_TRACEB_H */
