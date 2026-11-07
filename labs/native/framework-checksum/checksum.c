/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-checksum/checksum.c
 *
 * PURPOSE:
 *   Read bounded chunks while delegating digest computation to Umicom Framework.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "checksum.h"
#include <string.h>

UmiStatus BtbChecksumStream(FILE *stream, char output[UMI_SHA256_HEX_CAPACITY])
{
    if (stream == NULL || output == NULL) return UMI_STATUS_INVALID_ARGUMENT;
    if (ferror(stream)) return UMI_STATUS_IO_ERROR;
    UmiSha256 context;
    UmiSha256Init(&context);
    unsigned char buffer[4096];
    for (;;) {
        const size_t count = fread(buffer, 1, sizeof buffer, stream);
        /* A stream can return some bytes and also report an error. Refuse
         * a partial-file digest before exposing a success result. */
        if (ferror(stream)) return UMI_STATUS_IO_ERROR;
        if (count != 0) {
            const UmiStatus status = UmiSha256Update(&context, buffer, count);
            if (status != UMI_STATUS_OK) return status;
        }
        if (feof(stream)) break;
        if (count == 0) return UMI_STATUS_IO_ERROR;
    }
    unsigned char digest[UMI_SHA256_BYTES];
    const UmiStatus status = UmiSha256Final(&context, digest);
    if (status != UMI_STATUS_OK) return status;
    char result[UMI_SHA256_HEX_CAPACITY];
    UmiSha256Hex(digest, result);
    /* Publish a complete result once. SHA-256 implementation and constants
     * remain owned by Framework; this example teaches stream ownership. */
    memcpy(output, result, sizeof result);
    return UMI_STATUS_OK;
}

