/* Bits2Banking | Umicom Foundation | driver-lifetime contracts and recoverability | MIT */
#include "driver.h"
#include <stdio.h>
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr,"Failed at line %d: %s\n",__LINE__,#condition);return 1;} \
} while (0)
int main(void)
{
    BtbDriver driver = {0};
    CHECK(BtbDriverStart(&driver, 0U) == BTB_IRQ_INVALID_ARGUMENT);
    CHECK(BtbDriverStart(&driver, 47U) == BTB_IRQ_OK);
    CHECK(BtbDriverStart(&driver, 47U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverComplete(&driver, 10U) == BTB_IRQ_OK);
    CHECK(driver.service.committed == 10U);
    CHECK(BtbDriverComplete(&driver, 9U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverFail(&driver, 11U) == BTB_IRQ_OK);
    CHECK(driver.stage == BTB_DRIVER_FAULTED);
    CHECK(driver.service.committed == 10U && driver.service.inFlight == 11U);
    CHECK(BtbDriverStop(&driver) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverComplete(&driver, 12U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverReviewAndRecover(&driver, 12U) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverReviewAndRecover(&driver, 11U) == BTB_IRQ_OK);
    CHECK(driver.service.committed == 10U && driver.service.inFlight == 0U);
    CHECK(BtbDriverComplete(&driver, 11U) == BTB_IRQ_OK);
    CHECK(driver.service.committed == 11U && driver.reviewedFaults == 1U);
    CHECK(BtbDriverStop(&driver) == BTB_IRQ_OK);
    CHECK(BtbDriverStop(&driver) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbDriverStart(&driver, 99U) == BTB_IRQ_WRONG_STAGE);
    puts("Driver lifetime: accepted work protected; retry explicitly reviewed.");
    return 0;
}
