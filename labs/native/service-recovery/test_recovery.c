/* Bits2Banking — C23 Service-Recovery Tests | Umicom Foundation | MIT */
#include "recovery.h"
#include <stdio.h>
#define CHECK(x) do {if (!(x)) {fprintf(stderr,"FAIL: %s:%d %s\n",__FILE__,__LINE__,#x);return 1;}} while(0)
int main(void)
{
    BtbService service = {0};
    CHECK(BtbServiceStart(&service, 99U) == BTB_IRQ_OK);
    CHECK(BtbServiceStart(&service, 99U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceBegin(&service, 1U) == BTB_IRQ_OK);
    CHECK(BtbServiceBegin(&service, 2U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceStop(&service) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceFault(&service) == BTB_IRQ_OK);
    CHECK(BtbServiceCommit(&service) == BTB_IRQ_WRONG_STAGE);
    CHECK(service.committed == 0U && service.inFlight == 1U);
    CHECK(BtbServiceRecover(&service) == BTB_IRQ_OK);
    CHECK(service.committed == 0U && service.inFlight == 0U);
    CHECK(BtbServiceRecover(&service) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceBegin(&service, 1U) == BTB_IRQ_OK);
    CHECK(BtbServiceCommit(&service) == BTB_IRQ_OK);
    CHECK(BtbServiceBegin(&service, 1U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceBegin(&service, 2U) == BTB_IRQ_OK);
    CHECK(BtbServiceCommit(&service) == BTB_IRQ_OK);
    CHECK(service.committed == 2U && service.inFlight == 0U);
    CHECK(BtbServiceStop(&service) == BTB_IRQ_OK);
    CHECK(BtbServiceStop(&service) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceBegin(&service, 3U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbServiceStart(&service, 99U) == BTB_IRQ_WRONG_STAGE);
    puts("[OK] Accepted checkpoint retained; abandoned work must be retried deliberately.");
    return 0;
}
