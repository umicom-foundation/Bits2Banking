/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/usage_summary.c
 *
 * PURPOSE:
 *   Apply the same bounded usage-data contract in the language.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: provide one input file\n", stderr);
        return 2;
    }
    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        fputs("Could not read usage data\n", stderr);
        return EXIT_FAILURE;
    }

    /* Read one byte past the format limit and close before parsing. */
    unsigned char bytes[65];
    size_t length = fread(bytes, 1, sizeof bytes, input);
    int failed = ferror(input);
    if (fclose(input) == EOF || failed) {
        fputs("Could not read usage data\n", stderr);
        return EXIT_FAILURE;
    }
    if (!length || length > 64) {
        fputs("Invalid usage data\n", stderr);
        return EXIT_FAILURE;
    }

    /* Each LF commits one integer. A final partial line is invalid. */
    int total = 0, value = 0, digits = 0;
    for (size_t index = 0; index < length; ++index) {
        unsigned char current = bytes[index];
        if (current >= '0' && current <= '9' && digits < 2) {
            value = value * 10 + current - '0';
            ++digits;
        } else if (current == '\n' && digits != 0) {
            total += value;
            value = 0;
            digits = 0;
        } else {
            fputs("Invalid usage data\n", stderr);
            return EXIT_FAILURE;
        }
    }
    if (digits != 0) {
        fputs("Invalid usage data\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Total: %d\n", total);
    return EXIT_SUCCESS;
}
