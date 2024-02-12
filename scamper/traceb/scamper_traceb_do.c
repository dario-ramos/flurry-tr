/*
 * scamper_traceb_do.c
 *
 * $Id: scamper_traceb_do.c,v 1.154 2021/08/25 23:51:37 mjl Exp $
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "internal.h"

#include "scamper.h"
#include "scamper_debug.h"
#include "scamper_addr.h"
#include "scamper_list.h"
#include "scamper_traceb.h"
#include "scamper_task.h"
#include "scamper_traceb_do.h"
#include "scamper_options.h"
#include "scamper_file.h"
#include "scamper_osinfo.h"
#include "utils.h"

#define TRACEB_OPT_PROBECOUNT   2

/* the callback functions registered with the traceb task */
static scamper_task_funcs_t trace_funcs;

static const scamper_option_in_t opts[] =
  {
//  {'A', NULL, TRACEB_OPT_PROBETCPACK,  SCAMPER_OPTION_TYPE_NUM},
//  {'B', NULL, TRACEB_OPT_PAYLOAD,      SCAMPER_OPTION_TYPE_STR},
        { 'c', NULL, TRACEB_OPT_PROBECOUNT, SCAMPER_OPTION_TYPE_NUM },
//  {'C', NULL, TRACEB_OPT_PROBEICMPSUM, SCAMPER_OPTION_TYPE_STR},
//  {'d', NULL, TRACEB_OPT_PROBEDPORT,   SCAMPER_OPTION_TYPE_NUM},
//  {'F', NULL, TRACEB_OPT_PROBESPORT,   SCAMPER_OPTION_TYPE_NUM},
//  {'i', NULL, TRACEB_OPT_PROBEWAIT,    SCAMPER_OPTION_TYPE_STR},
//  {'m', NULL, TRACEB_OPT_PROBETTL,     SCAMPER_OPTION_TYPE_NUM},
//  {'M', NULL, TRACEB_OPT_REPLYPMTU,    SCAMPER_OPTION_TYPE_NUM},
//  {'o', NULL, TRACEB_OPT_REPLYCOUNT,   SCAMPER_OPTION_TYPE_NUM},
//  {'O', NULL, TRACEB_OPT_OPTION,       SCAMPER_OPTION_TYPE_STR},
//  {'p', NULL, TRACEB_OPT_PATTERN,      SCAMPER_OPTION_TYPE_STR},
//  {'P', NULL, TRACEB_OPT_PROBEMETHOD,  SCAMPER_OPTION_TYPE_STR},
//  {'R', NULL, TRACEB_OPT_RECORDROUTE,  SCAMPER_OPTION_TYPE_NULL},
//  {'s', NULL, TRACEB_OPT_PROBESIZE,    SCAMPER_OPTION_TYPE_NUM},
//  {'S', NULL, TRACEB_OPT_SRCADDR,      SCAMPER_OPTION_TYPE_STR},
//  {'T', NULL, TRACEB_OPT_TIMESTAMP,    SCAMPER_OPTION_TYPE_STR},
//  {'U', NULL, TRACEB_OPT_USERID,       SCAMPER_OPTION_TYPE_NUM},
//  {'W', NULL, TRACEB_OPT_PROBETIMEOUT, SCAMPER_OPTION_TYPE_NUM},
//  {'z', NULL, TRACEB_OPT_PROBETOS,     SCAMPER_OPTION_TYPE_NUM},
    };

static const int opts_cnt = SCAMPER_OPTION_COUNT(opts);

/* is this running on sunos */
static int sunos = 0;

/* address cache used to avoid reallocating the same address multiple times */
extern scamper_addrcache_t *addrcache;

void* scamper_do_traceb_alloc(char *str)
{
  char *addr;
  scamper_option_out_t *opts_out = NULL, *opt;
  scamper_traceb_t *trace = NULL;

  /* try and parse the string passed in */
  if (scamper_options_parse (str, opts, opts_cnt, &opts_out, &addr) != 0)
  {
    goto err;
  }

  /* if there is no IP address after the options string, then stop now */
  if (addr == NULL)
  {
    goto err;
  }

  scamper_options_free (opts_out);
  opts_out = NULL;

  trace = scamper_traceb_alloc ();
  if (trace == NULL)
  {
    printerror (__func__, "could not alloc traceb");
    goto err;
  }
  if ((trace->dst = scamper_addrcache_resolve (addrcache, AF_UNSPEC, addr))
      == NULL)
  {
    goto err;
  }

  return trace;

err:
  if (trace != NULL)
    scamper_traceb_free (trace);
  return NULL;
}

/*
 * scamper_do_traceb_alloctask
 *
 */
scamper_task_t* scamper_do_traceb_alloctask(void *data, scamper_list_t *list,
                                            scamper_cycle_t *cycle)
{
  scamper_traceb_t *trace = (scamper_traceb_t*) data;
  scamper_task_sig_t *sig = NULL;
  scamper_task_t *task = NULL;

  /* allocate a task structure and store the trace with it */
  if ((task = scamper_task_alloc (trace, &trace_funcs)) == NULL)
    goto err;

  /* declare the signature of the task's probes */
  if ((sig = scamper_task_sig_alloc (SCAMPER_TASK_SIG_TYPE_TX_IP)) == NULL)
    goto err;
  sig->sig_tx_ip_dst = scamper_addr_use (trace->dst);
  if (scamper_task_sig_add (task, sig) != 0)
    goto err;
  sig = NULL;

  return task;

err:
  if (sig != NULL)
    scamper_task_sig_free (sig);
  if (task != NULL)
  {
    scamper_task_setdatanull (task);
    scamper_task_free (task);
  }
  return NULL;
}

const char* scamper_do_traceb_usage(void)
{
  return "traceb";
}

static int traceb_arg_param_validate(int optid, char *param, long long *out)
{
  // TODO Implement
  return 0;
}

/*
 * scamper_do_traceb_arg_validate
 *
 *
 */
int scamper_do_traceb_arg_validate(int argc, char *argv[], int *stop)
{
  return scamper_options_validate (opts, opts_cnt, argc, argv, stop,
                                   traceb_arg_param_validate);
}

void scamper_do_traceb_free(void *data)
{
  scamper_traceb_free ((scamper_traceb_t*) data);
}

static scamper_traceb_t* traceb_getdata(const scamper_task_t *task)
{
  return scamper_task_getdata (task);
}

static void do_traceb_free(scamper_task_t *task)
{
  scamper_traceb_t *trace = traceb_getdata (task);

  if (trace != NULL)
    scamper_traceb_free (trace);

  return;
}

/*
 * do_traceb_probe
 *
 * time to probe, so send the packet.
 */
static void do_traceb_probe(scamper_task_t *task)
{
  // TODO Implement the actual probing instead of going straight to "done"
  scamper_task_queue_done (task, 500);
}

static void do_traceb_write(scamper_file_t *sf, scamper_task_t *task)
{
  scamper_file_write_traceb (sf, NULL); // TODO Pass trace data
  return;
}

int scamper_do_traceb_init(void)
{
  const scamper_osinfo_t *osinfo;

  // TODO Implement and wire up the commented out callbacks
  trace_funcs.probe = do_traceb_probe;
  // trace_funcs.handle_icmp    = do_trace_handle_icmp;
  // trace_funcs.handle_dl      = do_trace_handle_dl;
  // trace_funcs.handle_timeout = do_trace_handle_timeout;
  trace_funcs.write = do_traceb_write;
  trace_funcs.task_free = do_traceb_free;
  // trace_funcs.halt           = do_trace_halt;

  osinfo = scamper_osinfo_get ();
  if (SCAMPER_OSINFO_IS_SUNOS(osinfo))
    sunos = 1;

  return 0;
}
