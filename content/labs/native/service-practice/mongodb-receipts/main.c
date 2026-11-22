/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/mongodb-receipts/main.c
 *
 * PURPOSE:
 *   Check a typed projection before adapting it to the MongoDB C driver.
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

enum AmountField {
    AMOUNT_MISSING,
    AMOUNT_INT64,
    AMOUNT_WRONG_TYPE
};

struct ReceiptDocument {
    const char *receipt_id;
    enum AmountField amount_field;
    int64_t cents;
};

static bool decode_receipt(const struct ReceiptDocument *doc, int64_t *amount)
{
    // A required field keeps missing data distinct from a real zero-cents entry.
    if (doc->receipt_id == NULL || doc->receipt_id[0] == '\0' ||
        doc->amount_field != AMOUNT_INT64) {
        return false;
    }
    *amount = doc->cents;
    return true;
}

int main(void)
{
    const struct ReceiptDocument zero = {"R-42", AMOUNT_INT64, 0};
    const struct ReceiptDocument missing = {"R-43", AMOUNT_MISSING, 0};
    const struct ReceiptDocument wrong = {"R-44", AMOUNT_WRONG_TYPE, 2600};
    int64_t cents = -99;
    if (!decode_receipt(&zero, &cents) || cents != 0 ||
        decode_receipt(&missing, &cents) || cents != 0 ||
        decode_receipt(&wrong, &cents) || cents != 0) {
        fputs("document projection mismatch\n", stderr);
        return 1;
    }
    puts("document field checks ready");
    return 0;
}
