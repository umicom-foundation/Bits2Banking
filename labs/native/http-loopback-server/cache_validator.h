/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/cache_validator.h
 * PURPOSE: Teach bounded HTTP cache validation using weak file metadata tags.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_CACHE_VALIDATOR_H
#define BTB_CACHE_VALIDATOR_H
#include <stddef.h>
#include <stdint.h>

#define BTB_CACHE_TAG_CAPACITY 64U
#define BTB_CACHE_CONDITION_CAPACITY 256U

typedef enum BtbCacheResult {
    BTB_CACHE_INVALID = 0,
    BTB_CACHE_MISS = 1,
    BTB_CACHE_MATCH = 2
} BtbCacheResult;

/* A weak validator reports observed size and modification stamp. It is not a
 * byte-exact digest, signature or guarantee of identity after rapid edits. */
int BtbCacheTagFromMetadata(uint64_t bytes, uint64_t changedStamp,
                            char out[BTB_CACHE_TAG_CAPACITY]);

/* Parse '*' or comma-separated entity tags with optional W/ prefix. This
 * teaching subset accepts visible ASCII opaque-tags only and strict OWS;
 * invalid input is not silently treated as an ordinary cache miss. */
BtbCacheResult BtbCacheCompareIfNoneMatch(const char *condition,
                                           const char *currentTag);

/* Encode headers for an existing static file (200 or 304), with private
 * revalidation and no shared caches. 304 never declares or sends a body. */
int BtbCacheStaticHeaders(unsigned status, const char *mediaType, uint64_t bytes,
                          const char *tag, char *out, size_t capacity,
                          size_t *outLength);
#endif
