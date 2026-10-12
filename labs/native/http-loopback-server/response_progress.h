/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation
 * File: labs/native/http-loopback-server/response_progress.h
 * PURPOSE: Account for completed HTTP response bytes and disconnects.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_RESPONSE_PROGRESS_H
#define BTB_RESPONSE_PROGRESS_H
#include <stddef.h>
#include <stdint.h>

typedef enum BtbResponsePhase {
    BTB_RESPONSE_EMPTY = 0,
    BTB_RESPONSE_HEADERS,
    BTB_RESPONSE_BODY,
    BTB_RESPONSE_COMPLETE,
    BTB_RESPONSE_FAILED
} BtbResponsePhase;
typedef enum BtbResponsePart {
    BTB_RESPONSE_HEADER_PART = 1,
    BTB_RESPONSE_BODY_PART = 2
} BtbResponsePart;
typedef struct BtbResponseProgress {
    uint64_t expectedHeaders;
    uint64_t expectedBody;
    uint64_t sentHeaders;
    uint64_t sentBody;
    BtbResponsePhase phase;
} BtbResponseProgress;

/* A HEAD reply expects headers only on the wire even though its declared
 * Content-Length can describe a full GET body. The caller supplies the wire
 * lengths, not an assertion that the remote peer read those bytes. */
int BtbResponseProgressBegin(BtbResponseProgress *progress,
                             uint64_t wireHeaderBytes, uint64_t wireBodyBytes);
/* Accept only bytes positively reported as transmitted by the socket layer.
 * Invalid or over-capacity advances change nothing. */
int BtbResponseProgressAdvance(BtbResponseProgress *progress,
                               BtbResponsePart part, size_t bytes);
void BtbResponseProgressFail(BtbResponseProgress *progress);
int BtbResponseProgressComplete(const BtbResponseProgress *progress);
#endif
