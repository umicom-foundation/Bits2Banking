/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/http.c
 * PURPOSE: Bounded HTTP/1.1 request framing, loopback Host admission and
 *          fixed educational GET/HEAD responses.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "http.h"
#include <stdio.h>
#include <string.h>

static int BtbAlpha(unsigned char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
static int BtbDigit(unsigned char c)
{
    return c >= '0' && c <= '9';
}
static unsigned char BtbLower(unsigned char c)
{
    return c >= 'A' && c <= 'Z' ? (unsigned char)(c + ('a' - 'A')) : c;
}
static int BtbEqualCase(const unsigned char *bytes, size_t length, const char *word)
{
    const size_t expected = strlen(word);
    if (length != expected) return 0;
    for (size_t i = 0U; i < length; ++i)
        if (BtbLower(bytes[i]) != (unsigned char)word[i]) return 0;
    return 1;
}
/* Parse a literal loopback host and optional decimal port; no ambiguous DNS
 * alias, userinfo, IPv6 shorthand or external hostname is accepted. */
static int BtbHost(const unsigned char *value, size_t length, unsigned *port)
{
    static const char localhost[] = "localhost";
    static const char address[] = "127.0.0.1";
    size_t hostLength = 0U;
    while (hostLength < length && value[hostLength] != ':') ++hostLength;
    if (!BtbEqualCase(value, hostLength, localhost) &&
        !BtbEqualCase(value, hostLength, address)) return 0;
    if (hostLength == length) { *port = 0U; return 1; }
    unsigned parsed = 0U;
    if (hostLength + 1U == length) return 0;
    for (size_t i = hostLength + 1U; i < length; ++i) {
        if (!BtbDigit(value[i])) return 0;
        const unsigned digit = (unsigned)(value[i] - '0');
        if (parsed > (65535U - digit) / 10U) return 0;
        parsed = parsed * 10U + digit;
    }
    if (parsed < 1U) return 0;
    *port = parsed;
    return 1;
}
/* A full CRLF pair must be available before an individual line can end. */
static size_t BtbLineEnd(const unsigned char *bytes, size_t start, size_t end)
{
    for (size_t i = start; i + 1U < end; ++i)
        if (bytes[i] == '\r' && bytes[i + 1U] == '\n') return i;
    return end;
}
static int BtbTarget(const unsigned char *value, size_t length, char out[BTB_HTTP_MAX_PATH])
{
    if (length == 0U || length >= BTB_HTTP_FIXED_PATH_LIMIT || value[0] != '/') return 0;
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char c = value[i];
        if (c == '.' || c == '\\' || c == '%' || c == '?' || c == '#') return 0;
        if (!(BtbAlpha(c) || BtbDigit(c) || c == '/' || c == '-' || c == '_')) return 0;
    }
    (void)memcpy(out, value, length);
    out[length] = '\0';
    return 1;
}


/* Static-site URLs may contain .html, .css and a query. Only the path becomes
 * a filesystem selection; the file owner later checks every decoded segment.
 * Reject fragments, control bytes and ambiguous query encodings. */
static int BtbSiteTarget(const unsigned char *value, size_t length,
                         char out[BTB_HTTP_MAX_PATH])
{
    if (length == 0U || length >= BTB_HTTP_MAX_PATH || value[0] != '/') return 0;
    size_t pathLength = 0U;
    while (pathLength < length && value[pathLength] != '?') ++pathLength;
    if (pathLength == 0U) return 0;
    for (size_t i = 0U; i < pathLength; ++i) {
        const unsigned char c = value[i];
        if (!(BtbAlpha(c) || BtbDigit(c) || c == '/' || c == '-' || c == '_' ||
              c == '.' || c == '%')) return 0;
    }
    if (pathLength < length) {
        for (size_t i = pathLength + 1U; i < length; ++i) {
            const unsigned char c = value[i];
            if (!(BtbAlpha(c) || BtbDigit(c) || c == '=' || c == '&' ||
                  c == '_' || c == '-' || c == '.' || c == '%' || c == '+'))
                return 0;
        }
    }
    memcpy(out, value, pathLength);
    out[pathLength] = '\0';
    return 1;
}
/* The exact previous public parser is retained for review. Its request-line,
 * host and body-framing policy continues through the shared implementation
 * below. Static-file routing adds an explicit target grammar instead of
 * weakening existing two-route behaviour. */
#if 0
BtbHttpResult BtbHttpParse(const unsigned char *bytes, size_t byteCount,
                           BtbHttpRequest *out)
{
    if (out == NULL || (bytes == NULL && byteCount != 0U)) return BTB_HTTP_INVALID;
    if (byteCount > BTB_HTTP_MAX_HEADER) return BTB_HTTP_TOO_LARGE;
    if (byteCount == 0U) return BTB_HTTP_INCOMPLETE;
    size_t finished = 0U;
    /* Reject control characters, bare LF, bare CR and embedded NUL. A trailing
     * CR is allowed only while the network request remains incomplete. */
    for (size_t i = 0U; i < byteCount; ++i) {
        const unsigned char c = bytes[i];
        if (c == '\r') {
            if (i + 1U == byteCount) return BTB_HTTP_INCOMPLETE;
            if (bytes[i + 1U] != '\n') return BTB_HTTP_INVALID;
        } else if (c == '\n') {
            if (i == 0U || bytes[i - 1U] != '\r') return BTB_HTTP_INVALID;
        } else if (c < 0x20U || c > 0x7eU) {
            return BTB_HTTP_INVALID;
        }
        if (i >= 3U && bytes[i - 3U] == '\r' && bytes[i - 2U] == '\n' &&
            bytes[i - 1U] == '\r' && c == '\n') {
            finished = i + 1U;
            break;
        }
    }
    if (finished == 0U) return byteCount == BTB_HTTP_MAX_HEADER ? BTB_HTTP_TOO_LARGE
                                                                 : BTB_HTTP_INCOMPLETE;
    /* Do not accept request pipelining or payload bytes we cannot parse. */
    if (finished != byteCount) return BTB_HTTP_INVALID;
    const size_t firstEnd = BtbLineEnd(bytes, 0U, finished);
    if (firstEnd == finished || firstEnd > 255U) return BTB_HTTP_INVALID;
    size_t firstSpace = 0U;
    while (firstSpace < firstEnd && bytes[firstSpace] != ' ') ++firstSpace;
    if (firstSpace == firstEnd) return BTB_HTTP_INVALID;
    size_t secondSpace = firstSpace + 1U;
    while (secondSpace < firstEnd && bytes[secondSpace] != ' ') ++secondSpace;
    if (secondSpace == firstSpace + 1U || secondSpace == firstEnd) return BTB_HTTP_INVALID;
    if (firstEnd - secondSpace - 1U != 8U ||
        memcmp(bytes + secondSpace + 1U, "HTTP/1.1", 8U) != 0)
        return BTB_HTTP_INVALID;
    /* No extra spaces or optional request-line grammar in this teaching subset. */
    if (firstSpace != 3U && firstSpace != 4U) return BTB_HTTP_METHOD_NOT_ALLOWED;
    BtbHttpRequest candidate = {0};
    if (firstSpace == 3U && memcmp(bytes, "GET", 3U) == 0)
        candidate.method = BTB_HTTP_GET;
    else if (firstSpace == 4U && memcmp(bytes, "HEAD", 4U) == 0)
        candidate.method = BTB_HTTP_HEAD;
    else
        return BTB_HTTP_METHOD_NOT_ALLOWED;
    if (!BtbTarget(bytes + firstSpace + 1U, secondSpace - firstSpace - 1U,
                   candidate.path)) return BTB_HTTP_INVALID;
    size_t offset = firstEnd + 2U;
    unsigned hostSeen = 0U, headers = 0U;
    while (offset < finished) {
        const size_t end = BtbLineEnd(bytes, offset, finished);
        if (end == finished) return BTB_HTTP_INVALID;
        if (end == offset) break;
        if (++headers > 32U || end - offset > 512U) return BTB_HTTP_TOO_LARGE;
        size_t separator = offset;
        while (separator < end && bytes[separator] != ':') ++separator;
        if (separator == offset || separator == end) return BTB_HTTP_INVALID;
        for (size_t i = offset; i < separator; ++i)
            if (!(BtbAlpha(bytes[i]) || BtbDigit(bytes[i]) || bytes[i] == '-'))
                return BTB_HTTP_INVALID;
        size_t start = separator + 1U;
        while (start < end && (bytes[start] == ' ' || bytes[start] == '\t')) ++start;
        size_t valueEnd = end;
        while (valueEnd > start && bytes[valueEnd - 1U] == ' ') --valueEnd;
        if (BtbEqualCase(bytes + offset, separator - offset, "host")) {
            if (hostSeen++ != 0U || !BtbHost(bytes + start, valueEnd - start,
                                              &candidate.hostPort)) return BTB_HTTP_INVALID;
        } else if (BtbEqualCase(bytes + offset, separator - offset, "content-length") ||
                   BtbEqualCase(bytes + offset, separator - offset, "transfer-encoding")) {
            /* This lab has no request-body decoder; rejecting both avoids an
             * ambiguous body boundary or conflicting length declarations. */
            return BTB_HTTP_INVALID;
        }
        offset = end + 2U;
    }
    if (hostSeen != 1U) return BTB_HTTP_INVALID;
    *out = candidate;
    return BTB_HTTP_OK;
}

#endif

static BtbHttpResult BtbHttpParseInternal(const unsigned char *bytes, size_t byteCount,
                                           BtbHttpRequest *out, int staticFiles)
{
    if (out == NULL || (bytes == NULL && byteCount != 0U)) return BTB_HTTP_INVALID;
    if (byteCount > BTB_HTTP_MAX_HEADER) return BTB_HTTP_TOO_LARGE;
    if (byteCount == 0U) return BTB_HTTP_INCOMPLETE;
    size_t finished = 0U;
    /* Reject control characters, bare LF, bare CR and embedded NUL. A trailing
     * CR is allowed only while the network request remains incomplete. */
    for (size_t i = 0U; i < byteCount; ++i) {
        const unsigned char c = bytes[i];
        if (c == '\r') {
            if (i + 1U == byteCount) return BTB_HTTP_INCOMPLETE;
            if (bytes[i + 1U] != '\n') return BTB_HTTP_INVALID;
        } else if (c == '\n') {
            if (i == 0U || bytes[i - 1U] != '\r') return BTB_HTTP_INVALID;
        } else if (c < 0x20U || c > 0x7eU) {
            return BTB_HTTP_INVALID;
        }
        if (i >= 3U && bytes[i - 3U] == '\r' && bytes[i - 2U] == '\n' &&
            bytes[i - 1U] == '\r' && c == '\n') {
            finished = i + 1U;
            break;
        }
    }
    if (finished == 0U) return byteCount == BTB_HTTP_MAX_HEADER ? BTB_HTTP_TOO_LARGE
                                                                 : BTB_HTTP_INCOMPLETE;
    /* Do not accept request pipelining or payload bytes we cannot parse. */
    if (finished != byteCount) return BTB_HTTP_INVALID;
    const size_t firstEnd = BtbLineEnd(bytes, 0U, finished);
    if (firstEnd == finished ||
        firstEnd > (staticFiles ? BTB_HTTP_MAX_PATH + 16U : 255U)) return BTB_HTTP_INVALID;
    size_t firstSpace = 0U;
    while (firstSpace < firstEnd && bytes[firstSpace] != ' ') ++firstSpace;
    if (firstSpace == firstEnd) return BTB_HTTP_INVALID;
    size_t secondSpace = firstSpace + 1U;
    while (secondSpace < firstEnd && bytes[secondSpace] != ' ') ++secondSpace;
    if (secondSpace == firstSpace + 1U || secondSpace == firstEnd) return BTB_HTTP_INVALID;
    if (firstEnd - secondSpace - 1U != 8U ||
        memcmp(bytes + secondSpace + 1U, "HTTP/1.1", 8U) != 0)
        return BTB_HTTP_INVALID;
    /* No extra spaces or optional request-line grammar in this teaching subset. */
    if (firstSpace != 3U && firstSpace != 4U) return BTB_HTTP_METHOD_NOT_ALLOWED;
    BtbHttpRequest candidate = {0};
    if (firstSpace == 3U && memcmp(bytes, "GET", 3U) == 0)
        candidate.method = BTB_HTTP_GET;
    else if (firstSpace == 4U && memcmp(bytes, "HEAD", 4U) == 0)
        candidate.method = BTB_HTTP_HEAD;
    else
        return BTB_HTTP_METHOD_NOT_ALLOWED;
    if (!(staticFiles ? BtbSiteTarget(bytes + firstSpace + 1U,
                                       secondSpace - firstSpace - 1U, candidate.path)
                      : BtbTarget(bytes + firstSpace + 1U,
                                  secondSpace - firstSpace - 1U, candidate.path)))
        return BTB_HTTP_INVALID;
    size_t offset = firstEnd + 2U;
    unsigned hostSeen = 0U, headers = 0U;
    while (offset < finished) {
        const size_t end = BtbLineEnd(bytes, offset, finished);
        if (end == finished) return BTB_HTTP_INVALID;
        if (end == offset) break;
        if (++headers > 32U || end - offset > 512U) return BTB_HTTP_TOO_LARGE;
        size_t separator = offset;
        while (separator < end && bytes[separator] != ':') ++separator;
        if (separator == offset || separator == end) return BTB_HTTP_INVALID;
        for (size_t i = offset; i < separator; ++i)
            if (!(BtbAlpha(bytes[i]) || BtbDigit(bytes[i]) || bytes[i] == '-'))
                return BTB_HTTP_INVALID;
        size_t start = separator + 1U;
        while (start < end && (bytes[start] == ' ' || bytes[start] == '\t')) ++start;
        size_t valueEnd = end;
        while (valueEnd > start && bytes[valueEnd - 1U] == ' ') --valueEnd;
        if (BtbEqualCase(bytes + offset, separator - offset, "host")) {
            if (hostSeen++ != 0U || !BtbHost(bytes + start, valueEnd - start,
                                              &candidate.hostPort)) return BTB_HTTP_INVALID;
        } else if (staticFiles && BtbEqualCase(bytes + offset, separator - offset,
                                                  "if-none-match")) {
            const size_t valueBytes = valueEnd - start;
            if (candidate.ifNoneMatchPresent != 0U || valueBytes == 0U ||
                valueBytes >= sizeof candidate.ifNoneMatch)
                return BTB_HTTP_INVALID;
            memcpy(candidate.ifNoneMatch, bytes + start, valueBytes);
            candidate.ifNoneMatch[valueBytes] = '\0';
            /* The header is untrusted input. Validate the entire bounded list
             * before publishing a request or opening any filesystem object. */
            if (BtbCacheCompareIfNoneMatch(candidate.ifNoneMatch,
                                            "W/\"00000000\"") == BTB_CACHE_INVALID)
                return BTB_HTTP_INVALID;
            candidate.ifNoneMatchPresent = 1U;
        } else if (BtbEqualCase(bytes + offset, separator - offset, "content-length") ||
                   BtbEqualCase(bytes + offset, separator - offset, "transfer-encoding")) {
            /* This lab has no request-body decoder; rejecting both avoids an
             * ambiguous body boundary or conflicting length declarations. */
            return BTB_HTTP_INVALID;
        }
        offset = end + 2U;
    }
    if (hostSeen != 1U) return BTB_HTTP_INVALID;
    *out = candidate;
    return BTB_HTTP_OK;
}

BtbHttpResult BtbHttpParse(const unsigned char *bytes, size_t byteCount,
                           BtbHttpRequest *out)
{
    return BtbHttpParseInternal(bytes, byteCount, out, 0);
}
BtbHttpResult BtbHttpParseForFiles(const unsigned char *bytes, size_t byteCount,
                                   BtbHttpRequest *out)
{
    return BtbHttpParseInternal(bytes, byteCount, out, 1);
}

const char *BtbHttpResultText(BtbHttpResult result)
{
    switch (result) {
        case BTB_HTTP_OK: return "ok";
        case BTB_HTTP_INCOMPLETE: return "incomplete";
        case BTB_HTTP_INVALID: return "invalid";
        case BTB_HTTP_TOO_LARGE: return "too large";
        case BTB_HTTP_METHOD_NOT_ALLOWED: return "method not allowed";
    }
    return "unknown";
}
int BtbHttpRespond(const BtbHttpRequest *request, BtbHttpResult parseResult,
                   unsigned expectedPort, char *buffer, size_t capacity,
                   size_t *outBytes)
{
    if (buffer == NULL || outBytes == NULL || capacity == 0U ||
        expectedPort < 1024U || expectedPort > 65535U) return 0;
    static const char html[] = "<!doctype html><html lang=\"en\"><meta charset=\"utf-8\">"
        "<title>Bits2Banking C23 Web Lab</title><h1>Bits2Banking C23 web lab</h1>"
        "<p>GET /health for a native C23 response.</p></html>\n";
    static const char health[] = "{\"service\":\"bits2banking-http-lab\",\"status\":\"ready\"}\n";
    static const char error[] = "Request refused.\n";
    const char *body = error;
    const char *mime = "text/plain; charset=utf-8";
    int code = 400;
    const char *reason = "Bad Request";
    int head = request != NULL && request->method == BTB_HTTP_HEAD;
    if (parseResult == BTB_HTTP_OK && request != NULL &&
        (request->hostPort == 0U || request->hostPort == expectedPort)) {
        if (strcmp(request->path, "/") == 0) {
            code = 200; reason = "OK"; body = html; mime = "text/html; charset=utf-8";
        } else if (strcmp(request->path, "/health") == 0) {
            code = 200; reason = "OK"; body = health; mime = "application/json";
        } else {
            code = 404; reason = "Not Found"; body = "Not Found\n";
        }
    } else if (parseResult == BTB_HTTP_TOO_LARGE) {
        code = 431; reason = "Request Header Fields Too Large";
    } else if (parseResult == BTB_HTTP_METHOD_NOT_ALLOWED) {
        code = 405; reason = "Method Not Allowed";
    }
    const size_t contentLength = strlen(body);
    const int count = snprintf(buffer, capacity,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\nContent-Length: %zu\r\n"
        "Connection: close\r\nCache-Control: no-store\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "Content-Security-Policy: default-src 'none'; base-uri 'none'\r\n"
        "%s\r\n",
        code, reason, mime, contentLength,
        code == 405 ? "Allow: GET, HEAD\r\n" : "");
    if (count < 0 || (size_t)count >= capacity) return 0;
    const size_t headerCount = (size_t)count;
    const size_t sentBody = head ? 0U : contentLength;
    if (sentBody > capacity - headerCount) return 0;
    if (sentBody != 0U) (void)memcpy(buffer + headerCount, body, sentBody);
    *outBytes = headerCount + sentBody;
    return 1;
}

/* Only headers belong to this function. Streaming code owns all body bytes,
 * including partial-send recovery and the rule that HEAD has no body. */
int BtbHttpStaticHeaders(unsigned code, const char *mediaType, uint64_t bodyBytes,
                         char *buffer, size_t capacity, size_t *outBytes)
{
    const char *reason = NULL;
    switch (code) {
        case 200U: reason = "OK"; break;
        case 403U: reason = "Forbidden"; break;
        case 404U: reason = "Not Found"; break;
        case 413U: reason = "Content Too Large"; break;
        case 500U: reason = "Internal Server Error"; break;
        default: return 0;
    }
    if (buffer == NULL || outBytes == NULL || mediaType == NULL ||
        capacity == 0U || strchr(mediaType, '\r') || strchr(mediaType, '\n'))
        return 0;
    const int count = snprintf(buffer, capacity,
        "HTTP/1.1 %u %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %llu\r\n"
        "Connection: close\r\n"
        "Cache-Control: no-store\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "Content-Security-Policy: default-src 'self' data:; "
        "base-uri 'none'; frame-ancestors 'none'; "
        "style-src 'self' 'unsafe-inline'; "
        "script-src 'self' 'unsafe-inline'\r\n"
        "\r\n",
        code, reason, mediaType, (unsigned long long)bodyBytes);
    if (count < 0 || (size_t)count >= capacity) return 0;
    *outBytes = (size_t)count;
    return 1;
}
