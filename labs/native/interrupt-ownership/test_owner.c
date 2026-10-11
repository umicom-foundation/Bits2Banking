/* Bits2Banking — C23 Interrupt-Ownership Tests | Umicom Foundation | MIT */
#include "owner.h"
#include <stdio.h>
#define CHECK(x) do {if (!(x)) {fprintf(stderr,"FAIL: %s:%d %s\n",__FILE__,__LINE__,#x);return 1;}} while(0)
int main(void)
{
    BtbIrqDomain domain = {0};
    BtbIrqLease token = {0}, next = {0};
    CHECK(BtbIrqArm(&domain, token) == BTB_IRQ_NOT_INITIALISED ||
          BtbIrqArm(&domain, token) == BTB_IRQ_INVALID_ARGUMENT);
    CHECK(BtbIrqInitialize(&domain) == BTB_IRQ_OK);
    CHECK(BtbIrqInitialize(&domain) == BTB_IRQ_WRONG_STAGE);
    BtbIrqDomain copied = domain;
    BtbIrqLease unused = {0};
    CHECK(BtbIrqClaim(&copied, 1U, 4U, 1U, &unused) == BTB_IRQ_NOT_INITIALISED);
    CHECK(BtbIrqClaim(&domain, 1U, 50U, 1U, &token) == BTB_IRQ_OK);
    const BtbIrqLease saved = token;
    CHECK(BtbIrqClaim(&domain, 1U, 55U, 2U, &next) == BTB_IRQ_WRONG_STAGE);
    CHECK(next.source == 0U);
    BtbIrqLease wrongOwner = token;
    wrongOwner.owner = 99U;
    CHECK(BtbIrqArm(&domain, wrongOwner) == BTB_IRQ_WRONG_OWNER);
    BtbIrqStage stage = BTB_IRQ_FREE;
    CHECK(BtbIrqReadStage(&domain, token, &stage) == BTB_IRQ_OK && stage == BTB_IRQ_LEASED);
    CHECK(BtbIrqArm(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqRelease(&domain, token) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbIrqEnter(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqCancel(&domain, token) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbIrqAcknowledge(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqReturn(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqArm(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqEnter(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqFault(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqRelease(&domain, token) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbIrqRecover(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqRecover(&domain, token) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbIrqRelease(&domain, token) == BTB_IRQ_OK);
    CHECK(BtbIrqArm(&domain, saved) == BTB_IRQ_STALE_LEASE);
    CHECK(BtbIrqClaim(&domain, 1U, 55U, 1U, &next) == BTB_IRQ_WRONG_STAGE);
    CHECK(BtbIrqClaim(&domain, 1U, 55U, 2U, &next) == BTB_IRQ_OK);
    CHECK(BtbIrqArm(&domain, saved) == BTB_IRQ_STALE_LEASE);
    CHECK(BtbIrqReadStage(&domain, next, &stage) == BTB_IRQ_OK && stage == BTB_IRQ_LEASED);
    CHECK(BtbIrqRelease(&domain, next) == BTB_IRQ_OK);
    puts("[OK] Ownership and stale leases cannot bypass state transitions.");
    return 0;
}
