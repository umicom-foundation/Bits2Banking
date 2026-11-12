/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_reply_tests.c
 *
 * PURPOSE:
 *   Exercise range admission, copy errors and explicit retries without a MINIX guest.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "read_reply.h"
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); \
    return 1; \
} } while (0)

typedef struct CopyProbe {
    const char *source;
    size_t count;
    unsigned calls;
    int status;
    char copied[64];
} CopyProbe;

static int capture_copy(void *opaque, const char *source, size_t count)
{
    CopyProbe *probe = opaque;
    probe->source = source;
    probe->count = count;
    ++probe->calls;
    if (count > sizeof(probe->copied)) return 99;
    /* A failure is deliberately allowed to leave destination bytes changed.
     * The reply must report failure rather than inventing a byte count. */
    memcpy(probe->copied, source, count);
    return probe->status;
}
static const char text[] = "Umicom learning status: ready\n";

static int check_slice(uint64_t position, size_t requested, size_t offset,
    size_t count)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {91, 92, 93, 94};
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, position, requested,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COMPLETE);
    CHECK(reply.offset == offset && reply.bytes == count);
    CHECK(reply.copy_status == 0 && reply.copy_attempted == (count != 0));
    CHECK(probe.calls == (count != 0));
    if (count != 0) {
        CHECK(probe.source == text + offset && probe.count == count);
        CHECK(memcmp(probe.copied, text + offset, count) == 0);
    }
    return 0;
}
static int prefix(void) { return check_slice(0, 6, 0, 6); }
static int tail(void) { return check_slice(sizeof(text) - 4, 20, sizeof(text) - 4, 3); }
static int whole(void) { return check_slice(0, sizeof(text) - 1, 0, sizeof(text) - 1); }
static int eof(void) { return check_slice(sizeof(text) - 1, 8, sizeof(text) - 1, 0); }
static int beyond(void) { return check_slice(sizeof(text) + 7, 8, sizeof(text) - 1, 0); }
static int huge_position(void) { return check_slice(UINT64_MAX, SIZE_MAX, sizeof(text) - 1, 0); }
static int zero(void) { return check_slice(3, 0, 3, 0); }
static int huge_request(void) { return check_slice(3, SIZE_MAX, 3, sizeof(text) - 4); }

static int check_empty(const char *data)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {91, 92, 93, 94};
    CHECK(umi_learning_read_reply(data, 0, UINT64_MAX, SIZE_MAX,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COMPLETE);
    CHECK(reply.offset == 0 && reply.bytes == 0 && reply.copy_status == 0);
    CHECK(reply.copy_attempted == 0 && probe.calls == 0);
    return 0;
}
static int empty(void) { return check_empty(""); }
static int null_empty(void) { return check_empty(NULL); }

static int check_failure(int error)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {91, 92, 93, 94};
    probe.status = error;
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 3, 4,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COPY_FAILED);
    CHECK(reply.offset == 3 && reply.bytes == 0 && reply.copy_status == error);
    CHECK(reply.copy_attempted == 1 && probe.calls == 1 && probe.count == 4);
    CHECK(memcmp(probe.copied, text + 3, 4) == 0);
    return 0;
}
static int positive_failure(void) { return check_failure(27); }
static int negative_failure(void) { return check_failure(-27); }

static int retry(void)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {0};
    probe.status = 27;
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 3, 4,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COPY_FAILED);
    CHECK(reply.bytes == 0 && reply.copy_status == 27);
    probe.status = 0;
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 3, 4,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COMPLETE);
    CHECK(reply.bytes == 4 && reply.offset == 3 && reply.copy_status == 0);
    CHECK(reply.copy_attempted == 1 && probe.calls == 2);
    CHECK(probe.source == text + 3 && memcmp(probe.copied, text + 3, 4) == 0);
    return 0;
}
static int reuse_eof(void)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {0};
    probe.status = -27;
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 0, 4,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COPY_FAILED);
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, sizeof(text) - 1, 4,
        capture_copy, &probe, &reply) == UMI_LEARNING_READ_COMPLETE);
    CHECK(reply.offset == sizeof(text) - 1 && reply.bytes == 0);
    CHECK(reply.copy_attempted == 0 && reply.copy_status == 0 && probe.calls == 1);
    return 0;
}
static int unchanged(const UmiLearningReadReply *reply)
{
    return reply->offset == 91 && reply->bytes == 92 &&
        reply->copy_status == 93 && reply->copy_attempted == 94;
}
static int null_text(void)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {91, 92, 93, 94};
    CHECK(umi_learning_read_reply(NULL, 1, 0, 1, capture_copy, &probe, &reply)
        == UMI_LEARNING_READ_INVALID);
    CHECK(unchanged(&reply) && probe.calls == 0);
    return 0;
}
static int null_copy(void)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {91, 92, 93, 94};
    /* Even an EOF request requires a callback matching the public contract. */
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, UINT64_MAX, 0,
        NULL, &probe, &reply) == UMI_LEARNING_READ_INVALID);
    CHECK(unchanged(&reply) && probe.calls == 0);
    return 0;
}
static int null_reply(void)
{
    CopyProbe probe = {0};
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 0, 1,
        capture_copy, &probe, NULL) == UMI_LEARNING_READ_INVALID);
    CHECK(probe.calls == 0);
    return 0;
}
static int chunked(void)
{
    CopyProbe probe = {0};
    UmiLearningReadReply reply = {0};
    char assembled[sizeof(text)] = {0};
    size_t offset = 0;
    const size_t requests[] = {1, 3, 5};
    unsigned part = 0;
    for (;;) {
        size_t requested = requests[part % 3];
        CHECK(umi_learning_read_reply(text, sizeof(text) - 1, offset, requested,
            capture_copy, &probe, &reply) == UMI_LEARNING_READ_COMPLETE);
        CHECK(reply.offset == offset);
        if (reply.bytes == 0) break;
        CHECK(reply.bytes <= requested && reply.bytes <= sizeof(text) - 1 - offset);
        memcpy(assembled + offset, probe.copied, reply.bytes);
        offset += reply.bytes;
        ++part;
    }
    CHECK(offset == sizeof(text) - 1 && probe.calls == part);
    CHECK(memcmp(assembled, text, sizeof(text)) == 0);
    return 0;
}
static int accept_without_context(void *context, const char *source, size_t count)
{
    return context == NULL && source == text && count == 4 ? 0 : 91;
}
static int null_context(void)
{
    UmiLearningReadReply reply = {0};
    CHECK(umi_learning_read_reply(text, sizeof(text) - 1, 0, 4,
        accept_without_context, NULL, &reply) == UMI_LEARNING_READ_COMPLETE);
    CHECK(reply.bytes == 4 && reply.copy_attempted == 1 && reply.copy_status == 0);
    return 0;
}

typedef struct ReadCase { const char *name; int (*run)(void); } ReadCase;
static const ReadCase cases[] = {
    {"prefix", prefix}, {"tail", tail}, {"whole", whole},
    {"eof", eof}, {"beyond", beyond}, {"huge-position", huge_position},
    {"zero", zero}, {"empty", empty}, {"null-empty", null_empty},
    {"huge-request", huge_request}, {"positive-failure", positive_failure},
    {"negative-failure", negative_failure}, {"retry", retry},
    {"reuse-eof", reuse_eof}, {"null-text", null_text},
    {"null-copy", null_copy}, {"null-reply", null_reply},
    {"chunked", chunked}, {"null-context", null_context}
};
int main(int argc, char **argv)
{
    size_t index;
    if (argc == 2) {
        for (index = 0; index < sizeof(cases) / sizeof(cases[0]); ++index)
            if (strcmp(argv[1], cases[index].name) == 0) return cases[index].run();
    }
    fprintf(stderr, "usage: read-reply-tests CASE\n");
    return 2;
}
