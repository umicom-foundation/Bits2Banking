/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT */
#ifndef BTB_TCP_SERVER_H
#define BTB_TCP_SERVER_H
#include <stdint.h>
/* Bind IPv4 loopback only. maximumClients==0 serves until Ctrl+C; a positive
 * value allows controlled teaching runs. No TLS, authentication or concurrency. */
int BtbHttpServeLoopback(uint16_t port, unsigned maximumClients);
#endif
