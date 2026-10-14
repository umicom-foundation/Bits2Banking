/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-readonly-text/test_inspector.c
 * PURPOSE: Positive, negative, atomicity and repeatability C23 regression tests.
 *---------------------------------------------------------------------------*/
#include "inspector.h"

#include <stdio.h>
#include <string.h>

#ifndef BTB_FIXTURE_DIR
#error "BTB_FIXTURE_DIR must be defined by CMake"
#endif

static int PathFor(char *destination, size_t capacity, const char *name)
{
    int length = snprintf(destination, capacity, "%s/%s", BTB_FIXTURE_DIR, name);
    return length >= 0 && (size_t)length < capacity;
}

static int Same(const BtbTextSummary *left, const BtbTextSummary *right)
{
    return left->byteCount == right->byteCount &&
           left->lineCount == right->lineCount &&
           left->endsWithNewline == right->endsWithNewline;
}

static int InspectMatches(const char *filename, size_t limit,
                          BtbTextInspectStatus expectedStatus,
                          BtbTextSummary expectedSummary)
{
    char path[1024];
    const BtbTextSummary untouched = {77U, 88U, 9};
    BtbTextSummary summary = untouched;
    BtbTextInspectStatus status;
    if (!PathFor(path, sizeof(path), filename)) return 0;
    status = BtbTextInspectFile(path, limit, &summary);
    if (status != expectedStatus) {
        fprintf(stderr, "Wrong status for %s: got %s\n", filename,
                BtbTextInspectStatusText(status));
        return 0;
    }
    return Same(&summary, status == BTB_TEXT_OK ? &expectedSummary : &untouched);
}

int main(int argc, char **argv)
{
    const BtbTextSummary none = {0};
    const BtbTextSummary unchanged = {77U, 88U, 9};
    BtbTextSummary summary = unchanged;
    char path[1024];
    size_t i;
    if (argc != 2) return 2;

    if (strcmp(argv[1], "lf") == 0)
        return InspectMatches("sample.md", 100U, BTB_TEXT_OK,
                              (BtbTextSummary){26U, 2U, 1}) ? 0 : 1;
    if (strcmp(argv[1], "crlf") == 0)
        return InspectMatches("windows-crlf.txt", 100U, BTB_TEXT_OK,
                              (BtbTextSummary){15U, 2U, 1}) ? 0 : 1;
    if (strcmp(argv[1], "noeol") == 0)
        return InspectMatches("no-final-newline.txt", 100U, BTB_TEXT_OK,
                              (BtbTextSummary){11U, 1U, 0}) ? 0 : 1;
    if (strcmp(argv[1], "empty") == 0)
        return InspectMatches("empty.txt", 100U, BTB_TEXT_OK, none) ? 0 : 1;
    if (strcmp(argv[1], "binary") == 0)
        return InspectMatches("binary.bin", 100U, BTB_TEXT_BINARY, none) ? 0 : 1;
    if (strcmp(argv[1], "oversized") == 0)
        return InspectMatches("long.txt", 16U, BTB_TEXT_TOO_LARGE, none) ? 0 : 1;
    if (strcmp(argv[1], "missing") == 0)
        return InspectMatches("this-file-does-not-exist.txt", 100U,
                              BTB_TEXT_NOT_FOUND, none) ? 0 : 1;
    if (strcmp(argv[1], "invalid") == 0) {
        return BtbTextInspectFile(NULL, 10U, &summary) == BTB_TEXT_INVALID_ARGUMENT &&
               BtbTextInspectFile("", 10U, &summary) == BTB_TEXT_INVALID_ARGUMENT &&
               BtbTextInspectFile("abc", 0U, &summary) == BTB_TEXT_INVALID_ARGUMENT &&
               BtbTextInspectFile("abc", BTB_SYSADMIN_TEXT_MAX_BYTES + 1U,
                                  &summary) == BTB_TEXT_INVALID_ARGUMENT &&
               BtbTextInspectFile("abc", 10U, NULL) == BTB_TEXT_INVALID_ARGUMENT &&
               Same(&summary, &unchanged) ? 0 : 1;
    }
    if (strcmp(argv[1], "preserve") == 0) {
        if (!PathFor(path, sizeof(path), "long.txt")) return 1;
        return BtbTextInspectFile(path, 5U, &summary) == BTB_TEXT_TOO_LARGE &&
               Same(&summary, &unchanged) ? 0 : 1;
    }
    if (strcmp(argv[1], "repeat") == 0) {
        if (!PathFor(path, sizeof(path), "sample.md")) return 1;
        for (i = 0U; i < 10000U; ++i) {
            if (BtbTextInspectFile(path, 100U, &summary) != BTB_TEXT_OK ||
                !Same(&summary, &(BtbTextSummary){26U, 2U, 1})) return 1;
        }
        return 0;
    }
    return 2;
}
