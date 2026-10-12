#ifndef _WIN32
# define _POSIX_C_SOURCE 200809L
#endif
/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/nonblocking_server.c
 * PURPOSE: Optional bounded, nonblocking, single-threaded HTTP/1.1 reactor.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "nonblocking_server.h"
#include "nonblocking_policy.h"
#include "http.h"
#include "response_progress.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <winsock2.h>
# include <ws2tcpip.h>
# include <windows.h>
typedef SOCKET BtbNbSocket;
typedef int BtbNbIoResult;
# define BTB_NB_INVALID_SOCKET INVALID_SOCKET
# define BtbNbCloseSocket closesocket
#else
# include <arpa/inet.h>
# include <errno.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <unistd.h>
typedef int BtbNbSocket;
typedef ssize_t BtbNbIoResult;
# define BTB_NB_INVALID_SOCKET (-1)
# define BtbNbCloseSocket close
#endif

#define BTB_NB_OUTPUT_BYTES 8192U
#define BTB_NB_WRITE_SLICE 2048U
#define BTB_NB_SELECT_WAIT_US 100000

typedef struct BtbNbConnection {
    BtbNbSocket socket;
    BtbNbLifetime lifetime;
    unsigned char incoming[BTB_HTTP_MAX_HEADER];
    size_t incomingLength;
    char output[BTB_NB_OUTPUT_BYTES];
    size_t outputLength;
    size_t outputOffset;
    size_t headerLength;
    int fileChunk; /* All current output bytes belong to the body. */
    int streamFile;
    BtbStaticFile file;
    uint64_t fileRemaining;
    BtbResponseProgress progress;
} BtbNbConnection;

/* A signal handler may only set an atomic flag. The event loop itself owns all
 * descriptors, file handles, route borrows and the final release order. */
static volatile sig_atomic_t gNbStopRequested = 0;
static void BtbNbStopSignal(int signalNumber)
{
    (void)signalNumber;
    gNbStopRequested = 1;
}

static uint64_t BtbNbNow(void)
{
#ifdef _WIN32
    return (uint64_t)GetTickCount64();
#else
    struct timespec instant;
    if (clock_gettime(CLOCK_MONOTONIC, &instant) != 0) return 0U;
    return (uint64_t)instant.tv_sec * 1000U +
           (uint64_t)instant.tv_nsec / 1000000U;
#endif
}

static int BtbNbSetNonblocking(BtbNbSocket socket)
{
#ifdef _WIN32
    u_long enabled = 1UL;
    return ioctlsocket(socket, FIONBIO, &enabled) == 0;
#else
    const int flags = fcntl(socket, F_GETFL, 0);
    return flags >= 0 && fcntl(socket, F_SETFL, flags | O_NONBLOCK) == 0;
#endif
}

static int BtbNbRetryable(void)
{
#ifdef _WIN32
    const int code = WSAGetLastError();
    return code == WSAEWOULDBLOCK || code == WSAEINTR;
#else
    return errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR;
#endif
}

static void BtbNbRelease(BtbNbConnection *connection, int completed)
{
    if (connection->socket == BTB_NB_INVALID_SOCKET) return;
    if (!completed) BtbResponseProgressFail(&connection->progress);
    (void)BtbNbLifetimeFinish(&connection->lifetime, completed);
    BtbStaticFileClose(&connection->file);
    (void)BtbNbCloseSocket(connection->socket);
    /* A slot becomes reusable only after both native owners are released. */
    (void)memset(connection, 0, sizeof *connection);
    connection->socket = BTB_NB_INVALID_SOCKET;
}

static size_t BtbNbHeaderBoundary(const char *bytes, size_t count)
{
    for (size_t i = 3U; i < count; ++i)
        if (bytes[i - 3U] == '\r' && bytes[i - 2U] == '\n' &&
            bytes[i - 1U] == '\r' && bytes[i] == '\n') return i + 1U;
    return 0U;
}

/* Always publish one entirely prepared response. Neither the send buffer nor
 * the file owner can be reused while a previous response remains active. */
static int BtbNbResponseReady(BtbNbConnection *connection, size_t count,
                              size_t headerCount, uint64_t wireBody)
{
    if (count == 0U || count > sizeof connection->output ||
        headerCount == 0U || headerCount > count ||
        !BtbResponseProgressBegin(&connection->progress,
                                   (uint64_t)headerCount, wireBody)) return 0;
    connection->outputLength = count;
    connection->outputOffset = 0U;
    connection->headerLength = headerCount;
    connection->fileChunk = 0;
    return BtbNbLifetimeAdvance(&connection->lifetime, BTB_NB_WRITING,
                                 BtbNbNow());
}

static int BtbNbPrepareFixed(BtbNbConnection *connection,
                             const BtbHttpRequest *request,
                             BtbHttpResult parseResult, unsigned port)
{
    size_t count = 0U;
    if (!BtbHttpRespond(request, parseResult, port, connection->output,
                        sizeof connection->output, &count)) return 0;
    const size_t boundary = BtbNbHeaderBoundary(connection->output, count);
    if (boundary == 0U) return 0;
    return BtbNbResponseReady(connection, count, boundary,
                              (uint64_t)(count - boundary));
}

static int BtbNbPrepareRoute(BtbNbConnection *connection,
                             const BtbHttpRequest *request,
                             BtbRouteService *routes)
{
    BtbRouteResponse response = {0};
    const BtbRouteResult result = BtbRouteServiceDispatch(routes, request, &response);
    if (result == BTB_ROUTE_NOT_FOUND) return -1; /* Fall back to fixed/static. */
    if (result != BTB_ROUTE_OK) {
        static const char body[] = "Route unavailable\n";
        if (BtbRouteResponseSet(&response, 503U, BTB_ROUTE_PLAIN_TEXT,
                                body, sizeof body - 1U) != BTB_ROUTE_OK) return 0;
    }
    size_t count = 0U;
    size_t headerCount = 0U;
    if (BtbRouteEncode(request, &response, connection->output,
                       sizeof connection->output, &count,
                       &headerCount) != BTB_ROUTE_OK) return 0;
    return BtbNbResponseReady(connection, count, headerCount,
                              (uint64_t)(count - headerCount)) ? 1 : 0;
}

static int BtbNbPrepareStatic(BtbNbConnection *connection,
                              const BtbHttpRequest *request,
                              const BtbStaticRoot *root)
{
    const BtbStaticResult opened = BtbStaticFileOpen(root, request->path,
                                                      &connection->file);
    unsigned status = 200U;
    const char *errorText = NULL;
    if (opened == BTB_STATIC_NOT_FOUND) {
        status = 404U; errorText = "Not Found\n";
    } else if (opened == BTB_STATIC_FORBIDDEN) {
        status = 403U; errorText = "Forbidden\n";
    } else if (opened == BTB_STATIC_TOO_LARGE) {
        status = 413U; errorText = "File exceeds preview limit\n";
    } else if (opened != BTB_STATIC_OK) {
        status = 500U; errorText = "Internal Server Error\n";
    }
    if (opened == BTB_STATIC_OK && request->ifNoneMatchPresent != 0U &&
        BtbCacheCompareIfNoneMatch(request->ifNoneMatch,
                                   connection->file.cacheTag) == BTB_CACHE_MATCH)
        status = 304U;

    const uint64_t declared = status == 200U ? connection->file.bytes :
        status == 304U ? 0U : (uint64_t)strlen(errorText);
    const char *mediaType = (status == 200U || status == 304U) ?
        connection->file.mediaType : "text/plain; charset=utf-8";
    size_t headers = 0U;
    const int ready = (status == 200U || status == 304U) ?
        BtbCacheStaticHeaders(status, mediaType, declared,
                              connection->file.cacheTag,
                              connection->output, sizeof connection->output, &headers) :
        BtbHttpStaticHeaders(status, mediaType, declared,
                             connection->output, sizeof connection->output, &headers);
    if (!ready) return 0;

    size_t count = headers;
    if (status != 200U && status != 304U && request->method != BTB_HTTP_HEAD) {
        const size_t errorBytes = (size_t)declared;
        if (errorBytes > sizeof connection->output - count) return 0;
        (void)memcpy(connection->output + count, errorText, errorBytes);
        count += errorBytes;
    }
    const uint64_t wireBody = request->method == BTB_HTTP_HEAD ? 0U : declared;
    connection->streamFile = (status == 200U && request->method != BTB_HTTP_HEAD);
    connection->fileRemaining = connection->streamFile ? connection->file.bytes : 0U;
    return BtbNbResponseReady(connection, count, headers, wireBody);
}

static int BtbNbPrepare(BtbNbConnection *connection, unsigned port,
                         const BtbStaticRoot *root, BtbRouteService *routes)
{
    BtbHttpRequest request = {0};
    const BtbHttpResult parsed = root != NULL ?
        BtbHttpParseForFiles(connection->incoming, connection->incomingLength,
                             &request) :
        BtbHttpParse(connection->incoming, connection->incomingLength, &request);
    if (parsed == BTB_HTTP_INCOMPLETE) return 1; /* Keep reading. */
    if (parsed != BTB_HTTP_OK ||
        (request.hostPort != 0U && request.hostPort != port) ||
        strcmp(request.path, "/health") == 0) {
        return BtbNbPrepareFixed(connection, parsed == BTB_HTTP_OK ? &request : NULL,
                                 parsed, port);
    }
    if (routes != NULL) {
        const int route = BtbNbPrepareRoute(connection, &request, routes);
        if (route >= 0) return route;
    }
    if (root != NULL) return BtbNbPrepareStatic(connection, &request, root);
    return BtbNbPrepareFixed(connection, &request, parsed, port);
}

static void BtbNbRead(BtbNbConnection *connection, unsigned port,
                       const BtbStaticRoot *root, BtbRouteService *routes)
{
    if (connection->incomingLength >= sizeof connection->incoming) {
        if (!BtbNbPrepareFixed(connection, NULL, BTB_HTTP_TOO_LARGE, port))
            BtbNbRelease(connection, 0);
        return;
    }
    const size_t capacity = sizeof connection->incoming - connection->incomingLength;
#ifdef _WIN32
    const BtbNbIoResult count = recv(connection->socket,
        (char *)connection->incoming + connection->incomingLength,
        (int)capacity, 0);
#else
    const BtbNbIoResult count = recv(connection->socket,
        connection->incoming + connection->incomingLength, capacity, 0);
#endif
    if (count < 0 && BtbNbRetryable()) return;
    if (count <= 0) {
        BtbNbRelease(connection, 0);
        return;
    }
    connection->incomingLength += (size_t)count;
    if (!BtbNbLifetimeAdvance(&connection->lifetime, BTB_NB_READING,
                               BtbNbNow()) ||
        !BtbNbPrepare(connection, port, root, routes)) {
        BtbNbRelease(connection, 0);
        return;
    }
    /* When all 4096 bytes arrived without a complete header, report the
     * capacity refusal now; do not leave a peer parked until another byte. */
    if (connection->lifetime.phase == BTB_NB_READING &&
        connection->incomingLength == sizeof connection->incoming &&
        !BtbNbPrepareFixed(connection, NULL, BTB_HTTP_TOO_LARGE, port))
        BtbNbRelease(connection, 0);
}

static int BtbNbTrackSend(BtbNbConnection *connection, size_t amount)
{
    if (connection->fileChunk)
        return BtbResponseProgressAdvance(&connection->progress,
                                           BTB_RESPONSE_BODY_PART, amount);
    const size_t offset = connection->outputOffset;
    const size_t headerPart = offset < connection->headerLength ?
        ((connection->headerLength - offset) < amount ?
         (connection->headerLength - offset) : amount) : 0U;
    const size_t bodyPart = amount - headerPart;
    return (headerPart == 0U || BtbResponseProgressAdvance(
               &connection->progress, BTB_RESPONSE_HEADER_PART, headerPart)) &&
           (bodyPart == 0U || BtbResponseProgressAdvance(
               &connection->progress, BTB_RESPONSE_BODY_PART, bodyPart));
}

/* An outgoing chunk is either the complete prepared header/body response or
 * one separately loaded static-file block. No unbounded body is retained. */
static void BtbNbWrite(BtbNbConnection *connection)
{
    if (connection->outputOffset >= connection->outputLength) {
        if (connection->streamFile && connection->fileRemaining != 0U) {
            const size_t capacity = connection->fileRemaining <
                sizeof connection->output ? (size_t)connection->fileRemaining :
                sizeof connection->output;
            size_t received = 0U;
            if (BtbStaticFileRead(&connection->file, connection->output,
                                  capacity, &received) != BTB_STATIC_OK ||
                received == 0U || received > capacity) {
                BtbNbRelease(connection, 0);
                return;
            }
            connection->fileRemaining -= (uint64_t)received;
            connection->outputLength = received;
            connection->outputOffset = 0U;
            connection->fileChunk = 1;
        } else {
            const int success = BtbResponseProgressComplete(&connection->progress);
            BtbNbRelease(connection, success);
            return;
        }
    }
    const size_t left = connection->outputLength - connection->outputOffset;
    const size_t slice = left < BTB_NB_WRITE_SLICE ? left : BTB_NB_WRITE_SLICE;
#ifdef _WIN32
    const BtbNbIoResult sent = send(connection->socket,
        connection->output + connection->outputOffset, (int)slice, 0);
#else
# ifdef MSG_NOSIGNAL
    const BtbNbIoResult sent = send(connection->socket,
        connection->output + connection->outputOffset, slice, MSG_NOSIGNAL);
# else
    const BtbNbIoResult sent = send(connection->socket,
        connection->output + connection->outputOffset, slice, 0);
# endif
#endif
    if (sent < 0 && BtbNbRetryable()) return;
    if (sent <= 0 || !BtbNbTrackSend(connection, (size_t)sent) ||
        !BtbNbLifetimeAdvance(&connection->lifetime, BTB_NB_WRITING,
                               BtbNbNow())) {
        BtbNbRelease(connection, 0);
        return;
    }
    connection->outputOffset += (size_t)sent;
    if (connection->outputOffset == connection->outputLength &&
        (!connection->streamFile || connection->fileRemaining == 0U)) {
        const int completed = BtbResponseProgressComplete(&connection->progress);
        BtbNbRelease(connection, completed);
    }
}

static unsigned BtbNbActive(const BtbNbConnection connections[BTB_NB_CONNECTION_LIMIT])
{
    unsigned count = 0U;
    for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i)
        if (connections[i].socket != BTB_NB_INVALID_SOCKET) ++count;
    return count;
}

static BtbNbConnection *BtbNbFree(BtbNbConnection connections[BTB_NB_CONNECTION_LIMIT])
{
    for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i)
        if (connections[i].socket == BTB_NB_INVALID_SOCKET) return &connections[i];
    return NULL;
}

int BtbHttpServeNonblocking(uint16_t port, unsigned maximumClients,
                            const BtbStaticRoot *root, BtbRouteService *routes)
{
    if (port < 1024U || (root != NULL && root->owner == NULL) ||
        (routes != NULL && (routes->self != routes ||
                            routes->state != BTB_ROUTE_READY))) return 2;
#ifdef _WIN32
    WSADATA startup;
    if (WSAStartup(MAKEWORD(2, 2), &startup) != 0) return 1;
#endif
    int outcome = 0;
    BtbNbSocket listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == BTB_NB_INVALID_SOCKET) {
        outcome = 1;
        goto cleanup_winsock;
    }
    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
#ifdef _WIN32
    const int addressBytes = (int)sizeof address;
#else
    const socklen_t addressBytes = (socklen_t)sizeof address;
#endif
    if (bind(listener, (const struct sockaddr *)&address, addressBytes) != 0 ||
        listen(listener, (int)BTB_NB_CONNECTION_LIMIT) != 0 ||
        !BtbNbSetNonblocking(listener)) {
        fprintf(stderr, "Cannot start nonblocking listener on 127.0.0.1:%u.\n",
                (unsigned)port);
        outcome = 1;
        goto cleanup_listener;
    }
#ifndef _WIN32
    if (listener >= FD_SETSIZE) {
        outcome = 1;
        goto cleanup_listener;
    }
#endif
    BtbNbConnection clients[BTB_NB_CONNECTION_LIMIT] = {0};
    for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i)
        clients[i].socket = BTB_NB_INVALID_SOCKET;
    gNbStopRequested = 0;
    /* Restore the caller's signal dispositions before returning. This avoids
     * imposing the teaching server's signal behaviour on another subsystem. */
    void (*oldInt)(int) = signal(SIGINT, BtbNbStopSignal);
    void (*oldTerm)(int) = signal(SIGTERM, BtbNbStopSignal);
    printf("Bits2Banking nonblocking C23 HTTP lab: http://127.0.0.1:%u/\n",
           (unsigned)port);
    puts("Single select() reactor, eight connections, 3s idle/10s total deadlines.");
    fflush(stdout);
    unsigned accepted = 0U;
    uint64_t stopBegan = 0U;
    int stopping = 0;
    while (1) {
        const uint64_t now = BtbNbNow();
        if (!stopping && (gNbStopRequested ||
            (maximumClients != 0U && accepted >= maximumClients))) {
            stopping = 1;
            stopBegan = now;
            (void)BtbNbCloseSocket(listener);
            listener = BTB_NB_INVALID_SOCKET;
        }
        for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i) {
            if (clients[i].socket != BTB_NB_INVALID_SOCKET &&
                BtbNbLifetimeExpired(&clients[i].lifetime, now,
                    BTB_NB_IDLE_TIMEOUT_MS, BTB_NB_TOTAL_TIMEOUT_MS))
                BtbNbRelease(&clients[i], 0);
        }
        if (stopping && BtbNbActive(clients) == 0U) break;
        if (stopping && (now < stopBegan ||
            now - stopBegan >= BTB_NB_SHUTDOWN_GRACE_MS)) break;
        fd_set readers;
        fd_set writers;
        FD_ZERO(&readers);
        FD_ZERO(&writers);
        BtbNbSocket largest = 0;
        if (!stopping && BtbNbFree(clients) != NULL) {
            FD_SET(listener, &readers);
            largest = listener;
        }
        for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i) {
            if (clients[i].socket == BTB_NB_INVALID_SOCKET) continue;
            if (clients[i].lifetime.phase == BTB_NB_READING)
                FD_SET(clients[i].socket, &readers);
            else
                FD_SET(clients[i].socket, &writers);
            if (clients[i].socket > largest) largest = clients[i].socket;
        }
        struct timeval wait = {.tv_sec = 0, .tv_usec = BTB_NB_SELECT_WAIT_US};
#ifdef _WIN32
        const int selected = select(0, &readers, &writers, NULL, &wait);
#else
        const int selected = select(largest + 1, &readers, &writers, NULL, &wait);
#endif
        if (selected < 0) {
            if (BtbNbRetryable()) continue;
            outcome = 1;
            break;
        }
        if (selected == 0) continue;
        /* Admit at most one client per turn, so already-admitted peers retain
         * the opportunity to make progress under a busy accept queue. */
        if (!stopping && listener != BTB_NB_INVALID_SOCKET &&
            FD_ISSET(listener, &readers)) {
            BtbNbSocket peer = accept(listener, NULL, NULL);
            if (peer != BTB_NB_INVALID_SOCKET) {
                BtbNbConnection *slot = BtbNbFree(clients);
#ifndef _WIN32
                if (peer >= FD_SETSIZE) slot = NULL;
#endif
                if (slot == NULL || !BtbNbSetNonblocking(peer)) {
                    (void)BtbNbCloseSocket(peer);
                } else {
                    (void)memset(slot, 0, sizeof *slot);
                    slot->socket = peer;
                    if (!BtbNbLifetimeOpen(&slot->lifetime, BtbNbNow()))
                        BtbNbRelease(slot, 0);
                    else
                        ++accepted;
                }
            } else if (!BtbNbRetryable()) {
                outcome = 1;
                break;
            }
        }
        for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i) {
            if (clients[i].socket == BTB_NB_INVALID_SOCKET) continue;
            if (clients[i].lifetime.phase == BTB_NB_READING &&
                FD_ISSET(clients[i].socket, &readers))
                BtbNbRead(&clients[i], (unsigned)port, root, routes);
            else if (clients[i].lifetime.phase == BTB_NB_WRITING &&
                FD_ISSET(clients[i].socket, &writers))
                BtbNbWrite(&clients[i]);
        }
    }
    for (size_t i = 0U; i < BTB_NB_CONNECTION_LIMIT; ++i)
        BtbNbRelease(&clients[i], 0);
    (void)signal(SIGINT, oldInt);
    (void)signal(SIGTERM, oldTerm);
cleanup_listener:
    if (listener != BTB_NB_INVALID_SOCKET) (void)BtbNbCloseSocket(listener);
cleanup_winsock:
#ifdef _WIN32
    (void)WSACleanup();
#endif
    return outcome;
}
