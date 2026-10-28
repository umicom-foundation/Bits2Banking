/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/distributed-learning/federated-auth/main.c
 *
 * PURPOSE:
 *   Demonstrate HMAC authentication and tamper rejection by consuming the
 *   installed Framework native APIs with deterministic synthetic inputs.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_authenticated_frame.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const uint8_t educationKey[32] = {0x45,0x44,0x55,0x43,0x41,0x54,0x49,0x4f,
        0x4e,0x2d,0x4b,0x45,0x59,0x2d,0x4f,0x4e,0x4c,0x59,0x2d,0x4e,0x4f,
        0x54,0x2d,0x41,0x2d,0x53,0x45,0x43,0x52,0x45,0x54,0x21};
    const float syntheticDelta=0.125F;
    UmiAiTrainingFederatedWireRecord sample={0}, decoded={0};
    uint8_t wire[UMI_AI_FEDERATED_WIRE_MAX_BYTES]={0};
    uint8_t protected[UMI_AI_FEDERATED_AUTH_MAX_BYTES]={0};
    size_t wireCount=0U, authCount=0U;
    float observed=-1.0F;
    sample.kind=UMI_AI_FEDERATED_WIRE_RESULT;
    sample.roundId=100U;
    sample.sequence=1U;
    memset(sample.assignment.contributorId,1,32U);
    memset(sample.assignment.baseCheckpointSha256,2,32U);
    memset(sample.assignment.datasetCommitmentSha256,3,32U);
    memset(sample.assignment.dataPolicySha256,4,32U);
    sample.assignment.distinctSampleCount=10U;
    sample.assignment.localSteps=1U;
    sample.assignment.declaredTransferBytes=64U;
    sample.delta=&syntheticDelta;
    sample.deltaCount=1U;
    if (UmiAiTrainingFederatedWireEncode(&sample,wire,sizeof(wire),&wireCount)!=UMI_STATUS_OK ||
        UmiAiTrainingFederatedAuthSeal(wire,wireCount,2U,educationKey,
            sizeof(educationKey),protected,sizeof(protected),&authCount)!=UMI_STATUS_OK ||
        UmiAiTrainingFederatedAuthOpen(protected,authCount,2U,educationKey,
            sizeof(educationKey),&decoded,&observed,1U)!=UMI_STATUS_OK ||
        observed!=syntheticDelta) return 1;
    protected[UMI_AI_FEDERATED_AUTH_HEADER_BYTES+30U]^=1U;
    observed=-1.0F;
    if (UmiAiTrainingFederatedAuthOpen(protected,authCount,2U,educationKey,
            sizeof(educationKey),&decoded,&observed,1U)!=UMI_STATUS_PERMISSION_DENIED ||
        observed!=-1.0F) return 2;
    puts("Synthetic C23 authenticated frame accepted; tamper refused; not a LAN or proof-of-training test.");
    return 0;
}
