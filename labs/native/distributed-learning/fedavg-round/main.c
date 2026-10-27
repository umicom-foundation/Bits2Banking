/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/distributed-learning/fedavg-round/main.c
 *
 * PURPOSE:
 *   Exercise the installed Framework federated aggregation service with
 *   synthetic worker updates and transparent arithmetic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/federated_round.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    UmiAiTrainingFederatedRoundConfig config = {0};
    UmiAiTrainingFederatedRound *round = NULL;
    const float updates[3] = {0.05F, -0.01F, 0.08F};
    const uint64_t counts[3] = {100U, 250U, 150U};
    config.parameterCount = 1U;
    config.maximumContributors = 3U;
    config.maximumDeltaL2Norm = 1.0F;
    config.baseCheckpointSha256[0] = 0x41U; /* Synthetic test identity. */
    if (UmiAiTrainingFederatedRoundCreate(&config, &round) != UMI_STATUS_OK)
        return 1;
    for (size_t index = 0U; index < 3U; ++index) {
        UmiAiTrainingFederatedContribution c = {0};
        c.contributorId[0] = (uint8_t)(index + 1U);
        c.datasetCommitmentSha256[0] = (uint8_t)(index + 11U);
        memcpy(c.baseCheckpointSha256, config.baseCheckpointSha256, 32U);
        c.distinctSampleCount = counts[index];
        c.weightSpaceDelta = &updates[index];
        c.deltaCount = 1U;
        if (UmiAiTrainingFederatedRoundSubmit(round, &c) != UMI_STATUS_OK) {
            UmiAiTrainingFederatedRoundDestroy(round);
            return 1;
        }
    }
    float delta = 0.0F;
    const UmiStatus status = UmiAiTrainingFederatedRoundFinalise(
        round, &delta, 1U, NULL);
    if (status == UMI_STATUS_OK)
        printf("Synthetic model weight: 1.000 + %.3f = %.3f\n",
               (double)delta, 1.0 + (double)delta);
    const int numericallyCorrect = status == UMI_STATUS_OK &&
        delta > 0.028999F && delta < 0.029001F;
    UmiAiTrainingFederatedRoundDestroy(round);
    return numericallyCorrect ? 0 : 1;
}
