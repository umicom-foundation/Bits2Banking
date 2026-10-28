/*-----------------------------------------------------------------------------
 * Bits to Banking
 * File: labs/native/distributed-learning/anchored-evidence/main.c
 *
 * PURPOSE:
 *   Demonstrate an authorised synthetic federated round using reusable
 *   Framework C23 record-chain evidence and count-bound Merkle inclusion.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_evidence_anchor.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    uint8_t id[32] = {0x55U};
    uint8_t digests[3U * 32U] = {0};
    uint8_t payload[UMI_AI_FEDERATED_EVIDENCE_ANCHOR_BYTES] = {0};
    UmiRecordChainCheckpoint prior, expected;
    UmiRecordChainRecord record = {0};
    UmiRecordChainMerkleProof proof = {0};
    UmiAiTrainingFederatedEvidenceSummary summary = {0};
    UmiAiTrainingFederatedEvidenceView view = {0};
    for (size_t i = 0U; i < 3U; ++i) {
        digests[i * 32U] = (uint8_t)(i + 1U);
        digests[i * 32U + 31U] = (uint8_t)(i + 7U);
    }
    summary.roundId = UINT64_C(99);
    summary.submittedCount = UINT64_C(4);
    summary.acceptedCount = 3U;
    summary.baseCheckpointSha256[0] = 0x21U;
    summary.datasetPolicySha256[0] = 0x31U;
    summary.heldOutEvaluationSha256[0] = 0x41U;
    if (umi_record_chain_start(id, &prior) != UMI_STATUS_OK) return 1;
    expected = prior;
    if (UmiAiTrainingFederatedEvidenceAnchorCommit(&expected,
        &summary, digests, 3U, &record, payload) != UMI_STATUS_OK) return 2;
    if (UmiAiTrainingFederatedEvidenceAnchorProve(digests,
        3U, 1U, payload, &proof) != UMI_STATUS_OK) return 3;
    if (UmiAiTrainingFederatedEvidenceAnchorVerify(&prior, &record,
        payload, sizeof payload, &expected, digests + 32U,
        &proof, &view) != UMI_STATUS_OK) return 4;
    if (view.summary.acceptedCount != 3U || view.summary.submittedCount != 4U) return 5;
    /* Preserve an independent copy of the anchored root. Tampering a leaf
     * fails without needing a copy of the original three-item dataset. */
    uint8_t tampered[32];
    memcpy(tampered, digests + 32U, sizeof tampered);
    tampered[0] ^= 1U;
    if (UmiAiTrainingFederatedEvidenceAnchorVerify(&prior, &record,
        payload, sizeof payload, &expected, tampered,
        &proof, &view) == UMI_STATUS_OK) return 6;
    puts("Anchored synthetic evidence: three accepted receipts, inclusion valid, tampering rejected.");
    puts("This exercise does not perform real model training, identity signing or blockchain consensus.");
    return 0;
}
