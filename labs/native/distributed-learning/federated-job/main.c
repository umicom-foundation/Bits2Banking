/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/distributed-learning/federated-job/main.c
 *
 * PURPOSE:
 *   Teach three synthetic worker admissions and use the installed Framework
 *   federated-round mathematics through the native C23 job API. Demonstrate
 *   one rejected stale ticket without duplicating the aggregation algorithm.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_job.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const uint64_t sampleCount[3] = {100U, 250U, 150U};
    const float delta[3] = {0.05F, -0.01F, 0.08F};
    UmiAiTrainingFederatedJobConfig config = {0};
    UmiAiTrainingFederatedJob *job = NULL;
    UmiAiTrainingFederatedTicket ticket = {0};
    UmiAiTrainingFederatedRoundReport aggregate = {0};
    UmiAiTrainingFederatedJobReport jobState = {0};
    float result = -1234.0F;
    int ok = 0;
    config.round.parameterCount = 1U;
    config.round.maximumContributors = 3U;
    config.round.maximumDeltaL2Norm = 1.0F;
    memset(config.round.baseCheckpointSha256, 0x21, 32U);
    memset(config.dataPolicySha256, 0x31, 32U);
    config.roundId = UINT64_C(1001);
    config.maximumLocalSteps = UINT64_C(32);
    config.maximumSamplesPerAssignment = UINT64_C(500);
    config.maximumTransferBytesPerAssignment = 32U;
    config.maximumReservedTransferBytes = 32U;
    if (UmiAiTrainingFederatedJobCreate(&config, &job) != UMI_STATUS_OK)
        return 1;
    for (size_t i = 0U; i < 3U; ++i) {
        UmiAiTrainingFederatedAssignment a = {0};
        UmiAiTrainingFederatedContribution c = {0};
        memset(a.contributorId, (int)(i + 1U), 32U);
        memset(a.datasetCommitmentSha256, (int)(i + 11U), 32U);
        memcpy(a.baseCheckpointSha256, config.round.baseCheckpointSha256, 32U);
        memcpy(a.dataPolicySha256, config.dataPolicySha256, 32U);
        a.distinctSampleCount = sampleCount[i];
        a.localSteps = 12U;
        a.declaredTransferBytes = 16U;
        if (UmiAiTrainingFederatedJobAdmit(job, &a, &ticket) != UMI_STATUS_OK)
            goto cleanup;
        memcpy(c.contributorId, a.contributorId, 32U);
        memcpy(c.baseCheckpointSha256, a.baseCheckpointSha256, 32U);
        memcpy(c.datasetCommitmentSha256, a.datasetCommitmentSha256, 32U);
        c.distinctSampleCount = a.distinctSampleCount;
        c.weightSpaceDelta = &delta[i];
        c.deltaCount = 1U;
        if (UmiAiTrainingFederatedJobComplete(job, ticket, &c) != UMI_STATUS_OK)
            goto cleanup;
        /* A closed ticket must not count the update a second time. */
        if (UmiAiTrainingFederatedJobComplete(job, ticket, &c) !=
            UMI_STATUS_INVALID_STATE) goto cleanup;
    }
    if (UmiAiTrainingFederatedJobFinalise(job, &result, 1U, &aggregate) !=
        UMI_STATUS_OK) goto cleanup;
    if (UmiAiTrainingFederatedJobInspect(job, &jobState) != UMI_STATUS_OK)
        goto cleanup;
    if (fabsf(result - 0.029F) > 0.000001F ||
        aggregate.totalDistinctSamples != UINT64_C(500) ||
        jobState.completedAssignments != 3U ||
        jobState.pendingAssignments != 0U ||
        jobState.peakReservedTransferBytes != 16U) goto cleanup;
    printf("FedAvg candidate delta: %.6f\n", (double)result);
    puts("Three synthetic workers completed; no model was trained or published.");
    ok = 1;
cleanup:
    UmiAiTrainingFederatedJobDestroy(job);
    return ok ? 0 : 1;
}
