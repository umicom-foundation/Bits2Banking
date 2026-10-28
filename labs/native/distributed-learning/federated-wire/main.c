/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/distributed-learning/federated-wire/main.c
 *
 * PURPOSE:
 *   Teach how a tiny verified assignment and synthetic result cross a
 *   canonical binary interface before existing Framework job aggregation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_wire.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    UmiAiTrainingFederatedWireRecord request = {0};
    request.kind = UMI_AI_FEDERATED_WIRE_ASSIGNMENT;
    request.roundId = UINT64_C(41);
    request.sequence = UINT64_C(1);
    request.assignment.contributorId[0] = 1U;
    request.assignment.baseCheckpointSha256[0] = 88U;
    request.assignment.datasetCommitmentSha256[0] = 101U;
    request.assignment.dataPolicySha256[0] = 99U;
    request.assignment.distinctSampleCount = UINT64_C(100);
    request.assignment.localSteps = UINT64_C(2);
    request.assignment.declaredTransferBytes = 256U;
    uint8_t bytes[UMI_AI_FEDERATED_WIRE_MAX_BYTES] = {0};
    size_t written = 0U;
    if (UmiAiTrainingFederatedWireEncode(&request, bytes,
        sizeof(bytes), &written) != UMI_STATUS_OK || written != 216U)
        return 1;

    UmiAiTrainingFederatedWireRecord received = {0};
    if (UmiAiTrainingFederatedWireDecode(bytes, written,
        &received, NULL, 0U) != UMI_STATUS_OK ||
        received.assignment.distinctSampleCount != UINT64_C(100))
        return 2;

    /* A synthetic worker produces a fixed scalar. No neural-network
     * training or authorised real dataset access occurs in this laboratory. */
    const float toyDelta = 0.05F;
    received.kind = UMI_AI_FEDERATED_WIRE_RESULT;
    received.delta = &toyDelta;
    received.deltaCount = 1U;
    if (UmiAiTrainingFederatedWireEncode(&received, bytes,
        sizeof(bytes), &written) != UMI_STATUS_OK || written != 220U)
        return 3;
    float decoded = -1.0F;
    UmiAiTrainingFederatedWireRecord result = {0};
    if (UmiAiTrainingFederatedWireDecode(bytes, written,
        &result, &decoded, 1U) != UMI_STATUS_OK ||
        UmiAiTrainingFederatedWireMatchResult(&result,
        &request.assignment, request.roundId, request.sequence) != UMI_STATUS_OK ||
        fabsf(decoded-toyDelta) > 0.000001F)
        return 4;

    UmiMessageEnvelope envelope = {0};
    if (UmiAiTrainingFederatedWireBindEnvelope(bytes,
        written, &envelope) != UMI_STATUS_OK ||
        envelope.kind != UMI_MESSAGE_REPLY ||
        envelope.payload_data != bytes)
        return 5;
    puts("C23 lab: assignment 216 bytes, synthetic result 220 bytes,"
         " identity and Framework envelope verified");
    return 0;
}
