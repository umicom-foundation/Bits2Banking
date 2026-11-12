/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_reply.h
 *
 * PURPOSE:
 *   Plan a bounded teaching read and publish the outcome of one borrowed copy callback.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_LEARNING_READ_REPLY_H
#define UMICOM_LEARNING_READ_REPLY_H
#include <stddef.h>
#include <stdint.h>

/* The callback borrows source/context only until return: zero reports complete
 * success, any other value reports failure. Failure does not promise that the
 * destination was untouched. The helper neither authenticates nor owns grants. */
typedef int (*UmiLearningReadCopy)(void *context, const char *source, size_t count);
typedef enum UmiLearningReadResult {
    UMI_LEARNING_READ_INVALID = 0,
    UMI_LEARNING_READ_COMPLETE = 1,
    UMI_LEARNING_READ_COPY_FAILED = 2
} UmiLearningReadResult;
typedef struct UmiLearningReadReply {
    size_t offset;
    size_t bytes;           /* Acknowledged bytes, not inferred partial writes. */
    int copy_status;        /* Exact callback result; zero if no copy was needed. */
    int copy_attempted;
} UmiLearningReadReply;

/* C99 keeps this original lab compatible with the pinned MINIX teaching target.
 * text points to length accessible bytes (or NULL only when length is zero).
 * copy and reply must be non-NULL. context may be NULL if the callback permits it.
 * reply must not overlap text or context-owned storage. No global state is used.
 *
 * Invalid arguments leave reply unchanged and do not call copy. Valid operations
 * replace the entire logical report, including EOF and failed copies. EOF and
 * zero requests complete without a callback. At most one callback is made.
 * Position is supplied by the caller; no offset is advanced inside this helper. */
UmiLearningReadResult umi_learning_read_reply(const char *text, size_t length,
    uint64_t position, size_t requested, UmiLearningReadCopy copy, void *context,
    UmiLearningReadReply *reply);
#endif
