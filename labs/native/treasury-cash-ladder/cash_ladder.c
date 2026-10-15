/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/treasury-cash-ladder/cash_ladder.c
 * PURPOSE: Safe copied obligations with explicit currency and signed cashflows.
 *---------------------------------------------------------------------------*/
#include "cash_ladder.h"
#include <limits.h>
#include <string.h>
static int IsLeap(int y) { return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0); }
static int ValidDate(int32_t d) {
    int y=d/10000, m=(d/100)%100, day=d%100;
    static const int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (y<1900 || y>2200 || m<1 || m>12 || day<1) return 0;
    return day <= days[m-1] + (m==2 && IsLeap(y));
}
static int ValidCurrency(const char *c) {
    if (!c) return 0;
    for (int i=0;i<3;i++) if (c[i]<'A' || c[i]>'Z') return 0;
    return c[3]=='\0';
}
static int ValidFlow(const BtbCashFlow *f) {
    return f && f->id!=0 && ValidDate(f->valueDate) &&
        ValidCurrency(f->currency) && f->certainty>=BTB_CASH_FORECAST &&
        f->certainty<=BTB_CASH_SETTLED;
}
BtbCashResult BtbCashLadderInit(BtbCashLadder *ladder) {
    if(!ladder) return BTB_CASH_INVALID;
    *ladder=(BtbCashLadder){0}; return BTB_CASH_OK;
}
BtbCashResult BtbCashLadderAdd(BtbCashLadder *ladder,BtbCashFlow flow) {
    if (!ladder || ladder->count>BTB_CASH_CAPACITY || !ValidFlow(&flow)) return BTB_CASH_INVALID;
    for(size_t i=0;i<ladder->count;i++) if(ladder->flows[i].id==flow.id) return BTB_CASH_DUPLICATE;
    if (ladder->count==BTB_CASH_CAPACITY) return BTB_CASH_FULL;
    ladder->flows[ladder->count++]=flow;
    return BTB_CASH_OK;
}
BtbCashResult BtbCashLadderTotal(const BtbCashLadder *ladder,const char *currency,
    int32_t firstDate,int32_t lastDate,BtbCashCertainty certainty,int64_t *out) {
    if(!ladder || ladder->count>BTB_CASH_CAPACITY || !ValidCurrency(currency) ||
       !ValidDate(firstDate) || !ValidDate(lastDate) || firstDate>lastDate ||
       certainty<BTB_CASH_FORECAST || certainty>BTB_CASH_SETTLED || !out) return BTB_CASH_INVALID;
    int64_t sum=0;
    for(size_t i=0;i<ladder->count;i++) {
        const BtbCashFlow *f=&ladder->flows[i];
        if(!ValidFlow(f)) return BTB_CASH_INVALID;
        if(strcmp(f->currency,currency)!=0 || f->valueDate<firstDate ||
           f->valueDate>lastDate || f->certainty<certainty) continue;
        if((f->minorUnits>0 && sum>INT64_MAX-f->minorUnits) ||
           (f->minorUnits<0 && sum<INT64_MIN-f->minorUnits)) return BTB_CASH_OVERFLOW;
        sum+=f->minorUnits;
    }
    *out=sum; return BTB_CASH_OK;
}
