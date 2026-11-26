/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/web/shell-practice/shell.c
 *
 * PURPOSE:
 *   Teach folder commands and command status in a fixed browser workspace.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "shell.h"

#include <stdbool.h>
#include <stddef.h>

enum { QueryCapacity = 192 };
enum ShellMode { Bash, PowerShell, ShellCount };
enum Folder { Practice, Reports, Samples, FolderCount };
enum Status { Succeeded, PathMissing, InvalidSyntax, Unsupported = 127 };
enum Action { ShowLocation, ListFolder, ChangeFolder, ReadFile, ShowStatus };

typedef struct {
    const unsigned char *start;
    size_t length;
} Word;

/* Every path names lesson data. The module has no filesystem or process
 * imports, so a supported command can only select an entry from this table. */
static const char *const locations[FolderCount][ShellCount] = {
    {"/practice\n", "C:\\practice\n"},
    {"/practice/reports\n", "C:\\practice\\reports\n"},
    {"/practice/samples\n", "C:\\practice\\samples\n"},
};
static const char *const listing[FolderCount] = {
    "reports\nsamples\n", "closing notes.txt\n", "limits.txt\n",
};
static const char *const contents[FolderCount] = {
    "", "Approved\nPending\nApproved\n", "Daily review limit: 4\n",
};
static const char *const fileNames[FolderCount] = {
    "", "closing notes.txt", "limits.txt",
};

static const struct {
    const char *names[ShellCount];
    enum Action action;
} commands[] = {
    {{"pwd", "Get-Location"}, ShowLocation},
    {{"ls", "Get-ChildItem"}, ListFolder},
    {{"cd", "Set-Location"}, ChangeFolder},
    {{"cat", "Get-Content"}, ReadFile},
    {{"echo", "$?"}, ShowStatus},
};

static unsigned char query[QueryCapacity];
static const char *output = "";
static enum Folder directory[ShellCount];
static enum Status previous[ShellCount];

unsigned char *BtbShellInput(void) { return query; }
size_t BtbShellCapacity(void) { return sizeof query; }
const char *BtbShellOutput(void) { return output; }

size_t BtbShellOutputLength(void)
{
    size_t length = 0;
    while (output[length]) ++length;
    return length;
}

static bool Space(unsigned char byte)
{
    return byte == ' ' || byte == '\t';
}

static unsigned char Lower(unsigned char byte)
{
    return byte >= 'A' && byte <= 'Z' ? (unsigned char)(byte + ('a' - 'A')) : byte;
}

static bool Match(Word word, const char *literal, enum ShellMode mode)
{
    size_t index = 0;
    while (index < word.length && literal[index]) {
        unsigned char left = word.start[index];
        unsigned char right = (unsigned char)literal[index];
        if (mode == PowerShell) {
            left = Lower(left);
            right = Lower(right);
        }
        if (left != right) return false;
        ++index;
    }
    return index == word.length && literal[index] == '\0';
}

/* Admit one command and at most one argument. Quoting groups a filename
 * that contains spaces. It never performs substitutions or escaping. */
static bool ReadWords(size_t length, Word *command, Word *argument)
{
    const unsigned char *at = query;
    const unsigned char *end = query + length;
    while (at < end && Space(*at)) ++at;
    command->start = at;
    while (at < end && !Space(*at)) ++at;
    command->length = (size_t)(at - command->start);
    while (at < end && Space(*at)) ++at;
    if (at == end) return command->length != 0;

    const unsigned char quote = (*at == '\'' || *at == '"') ? *at++ : 0;
    argument->start = at;
    while (at < end && (quote ? *at != quote : !Space(*at))) ++at;
    argument->length = (size_t)(at - argument->start);
    if (!argument->length || (quote && at == end)) return false;
    if (quote) ++at;
    while (at < end && Space(*at)) ++at;
    return at == end;
}

static enum Status Result(enum ShellMode mode, enum Status status, const char *text)
{
    /* Keep each session's previous status separate from the displayed result. */
    previous[mode] = status;
    output = text;
    return status;
}

static enum Status Move(enum ShellMode mode, Word argument)
{
    if (Match(argument, "..", mode)) directory[mode] = Practice;
    else if (Match(argument, ".", mode)) return Result(mode, Succeeded, "");
    else if (directory[mode] == Practice && Match(argument, "reports", mode)) directory[mode] = Reports;
    else if (directory[mode] == Practice && Match(argument, "samples", mode)) directory[mode] = Samples;
    else return Result(mode, PathMissing, "Folder is not in this practice workspace.\n");
    return Result(mode, Succeeded, "");
}

static const char *PreviousStatus(enum ShellMode mode)
{
    if (mode == PowerShell) return previous[mode] == Succeeded ? "True\n" : "False\n";
    switch (previous[mode]) {
        case Succeeded: return "0\n";
        case PathMissing: return "1\n";
        case InvalidSyntax: return "2\n";
        case Unsupported: return "127\n";
    }
    return "";
}

static enum Status Execute(enum ShellMode mode, enum Action action, Word argument)
{
    const enum Folder folder = directory[mode];
    const bool hasArgument = argument.length != 0;
    switch (action) {
        case ShowLocation:
            if (!hasArgument) return Result(mode, Succeeded, locations[folder][mode]);
            break;
        case ListFolder:
            if (!hasArgument) return Result(mode, Succeeded, listing[folder]);
            break;
        case ChangeFolder:
            if (hasArgument) return Move(mode, argument);
            break;
        case ReadFile:
            if (hasArgument && folder != Practice && Match(argument, fileNames[folder], mode))
                return Result(mode, Succeeded, contents[folder]);
            if (hasArgument) return Result(mode, PathMissing, "File is not in this practice folder.\n");
            break;
        case ShowStatus:
            if ((mode == Bash && Match(argument, "$?", mode)) || (mode == PowerShell && !hasArgument))
                return Result(mode, Succeeded, PreviousStatus(mode));
            break;
    }
    return Result(mode, InvalidSyntax, "Use the command form shown in the lesson.\n");
}

unsigned BtbShellSubmit(unsigned requestedMode, size_t length)
{
    if (requestedMode >= ShellCount) {
        output = "Choose Bash or PowerShell.\n";
        return InvalidSyntax;
    }
    const enum ShellMode mode = (enum ShellMode)requestedMode;
    Word command = {0};
    Word argument = {0};
    if (length > sizeof query)
        return (unsigned)Result(mode, InvalidSyntax, "This command is too long for the practice workspace.\n");
    if (length == 0 || !ReadWords(length, &command, &argument))
        return (unsigned)Result(mode, InvalidSyntax, "Enter one command. Quote a filename with spaces.\n");

    for (size_t index = 0; index < sizeof commands / sizeof commands[0]; ++index) {
        if (Match(command, commands[index].names[mode], mode))
            return (unsigned)Execute(mode, commands[index].action, argument);
    }
    return (unsigned)Result(mode, Unsupported, "Command is outside this practice lesson.\n");
}

void BtbShellReset(unsigned requestedMode)
{
    if (requestedMode >= ShellCount) return;
    directory[requestedMode] = Practice;
    (void)Result((enum ShellMode)requestedMode, Succeeded, "");
}
