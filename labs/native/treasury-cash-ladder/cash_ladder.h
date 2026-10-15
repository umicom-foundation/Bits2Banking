/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/treasury-cash-ladder/cash_ladder.h
 * PURPOSE: A deterministic, educational cash-obligation and currency ladder.
 * NO banking connectivity, persistence or external payment initiation.
 *---------------------------------------------------------------------------*/
#ifndef BTB_TREASURY_CASH_LADDER_H
#define BTB_TREASURY_CASH_LADDER_H
#include <stddef.h>
#include <stdint.h>
#define BTB_CASH_CAPACITY 16U
#define BTB_CASH_CURRENCY_BYTES 4U
typedef enum BtbCashResult { BTB_CASH_OK = 0, BTB_CASH_INVALID, BTB_CASH_FULL,
    BTB_CASH_DUPLICATE, BTB_CASH_NOT_FOUND, BTB_CASH_OVERFLOW } BtbCashResult;
typedef enum BtbCashCertainty { BTB_CASH_FORECAST = 0, BTB_CASH_CONFIRMED = 1,
    BTB_CASH_SETTLED = 2 } BtbCashCertainty;
typedef struct BtbCashFlow {
    uint64_t id;                 /* Unique classroom identity, never a bank ID. */
    int32_t valueDate;          /* YYYYMMDD classroom index; validated date. */
    int64_t minorUnits;         /* Signed: receipts positive; payments negative. */
    char currency[BTB_CASH_CURRENCY_BYTES]; /* Three uppercase letters + NUL. */
    BtbCashCertainty certainty;
} BtbCashFlow;
typedef struct BtbCashLadder {
    BtbCashFlow flows[BTB_CASH_CAPACITY];
    size_t count;
} BtbCashLadder;
/* Caller owns all storage. Rejected additions leave the entire ladder unchanged. */
BtbCashResult BtbCashLadderInit(BtbCashLadder *ladder);
BtbCashResult BtbCashLadderAdd(BtbCashLadder *ladder, BtbCashFlow flow);
/* Only summarises exactly matching currency and inclusive date range; no FX. */
BtbCashResult BtbCashLadderTotal(const BtbCashLadder *ladder,
    const char *currency, int32_t firstDate, int32_t lastDate,
    BtbCashCertainty minimumCertainty, int64_t *outMinorUnits);
#endif
