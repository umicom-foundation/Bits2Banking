/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/umicom-c-project/compare-int-input.c
 *
 * PURPOSE:
 *   Call the same signed-input lesson function as a defined native C calculation.
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
#include <limits.h>
#include <stdio.h>

int umicom_run(int input);

int main(int argc, char **argv)
{
    static_assert(INT_MIN == INT32_MIN && INT_MAX == INT32_MAX,
                  "This comparison requires a signed 32-bit native int");
    if (argc != 2) {
        fputs("Usage: compare-int-input SIGNED_DECIMAL\n", stderr);
        return 2;
    }
    const char *text = argv[1];
    const char *digits = (*text == '-' || *text == '+') ? text + 1 : text;
    if (*digits < '0' || *digits > '9') {
        fputs("Enter one signed decimal integer.\n", stderr);
        return 2;
    }
    errno = 0;
    char *end = NULL;
    const intmax_t parsed = strtoimax(text, &end, 10);
    if (errno == ERANGE || *end != '\0' || parsed < INT32_MIN || parsed > INT32_MAX) {
        fputs("Enter one signed 32-bit decimal integer.\n", stderr);
        return 2;
    }

    /* For negative inputs, input * 2 must remain at least INT_MIN. Positive
     * inputs also add two. Prove the bounds before native C evaluates either. */
    if (parsed < INT32_MIN / 2 || parsed > (INT32_MAX - 2) / 2) {
        fputs("The lesson calculation is outside the signed 32-bit result range.\n", stderr);
        return 1;
    }
    return printf("Result: %d\n", umicom_run((int)parsed)) < 0 || fflush(stdout) != 0;
}
