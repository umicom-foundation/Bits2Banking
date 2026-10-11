/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/http-byte-parser/fuzz_request_line.c
 * PURPOSE: Run the same parser against many bounded malformed byte sequences.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "request_line.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* This entry point can be used by a later LLVM libFuzzer build. The normal
 * educational build uses a deterministic test driver and needs only GCC/Clang. */
int LLVMFuzzerTestOneInput(const uint8_t *bytes, size_t count)
{
    BtbHttpRequestLine parsed;
    memset(&parsed, 0xa5, sizeof parsed);
    BtbHttpRequestLine previous = parsed;
    BtbHttpResult result = BtbParseRequestLine(bytes, count, &parsed);
    if (result == BTB_HTTP_OK) {
        if (parsed.path[0] != '/' || parsed.major != 1U ||
            (parsed.minor != 0U && parsed.minor != 1U) ||
            (strcmp(parsed.method, "GET") != 0 && strcmp(parsed.method, "HEAD") != 0) ||
            memchr(parsed.method, '\0', sizeof parsed.method) == NULL ||
            memchr(parsed.path, '\0', sizeof parsed.path) == NULL) abort();
    } else if (memcmp(&parsed, &previous, sizeof parsed) != 0) abort();
    return 0;
}

#ifdef BTB_SEEDED_FUZZ_DRIVER
static uint32_t NextRandom(uint32_t *state)
{
    /* Wraparound is intentional and defined for unsigned integers. */
    *state ^= *state << 13U;
    *state ^= *state >> 17U;
    *state ^= *state << 5U;
    return *state;
}
int main(void)
{
    static const unsigned char base[] = "GET /docs/ HTTP/1.1\r\n";
    uint32_t seed = UINT32_C(0x7f31a56b);
    uint8_t input[BTB_HTTP_LINE_MAX_BYTES + 1U];
    (void)LLVMFuzzerTestOneInput(base, sizeof base - 1U);
    for (size_t trial = 0U; trial < 5000U; ++trial) {
        size_t length = (size_t)(NextRandom(&seed) % (unsigned)sizeof input);
        for (size_t i = 0U; i < length; ++i)
            input[i] = (uint8_t)(NextRandom(&seed) & 0xffU);
        (void)LLVMFuzzerTestOneInput(input, length);
        /* Some inputs begin as a valid request with one mutated byte. */
        memcpy(input, base, sizeof base - 1U);
        size_t p = (size_t)(NextRandom(&seed) % (unsigned)(sizeof base - 1U));
        input[p] ^= (uint8_t)(NextRandom(&seed) & 0xffU);
        (void)LLVMFuzzerTestOneInput(input, sizeof base - 1U);
    }
    puts("5000 arbitrary byte spans and 5000 mutated request lines checked.");
    return 0;
}
#endif
