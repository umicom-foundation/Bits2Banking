/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT */
#ifndef BTB_TCP_SERVER_H
#define BTB_TCP_SERVER_H
#include <stdint.h>
#include "static_files.h"
/* Bind IPv4 loopback only. maximumClients==0 serves until Ctrl+C; a positive
 * value allows controlled teaching runs. No TLS, authentication or concurrency. */
int BtbHttpServeLoopback(uint16_t port, unsigned maximumClients);
/* Optional read-only static root. NULL keeps the original fixed-route server.
 * Both modes use one listener and the same parser, send, deadline and cleanup. */
int BtbHttpServeLoopbackWithRoot(uint16_t port, unsigned maximumClients,
                                 const BtbStaticRoot *root);
#endif
