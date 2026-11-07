/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/text-editor/main.c
 *
 * PURPOSE:
 *   Provide line commands for a small editor without choosing hidden paths.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "editor.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int ReadIndex(const char **cursor, size_t *value)
{
    const char *p = *cursor;
    size_t result = 0;
    if (*p < '0' || *p > '9') return 0;
    while (*p >= '0' && *p <= '9') {
        const size_t digit = (size_t)(*p - '0');
        if (result > (SIZE_MAX - digit) / 10U) return 0;
        result = result * 10U + digit;
        ++p;
    }
    *cursor = p;
    *value = result;
    return 1;
}

/* Read a complete command before executing it. Counting bytes directly makes
   embedded NUL and overlong input explicit failures instead of accepting a
   truncated command prefix. Drain a rejected line so its tail cannot execute. */
static int ReadCommand(char *command, size_t capacity)
{
    size_t length = 0;
    int invalid = 0;
    int byte;
    while ((byte = getchar()) != EOF && byte != '\n') {
        if (byte == 0 || length >= capacity - 1U) invalid = 1;
        else command[length++] = (char)byte;
    }
    if (ferror(stdin)) return -1;
    if (byte == EOF && length == 0 && !invalid) return 0;
    if (length > 0 && command[length - 1U] == '\r') --length;
    command[length] = '\0';
    return invalid ? -1 : 1;
}

int main(void)
{
    BtbEditor editor = {0};
    char command[2048];
    int rejected = 0;
    puts("Commands: append TEXT | insert POSITION TEXT | erase POSITION COUNT");
    /* Retain the earlier help line to document the original command set.
       The active line includes the checked existing-file loading path. */
#if 0
    puts("show | undo | save PATH | quit | discard");
#endif
    puts("show | undo | open PATH | save PATH | quit | discard");
    for (;;) {
        const int input = ReadCommand(command, sizeof command);
        if (input == 0) break;
        if (input < 0) {
            puts("ERROR: command input is invalid or too long");
            rejected = 1;
            if (ferror(stdin)) break;
            continue;
        }
        const size_t length = strlen(command);
        if (strcmp(command, "show") == 0) {
            printf("TEXT: %s\n", editor.text);
            continue;
        }
        if (strcmp(command, "discard") == 0) break;
        if (strcmp(command, "quit") == 0) {
            if (editor.dirty) { puts("Unsaved changes: save PATH or discard."); continue; }
            break;
        }
        BtbEditResult result = BTB_EDIT_INVALID;
        if (strncmp(command, "append ", 7) == 0)
            result = BtbEditorInsert(&editor, editor.length, command + 7, length - 7U);
        else if (strncmp(command, "insert ", 7) == 0) {
            const char *cursor = command + 7;
            size_t position;
            if (ReadIndex(&cursor, &position) && *cursor == ' ')
                result = BtbEditorInsert(&editor, position, cursor + 1, strlen(cursor + 1));
        } else if (strncmp(command, "erase ", 6) == 0) {
            const char *cursor = command + 6;
            size_t position, count;
            if (ReadIndex(&cursor, &position) && *cursor == ' ') {
                ++cursor;
                if (ReadIndex(&cursor, &count) && *cursor == '\0')
                    result = BtbEditorErase(&editor, position, count);
            }
        } else if (strcmp(command, "undo") == 0) result = BtbEditorUndo(&editor);
        else if (strncmp(command, "save ", 5) == 0)
            result = BtbEditorSaveNew(&editor, command + 5);
        else if (strncmp(command, "open ", 5) == 0)
            result = BtbEditorLoadFile(&editor, command + 5);
        if (result == BTB_EDIT_OK) puts("OK");
        else {
            printf("ERROR %d: command refused; text unchanged.\n", (int)result);
            if (result == BTB_EDIT_IO)
                puts("Check the path, existing files and permissions; a failed write may leave a partial new file.");
            if (result == BTB_EDIT_DIRTY)
                puts("Save the current document to a new path before opening another file.");
            rejected = 1;
        }
    }
    if (editor.dirty) fputs("Session ended with unsaved changes.\n", stderr);
    return rejected || ferror(stdin) || ferror(stdout) || fflush(stdout) == EOF ? 1 : 0;
}
