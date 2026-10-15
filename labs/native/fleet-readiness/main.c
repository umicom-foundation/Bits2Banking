/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * Offline multi-host review demonstration. Does not inspect any real machine. */
#include "fleet_fixture.h"
#include <stdio.h>

int main(void)
{
    BtbFleetReview review;
    BtbFleetDecision decision;
    if (!BtbFleetTrainingReview(&review, 1U, 0) ||
        BtbFleetEvaluate(&review, &decision) != BTB_FLEET_OK) return 1;
    (void)printf("Before second host: %s (missing=%zu)\n",
                 BtbFleetStatusText(decision.status), decision.missingCount);
    if (!BtbFleetTrainingReview(&review, 2U, 0) ||
        BtbFleetEvaluate(&review, &decision) != BTB_FLEET_OK) return 1;
    (void)printf("Both hosts independently reviewed: %s\n",
                 BtbFleetStatusText(decision.status));
    review.hosts[1].applicationOperationVerified = 0;
    if (BtbFleetEvaluate(&review, &decision) != BTB_FLEET_OK) return 1;
    (void)printf("User-facing Notes storage operation fails: %s\n",
                 BtbFleetStatusText(decision.status));
    if (!BtbFleetTrainingReview(&review, 2U, 2) ||
        BtbFleetEvaluate(&review, &decision) != BTB_FLEET_OK) return 1;
    (void)printf("Previous release restored after failed change: %s\n",
                 BtbFleetStatusText(decision.status));
    return decision.status == BTB_FLEET_RESTORED_ONLY ? 0 : 1;
}
