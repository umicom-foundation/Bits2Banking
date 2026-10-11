/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/binary-payment-records/test_record.c
 * PURPOSE: Test byte order, capacity, malformed fields, and output ownership.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "record.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "[FAIL] %s:%d: %s\n", __FILE__, __LINE__, #condition); \
    return 1; } } while (0)

int main(void)
{
    const BtbPaymentRecord source = {27U, 125000U, {'G', 'B', 'P'}, 1U};
    const unsigned char expected[BTB_PAYMENT_RECORD_SIZE] = {
        0x00U, 0x00U, 0x00U, 0x1BU,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U, 0xE8U, 0x48U,
        0x47U, 0x42U, 0x50U, 0x01U
    };
    unsigned char actual[BTB_PAYMENT_RECORD_SIZE + 1U];
    memset(actual, 0xA5, sizeof(actual));
    size_t written = 999U;
    REQUIRE(BtbEncodeRecord(&source, actual, BTB_PAYMENT_RECORD_SIZE - 1U,
                            &written) == BTB_RECORD_TOO_SMALL);
    REQUIRE(written == 999U && actual[0] == 0xA5U && actual[15] == 0xA5U);
    REQUIRE(BtbEncodeRecord(&source, actual, sizeof(actual), &written) == BTB_RECORD_OK);
    REQUIRE(written == BTB_PAYMENT_RECORD_SIZE && actual[16] == 0xA5U);
    REQUIRE(memcmp(actual, expected, sizeof(expected)) == 0);

    BtbPaymentRecord decoded = {0};
    REQUIRE(BtbDecodeRecord(actual, written, &decoded) == BTB_RECORD_OK);
    REQUIRE(decoded.paymentId == source.paymentId);
    REQUIRE(decoded.amountMinor == source.amountMinor);
    REQUIRE(memcmp(decoded.currency, source.currency, 3U) == 0);
    REQUIRE(decoded.state == 1U);

    const BtbPaymentRecord original = decoded;
    actual[12] = 'g';
    REQUIRE(BtbDecodeRecord(actual, written, &decoded) == BTB_RECORD_INVALID);
    REQUIRE(memcmp(&original, &decoded, sizeof(decoded)) == 0);
    actual[12] = 'G';
    actual[15] = 0xFFU;
    REQUIRE(BtbDecodeRecord(actual, written, &decoded) == BTB_RECORD_INVALID);
    REQUIRE(memcmp(&original, &decoded, sizeof(decoded)) == 0);
    actual[15] = 1U;
    REQUIRE(BtbDecodeRecord(actual, written - 1U, &decoded) == BTB_RECORD_INVALID);
    REQUIRE(BtbDecodeRecord(actual, written + 1U, &decoded) == BTB_RECORD_INVALID);
    REQUIRE(memcmp(&original, &decoded, sizeof(decoded)) == 0);

    BtbPaymentRecord bad = source;
    bad.amountMinor = 0U;
    memset(actual, 0xA5, sizeof(actual));
    REQUIRE(BtbEncodeRecord(&bad, actual, sizeof(actual), &written) == BTB_RECORD_INVALID);
    REQUIRE(actual[0] == 0xA5U);
    REQUIRE(BtbEncodeRecord(NULL, actual, sizeof(actual), &written) == BTB_RECORD_INVALID);
    REQUIRE(BtbDecodeRecord(NULL, BTB_PAYMENT_RECORD_SIZE, &decoded) == BTB_RECORD_INVALID);
    puts("Binary record encoding and rejection tests passed.");
    return 0;
}
