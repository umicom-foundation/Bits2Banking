#ifndef _WIN32
# define _POSIX_C_SOURCE 200809L
#endif
/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/tcp_server.c
 * PURPOSE: Minimal native loopback TCP adapter for a fixed C23 HTTP lesson.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "tcp_server.h"
#include "http.h"
#include "static_files.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>
typedef SOCKET BtbSocket;
typedef int BtbSocketResult;
# define BTB_INVALID_SOCKET INVALID_SOCKET
# define BtbCloseSocket closesocket
#else
# include <arpa/inet.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <unistd.h>
typedef int BtbSocket;
typedef ssize_t BtbSocketResult;
# define BTB_INVALID_SOCKET (-1)
# define BtbCloseSocket close
#endif

/* A client receives at most ten seconds of elapsed service in this learning
 * server. The socket's three-second I/O deadline is per blocking syscall; an
 * overall deadline prevents a slow peer from extending a bounded stream. */
static uint64_t BtbMilliseconds(void)
{
#ifdef _WIN32
    return (uint64_t)GetTickCount64();
#else
    struct timespec point;
    if (clock_gettime(CLOCK_MONOTONIC, &point) != 0) return 0U;
    return (uint64_t)point.tv_sec * 1000U + (uint64_t)point.tv_nsec / 1000000U;
#endif
}
static int BtbTimeExpired(uint64_t began)
{
    const uint64_t now = BtbMilliseconds();
    return now == 0U || now < began || now - began >= 10000U;
}
static volatile sig_atomic_t gStopRequested = 0;
static void BtbStop(int sig)
{
    (void)sig;
    gStopRequested = 1;
}
static int BtbSendAll(BtbSocket socket, const char *buffer, size_t bytes,
                      uint64_t began)
{
    for (size_t used = 0U; used < bytes;) {
        if (BtbTimeExpired(began)) return 0;
        const size_t left = bytes - used;
        const int amount = (int)(left > 1024U ? 1024U : left);
        #ifdef _WIN32
        const BtbSocketResult written = send(socket, buffer + used, amount, 0);
#else
        #if defined(MSG_NOSIGNAL)
        const BtbSocketResult written = send(socket, buffer + used, (size_t)amount, MSG_NOSIGNAL);
#else
        const BtbSocketResult written = send(socket, buffer + used, (size_t)amount, 0);
#endif
#endif
        if (written <= 0) return 0;
        used += (size_t)written;
    }
    return 1;
}
/* Send one open file with bounded working memory and an explicit byte count.
 * Short writes are retried, premature file EOF is not presented as success,
 * and a closed client cannot lead to an unbounded retry loop. */
static int BtbSendStaticFile(BtbSocket client, BtbStaticFile *file,
                             uint64_t began)
{
    unsigned char chunk[BTB_STATIC_STREAM_BYTES];
    uint64_t remaining = file->bytes;
    while (remaining != 0U) {
        if (BtbTimeExpired(began)) return 0;
        const size_t amount = remaining < sizeof(chunk) ? (size_t)remaining : sizeof(chunk);
        size_t received = 0U;
        if (BtbStaticFileRead(file, chunk, amount, &received) != BTB_STATIC_OK ||
            received == 0U || received > amount) return 0;
        if (!BtbSendAll(client, (const char *)chunk, received, began)) return 0;
        remaining -= (uint64_t)received;
    }
    return 1;
}
static void BtbHandleClient(BtbSocket client, unsigned port, const BtbStaticRoot *root)
{
#ifdef _WIN32
    DWORD timeout = 3000U;
    (void)setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout,
                     (int)sizeof timeout);
    (void)setsockopt(client, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout,
                     (int)sizeof timeout);
#else
    struct timeval timeout = {.tv_sec = 3, .tv_usec = 0};
    (void)setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout);
    (void)setsockopt(client, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof timeout);
#endif
    const uint64_t began = BtbMilliseconds();
    unsigned char data[BTB_HTTP_MAX_HEADER];
    size_t used = 0U;
    BtbHttpRequest request = {0};
    BtbHttpResult result = BTB_HTTP_INCOMPLETE;
    while (used < sizeof data && !BtbTimeExpired(began)) {
        #ifdef _WIN32
        const BtbSocketResult read = recv(client, (char *)data + used,
                                          (int)(sizeof data - used), 0);
#else
        const BtbSocketResult read = recv(client, (char *)data + used,
                                          sizeof data - used, 0);
#endif
        if (read <= 0) break;
        used += (size_t)read;
        result = root != NULL ? BtbHttpParseForFiles(data, used, &request)
                              : BtbHttpParse(data, used, &request);
        if (result != BTB_HTTP_INCOMPLETE) break;
    }
    if (result == BTB_HTTP_INCOMPLETE)
        result = used >= sizeof data ? BTB_HTTP_TOO_LARGE : BTB_HTTP_INVALID;
    char response[2048];
    size_t responseBytes = 0U;
    /* Preserve original two-route behaviour when no static root is provided.
     * /health is deliberately retained in static mode as a diagnostic route. */
    if (root == NULL || result != BTB_HTTP_OK ||
        strcmp(request.path, "/health") == 0 ||
        (request.hostPort != 0U && request.hostPort != port)) {
        if (BtbHttpRespond(result == BTB_HTTP_OK ? &request : NULL, result,
                           port, response, sizeof response, &responseBytes))
            (void)BtbSendAll(client, response, responseBytes, began);
        return;
    }
    BtbStaticFile file = {0};
    const BtbStaticResult opened = BtbStaticFileOpen(root, request.path, &file);
    unsigned code = 200U;
    const char *message = NULL;
    if (opened == BTB_STATIC_NOT_FOUND) { code = 404U; message = "Not Found\n"; }
    else if (opened == BTB_STATIC_FORBIDDEN) { code = 403U; message = "Forbidden\n"; }
    else if (opened == BTB_STATIC_TOO_LARGE) { code = 413U; message = "File exceeds preview limit\n"; }
    else if (opened != BTB_STATIC_OK) { code = 500U; message = "Internal Server Error\n"; }
    const uint64_t bytes = code == 200U ? file.bytes : (uint64_t)strlen(message);
    const char *mediaType = code == 200U ? file.mediaType : "text/plain; charset=utf-8";
    const int headers = BtbHttpStaticHeaders(code, mediaType, bytes,
                                              response, sizeof response, &responseBytes);
    int delivered = headers && BtbSendAll(client, response, responseBytes, began);
    if (delivered && request.method != BTB_HTTP_HEAD) {
        if (code == 200U) delivered = BtbSendStaticFile(client, &file, began);
        else delivered = BtbSendAll(client, message, (size_t)bytes, began);
    }
    if (!delivered) fprintf(stderr, "Static response incomplete or client disconnected.\n");
    BtbStaticFileClose(&file);
}
int BtbHttpServeLoopbackWithRoot(uint16_t port, unsigned maximumClients,
                                 const BtbStaticRoot *root)
{
    if (root != NULL && root->owner == NULL) return 2;
    if (port < 1024U) return 2;
#ifdef _WIN32
    WSADATA startup;
    if (WSAStartup(MAKEWORD(2, 2), &startup) != 0) return 1;
#endif
    BtbSocket server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == BTB_INVALID_SOCKET) {
        fprintf(stderr, "Unable to create a TCP socket.\n");
#ifdef _WIN32
        (void)WSACleanup();
#endif
        return 1;
    }
    struct sockaddr_in address;
    (void)memset(&address, 0, sizeof address);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#ifdef _WIN32
    const int addressSize = (int)sizeof address;
#else
    const socklen_t addressSize = (socklen_t)sizeof address;
#endif
    if (bind(server, (const struct sockaddr *)&address, addressSize) != 0 ||
        listen(server, 4) != 0) {
        fprintf(stderr, "Cannot listen on 127.0.0.1:%u. Is the port in use?\n", (unsigned)port);
        (void)BtbCloseSocket(server);
#ifdef _WIN32
        (void)WSACleanup();
#endif
        return 1;
    }
    gStopRequested = 0;
    (void)signal(SIGINT, BtbStop);
    (void)signal(SIGTERM, BtbStop);
    printf("Bits2Banking C23 HTTP lab: http://127.0.0.1:%u/\n", (unsigned)port);
    if (root == NULL)
        puts("Routes: GET / and GET /health. HEAD is supported. Stop with Ctrl+C.");
    else
        puts("Read-only static root enabled. GET/HEAD files and /health. Stop with Ctrl+C.");
    fflush(stdout);
    unsigned handled = 0U;
    int outcome = 0;
    while (!gStopRequested && (maximumClients == 0U || handled < maximumClients)) {
        fd_set listeners;
        FD_ZERO(&listeners);
        FD_SET(server, &listeners);
        struct timeval wait = {.tv_sec = 0, .tv_usec = 250000};
#ifdef _WIN32
        const int selected = select(0, &listeners, NULL, NULL, &wait);
#else
        const int selected = select(server + 1, &listeners, NULL, NULL, &wait);
#endif
        if (selected == 0) continue;
        if (selected < 0) {
            if (gStopRequested) break;
#ifndef _WIN32
            if (errno == EINTR) continue;
#endif
            outcome = 1; break;
        }
        BtbSocket client = accept(server, NULL, NULL);
        if (client == BTB_INVALID_SOCKET) {
            if (gStopRequested) break;
            outcome = 1; break;
        }
        BtbHandleClient(client, (unsigned)port, root);
        (void)BtbCloseSocket(client);
        ++handled;
    }
    (void)BtbCloseSocket(server);
#ifdef _WIN32
    (void)WSACleanup();
#endif
    return outcome;
}

/* Keep the established API and its fixed routes available to previous lessons.
 * Static serving is an explicitly selected extension, not a replacement. */
int BtbHttpServeLoopback(uint16_t port, unsigned maximumClients)
{
    return BtbHttpServeLoopbackWithRoot(port, maximumClients, NULL);
}
