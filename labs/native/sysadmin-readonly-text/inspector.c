/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-readonly-text/inspector.c
 * PURPOSE: Read-only bounded byte/line counting for a first C23 laboratory.
 *
 * The state is local to this function; a reported error does not publish a
 * partially inspected result. The native C library owns the opened stream.
 *---------------------------------------------------------------------------*/
#include "inspector.h"

#include <errno.h>
#include <stdio.h>

BtbTextInspectStatus BtbTextInspectFile(
    const char *path, size_t maxBytes, BtbTextSummary *outSummary)
{
    BtbTextSummary result = {0};
    FILE *stream;
    int nextByte;
    int previousByte = EOF;
    BtbTextInspectStatus status = BTB_TEXT_OK;

    if (path == NULL || path[0] == '\0' || outSummary == NULL ||
        maxBytes == 0U || maxBytes > BTB_SYSADMIN_TEXT_MAX_BYTES) {
        return BTB_TEXT_INVALID_ARGUMENT;
    }

    errno = 0;
    stream = fopen(path, "rb");
    if (stream == NULL) {
        return errno == ENOENT ? BTB_TEXT_NOT_FOUND : BTB_TEXT_IO_ERROR;
    }

    while ((nextByte = fgetc(stream)) != EOF) {
        if (result.byteCount >= (uint64_t)maxBytes) {
            status = BTB_TEXT_TOO_LARGE;
            break;
        }
        if (nextByte == 0) {
            status = BTB_TEXT_BINARY;
            break;
        }
        ++result.byteCount;
        if (nextByte == '\n') {
            ++result.lineCount;
        }
        previousByte = nextByte;
    }
    if (status == BTB_TEXT_OK && ferror(stream) != 0) {
        status = BTB_TEXT_IO_ERROR;
    }
    if (fclose(stream) != 0) {
        status = BTB_TEXT_IO_ERROR;
    }
    if (status != BTB_TEXT_OK) {
        return status;
    }
    result.endsWithNewline = previousByte == '\n';
    if (result.byteCount > 0U && previousByte != '\n') {
        ++result.lineCount;
    }
    *outSummary = result;
    return BTB_TEXT_OK;
}

const char *BtbTextInspectStatusText(BtbTextInspectStatus status)
{
    switch (status) {
        case BTB_TEXT_OK: return "OK";
        case BTB_TEXT_INVALID_ARGUMENT: return "INVALID_ARGUMENT";
        case BTB_TEXT_NOT_FOUND: return "NOT_FOUND";
        case BTB_TEXT_IO_ERROR: return "IO_ERROR";
        case BTB_TEXT_TOO_LARGE: return "TOO_LARGE";
        case BTB_TEXT_BINARY: return "BINARY";
        default: return "UNKNOWN_STATUS";
    }
}
