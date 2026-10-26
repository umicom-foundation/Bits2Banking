/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/kernel-bounded-input/test_input.c
 *
 * PURPOSE:
 *   Verify exact field length, failure atomicity and rejection after line damage.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/kernel/console_shell.h"
#include <stdio.h>
#include <string.h>
#define CHECK(e) do { if (!(e)) { fprintf(stderr, "check %d: %s\n", __LINE__, #e); return 1; } } while (0)
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    UmicomU64 value = 41U;
    if (!strcmp(argv[1], "span")) {
        const char packet[4] = {'1', '2', '3', 'x'};
        CHECK(UmicomKernelShellUnsignedSpan(packet, 3U, &value) && value == 123U);
        CHECK(!UmicomKernelShellUnsignedSpan(packet, sizeof packet, &value) && value == 123U);
    } else if (!strcmp(argv[1], "rejected")) {
        const char nul[3] = {'1', 0, '2'};
        CHECK(!UmicomKernelShellUnsignedSpan(nul, sizeof nul, &value));
        CHECK(!UmicomKernelShellUnsignedSpan("-1", 2U, &value));
        CHECK(!UmicomKernelShellUnsignedSpan("18446744073709551616", 20U, &value));
    } else if (!strcmp(argv[1], "unchanged")) {
        CHECK(!UmicomKernelShellUnsignedSpan("2?", 2U, &value));
        CHECK(value == 41U);
        CHECK(!UmicomKernelShellUnsignedSpan(NULL, 1U, &value) && value == 41U);
    } else if (!strcmp(argv[1], "line-loss")) {
        UmicomKernelConsoleLine line = {0};
        CHECK(UmicomKernelConsoleLineFeed(&line, 'r') == UMICOM_CONSOLE_LINE_NONE);
        CHECK(UmicomKernelConsoleLineFeed(&line, 0U) == UMICOM_CONSOLE_LINE_NONE);
        CHECK(UmicomKernelConsoleLineFeed(&line, '\n') == UMICOM_CONSOLE_LINE_REJECTED);
        CHECK(line.length == 0U);
        CHECK(UmicomKernelConsoleLineFeed(&line, 'h') == UMICOM_CONSOLE_LINE_NONE);
        CHECK(UmicomKernelConsoleLineFeed(&line, '\n') == UMICOM_CONSOLE_LINE_READY);
        CHECK(!strcmp(line.bytes, "h"));
    } else return 2;
    return 0;
}
