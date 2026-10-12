/* Bits2Banking | Umicom Foundation | C23 fictional driver-lifetime demonstration | MIT */
#include "driver.h"
#include <stdio.h>
int main(void)
{
    BtbDriver driver = {0};
    if (BtbDriverStart(&driver, 28U) != BTB_IRQ_OK ||
        BtbDriverComplete(&driver, 100U) != BTB_IRQ_OK ||
        BtbDriverFail(&driver, 101U) != BTB_IRQ_OK ||
        BtbDriverReviewAndRecover(&driver, 101U) != BTB_IRQ_OK ||
        BtbDriverComplete(&driver, 101U) != BTB_IRQ_OK ||
        BtbDriverStop(&driver) != BTB_IRQ_OK) {
        fputs("Fictional driver lifecycle failed.\n", stderr);
        return 1;
    }
    printf("Driver stopped. Accepted revision: %u. Reviewed faults: %u.\n",
           driver.service.committed, driver.reviewedFaults);
    return 0;
}
