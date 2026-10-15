/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT | Fictional treasury demo. */
#include "cash_ladder.h"
#include <inttypes.h>
#include <stdio.h>
int main(void) {
    BtbCashLadder ladder;
    if(BtbCashLadderInit(&ladder)!=BTB_CASH_OK) return 1;
    if(BtbCashLadderAdd(&ladder,(BtbCashFlow){1,20261102,120000,"GBP",BTB_CASH_CONFIRMED})!=BTB_CASH_OK) return 2;
    if(BtbCashLadderAdd(&ladder,(BtbCashFlow){2,20261102,-75000,"GBP",BTB_CASH_SETTLED})!=BTB_CASH_OK) return 3;
    if(BtbCashLadderAdd(&ladder,(BtbCashFlow){3,20261102,300000,"USD",BTB_CASH_FORECAST})!=BTB_CASH_OK) return 4;
    int64_t total=0;
    if(BtbCashLadderTotal(&ladder,"GBP",20261101,20261130,BTB_CASH_CONFIRMED,&total)!=BTB_CASH_OK) return 5;
    printf("Fictional GBP confirmed-or-settled net: %" PRId64 " minor units\n",total);
    printf("USD is excluded. Confirmed does not mean settled. No payment is made.\n");
    return total==45000 ? 0 : 6;
}
