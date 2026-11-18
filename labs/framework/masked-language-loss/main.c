/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/main.c
 *
 * PURPOSE:
 *   Observe selected-token loss and one toy score update through Framework-owned differentiation.
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

int main(void)
{
    UmiAiTrainingTape *tape = NULL;
    UmiAiTrainingTensor *scores = NULL, *loss = NULL;
    /* Four score rows and three possible target classes. These are invented
     * numbers, not token IDs from an actual language model or chat template. */
    const float initial[12] = {0};
    const size_t targets[4] = {2U, 1U, 0U, 2U};
    const unsigned char selected[4] = {0U, 0U, 1U, 1U};
    float before = 0.0F, after = 0.0F, gradients[12];
    int result = 1;
    if (UmiAiTrainingTapeCreate(&tape) != UMI_STATUS_OK) goto finish;
    if (UmiAiTrainingTensorCreate(tape, 4U, 3U, initial, 12U, 1, &scores) != UMI_STATUS_OK) goto finish;
    if (UmiAiTrainingMaskedCrossEntropy(tape, scores, targets, 4U, selected, 4U, &loss) != UMI_STATUS_OK) goto finish;
    if (UmiAiTrainingTensorValues(loss, &before, 1U) != UMI_STATUS_OK) goto finish;
    if (fabs((double)before - log(3.0)) > 1e-6) goto finish;
    if (UmiAiTrainingBackward(tape, loss) != UMI_STATUS_OK) goto finish;
    if (UmiAiTrainingTensorGradients(scores, gradients, 12U) != UMI_STATUS_OK) goto finish;
    for (size_t i = 0U; i < 6U; ++i) if (gradients[i] != 0.0F) goto finish;
    if (gradients[6] >= 0.0F || gradients[11] >= 0.0F) goto finish;
    if (UmiAiTrainingSgdStep(tape, scores, 0.1F) != UMI_STATUS_OK) goto finish;
    /* Rewind invalidates the previous loss handle. Retain the original score
     * leaf and build a fresh objective after changing its values. */
    if (UmiAiTrainingTapeRewind(tape, 1U) != UMI_STATUS_OK) goto finish;
    loss = NULL;
    if (UmiAiTrainingMaskedCrossEntropy(tape, scores, targets, 4U, selected, 4U, &loss) != UMI_STATUS_OK) goto finish;
    if (UmiAiTrainingTensorValues(loss, &after, 1U) != UMI_STATUS_OK || !(after < before)) goto finish;
    printf("Selected rows: 2 of 4; loss %.7f -> %.7f\n", (double)before, (double)after);
    puts("Excluded score rows received zero gradient from this objective.");
    puts("Toy score update only: no tokenizer, pretrained model, files or network.");
    result = 0;
finish:
    UmiAiTrainingTapeDestroy(tape);
    if (result) fputs("Loss exercise failed; inspect the first refused operation or value check.\n", stderr);
    return result;
}
