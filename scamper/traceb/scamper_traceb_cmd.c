/*
 * scamper_traceb_cmd.c
 *
 * $Id: scamper_traceb_cmd.c,v 0.1 2024/04/09 17:13:38 dario-ramos Exp $
 *
 * Copyright (C) 2003-2006 Matthew Luckie
 * Copyright (C) 2006-2011 The University of Waikato
 * Copyright (C) 2008      Alistair King
 * Copyright (C) 2012-2015 The Regents of the University of California
 * Copyright (C) 2015      The University of Waikato
 * Copyright (C) 2019-2023 Matthew Luckie
 * Copyright (C) 2024      The Regents of the University of California
 * Copyright (C) 2021-2024 Dario Ramos
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "internal.h"

#include "scamper_traceb.h"
#include "scamper_traceb_cmd.h"
#include "scamper_options.h"
#include "utils.h"

#define TRACEB_OPT_DPORT       1
#define TRACEB_OPT_FIRSTHOP    2
#define TRACEB_OPT_GAPLIMIT    3
#define TRACEB_OPT_GAPACTION   4
#define TRACEB_OPT_LOOPS       5
#define TRACEB_OPT_HOPLIMIT    7
#define TRACEB_OPT_PMTUD       8
#define TRACEB_OPT_PAYLOAD     9
#define TRACEB_OPT_METHOD      10
#define TRACEB_OPT_ATTEMPTS    11
#define TRACEB_OPT_ALLATTEMPTS 12
#define TRACEB_OPT_SPORT       13
#define TRACEB_OPT_TOS         14
#define TRACEB_OPT_TTLDST      15
#define TRACEB_OPT_USERID      16
#define TRACEB_OPT_WAITTIMEOUT 17
#define TRACEB_OPT_SRCADDR     18
#define TRACEB_OPT_CONFIDENCE  19
#define TRACEB_OPT_WAITPROBE   20
#define TRACEB_OPT_GSSENTRY    21
#define TRACEB_OPT_LSSNAME     22
#define TRACEB_OPT_OFFSET      23
#define TRACEB_OPT_OPTION      24
#define TRACEB_OPT_RTRADDR     25
#define TRACEB_OPT_SQUERIES    26
#define TRACEB_OPT_WAITPROBE_HOP 27

static const scamper_option_in_t opts[] = {
  // TODO Check which options are necessary
  {'c', NULL, TRACEB_OPT_CONFIDENCE,  SCAMPER_OPTION_TYPE_NUM},
  {'d', NULL, TRACEB_OPT_DPORT,       SCAMPER_OPTION_TYPE_STR},
  {'f', NULL, TRACEB_OPT_FIRSTHOP,    SCAMPER_OPTION_TYPE_NUM},
  {'g', NULL, TRACEB_OPT_GAPLIMIT,    SCAMPER_OPTION_TYPE_NUM},
  {'G', NULL, TRACEB_OPT_GAPACTION,   SCAMPER_OPTION_TYPE_NUM},
  {'H', NULL, TRACEB_OPT_WAITPROBE_HOP, SCAMPER_OPTION_TYPE_STR},
  {'l', NULL, TRACEB_OPT_LOOPS,       SCAMPER_OPTION_TYPE_NUM},
  {'m', NULL, TRACEB_OPT_HOPLIMIT,    SCAMPER_OPTION_TYPE_NUM},
  {'M', NULL, TRACEB_OPT_PMTUD,       SCAMPER_OPTION_TYPE_NULL},
  {'N', NULL, TRACEB_OPT_SQUERIES,    SCAMPER_OPTION_TYPE_NUM},
  {'o', NULL, TRACEB_OPT_OFFSET,      SCAMPER_OPTION_TYPE_NUM},
  {'O', NULL, TRACEB_OPT_OPTION,      SCAMPER_OPTION_TYPE_STR},
  {'p', NULL, TRACEB_OPT_PAYLOAD,     SCAMPER_OPTION_TYPE_STR},
  {'P', NULL, TRACEB_OPT_METHOD,      SCAMPER_OPTION_TYPE_STR},
  {'q', NULL, TRACEB_OPT_ATTEMPTS,    SCAMPER_OPTION_TYPE_NUM},
  {'Q', NULL, TRACEB_OPT_ALLATTEMPTS, SCAMPER_OPTION_TYPE_NULL},
  {'r', NULL, TRACEB_OPT_RTRADDR,     SCAMPER_OPTION_TYPE_STR},
  {'s', NULL, TRACEB_OPT_SPORT,       SCAMPER_OPTION_TYPE_NUM},
  {'S', NULL, TRACEB_OPT_SRCADDR,     SCAMPER_OPTION_TYPE_STR},
  {'t', NULL, TRACEB_OPT_TOS,         SCAMPER_OPTION_TYPE_STR},
  {'T', NULL, TRACEB_OPT_TTLDST,      SCAMPER_OPTION_TYPE_NULL},
  {'U', NULL, TRACEB_OPT_USERID,      SCAMPER_OPTION_TYPE_NUM},
  {'w', NULL, TRACEB_OPT_WAITTIMEOUT, SCAMPER_OPTION_TYPE_STR},
  {'W', NULL, TRACEB_OPT_WAITPROBE,   SCAMPER_OPTION_TYPE_STR},
  {'z', NULL, TRACEB_OPT_GSSENTRY,    SCAMPER_OPTION_TYPE_STR},
  {'Z', NULL, TRACEB_OPT_LSSNAME,     SCAMPER_OPTION_TYPE_STR},
};
static const int opts_cnt = SCAMPER_OPTION_COUNT(opts);

typedef struct opt_limit
{
  char      *name;
  long long  min;
  long long  max;
} opt_limit_t;

static const opt_limit_t limits[] = {
  {NULL, 0, 0}, /* zero unused */
  {"dport", 1, 65535},
  {"firsthop", 1, 255},
  {"gaplimit", 1, 255},
  {"gapaction", 1, 2},
  {"loops", 0, 255},
  {NULL, 0, 0}, /* unused */
  {"hoplimit", 0, 255},
  {NULL, 0, 0}, /* pmtud */
  {NULL, 0, 0}, /* payload */
  {NULL, 0, 0}, /* method */
  {"attempts", 1, 20},
  {NULL, 0, 0}, /* all-attempts */
  {"sport", 0, 65535},
  {"tos", 0, 255},
  {NULL, 0, 0}, /* ttldst */
  {"userid", 0, UINT32_MAX},
  {NULL, 0, 0}, /* wait-timeout */
  {NULL, 0, 0}, /* srcaddr */
  {NULL, 0, 0}, /* confidence */
  {NULL, 0, 0}, /* wait-probe */
  {NULL, 0, 0}, /* gss-entry */
  {NULL, 0, 0}, /* lss-name */
  {"offset", 0, 8190},
  {NULL, 0, 0}, /* -O options */
  {NULL, 0, 0}, /* rtr-addr */
  {NULL, 1, 255}, /* squeries */
  {NULL, 0, 0}, /* wait-probe-hop */
};

static int traceb_arg_param_validate(int optid, char *param, long long *out,
				    char *errbuf, size_t errlen)
{
  struct timeval tv;
  long tmp = 0;
  int i;

#ifndef NDEBUG
  errbuf[0] = '\0';
#endif

  switch(optid)
    {
    case TRACEB_OPT_DPORT:
    case TRACEB_OPT_FIRSTHOP:
    case TRACEB_OPT_GAPLIMIT:
    case TRACEB_OPT_GAPACTION:
    case TRACEB_OPT_LOOPS:
    case TRACEB_OPT_OFFSET:
    case TRACEB_OPT_HOPLIMIT:
    case TRACEB_OPT_ATTEMPTS:
    case TRACEB_OPT_SPORT:
    case TRACEB_OPT_SQUERIES:
    case TRACEB_OPT_TOS:
    case TRACEB_OPT_USERID:
      if(string_tolong(param, &tmp) != 0 ||
	 tmp < limits[optid].min || tmp > limits[optid].max)
	{
	  snprintf(errbuf, errlen, "%s must be within %lld - %lld",
		   limits[optid].name, limits[optid].min, limits[optid].max);
	  goto err;
	}
      break;

    case TRACEB_OPT_OPTION:
      if(strcasecmp(param, "const-payload") == 0)
	tmp = SCAMPER_TRACEB_FLAG_CONSTPAYLOAD;
      else if(strcasecmp(param, "dl") == 0)
	tmp = SCAMPER_TRACEB_FLAG_DL;
      else if(strcasecmp(param, "dtree-noback") == 0)
	tmp = SCAMPER_TRACEB_DTREE_FLAG_NOBACK;
      else if(strcasecmp(param, "ptr") == 0)
	{
#ifndef DISABLE_SCAMPER_HOST
	  tmp = SCAMPER_TRACEB_FLAG_PTR;
#else
	  snprintf(errbuf, errlen, "scamper not built with host support");
	  goto err;
#endif
	}
      else if(strcasecmp(param, "raw") == 0)
	tmp = SCAMPER_TRACEB_FLAG_RAW;
      else
	{
	  snprintf(errbuf, errlen, "unknown option");
	  goto err;
	}
      break;

    case TRACEB_OPT_PAYLOAD:
      if((i = string_ishex(param)) == 0)
	{
	  snprintf(errbuf, errlen, "payload must be specified in hex");
	  goto err;
	}
      if((i % 2) != 0)
	{
	  snprintf(errbuf, errlen, "expected even number of hex characters");
	  goto err;
	}
      tmp = i;
      break;

    case TRACEB_OPT_METHOD:
      if(strcasecmp(param, "UDP") == 0)
	tmp = SCAMPER_TRACEB_TYPE_UDP;
      else if(strcasecmp(param, "TCP") == 0)
	tmp = SCAMPER_TRACEB_TYPE_TCP;
      else if(strcasecmp(param, "ICMP") == 0)
	tmp = SCAMPER_TRACEB_TYPE_ICMP_ECHO;
      else if(strcasecmp(param, "ICMP-paris") == 0)
	tmp = SCAMPER_TRACEB_TYPE_ICMP_ECHO_PARIS;
      else if(strcasecmp(param, "UDP-paris") == 0)
	tmp = SCAMPER_TRACEB_TYPE_UDP_PARIS;
      else if(strcasecmp(param, "TCP-ack") == 0)
	tmp = SCAMPER_TRACEB_TYPE_TCP_ACK;
      else
	{
	  snprintf(errbuf, errlen, "invalid traceb method");
	  goto err;
	}
      break;

    case TRACEB_OPT_WAITTIMEOUT:
      if(timeval_fromstr(&tv, param, 1000000) != 0)
	{
	  snprintf(errbuf, errlen, "malformed timeout");
	  goto err;
	}
      if(tv.tv_usec != 0)
	{
	  snprintf(errbuf, errlen, "timeout cannot have fractions of second");
	  goto err;
	}
      if(timeval_cmp_lt(&tv, 1, 0) || timeval_cmp_gt(&tv, 10, 0))
	{
	  snprintf(errbuf, errlen, "timeout must be within 1s - 10s");
	  goto err;
	}
      tmp = (tv.tv_sec * 1000000) + tv.tv_usec;
      break;

    case TRACEB_OPT_WAITPROBE:
      if(timeval_fromstr(&tv, param, 10000) != 0)
	{
	  snprintf(errbuf, errlen, "malformed inter-probe delay");
	  goto err;
	}
      if((tv.tv_usec % 10000) != 0)
	{
	  snprintf(errbuf, errlen, "inter-probe granularity limited to 10ms");
	  goto err;
	}
      if(timeval_cmp_gt(&tv, 2, 0))
	{
	  snprintf(errbuf, errlen, "inter-probe delay cannot be > 2s");
	  goto err;
	}
      tmp = (tv.tv_sec * 1000000) + tv.tv_usec;
      break;

    case TRACEB_OPT_WAITPROBE_HOP:
      if(timeval_fromstr(&tv, param, 1000000) != 0)
	{
	  snprintf(errbuf, errlen, "malformed wait-probe-hop delay");
	  goto err;
	}
      if(timeval_cmp_gt(&tv, 2, 0))
	{
	  snprintf(errbuf, errlen, "wait-probe-hop delay cannot be > 2s");
	  goto err;
	}
      tmp = (tv.tv_sec * 1000000) + tv.tv_usec;
      break;

    case TRACEB_OPT_CONFIDENCE:
      if(string_tolong(param, &tmp) != 0 || (tmp != 95 && tmp != 99))
	{
	  snprintf(errbuf, errlen, "confidence must be 95 or 99");
	  goto err;
	}
      break;

    case TRACEB_OPT_SRCADDR:
    case TRACEB_OPT_GSSENTRY:
    case TRACEB_OPT_LSSNAME:
    case TRACEB_OPT_RTRADDR:
      /* these parameters are validated at execution time */
      break;

    case TRACEB_OPT_PMTUD:
    case TRACEB_OPT_ALLATTEMPTS:
    case TRACEB_OPT_TTLDST:
      /* these options don't have parameters */
      break;

    default:
      goto err;
    }

  /* valid parameter */
  if(out != NULL)
    *out = (long long)tmp;
  return 0;

 err:
  assert(errbuf[0] != '\0');
  return -1;
}

int scamper_do_traceb_arg_validate(int argc, char *argv[], int *stop,
                                   char *errbuf, size_t errlen)
{
  return scamper_options_validate(opts, opts_cnt, argc, argv, stop,
                                  errbuf, errlen, traceb_arg_param_validate);
}

const char *scamper_do_traceb_usage(void)
{
  // TODO Adjust to traceb
  return
    "traceb [-MQT] [-c confidence] [-d dport] [-f firsthop]\n"
    "      [-g gaplimit] [-G gapaction] [-H wait-probe-hop] [-l loops]\n"
    "      [-m maxttl] [-N squeries] [-o offset] [-O options] [-p payload]\n"
    "      [-P method] [-q attempts] [-r rtraddr] [-s sport] [-S srcaddr]\n"
    "      [-t tos] [-U userid] [-w wait-timeout] [-W wait-probe]\n"
    "      [-z gss-entry] [-Z lss-name]";
}
