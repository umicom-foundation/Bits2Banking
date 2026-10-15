/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT | Deterministic C23 tests. */
#include "cash_ladder.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
static int Run(const char *name) {
    BtbCashLadder l; int64_t out=72;
    BtbCashFlow f={1,20261231,100,"GBP",BTB_CASH_CONFIRMED};
    if(strcmp(name,"init")==0) return BtbCashLadderInit(&l)==BTB_CASH_OK && l.count==0 ? 0:1;
    if(BtbCashLadderInit(&l)!=BTB_CASH_OK || BtbCashLadderAdd(&l,f)!=BTB_CASH_OK) return 2;
    if(strcmp(name,"duplicate")==0) return BtbCashLadderAdd(&l,f)==BTB_CASH_DUPLICATE && l.count==1?0:3;
    if(strcmp(name,"currency")==0) return BtbCashLadderTotal(&l,"USD",20261201,20261231,BTB_CASH_FORECAST,&out)==BTB_CASH_OK && out==0?0:4;
    if(strcmp(name,"confirmed")==0) return BtbCashLadderTotal(&l,"GBP",20261201,20261231,BTB_CASH_CONFIRMED,&out)==BTB_CASH_OK && out==100?0:5;
    if(strcmp(name,"settled")==0) return BtbCashLadderTotal(&l,"GBP",20261201,20261231,BTB_CASH_SETTLED,&out)==BTB_CASH_OK && out==0?0:6;
    if(strcmp(name,"invalid-date")==0) {f.id=2;f.valueDate=20260230;return BtbCashLadderAdd(&l,f)==BTB_CASH_INVALID && l.count==1?0:7;}
    if(strcmp(name,"invalid-currency")==0) {f.id=2;memcpy(f.currency,"gbp",4);return BtbCashLadderAdd(&l,f)==BTB_CASH_INVALID?0:8;}
    if(strcmp(name,"atomic-output")==0) return BtbCashLadderTotal(&l,"GBP",20261231,20261201,BTB_CASH_FORECAST,&out)==BTB_CASH_INVALID && out==72?0:9;
    if(strcmp(name,"overflow")==0) {f.minorUnits=INT64_MAX;f.id=2;if(BtbCashLadderAdd(&l,f)!=BTB_CASH_OK)return 10; return BtbCashLadderTotal(&l,"GBP",20261201,20261231,BTB_CASH_FORECAST,&out)==BTB_CASH_OVERFLOW && out==72?0:11;}
    if(strcmp(name,"capacity")==0) {for(unsigned i=2;i<=16;i++){f.id=i;if(BtbCashLadderAdd(&l,f)!=BTB_CASH_OK) return 12;}f.id=17;return BtbCashLadderAdd(&l,f)==BTB_CASH_FULL && l.count==16?0:13;}
    if(strcmp(name,"leap")==0) {f.id=2;f.valueDate=20280229;return BtbCashLadderAdd(&l,f)==BTB_CASH_OK?0:14;}
    if(strcmp(name,"negative")==0) {f.id=2;f.minorUnits=-70;if(BtbCashLadderAdd(&l,f)!=BTB_CASH_OK)return 15;return BtbCashLadderTotal(&l,"GBP",20261201,20261231,BTB_CASH_FORECAST,&out)==BTB_CASH_OK && out==30?0:16;}
    return 17;
}
int main(int argc,char **argv) { if(argc!=2)return 18;int r=Run(argv[1]);if(r)fprintf(stderr,"Test %s failed: %d\n",argv[1],r);return r; }
