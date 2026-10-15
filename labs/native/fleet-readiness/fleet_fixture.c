/* Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * Source identity and package checksum are fictional classroom constants. */
#include "fleet_fixture.h"
#include "operations_fixture.h"
#include <stdio.h>
#include <string.h>

static const char FLEET_REVISION[] = "0123456789abcdef0123456789abcdef01234567";
static const char FLEET_DIGEST[] =
    "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

int BtbFleetTrainingPolicy(BtbFleetPolicy *policy)
{
    if (policy == NULL) return 0;
    *policy = (BtbFleetPolicy){0};
    (void)snprintf(policy->sourceRevision, sizeof policy->sourceRevision,
                   "%s", FLEET_REVISION);
    (void)snprintf(policy->expectedPackageSha256,
                   sizeof policy->expectedPackageSha256, "%s", FLEET_DIGEST);
    (void)snprintf(policy->requiredHosts[0], sizeof policy->requiredHosts[0],
                   "%s", "notes-gateway");
    (void)snprintf(policy->requiredHosts[1], sizeof policy->requiredHosts[1],
                   "%s", "notes-storage");
    policy->hostCount = 2U;
    policy->reviewTimeSeconds = 1600U;
    policy->maximumEvidenceAgeSeconds = 120U;
    return 1;
}

int BtbFleetTrainingHost(BtbFleetHostEvidence *host, const char *hostId,
                         int operationsMode, int attachOperationsEvidence)
{
    if (host == NULL || hostId == NULL || strlen(hostId) >=
        sizeof host->hostId) return 0;
    *host = (BtbFleetHostEvidence){0};
    (void)snprintf(host->hostId, sizeof host->hostId, "%s", hostId);
    (void)snprintf(host->observedSourceRevision,
                   sizeof host->observedSourceRevision, "%s", FLEET_REVISION);
    (void)snprintf(host->observedPackageSha256,
                   sizeof host->observedPackageSha256, "%s", FLEET_DIGEST);
    host->observationId = 500U;
    host->observedSeconds = 1550U;
    host->filesystemReadable = 1;
    host->applicationOperationVerified = 1;
    host->clockSynchronised = 1;
    host->packageProvenanceReviewed = 1;
    host->independentReviewerAssigned = 1;
    host->evidenceRedacted = 1;
    return BtbOpsTrainingReview(&host->operations, operationsMode,
                                attachOperationsEvidence);
}

int BtbFleetTrainingReview(BtbFleetReview *review, size_t attachCount,
                           int mode)
{
    BtbFleetPolicy policy;
    size_t index;
    if (review == NULL || attachCount > 2U ||
        !BtbFleetTrainingPolicy(&policy) ||
        BtbFleetInit(review, &policy) != BTB_FLEET_OK) return 0;
    for (index = 0U; index < attachCount; ++index) {
        BtbFleetHostEvidence host;
        if (!BtbFleetTrainingHost(&host, policy.requiredHosts[index], mode, 1) ||
            BtbFleetAttach(review, &host) != BTB_FLEET_OK) return 0;
    }
    return 1;
}
