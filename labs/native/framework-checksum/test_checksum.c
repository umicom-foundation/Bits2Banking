/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-checksum/test_checksum.c
 *
 * PURPOSE:
 *   Check known digest vectors, chunk boundaries and failure output preservation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "checksum.h"
#include <stdlib.h>
#include <string.h>

static int CheckBytes(const unsigned char *bytes, size_t length, const char *expected)
{
    FILE *stream = tmpfile();
    if (stream == NULL) return 1;
    if ((length != 0 && fwrite(bytes, 1, length, stream) != length) ||
        fflush(stream) != 0 || fseek(stream, 0, SEEK_SET) != 0) {
        (void)fclose(stream);
        return 1;
    }
    char actual[UMI_SHA256_HEX_CAPACITY] = "unchanged";
    const UmiStatus status = BtbChecksumStream(stream, actual);
    const int close_result = fclose(stream);
    return status != UMI_STATUS_OK || close_result != 0 || strcmp(actual, expected) != 0;
}

int main(void)
{
    /* These two fixed vectors are independent of the implementation under test. */
    if (CheckBytes(NULL, 0,
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") != 0 ||
        CheckBytes((const unsigned char *)"abc", 3,
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad") != 0)
        return EXIT_FAILURE;
    unsigned char data[8193];
    for (size_t i = 0; i < sizeof data; ++i) data[i] = (unsigned char)(i % 251U);
    const size_t lengths[] = {1, 4095, 4096, 4097, 8192, 8193};
    for (size_t i = 0; i < sizeof lengths / sizeof lengths[0]; ++i) {
        char expected[UMI_SHA256_HEX_CAPACITY];
        /* Comparing incremental and one-buffer calls checks adapter chunking;
         * it is not independent evidence for the cryptographic algorithm. */
        if (UmiSha256Buffer(data, lengths[i], expected) != UMI_STATUS_OK ||
            CheckBytes(data, lengths[i], expected) != 0) return EXIT_FAILURE;
    }
    char preserved[UMI_SHA256_HEX_CAPACITY] = "unchanged";
    if (BtbChecksumStream(NULL, preserved) != UMI_STATUS_INVALID_ARGUMENT ||
        strcmp(preserved, "unchanged") != 0) return EXIT_FAILURE;
    FILE *stream = tmpfile();
    if (stream == NULL) return EXIT_FAILURE;
    const UmiStatus invalid = BtbChecksumStream(stream, NULL);
    const int closed = fclose(stream);
    if (invalid != UMI_STATUS_INVALID_ARGUMENT || closed != 0) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

