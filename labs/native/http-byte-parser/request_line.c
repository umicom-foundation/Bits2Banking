/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/http-byte-parser/request_line.c
 * PURPOSE: Parse a bounded byte slice without strlen or partial publication.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "request_line.h"
#include <string.h>

static int IsSeparator(const uint8_t *bytes, size_t begin, size_t end,
                       size_t *separator)
{
    for (size_t index = begin; index < end; ++index) {
        if (bytes[index] == (uint8_t)' ') {
            *separator = index;
            return 1;
        }
    }
    return 0;
}

static int IsSafePath(const uint8_t *bytes, size_t begin, size_t end)
{
    if (end <= begin || end - begin > BTB_HTTP_PATH_MAX_BYTES ||
        bytes[begin] != (uint8_t)'/') return 0;
    /* This lesson deliberately accepts only a narrow ASCII path grammar,
     * leaving percent-decoding, URL normalization and routing to Framework. */
    size_t segmentBegin = begin + 1U;
    for (size_t i = begin; i < end; ++i) {
        uint8_t ch = bytes[i];
        if (ch < 0x21U || ch > 0x7eU || ch == (uint8_t)'\\' ||
            ch == (uint8_t)'?' || ch == (uint8_t)'#' || ch == (uint8_t)'%') return 0;
        if (ch == (uint8_t)'/' || i + 1U == end) {
            size_t segmentEnd = ch == (uint8_t)'/' ? i : i + 1U;
            if (segmentEnd >= segmentBegin &&
                segmentEnd - segmentBegin == 2U &&
                bytes[segmentBegin] == (uint8_t)'.' &&
                bytes[segmentBegin + 1U] == (uint8_t)'.') return 0;
            segmentBegin = i + 1U;
        }
    }
    return 1;
}

BtbHttpResult BtbParseRequestLine(const uint8_t *bytes, size_t byteCount,
                                  BtbHttpRequestLine *out)
{
    if (bytes == NULL || out == NULL || byteCount < 16U) return BTB_HTTP_INVALID;
    if (byteCount > BTB_HTTP_LINE_MAX_BYTES) return BTB_HTTP_TOO_LONG;
    /* A single input line must end in CRLF, not an extra header or two lines. */
    if (bytes[byteCount - 2U] != 13U || bytes[byteCount - 1U] != 10U)
        return BTB_HTTP_INVALID;
    size_t lineEnd = byteCount - 2U;
    for (size_t i = 0U; i < lineEnd; ++i) {
        if (bytes[i] == 0U || bytes[i] == 13U || bytes[i] == 10U)
            return BTB_HTTP_INVALID;
    }
    size_t first = 0U, second = 0U;
    if (!IsSeparator(bytes, 0U, lineEnd, &first) ||
        !IsSeparator(bytes, first + 1U, lineEnd, &second)) return BTB_HTTP_INVALID;
    size_t methodLength = first, pathBegin = first + 1U;
    if (second <= pathBegin || !IsSafePath(bytes, pathBegin, second))
        return BTB_HTTP_INVALID;
    if (!((methodLength == 3U && memcmp(bytes, "GET", 3U) == 0) ||
          (methodLength == 4U && memcmp(bytes, "HEAD", 4U) == 0)))
        return BTB_HTTP_UNSUPPORTED;
    const size_t versionBegin = second + 1U;
    if (lineEnd - versionBegin != 8U ||
        memcmp(bytes + versionBegin, "HTTP/1.", 7U) != 0 ||
        (bytes[versionBegin + 7U] != (uint8_t)'0' &&
         bytes[versionBegin + 7U] != (uint8_t)'1')) return BTB_HTTP_UNSUPPORTED;

    /* Stage the complete result, then commit once. */
    BtbHttpRequestLine staged = {0};
    memcpy(staged.method, bytes, methodLength);
    staged.method[methodLength] = '\0';
    size_t pathLength = second - pathBegin;
    memcpy(staged.path, bytes + pathBegin, pathLength);
    staged.path[pathLength] = '\0';
    staged.major = 1U;
    staged.minor = (unsigned)(bytes[versionBegin + 7U] - (uint8_t)'0');
    *out = staged;
    return BTB_HTTP_OK;
}
