/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/multikernel-memory-owner/main.c
 *
 * PURPOSE:
 *   Teach how to check a byte range against an explicit memory owner.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint64_t start;
    uint64_t length;
} ByteRange;

typedef struct {
    unsigned owner;
    ByteRange range;
} MemoryClaim;

/* Exclude empty ranges and check the addition before computing an exclusive end. */
static bool byte_range_valid(ByteRange range)
{
    return range.length != 0U && range.length <= UINT64_MAX - range.start;
}

/* Compare a request with its recorded owner. Subtraction leaves a count of
 * available bytes even at a region boundary, where that count may be zero. */
static bool contains_request(MemoryClaim authority, MemoryClaim request)
{
    if (authority.owner != request.owner || !byte_range_valid(authority.range) ||
        !byte_range_valid(request.range) || request.range.start < authority.range.start) {
        return false;
    }

    const uint64_t available_end = authority.range.start + authority.range.length;
    return request.range.start <= available_end &&
           request.range.length <= available_end - request.range.start;
}

typedef struct {
    const char *name;
    MemoryClaim authority;
    MemoryClaim request;
    bool admitted;
} Example;

/* These exercises model a single record. They never dereference an address or
 * require special access to the host's physical memory. */
static const Example examples[] = {
    {"inside", {2U, {4096U, 4096U}}, {2U, {4112U, 16U}}, true},
    {"last-byte", {2U, {4096U, 4096U}}, {2U, {8191U, 1U}}, true},
    {"starts-at-end", {2U, {4096U, 4096U}}, {2U, {8192U, 1U}}, false},
    {"crosses-end", {2U, {4096U, 4096U}}, {2U, {8191U, 2U}}, false},
    {"starts-before", {2U, {4096U, 4096U}}, {2U, {4095U, 2U}}, false},
    {"wrong-owner", {2U, {4096U, 4096U}}, {3U, {4112U, 16U}}, false},
    {"empty", {2U, {4096U, 4096U}}, {2U, {4112U, 0U}}, false},
    {"wrapped-request", {2U, {4096U, 4096U}}, {2U, {UINT64_MAX - 1U, 2U}}, false},
    {"wrapped-authority", {2U, {UINT64_MAX - 7U, 9U}}, {2U, {UINT64_MAX - 7U, 1U}}, false}
};

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: multikernel-memory-owner CASE\n", stderr);
        return 2;
    }

    /* Each named case returns its result to the test runner independently. */
    for (size_t index = 0U; index < sizeof examples / sizeof examples[0]; ++index) {
        const Example *example = &examples[index];
        if (strcmp(argv[1], example->name) == 0) {
            const bool admitted = contains_request(example->authority, example->request);
            printf("%s: %s\n", example->name, admitted ? "admitted" : "refused");
            return admitted == example->admitted ? 0 : 1;
        }
    }

    fputs("Unknown case. Run ctest --test-dir build/memory-owner -N to list the exercises.\n", stderr);
    return 2;
}
