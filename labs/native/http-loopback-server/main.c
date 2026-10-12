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
/* Original fixed-route command parser remains available for source review.
 * Its observable --port and --once behaviour is preserved in the active path. */
#if 0
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
#endif

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Usage: btb-http-server --port 8765 [--root ABSOLUTE_SITE_DIRECTORY] [--once]\n"
             "Loopback-only C23 teaching web server at 127.0.0.1, GET/HEAD and /health.\n"
             "Without --root the original fixed routes are preserved.\n"
             "With --root, serve read-only regular files beneath that directory.\n"
             "No upload, directory listing, PHP execution, TLS or public binding.\n"
             "Files are limited to 64 MiB, with an overall 10-second client deadline.\n"
             "Press Ctrl+C to stop the server.");
        return 0;
    }
    uint16_t port = 0U;
    unsigned once = 0U;
    const char *rootPath = NULL;
    if (argc < 3 || strcmp(argv[1], "--port") != 0 ||
        !BtbPort(argv[2], &port)) {
        fputs("Usage: btb-http-server --port <1024..65535> [--root ABSOLUTE_PATH] [--once]\n", stderr);
        return 2;
    }
    for (int i = 3; i < argc; ++i) {
        if (strcmp(argv[i], "--once") == 0 && once == 0U) once = 1U;
        else if (strcmp(argv[i], "--root") == 0 && rootPath == NULL && i + 1 < argc)
            rootPath = argv[++i];
        else {
            fputs("Invalid or repeated server option. Use --help.\n", stderr);
            return 2;
        }
    }
    if (rootPath == NULL) return BtbHttpServeLoopback(port, once);
    BtbStaticRoot root = {0};
    const BtbStaticResult opened = BtbStaticRootOpen(rootPath, &root);
    if (opened != BTB_STATIC_OK) {
        fprintf(stderr, "Cannot open read-only static root (%s): %s\n",
                rootPath, BtbStaticResultText(opened));
        return 2;
    }
    const int exitCode = BtbHttpServeLoopbackWithRoot(port, once, &root);
    BtbStaticRootClose(&root);
    return exitCode;
}
