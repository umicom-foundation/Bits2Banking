/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: read_reply.c
 *
 * PURPOSE:
 *   Separate portable read bounds from the release-specific grant-copy mechanism.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "read_reply.h"
#include "read_window.h"

UmiLearningReadResult umi_learning_read_reply(const char *text, size_t length,
    uint64_t position, size_t requested, UmiLearningReadCopy copy, void *context,
    UmiLearningReadReply *reply)
{
    UmiLearningReadReply candidate = {0, 0, 0, 0};
    size_t count = 0;
    if (reply == NULL || copy == NULL || (text == NULL && length != 0))
        return UMI_LEARNING_READ_INVALID;

    /* Reuse the existing subtraction-based range proof. No pointer arithmetic
     * occurs until a nonempty slice has been admitted by that shared lab helper. */
    if (!umi_learning_read_window(position, requested, length,
            &candidate.offset, &count))
        return UMI_LEARNING_READ_INVALID;
    if (count != 0) {
        candidate.copy_attempted = 1;
        candidate.copy_status = copy(context, text + candidate.offset, count);
        if (candidate.copy_status != 0) {
            /* Publish the failure as a new observation. We cannot infer how
             * much a failed callback wrote, so no bytes are acknowledged. */
            *reply = candidate;
            return UMI_LEARNING_READ_COPY_FAILED;
        }
        candidate.bytes = count;
    }
    *reply = candidate;
    return UMI_LEARNING_READ_COMPLETE;
}
