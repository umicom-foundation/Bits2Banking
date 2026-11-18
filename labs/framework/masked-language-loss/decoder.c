/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/decoder.c
 *
 * PURPOSE:
 *   Train a small native decoder on selected target positions while checking graph ownership after every step.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/decoder.h"
#include <math.h>
#include <stdio.h>

/* Integer IDs represent a tiny made-up vocabulary. They are already aligned:
 * each target is the token following its input position. No tokenizer, role
 * parser, network call or model download occurs in this teaching program. */
int main(void)
{
    const UmiAiTrainingDecoderConfig config = {8U, 3U, 4U, 8U, 2U, 42U};
    const size_t inputs[6] = {1U, 2U, 3U, 4U, 5U, 6U};
    const size_t targets[6] = {2U, 3U, 4U, 5U, 6U, 7U};
    const unsigned char selected[6] = {0U, 0U, 1U, 0U, 1U, 1U};
    UmiAiTrainingDecoder *model = NULL;
    UmiAiTrainingTapeMemory baseline, current;
    UmiAiTrainingDecoderConfig inspected;
    uint64_t steps = 0U;
    float before = 0.0F, trainingLoss = 0.0F, after = 0.0F;
    UmiStatus status = UmiAiTrainingDecoderCreate(&config, &model);
    if (status != UMI_STATUS_OK) goto finish;
    status = UmiAiTrainingDecoderMemoryInspect(model, &baseline);
    if (status != UMI_STATUS_OK) goto finish;
    status = UmiAiTrainingDecoderEvaluateMasked(model, inputs, targets, 6U,
        selected, 6U, &before);
    if (status != UMI_STATUS_OK) goto finish;
    for (size_t step = 0U; step < 40U; ++step) {
        status = UmiAiTrainingDecoderTrainMaskedStep(model, inputs, targets, 6U,
            selected, 6U, 0.05F, &trainingLoss);
        if (status != UMI_STATUS_OK) goto finish;
        status = UmiAiTrainingDecoderMemoryInspect(model, &current);
        if (status != UMI_STATUS_OK) goto finish;
        if (current.currentBytes != baseline.currentBytes ||
            current.tensorCount != baseline.tensorCount) {
            fputs("Temporary graph storage was not released.\n", stderr);
            status = UMI_STATUS_INVALID_ARGUMENT;
            goto finish;
        }
    }
    status = UmiAiTrainingDecoderEvaluateMasked(model, inputs, targets, 6U,
        selected, 6U, &after);
    if (status != UMI_STATUS_OK) goto finish;
    status = UmiAiTrainingDecoderInspect(model, &inspected, &steps);
    if (status != UMI_STATUS_OK) goto finish;
    if (steps != 40U || !isfinite(before) || !isfinite(after) || after >= before) {
        fputs("The fixed teaching fixture did not meet its expected outcome.\n", stderr);
        status = UMI_STATUS_INVALID_ARGUMENT;
        goto finish;
    }
    printf("Selected targets: 3 of 6; completed SGD steps: %llu\n",
        (unsigned long long)steps);
    printf("Selected-target loss before: %.6f; after: %.6f\n", before, after);
    printf("Persistent graph bytes: %zu; observed graph peak: %zu\n",
        current.currentBytes, current.peakBytes);
    puts("This memorizes a tiny fixture; it does not establish language quality.");
finish:
    UmiAiTrainingDecoderDestroy(model);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Training lesson failed with status %d.\n", (int)status);
        return 1;
    }
    return 0;
}
