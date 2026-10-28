/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/distributed-learning/federated-audit/main.c
 *
 * PURPOSE:
 *   Exercise the existing native Framework record-chain audit adapter with a
 *   synthetic research decision and independently checked final checkpoint.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_audit_chain.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const uint8_t chainId[32] = {0x42U, 0x69U, 0x74U, 0x73U};
    UmiRecordChainCheckpoint writer = {0}, reader = {0};
    UmiRecordChainRecord record = {0};
    uint8_t payload[UMI_AI_FEDERATED_AUDIT_PAYLOAD_BYTES] = {0};
    UmiAiTrainingFederatedAuditEvidence evidence = {0}, observed = {0};
    evidence.roundId = 2U;
    evidence.workerSequence = 1U;
    evidence.distinctSamples = 100U;
    evidence.outcome = UMI_AI_FEDERATED_AUDIT_ACCEPTED;
    memset(evidence.contributorId, 1, 32U);
    memset(evidence.baseCheckpointSha256, 2, 32U);
    memset(evidence.datasetCommitmentSha256, 3, 32U);
    memset(evidence.policySha256, 4, 32U);
    memset(evidence.updateCommitmentSha256, 5, 32U);
    memset(evidence.evaluationCommitmentSha256, 6, 32U);
    if (UmiAiTrainingFederatedAuditStart(chainId, &writer) != UMI_STATUS_OK)
        return 1;
    reader = writer;
    if (UmiAiTrainingFederatedAuditAppend(&writer, &evidence,
        &record, payload) != UMI_STATUS_OK) return 2;
    if (UmiAiTrainingFederatedAuditAccept(&reader, &record,
        payload, sizeof(payload), &observed) != UMI_STATUS_OK) return 3;
    if (!umi_record_chain_checkpoint_equal(&writer, &reader)) return 4;
    if (observed.distinctSamples != 100U) return 5;
    puts("Bits2Banking: synthetic audit chain verified; consensus not claimed");
    return 0;
}
