/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/operations_fixture.c
 * PURPOSE: Build safe training records by reusing Update 44 fixture functions.
 *---------------------------------------------------------------------------*/
#include "operations_fixture.h"
#include "training_fixture.h"
#include <stdio.h>

int BtbOpsTrainingPolicy(BtbOpsPolicy *policy)
{
    if (policy == NULL) return 0;
    *policy = (BtbOpsPolicy){0};
    (void)snprintf(policy->serviceId, sizeof policy->serviceId, "%s", "notes-demo");
    (void)snprintf(policy->sourceRevision, sizeof policy->sourceRevision, "%s",
                   "0123456789abcdef0123456789abcdef01234567");
    policy->reviewStartSeconds = 1200U;
    policy->reviewEndSeconds = 1800U;
    policy->maximumHeartbeatAgeSeconds = 180U;
    policy->maximumBackupAgeSeconds = 400U;
    policy->maximumRestoreDrillAgeSeconds = 500U;
    policy->maximumDataLossSeconds = 300U;
    policy->maximumRecoveryDurationSeconds = 300U;
    policy->maximumQueuedJobs = 5U;
    return 1;
}

int BtbOpsTrainingEvidence(BtbOpsEvidence *evidence)
{
    if (evidence == NULL) return 0;
    *evidence = (BtbOpsEvidence){0};
    evidence->captureId = 450U;
    evidence->observedSeconds = 1500U;
    (void)snprintf(evidence->observedSourceRevision,
                   sizeof evidence->observedSourceRevision, "%s",
                   "0123456789abcdef0123456789abcdef01234567");
    evidence->lastHealthySeconds = 1420U;
    evidence->lastVerifiedBackupSeconds = 1300U;
    evidence->lastSuccessfulRestoreDrillSeconds = 1250U;
    evidence->estimatedDataLossSeconds = 120U;
    evidence->measuredRecoverySeconds = 180U;
    evidence->queuedJobs = 2U;
    evidence->alertRouteTested = 1;
    evidence->onCallOwnerAssigned = 1;
    evidence->independentRestoreVerified = 1;
    evidence->auditEvidenceRedacted = 1;
    return 1;
}

int BtbOpsTrainingReview(BtbOpsReview *review, int upstreamMode, int attachEvidence)
{
    BtbSecurityReview security;
    BtbOpsPolicy policy;
    BtbOpsEvidence evidence;
    if (review == NULL || (attachEvidence != 0 && attachEvidence != 1) ||
        !BtbSecurityTrainingComplete(&security, upstreamMode) ||
        !BtbOpsTrainingPolicy(&policy) ||
        BtbOpsInit(review, &policy, &security) != BTB_OPS_OK)
        return 0;
    if (attachEvidence == 0) return 1;
    return BtbOpsTrainingEvidence(&evidence) &&
        BtbOpsAttach(review, &evidence) == BTB_OPS_OK;
}
