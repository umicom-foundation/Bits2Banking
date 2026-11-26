/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/fastcgi-head-review/test_head_review.c
 *
 * PURPOSE:
 *   Compare exact HEAD wire bytes and verify failure leaves caller storage unchanged.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "head_review.h"
#include <stdio.h>
#include <string.h>

static const char no_length[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
static const char length_zero[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 0\r\n\r\n";
static const char length_forty_two[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 42\r\n\r\n";

typedef struct Fixture {
    const char *name;
    BitsHeadMetadata metadata;
    size_t capacity;
    BitsHeadResult result;
    const char *expected;
    const char *worker_document;
} Fixture;

static bool CheckFixture(const Fixture *fixture)
{
    char expected_state[96];
    char actual[sizeof expected_state];
    memset(expected_state, '@', sizeof expected_state);
    memcpy(actual, expected_state, sizeof actual);
    const BitsHeadResult result = BitsHeadReviewFormat(fixture->metadata, actual, fixture->capacity);
    if (result != fixture->result) return false;

    /* A refused output cannot publish even a partial status line. */
    if (result != BITS_HEAD_OK) return memcmp(actual, expected_state, sizeof actual) == 0;

    /* Compare the C terminator as well. An untransmitted worker document
     * cannot contribute any byte after the terminal blank line. */
    const size_t wire_bytes = strlen(fixture->expected);
    return memcmp(actual, fixture->expected, wire_bytes + 1U) == 0 &&
        (fixture->worker_document == NULL || strstr(actual, fixture->worker_document) == NULL);
}

int main(int argc, char **argv)
{
    static const Fixture cases[] = {
        {"known", {true, 42U}, 96U, BITS_HEAD_OK, length_forty_two, NULL},
        {"known-zero", {true, 0U}, 96U, BITS_HEAD_OK, length_zero, NULL},
        {"unknown", {false, 0U}, 96U, BITS_HEAD_OK, no_length, NULL},
        {"discard-document", {false, 20U}, 96U, BITS_HEAD_OK, no_length, "offline fixture data"},
        {"length-limit", {true, BITS_HEAD_REVIEW_LENGTH_LIMIT + 1U}, 96U, BITS_HEAD_RANGE, NULL, NULL},
        {"short-output", {true, 42U}, sizeof length_forty_two - 1U, BITS_HEAD_OUTPUT, NULL, NULL}
    };
    if (argc != 2) return 2;
    for (size_t i = 0U; i < sizeof cases / sizeof cases[0]; ++i) {
        if (strcmp(argv[1], cases[i].name) != 0) continue;
        if (CheckFixture(&cases[i])) return 0;
        fprintf(stderr, "HEAD fixture %s failed its byte or output-state check.\n", cases[i].name);
        return 1;
    }
    return 2;
}

