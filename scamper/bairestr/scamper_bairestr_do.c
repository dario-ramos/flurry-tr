/*
 * scamper_bairestr_do.c
 *
 * $Id: scamper_bairestr_do.c,v 1.154 2021/08/25 23:51:37 mjl Exp $
 *
 * Copyright (C) 2005-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2012-2015 The Regents of the University of California
 * Copyright (C) 2016-2019 Matthew Luckie
 * Copyright (C) 2021-2022 Dario Ramos
 * Author: Matthew Luckie
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

#include "scamper_bairestr_do.h"

#include "scamper_options.h"
#include <stddef.h>

#define BAIRESTR_OPT_PROBECOUNT   2

static const scamper_option_in_t opts[] = {
//  {'A', NULL, BAIRESTR_OPT_PROBETCPACK,  SCAMPER_OPTION_TYPE_NUM},
//  {'B', NULL, BAIRESTR_OPT_PAYLOAD,      SCAMPER_OPTION_TYPE_STR},
  {'c', NULL, BAIRESTR_OPT_PROBECOUNT,   SCAMPER_OPTION_TYPE_NUM},
//  {'C', NULL, BAIRESTR_OPT_PROBEICMPSUM, SCAMPER_OPTION_TYPE_STR},
//  {'d', NULL, BAIRESTR_OPT_PROBEDPORT,   SCAMPER_OPTION_TYPE_NUM},
//  {'F', NULL, BAIRESTR_OPT_PROBESPORT,   SCAMPER_OPTION_TYPE_NUM},
//  {'i', NULL, BAIRESTR_OPT_PROBEWAIT,    SCAMPER_OPTION_TYPE_STR},
//  {'m', NULL, BAIRESTR_OPT_PROBETTL,     SCAMPER_OPTION_TYPE_NUM},
//  {'M', NULL, BAIRESTR_OPT_REPLYPMTU,    SCAMPER_OPTION_TYPE_NUM},
//  {'o', NULL, BAIRESTR_OPT_REPLYCOUNT,   SCAMPER_OPTION_TYPE_NUM},
//  {'O', NULL, BAIRESTR_OPT_OPTION,       SCAMPER_OPTION_TYPE_STR},
//  {'p', NULL, BAIRESTR_OPT_PATTERN,      SCAMPER_OPTION_TYPE_STR},
//  {'P', NULL, BAIRESTR_OPT_PROBEMETHOD,  SCAMPER_OPTION_TYPE_STR},
//  {'R', NULL, BAIRESTR_OPT_RECORDROUTE,  SCAMPER_OPTION_TYPE_NULL},
//  {'s', NULL, BAIRESTR_OPT_PROBESIZE,    SCAMPER_OPTION_TYPE_NUM},
//  {'S', NULL, BAIRESTR_OPT_SRCADDR,      SCAMPER_OPTION_TYPE_STR},
//  {'T', NULL, BAIRESTR_OPT_TIMESTAMP,    SCAMPER_OPTION_TYPE_STR},
//  {'U', NULL, BAIRESTR_OPT_USERID,       SCAMPER_OPTION_TYPE_NUM},
//  {'W', NULL, BAIRESTR_OPT_PROBETIMEOUT, SCAMPER_OPTION_TYPE_NUM},
//  {'z', NULL, BAIRESTR_OPT_PROBETOS,     SCAMPER_OPTION_TYPE_NUM},
};

static const int opts_cnt = SCAMPER_OPTION_COUNT(opts);

const char *scamper_do_bairestr_usage(void)
{
  return
    "bairestr";
}

static int bairestr_arg_param_validate(int optid, char *param, long long *out)
{
	// TODO Implement
	return 0;
//  long long tmp = 0;
//  int i;
//
//  switch(optid)
//    {
//    case PING_OPT_PROBETCPACK:
//      if(string_tollong(param, &tmp) == 1 || tmp < 0 || tmp > TCP_MAX_SEQNUM)
//	goto err;
//      break;
//
//    case PING_OPT_PAYLOAD:
//      for(i=0; param[i] != '\0'; i++)
//	if(ishex(param[i]) == 0)
//	  goto err;
//      if(i == 0 || (i % 2) != 0)
//	goto err;
//      tmp = i / 2;
//      if(tmp > 1000)
//	goto err;
//      break;
//
//    case PING_OPT_PROBECOUNT:
//      if(string_tollong(param, &tmp) == -1 ||
//	 tmp < SCAMPER_DO_PING_PROBECOUNT_MIN ||
//	 tmp > SCAMPER_DO_PING_PROBECOUNT_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_PROBEICMPSUM:
//      if(string_tollong(param, &tmp) == -1 || tmp < 0 || tmp > 65535)
//	goto err;
//      break;
//
//    case PING_OPT_PROBEDPORT:
//      if(string_tollong(param, &tmp) == -1 ||
//	 tmp < SCAMPER_DO_PING_PROBEDPORT_MIN ||
//	 tmp > SCAMPER_DO_PING_PROBEDPORT_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_PROBESPORT:
//      if(string_tollong(param, &tmp) == -1 ||
//	 tmp < SCAMPER_DO_PING_PROBESPORT_MIN ||
//	 tmp > SCAMPER_DO_PING_PROBESPORT_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_PROBEMETHOD:
//      if(strcasecmp(param, "icmp-echo") == 0)
//	tmp = SCAMPER_PING_METHOD_ICMP_ECHO;
//      else if(strcasecmp(param, "tcp-ack") == 0)
//	tmp = SCAMPER_PING_METHOD_TCP_ACK;
//      else if(strcasecmp(param, "tcp-ack-sport") == 0)
//	tmp = SCAMPER_PING_METHOD_TCP_ACK_SPORT;
//      else if(strcasecmp(param, "udp") == 0)
//	tmp = SCAMPER_PING_METHOD_UDP;
//      else if(strcasecmp(param, "udp-dport") == 0)
//	tmp = SCAMPER_PING_METHOD_UDP_DPORT;
//      else if(strcasecmp(param, "icmp-time") == 0)
//	tmp = SCAMPER_PING_METHOD_ICMP_TIME;
//      else if(strcasecmp(param, "tcp-syn") == 0)
//	tmp = SCAMPER_PING_METHOD_TCP_SYN;
//      else if(strcasecmp(param, "tcp-synack") == 0)
//	tmp = SCAMPER_PING_METHOD_TCP_SYNACK;
//      else if(strcasecmp(param, "tcp-rst") == 0)
//	tmp = SCAMPER_PING_METHOD_TCP_RST;
//      else
//	goto err;
//      break;
//
//    /* how long to wait between sending probes */
//    case PING_OPT_PROBEWAIT:
//      if(validate_probe_wait(param, &tmp) != 0)
//	goto err;
//      break;
//
//    /* the ttl to probe with */
//    case PING_OPT_PROBETTL:
//      if(string_tollong(param, &tmp) == -1 ||
//	 tmp < SCAMPER_DO_PING_PROBETTL_MIN  ||
//	 tmp > SCAMPER_DO_PING_PROBETTL_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    /* how many unique replies are required before the ping completes */
//    case PING_OPT_REPLYCOUNT:
//      if(string_tollong(param, &tmp) == -1  ||
//	 tmp < SCAMPER_DO_PING_REPLYCOUNT_MIN ||
//	 tmp > SCAMPER_DO_PING_REPLYCOUNT_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_REPLYPMTU:
//      if(string_tollong(param, &tmp) != 0 ||
//	 tmp < SCAMPER_DO_PING_REPLYPMTU_MIN ||
//	 tmp > SCAMPER_DO_PING_REPLYPMTU_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_OPTION:
//      if(strcasecmp(param, "spoof") != 0 && strcasecmp(param, "dl") != 0 &&
//	 strcasecmp(param, "tbt") != 0 && strcasecmp(param, "nosrc") != 0)
//	goto err;
//      break;
//
//    case PING_OPT_PATTERN:
//      /*
//       * sanity check that only hex characters are present, and that
//       * the pattern string is not too long.
//       */
//      for(i=0; i<SCAMPER_DO_PING_PATTERN_MAX; i++)
//	{
//	  if(param[i] == '\0') break;
//	  if(ishex(param[i]) == 0) goto err;
//	}
//      if(i == SCAMPER_DO_PING_PATTERN_MAX) goto err;
//      break;
//
//    /* the size of each probe */
//    case PING_OPT_PROBESIZE:
//      if(string_tollong(param, &tmp) == -1 || tmp < 0 || tmp > 65535)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_USERID:
//      if(string_tollong(param, &tmp) != 0 || tmp < 0)
//	goto err;
//      break;
//
//    case PING_OPT_SRCADDR:
//    case PING_OPT_TIMESTAMP:
//      break;
//
//    /* the tos bits to include in each probe */
//    case PING_OPT_PROBETOS:
//      if(string_tollong(param, &tmp) == -1 ||
//	 tmp < SCAMPER_DO_PING_PROBETOS_MIN  ||
//	 tmp > SCAMPER_DO_PING_PROBETOS_MAX)
//	{
//	  goto err;
//	}
//      break;
//
//    case PING_OPT_PROBETIMEOUT:
//      if(string_tollong(param, &tmp) != 0 ||
//	 tmp < SCAMPER_DO_PING_PROBETIMEOUT_MIN ||
//	 tmp > SCAMPER_DO_PING_PROBETIMEOUT_MAX)
//	goto err;
//      break;
//
//    default:
//      return -1;
//    }
//
//  /* valid parameter */
//  if(out != NULL)
//    *out = tmp;
//  return 0;
//
// err:
//  return -1;
}

/*
 * scamper_do_bairestr_arg_validate
 *
 *
 */
int scamper_do_bairestr_arg_validate(int argc, char *argv[], int *stop)
{
  return scamper_options_validate(opts, opts_cnt, argc, argv, stop,
				  bairestr_arg_param_validate);
}
