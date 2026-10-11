/* Bits2Banking — C23 Interrupt-Ownership Laboratory | Umicom Foundation | MIT */
#include "owner.h"
#include <stdio.h>
int main(void)
{
    BtbIrqDomain domain = {0};
    BtbIrqLease lease = {0};
    if (BtbIrqInitialize(&domain) != BTB_IRQ_OK ||
        BtbIrqClaim(&domain, 1U, 20U, 1U, &lease) != BTB_IRQ_OK ||
        BtbIrqArm(&domain, lease) != BTB_IRQ_OK ||
        BtbIrqEnter(&domain, lease) != BTB_IRQ_OK ||
        BtbIrqAcknowledge(&domain, lease) != BTB_IRQ_OK ||
        BtbIrqReturn(&domain, lease) != BTB_IRQ_OK ||
        BtbIrqRelease(&domain, lease) != BTB_IRQ_OK) return 1;
    puts("Learning interrupt source 1: claim, arm, enter, acknowledge, return, release.");
    puts("No real interrupt or hardware register was touched.");
    return 0;
}
