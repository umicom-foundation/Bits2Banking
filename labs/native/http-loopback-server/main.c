/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/main.c
 * PURPOSE: Select an explicit port and start the loopback-only C23 web lab.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "tcp_server.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

static int BtbPort(const char *argument, uint16_t *outPort)
{
    unsigned number = 0U;
    if (argument == NULL || argument[0] == '\0') return 0;
    for (size_t i = 0U; argument[i] != '\0'; ++i) {
        if (argument[i] < '0' || argument[i] > '9') return 0;
        unsigned digit = (unsigned)(argument[i] - '0');
        if (number > (65535U - digit) / 10U) return 0;
        number = number * 10U + digit;
    }
    if (number < 1024U) return 0;
    *outPort = (uint16_t)number;
    return 1;
}
int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Usage: btb-http-server --port 8765 [--once]\n"
             "Local C23 learning service on 127.0.0.1 only.\n"
             "No TLS, uploads, external network binding or filesystem serving.");
        return 0;
    }
    uint16_t port = 0U;
    if ((argc != 3 && argc != 4) || strcmp(argv[1], "--port") != 0 ||
        !BtbPort(argv[2], &port) || (argc == 4 && strcmp(argv[3], "--once") != 0)) {
        fputs("Usage: btb-http-server --port <1024..65535> [--once]\n", stderr);
        return 2;
    }
    return BtbHttpServeLoopback(port, argc == 4 ? 1U : 0U);
}
