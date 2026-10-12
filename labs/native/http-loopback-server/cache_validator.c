/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/cache_validator.c
 * PURPOSE: Bounded weak validators, If-None-Match lists and correct 304 replies.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "cache_validator.h"
#include <stdio.h>
#include <string.h>

/* C23 has no strnlen; explicitly bound every scan. */
static size_t BtbCacheLength(const char *value, size_t limit)
{
    size_t used = 0U;
    while (used < limit && value[used] != '\0') ++used;
    return used;
}
int BtbCacheTagFromMetadata(uint64_t bytes, uint64_t changedStamp,
                            char out[BTB_CACHE_TAG_CAPACITY])
{
    if (out == NULL) return 0;
    char candidate[BTB_CACHE_TAG_CAPACITY];
    int count = snprintf(candidate, sizeof candidate, "W/\"%016llx-%016llx\"",
                         (unsigned long long)bytes, (unsigned long long)changedStamp);
    if (count <= 0 || (size_t)count >= sizeof candidate) return 0;
    memcpy(out, candidate, (size_t)count + 1U);
    return 1;
}
static int BtbCacheOpaque(unsigned char value)
{
    /* RFC entity-tag opaque characters, constrained to portable visible ASCII. */
    return value == 0x21U || (value >= 0x23U && value <= 0x7eU);
}
static void BtbCacheSkipSpace(const char **cursor)
{
    while (**cursor == ' ' || **cursor == '\t') ++*cursor;
}
/* Read one tagged value and lend its opaque, delimited byte span. */
static int BtbCacheParseTag(const char **cursor, const char **start,
                            size_t *length)
{
    const char *current = *cursor;
    if (current[0] == 'W' && current[1] == '/') current += 2;
    if (*current != '"') return 0;
    ++current;
    const char *contents = current;
    while (*current != '\0' && BtbCacheOpaque((unsigned char)*current)) ++current;
    if (*current != '"') return 0;
    *start = contents;
    *length = (size_t)(current - contents);
    *cursor = current + 1;
    return 1;
}
BtbCacheResult BtbCacheCompareIfNoneMatch(const char *condition,
                                           const char *currentTag)
{
    if (condition == NULL || currentTag == NULL) return BTB_CACHE_INVALID;
    const size_t inputLength = BtbCacheLength(condition, BTB_CACHE_CONDITION_CAPACITY);
    if (inputLength == 0U || inputLength >= BTB_CACHE_CONDITION_CAPACITY)
        return BTB_CACHE_INVALID;
    const size_t tagLength = BtbCacheLength(currentTag, BTB_CACHE_TAG_CAPACITY);
    if (tagLength == 0U || tagLength >= BTB_CACHE_TAG_CAPACITY) return BTB_CACHE_INVALID;
    const char *expected = currentTag;
    const char *expectedBytes = NULL;
    size_t expectedLength = 0U;
    if (!BtbCacheParseTag(&expected, &expectedBytes, &expectedLength) || *expected != '\0')
        return BTB_CACHE_INVALID;
    const char *cursor = condition;
    BtbCacheSkipSpace(&cursor);
    if (*cursor == '*') {
        ++cursor;
        BtbCacheSkipSpace(&cursor);
        return *cursor == '\0' ? BTB_CACHE_MATCH : BTB_CACHE_INVALID;
    }
    unsigned found = 0U;
    unsigned count = 0U;
    for (;;) {
        const char *member = NULL;
        size_t length = 0U;
        if (++count > 24U || !BtbCacheParseTag(&cursor, &member, &length))
            return BTB_CACHE_INVALID;
        if (length == expectedLength && memcmp(member, expectedBytes, length) == 0)
            found = 1U;
        BtbCacheSkipSpace(&cursor);
        if (*cursor == '\0') break;
        if (*cursor != ',') return BTB_CACHE_INVALID;
        ++cursor;
        BtbCacheSkipSpace(&cursor);
        if (*cursor == '\0') return BTB_CACHE_INVALID;
    }
    return found ? BTB_CACHE_MATCH : BTB_CACHE_MISS;
}
int BtbCacheStaticHeaders(unsigned status, const char *mediaType, uint64_t bytes,
                          const char *tag, char *out, size_t capacity,
                          size_t *outLength)
{
    if ((status != 200U && status != 304U) || mediaType == NULL || out == NULL ||
        outLength == NULL || capacity == 0U || tag == NULL ||
        strchr(mediaType, '\r') != NULL || strchr(mediaType, '\n') != NULL ||
        BtbCacheCompareIfNoneMatch(tag, tag) != BTB_CACHE_MATCH) return 0;
    const char *reason = status == 200U ? "OK" : "Not Modified";
    const int used = status == 200U ?
        snprintf(out, capacity,
            "HTTP/1.1 %u %s\r\nContent-Type: %s\r\n"
            "Content-Length: %llu\r\n"
            "ETag: %s\r\nCache-Control: private, no-cache\r\n"
            "Connection: close\r\nX-Content-Type-Options: nosniff\r\n"
            "Content-Security-Policy: default-src 'self' data:; "
            "base-uri 'none'; frame-ancestors 'none'; "
            "style-src 'self' 'unsafe-inline'; script-src 'self' 'unsafe-inline'\r\n\r\n",
            status, reason, mediaType, (unsigned long long)bytes, tag) :
        snprintf(out, capacity,
            "HTTP/1.1 304 %s\r\nETag: %s\r\n"
            "Cache-Control: private, no-cache\r\n"
            "Connection: close\r\nX-Content-Type-Options: nosniff\r\n\r\n",
            reason, tag);
    if (used < 0 || (size_t)used >= capacity) return 0;
    *outLength = (size_t)used;
    return 1;
}
