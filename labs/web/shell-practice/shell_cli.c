/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/web/shell-practice/shell_cli.c
 *
 * PURPOSE:
 *   Run the same fixed practice commands from a desktop terminal.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "shell.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2 || (strcmp(argv[1], "bash") && strcmp(argv[1], "powershell"))) {
        (void)fputs("Usage: shell-practice bash|powershell\n", stderr);
        return 2;
    }

    const unsigned mode = !strcmp(argv[1], "powershell") ? 1U : 0U;
    unsigned char *input = BtbShellInput();
    const size_t capacity = BtbShellCapacity();
    /* Consume a complete line even when it exceeds the model's buffer.
     * Passing capacity plus one reports refusal without writing beyond it. */
    for (;;) {
        size_t used = 0;
        int byte;
        while ((byte = getchar()) != EOF && byte != '\n') {
            if (used < capacity) input[used] = (unsigned char)byte;
            if (used <= capacity) ++used;
        }
        if (byte == EOF && !used) break;
        if (used && used <= capacity && input[used - 1U] == '\r') --used;
        (void)BtbShellSubmit(mode, used);
        if (fputs(BtbShellOutput(), stdout) == EOF || fflush(stdout) == EOF) return 1;
    }
    return ferror(stdin) ? 1 : 0;
}
