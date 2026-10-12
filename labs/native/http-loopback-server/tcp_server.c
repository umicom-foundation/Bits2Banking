/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/tcp_server.c
 * PURPOSE: Minimal native loopback TCP adapter for a fixed C23 HTTP lesson.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "tcp_server.h"
#include "http.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
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

static volatile sig_atomic_t gStopRequested = 0;
static void BtbStop(int sig)
{
    (void)sig;
    gStopRequested = 1;
}
static int BtbSendAll(BtbSocket socket, const char *buffer, size_t bytes)
{
    for (size_t used = 0U; used < bytes;) {
        const size_t left = bytes - used;
        const int amount = (int)(left > 1024U ? 1024U : left);
        #ifdef _WIN32
        const BtbSocketResult written = send(socket, buffer + used, amount, 0);
#else
        const BtbSocketResult written = send(socket, buffer + used, (size_t)amount, 0);
#endif
        if (written <= 0) return 0;
        used += (size_t)written;
    }
    return 1;
}
static void BtbHandleClient(BtbSocket client, unsigned port)
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
    unsigned char data[BTB_HTTP_MAX_HEADER];
    size_t used = 0U;
    BtbHttpRequest request = {0};
    BtbHttpResult result = BTB_HTTP_INCOMPLETE;
    while (used < sizeof data) {
        #ifdef _WIN32
        const BtbSocketResult read = recv(client, (char *)data + used,
                                          (int)(sizeof data - used), 0);
#else
        const BtbSocketResult read = recv(client, (char *)data + used,
                                          sizeof data - used, 0);
#endif
        if (read <= 0) break;
        used += (size_t)read;
        result = BtbHttpParse(data, used, &request);
        if (result != BTB_HTTP_INCOMPLETE) break;
    }
    if (result == BTB_HTTP_INCOMPLETE)
        result = used >= sizeof data ? BTB_HTTP_TOO_LARGE : BTB_HTTP_INVALID;
    char response[2048];
    size_t responseBytes = 0U;
    if (BtbHttpRespond(result == BTB_HTTP_OK ? &request : NULL, result,
                       port, response, sizeof response, &responseBytes))
        (void)BtbSendAll(client, response, responseBytes);
}
int BtbHttpServeLoopback(uint16_t port, unsigned maximumClients)
{
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
    puts("Routes: GET / and GET /health. HEAD is supported. Stop with Ctrl+C.");
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
        BtbHandleClient(client, (unsigned)port);
        (void)BtbCloseSocket(client);
        ++handled;
    }
    (void)BtbCloseSocket(server);
#ifdef _WIN32
    (void)WSACleanup();
#endif
    return outcome;
}
