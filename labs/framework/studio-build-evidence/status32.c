/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/studio-build-evidence/status32.c
 *
 * PURPOSE:
 *   Compare signed, unsigned and hexadecimal views of one 32-bit status.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool ReadStatusWord(const char *text, uint32_t *word)
{
    char *end;
    errno = 0;
    /* Admit the explicitly signed decimal range separately. Unsigned
     * conversion is defined modulo 2^32 after the signed value is checked. */
    if (text[0] == '-') {
        if (text[1] < '0' || text[1] > '9') return false;
        const intmax_t value = strtoimax(text, &end, 10);
        if (errno || *end != '\0' || value < INT32_MIN) return false;
        *word = (uint32_t)value;
        return true;
    }

    /* Positive decimal and prefixed hexadecimal use the entire word range.
     * Whitespace and implicit octal are outside this small evidence format. */
    if (text[0] < '0' || text[0] > '9') return false;
    const bool hex = text[0] == '0' && (text[1] == 'x' || text[1] == 'X');
    const uintmax_t value = strtoumax(text, &end, hex ? 16 : 10);
    if (errno || *end != '\0' || value > UINT32_MAX) return false;
    *word = (uint32_t)value;
    return true;
}

int main(int argc, char **argv)
{
    uint32_t word;
    if (argc != 2 || !ReadStatusWord(argv[1], &word)) {
        fputs("invalid 32-bit status\n", stderr);
        return 3;
    }
    /* Compute the two's-complement view in a wider signed type, avoiding
     * implementation-defined conversion of a large uint32_t to int32_t. */
    const int64_t signed_view = word > INT32_MAX ?
        (int64_t)word - INT64_C(4294967296) : (int64_t)word;
    if (printf("hex=0x%08" PRIx32 " unsigned=%" PRIu32 " signed=%" PRId64 "\n",
        word, word, signed_view) < 0 || fflush(stdout) == EOF) return 1;
    return 0;
}
