/* Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
 * Response completion is a byte-accounting fact, not proof of client receipt. */
#include "response_progress.h"

int BtbResponseProgressBegin(BtbResponseProgress *progress,
                             uint64_t wireHeaderBytes, uint64_t wireBodyBytes)
{
    if (progress == NULL || wireHeaderBytes == 0U) return 0;
    *progress = (BtbResponseProgress){.expectedHeaders=wireHeaderBytes,
                                       .expectedBody=wireBodyBytes,
                                       .phase=BTB_RESPONSE_HEADERS};
    return 1;
}
int BtbResponseProgressAdvance(BtbResponseProgress *progress,
                               BtbResponsePart part, size_t bytes)
{
    if (progress == NULL) return 0;
    if (part == BTB_RESPONSE_HEADER_PART && progress->phase == BTB_RESPONSE_HEADERS) {
        if (progress->sentHeaders > progress->expectedHeaders ||
            (uint64_t)bytes > progress->expectedHeaders - progress->sentHeaders) return 0;
        progress->sentHeaders += (uint64_t)bytes;
        if (progress->sentHeaders == progress->expectedHeaders)
            progress->phase = progress->expectedBody == 0U ? BTB_RESPONSE_COMPLETE : BTB_RESPONSE_BODY;
        return 1;
    }
    if (part == BTB_RESPONSE_BODY_PART && progress->phase == BTB_RESPONSE_BODY) {
        if (progress->sentBody > progress->expectedBody ||
            (uint64_t)bytes > progress->expectedBody - progress->sentBody) return 0;
        progress->sentBody += (uint64_t)bytes;
        if (progress->sentBody == progress->expectedBody) progress->phase = BTB_RESPONSE_COMPLETE;
        return 1;
    }
    return 0;
}
void BtbResponseProgressFail(BtbResponseProgress *progress)
{
    if (progress != NULL && progress->phase != BTB_RESPONSE_EMPTY &&
        progress->phase != BTB_RESPONSE_COMPLETE) progress->phase = BTB_RESPONSE_FAILED;
}
int BtbResponseProgressComplete(const BtbResponseProgress *progress)
{
    return progress != NULL && progress->phase == BTB_RESPONSE_COMPLETE &&
           progress->sentHeaders == progress->expectedHeaders &&
           progress->sentBody == progress->expectedBody;
}
