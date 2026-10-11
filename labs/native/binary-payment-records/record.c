/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/binary-payment-records/record.c
 * PURPOSE: Encode a fixed-width, network-byte-order record without struct casts.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "record.h"

static int Valid(const BtbPaymentRecord *record)
{
    if (record == NULL || record->paymentId == 0U || record->amountMinor == 0U ||
        (record->state != 1U && record->state != 2U)) return 0;
    for (size_t i = 0U; i < 3U; ++i)
        if (record->currency[i] < 'A' || record->currency[i] > 'Z') return 0;
    return 1;
}

/* These shifts operate on unsigned values and write the most significant
 * byte first, independently of the CPU's native byte order. */
static void WriteBE(unsigned char *bytes, uint64_t value, size_t length)
{
    for (size_t i = 0U; i < length; ++i)
        bytes[i] = (unsigned char)(value >> (8U * (length - 1U - i)));
}

static uint64_t ReadBE(const unsigned char *bytes, size_t length)
{
    uint64_t value = 0U;
    for (size_t i = 0U; i < length; ++i)
        value = (value << 8U) | (uint64_t)bytes[i];
    return value;
}

BtbRecordStatus BtbEncodeRecord(const BtbPaymentRecord *source,
                                unsigned char *destination, size_t capacity,
                                size_t *outWritten)
{
    if (source == NULL || destination == NULL || outWritten == NULL || !Valid(source))
        return BTB_RECORD_INVALID;
    if (capacity < BTB_PAYMENT_RECORD_SIZE) return BTB_RECORD_TOO_SMALL;
    WriteBE(destination, source->paymentId, 4U);
    WriteBE(destination + 4U, source->amountMinor, 8U);
    for (size_t i = 0U; i < 3U; ++i) destination[12U + i] = (unsigned char)source->currency[i];
    destination[15U] = source->state;
    *outWritten = BTB_PAYMENT_RECORD_SIZE;
    return BTB_RECORD_OK;
}

BtbRecordStatus BtbDecodeRecord(const unsigned char *bytes, size_t length,
                                BtbPaymentRecord *destination)
{
    if (bytes == NULL || destination == NULL) return BTB_RECORD_INVALID;
    if (length != BTB_PAYMENT_RECORD_SIZE) return BTB_RECORD_INVALID;
    BtbPaymentRecord candidate = {0};
    candidate.paymentId = (uint32_t)ReadBE(bytes, 4U);
    candidate.amountMinor = ReadBE(bytes + 4U, 8U);
    for (size_t i = 0U; i < 3U; ++i) candidate.currency[i] = (char)bytes[12U + i];
    candidate.state = bytes[15U];
    if (!Valid(&candidate)) return BTB_RECORD_INVALID;
    *destination = candidate;
    return BTB_RECORD_OK;
}
