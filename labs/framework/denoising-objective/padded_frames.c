/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/padded_frames.c
 *
 * PURPOSE:
 *   Compare full and selected-value objectives for synthetic unequal-length clips through the shared training tape.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/tape.h"
#include <math.h>
#include <stdio.h>

typedef struct Measurement {
    float completeLoss;
    float selectedLoss;
    float gradients[6];
    float updated[6];
    size_t maskBytes;
} Measurement;

/* Two clips occupy three slots each. Clip A has three observed scalar frames;
 * clip B has one. The last two slots are storage padding, not observations.
 * Real frames would require a validity byte for every channel being scored. */
static UmiStatus Measure(float paddingValue, Measurement *out)
{
    const float predictionValues[6] = {1, 2, 3, 4, paddingValue, paddingValue};
    const float targetValues[6] = {0, 0, 0, 0, 0, 0};
    const unsigned char observed[6] = {1, 1, 1, 1, 0, 0};
    UmiAiTrainingTape *tape = NULL;
    UmiAiTrainingTensor *prediction = NULL, *target = NULL;
    UmiAiTrainingTensor *complete = NULL, *selected = NULL;
    UmiAiTrainingTapeMemory before = {0}, after = {0};
    Measurement candidate = {0};
    UmiStatus status = UmiAiTrainingTapeCreate(&tape);
    if (status != UMI_STATUS_OK) return status;
    status = UmiAiTrainingTensorCreate(tape, 2U, 3U, predictionValues, 6U, 1, &prediction);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTensorCreate(tape, 2U, 3U, targetValues, 6U, 0, &target);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingMeanSquaredError(tape, prediction, target, &complete);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTensorValues(complete, &candidate.completeLoss, 1U);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTapeMemoryInspect(tape, &before);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingMaskedMeanSquaredError(tape, prediction, target, observed, 6U, &selected);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTensorValues(selected, &candidate.selectedLoss, 1U);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTapeMemoryInspect(tape, &after);
    if (status != UMI_STATUS_OK) goto done;
    candidate.maskBytes = after.auxiliaryBytes - before.auxiliaryBytes;
    /* Backward starts from the selected scalar. Merely computing the complete
     * scalar for comparison does not give that independent result a weight. */
    status = UmiAiTrainingBackward(tape, selected);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTensorGradients(prediction, candidate.gradients, 6U);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingSgdStep(tape, prediction, 0.1F);
    if (status != UMI_STATUS_OK) goto done;
    status = UmiAiTrainingTensorValues(prediction, candidate.updated, 6U);
    if (status == UMI_STATUS_OK) *out = candidate;
done:
    UmiAiTrainingTapeDestroy(tape);
    return status;
}
static int Close(float actual, float expected)
{ return fabsf(actual - expected) < 0.00001F; }
int main(void)
{
    Measurement zeroPadding = {0}, otherPadding = {0};
    if (Measure(0, &zeroPadding) != UMI_STATUS_OK || Measure(9, &otherPadding) != UMI_STATUS_OK) {
        fputs("Framework could not complete the bounded loss exercise.\n", stderr);
        return 1;
    }
    if (zeroPadding.completeLoss != 5 || otherPadding.completeLoss != 32 ||
        zeroPadding.selectedLoss != 7.5F || otherPadding.selectedLoss != 7.5F ||
        zeroPadding.maskBytes != 6U || otherPadding.maskBytes != 6U) return 2;
    const float gradients[6] = {0.5F, 1, 1.5F, 2, 0, 0};
    for (size_t i = 0U; i < 6U; ++i) {
        if (zeroPadding.gradients[i] != gradients[i] || otherPadding.gradients[i] != gradients[i]) return 3;
        if (i < 4U && (!Close(zeroPadding.updated[i], (float)(i + 1U) * 0.95F) ||
            !Close(otherPadding.updated[i], zeroPadding.updated[i]))) return 4;
    }
    if (zeroPadding.updated[4] != 0 || zeroPadding.updated[5] != 0 ||
        otherPadding.updated[4] != 9 || otherPadding.updated[5] != 9) return 5;
    puts("Umicom Framework: synthetic padded-frame objective");
    puts("Padding 0: complete mean = 5.000000; observed-value mean = 7.500000");
    puts("Padding 9: complete mean = 32.000000; observed-value mean = 7.500000");
    puts("Selected gradients: 0.5 1.0 1.5 2.0 0.0 0.0");
    puts("One prediction update: 0.95 1.90 2.85 3.80; padding unchanged");
    puts("Selection storage: 6 bytes; this is not total process memory");
    return fflush(stdout) == 0 ? 0 : 6;
}
