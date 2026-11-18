/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/padded_decoder.c
 *
 * PURPOSE:
 *   Teach independent decoder context and objective selections with bounded repeated native SGD steps.
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
#include <stdlib.h>
#include <string.h>

/* Integer IDs are invented vocabulary entries. This small program teaches
 * tensor/data policy; it does not tokenize documents or adapt an external LLM. */
int main(void)
{
    const UmiAiTrainingDecoderConfig config = {8, 3, 4, 8, 2, 42};
    const size_t input[6] = {1, 2, 3, 4, 5, 6};
    const size_t changed_padding[6] = {1, 7, 3, 0, 5, 6};
    const size_t targets[6] = {2, 3, 4, 5, 6, 7};
    const unsigned char attention[6] = {1, 0, 1, 0, 1, 1};
    const unsigned char objective[6] = {0, 0, 1, 0, 0, 1};
    UmiAiTrainingDecoder *model = NULL;
    UmiAiTrainingTapeMemory initial_memory, after;
    float first = 0, last = 0, pre_update = 0, original[48], changed[48];
    UmiStatus status = UmiAiTrainingDecoderCreate(&config, &model);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderMemoryInspect(model, &initial_memory);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderLogitsPadded(model, input, 6,
            attention, 6, original, 48);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderLogitsPadded(model, changed_padding, 6,
            attention, 6, changed, 48);
    if (status == UMI_STATUS_OK && memcmp(original, changed, sizeof original))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderEvaluatePadded(model, input, targets, 6,
            attention, 6, objective, 6, &first);
    for (size_t step = 0; status == UMI_STATUS_OK && step < 40; ++step) {
        status = UmiAiTrainingDecoderTrainPaddedStep(model, input, targets, 6,
            attention, 6, objective, 6, 0.03F, &pre_update);
        if (status == UMI_STATUS_OK)
            status = UmiAiTrainingDecoderMemoryInspect(model, &after);
        if (status == UMI_STATUS_OK &&
            (after.currentBytes != initial_memory.currentBytes ||
             after.tensorCount != initial_memory.tensorCount ||
             after.auxiliaryBytes != initial_memory.auxiliaryBytes))
            status = UMI_STATUS_INVALID_STATE;
    }
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderEvaluatePadded(model, input, targets, 6,
            attention, 6, objective, 6, &last);
    if (status == UMI_STATUS_OK && (!isfinite(first) || !isfinite(last) || last >= first))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK) {
        printf("Selected objective before: %.6f; after: %.6f\n", (double)first, (double)last);
        printf("Last step returned pre-update loss: %.6f\n", (double)pre_update);
        puts("Changing padding IDs left selected logits unchanged.");
        printf("Forty SGD steps released temporary graphs; retained bytes: %zu\n",
            initial_memory.currentBytes);
    } else {
        fprintf(stderr, "Padded decoder lesson refused with status %d\n", (int)status);
    }
    UmiAiTrainingDecoderDestroy(model);
    return status == UMI_STATUS_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}
