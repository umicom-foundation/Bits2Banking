/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/binary-payment-records/record.h
 * PURPOSE: Define a bounded example wire format for simulated payment records.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS_TO_BANKING_PAYMENT_RECORD_H
#define BITS_TO_BANKING_PAYMENT_RECORD_H
#include <stddef.h>
#include <stdint.h>

#define BTB_PAYMENT_RECORD_SIZE 16U

typedef enum BtbRecordStatus {
    BTB_RECORD_OK = 0,
    BTB_RECORD_INVALID = 1,
    BTB_RECORD_TOO_SMALL = 2
} BtbRecordStatus;

typedef struct BtbPaymentRecord {
    uint32_t paymentId;
    uint64_t amountMinor;
    char currency[3]; /* Three uppercase ASCII bytes, deliberately not a C string. */
    uint8_t state;    /* 1 = pending, 2 = reviewed. No payment execution. */
} BtbPaymentRecord;

/* Success writes exactly BTB_PAYMENT_RECORD_SIZE bytes. Rejection leaves
 * the caller's output buffer and outWritten unchanged. No memory is allocated. */
BtbRecordStatus BtbEncodeRecord(const BtbPaymentRecord *source,
                                unsigned char *destination, size_t capacity,
                                size_t *outWritten);

/* Decode a complete 16-byte record; reject malformed or trailing data.
 * On failure, the destination record remains unchanged. */
BtbRecordStatus BtbDecodeRecord(const unsigned char *bytes, size_t length,
                                BtbPaymentRecord *destination);
#endif
