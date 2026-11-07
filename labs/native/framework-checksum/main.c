/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-checksum/main.c
 *
 * PURPOSE:
 *   Print a digest only after reading and closing the user's selected file successfully.
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

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: btb-checksum <file>\n", stderr);
        return EXIT_FAILURE;
    }
    FILE *stream = fopen(argv[1], "rb");
    if (stream == NULL) {
        perror("Cannot open input file");
        return EXIT_FAILURE;
    }
    char digest[UMI_SHA256_HEX_CAPACITY];
    UmiStatus status = BtbChecksumStream(stream, digest);
    if (fclose(stream) != 0 && status == UMI_STATUS_OK) status = UMI_STATUS_IO_ERROR;
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Cannot complete checksum: %s\n", umi_status_text(status));
        return EXIT_FAILURE;
    }
    if (puts(digest) == EOF || fflush(stdout) == EOF) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

