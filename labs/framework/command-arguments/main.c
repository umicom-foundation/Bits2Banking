/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/command-arguments/main.c
 *
 * PURPOSE:
 *   Inspect Framework command arguments and preserve a valid plan after a rejected edit.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/developer/command_line.h"
#include <stdio.h>
#include <string.h>

/* This lab inspects a plan. It deliberately does not launch the named program. */
int main(void)
{
    static const char text[] = "compiler -c \"source file.c\" \"\"";
    static const char unfinished[] = "compiler \"unfinished";
    UmiDeveloperCommandLine command = {0};
    unsigned char previous[sizeof(command)];
    UmiStatus status;
    size_t index;

    status = umi_developer_command_line_parse_n(text, sizeof(text) - 1U, &command);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Command rejected: %d\n", (int)status);
        return 1;
    }
    if (command.argument_count != 3U ||
        strcmp(command.arguments[1], "source file.c") != 0 ||
        command.arguments[2][0] != '\0') {
        fputs("The parsed argument boundaries do not match the exercise.\n", stderr);
        return 1;
    }
    printf("Program: %s\n", command.program);
    for (index = 0U; index < command.argument_count; ++index)
        printf("Argument %zu: [%s]\n", index + 1U, command.arguments[index]);

    memcpy(previous, &command, sizeof(command));
    status = umi_developer_command_line_parse_n(
        unfinished, sizeof(unfinished) - 1U, &command);
    if (status != UMI_STATUS_PARSE_ERROR ||
        memcmp(previous, &command, sizeof(command)) != 0) {
        fputs("The rejected edit changed the saved plan.\n", stderr);
        return 1;
    }
    puts("Rejected edit left the previous plan unchanged.");
    return 0;
}
