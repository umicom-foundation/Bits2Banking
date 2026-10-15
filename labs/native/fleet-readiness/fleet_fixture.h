/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * Deterministic fake inventory, never populated from real operating systems. */
#ifndef BTB_FLEET_FIXTURE_H
#define BTB_FLEET_FIXTURE_H
#include "fleet_readiness.h"
int BtbFleetTrainingPolicy(BtbFleetPolicy *policy);
int BtbFleetTrainingHost(BtbFleetHostEvidence *host, const char *hostId,
                         int operationsMode, int attachOperationsEvidence);
int BtbFleetTrainingReview(BtbFleetReview *review, size_t attachCount,
                           int mode);
#endif
