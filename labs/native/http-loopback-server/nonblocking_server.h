/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/nonblocking_server.h
 * PURPOSE: Optional single-threaded select() reactor for local HTTP lessons.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_NONBLOCKING_SERVER_H
#define BTB_NONBLOCKING_SERVER_H
#include <stdint.h>
#include "static_files.h"
#include "route_service.h"

/* Eight real connections, one bounded event loop, no socket worker threads.
 * This is a teaching backend, not Umicom Framework's production web service. */
#define BTB_NB_CONNECTION_LIMIT 8U
#define BTB_NB_IDLE_TIMEOUT_MS 3000U
#define BTB_NB_TOTAL_TIMEOUT_MS 10000U
#define BTB_NB_SHUTDOWN_GRACE_MS 11000U

/* Preserves the old blocking entry points by being selected explicitly.
 * maximumClients==0 runs until Ctrl+C. Others stop accepting after that many
 * accepted clients and finish or expire those already admitted. */
int BtbHttpServeNonblocking(uint16_t port, unsigned maximumClients,
                            const BtbStaticRoot *root,
                            BtbRouteService *routes);
#endif
