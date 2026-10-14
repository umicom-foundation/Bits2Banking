/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-readonly-text/inspector.h
 * PURPOSE: Bounded read-only educational text-file inspection contract.
 *
 * OWNER: The caller retains ownership of the path and output storage.
 *        The implementation owns only a temporary read-only C stream.
 *        On every non-OK result, the caller's output remains unchanged.
 *        This is a teaching program, NOT a replacement for the portable
 *        Umicom Framework filesystem APIs or a secure untrusted-path reader.
 *---------------------------------------------------------------------------*/
#ifndef BTB_SYSADMIN_TEXT_INSPECTOR_H
#define BTB_SYSADMIN_TEXT_INSPECTOR_H

#include <stddef.h>
#include <stdint.h>

#define BTB_SYSADMIN_TEXT_MAX_BYTES 65536U

typedef enum BtbTextInspectStatus {
    BTB_TEXT_OK = 0,
    BTB_TEXT_INVALID_ARGUMENT,
    BTB_TEXT_NOT_FOUND,
    BTB_TEXT_IO_ERROR,
    BTB_TEXT_TOO_LARGE,
    BTB_TEXT_BINARY
} BtbTextInspectStatus;

typedef struct BtbTextSummary {
    uint64_t byteCount;
    uint64_t lineCount;
    int endsWithNewline;
} BtbTextSummary;

/* Read an explicitly named local file. Limit must be in [1, MAX_BYTES].
 * Lines are counted by LF, with one extra line for a non-empty final fragment.
 * CRLF therefore counts as one line ending. This routine does not parse
 * Unicode or a formal text grammar. NUL bytes are rejected as binary data.
 * A refused operation never changes caller-owned `outSummary`.
 * No files are created, truncated, overwritten, renamed or deleted. */
BtbTextInspectStatus BtbTextInspectFile(
    const char *path, size_t maxBytes, BtbTextSummary *outSummary);

const char *BtbTextInspectStatusText(BtbTextInspectStatus status);

#endif
