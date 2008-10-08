/**
 * RRDTool - src/rrd_client.h
 * Copyright (C) 2008 Florian octo Forster
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; only version 2 of the License is applicable.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * Authors:
 *   Florian octo Forster <octo at verplant.org>
 **/

#ifndef __RRD_CLIENT_H
#define __RRD_CLIENT_H 1

#include <stdint.h>

#ifndef RRDCACHED_DEFAULT_ADDRESS
# define RRDCACHED_DEFAULT_ADDRESS "unix:/tmp/rrdcached.sock"
#endif

#define RRDCACHED_DEFAULT_PORT "42217"
#define ENV_RRDCACHED_ADDRESS "RRDCACHED_ADDRESS"

int rrdc_connect (const char *addr);
int rrdc_is_connected(const char *daemon_addr);
int rrdc_disconnect (void);

int rrdc_update (const char *filename, int values_num,
        const char * const *values);

int rrdc_flush (const char *filename);
int rrdc_flush_if_daemon (const char *opt_daemon, const char *filename);


struct rrdc_stats_s
{
  const char *name;
  uint16_t type;
#define RRDC_STATS_TYPE_GAUGE   0x0001
#define RRDC_STATS_TYPE_COUNTER 0x0002
  uint16_t flags;
  union
  {
    uint64_t counter;
    double   gauge;
  } value;
  struct rrdc_stats_s *next;
};
typedef struct rrdc_stats_s rrdc_stats_t;

int rrdc_stats_get (rrdc_stats_t **ret_stats);
void rrdc_stats_free (rrdc_stats_t *ret_stats);

#endif /* __RRD_CLIENT_H */
/*
 * vim: set sw=2 sts=2 ts=8 et fdm=marker :
 */