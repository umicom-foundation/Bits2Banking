/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/adamw_decoder.c
 *
 * PURPOSE:
 *   Teach selected AdamW state, loss reduction and exact same-build checkpoint continuation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/optimizer.h"
#include "umicom/ai/training/optimizer_checkpoint.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This laboratory uses invented token IDs and one small CPU decoder. It trains
 * from a seed; it does not import a pretrained model or generate useful prose. */
int main(void)
{
    const UmiAiTrainingDecoderConfig geometry = {8,3,4,8,2,42};
    const size_t input[6] = {1,2,3,4,5,6}, target[6] = {2,3,4,5,6,7};
    const unsigned char attention[6] = {1,0,1,0,1,1};
    const unsigned char objective[6] = {0,0,1,0,0,1};
    UmiAiTrainingDecoder *model = NULL, *resumed = NULL;
    UmiAiTrainingAdamW *optimizer = NULL, *resumed_optimizer = NULL;
    UmiAiTrainingAdamWConfig options;
    UmiAiTrainingTapeMemory initial_memory, after;
    unsigned char *checkpoint = NULL, *comparison = NULL;
    size_t capacity = 0, written = 0, compared = 0, state_bytes = 0, final_bytes = 0;
    uint64_t steps = 0;
    float initial = 0, final = 0, original_loss = 0, resumed_loss = 0;
    UmiStatus status = UmiAiTrainingAdamWDefaults(&options);
    if (status == UMI_STATUS_OK) status = UmiAiTrainingDecoderCreate(&geometry, &model);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderAdamWCreate(model, &options, &optimizer);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderMemoryInspect(model, &initial_memory);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWInspect(optimizer, &steps, &state_bytes);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderEvaluatePadded(model, input, target, 6,
            attention, 6, objective, 6, &initial);
    for (size_t step = 0; status == UMI_STATUS_OK && step < 20; ++step)
        status = UmiAiTrainingDecoderTrainAdamWPaddedStep(model, optimizer,
            input, target, 6, attention, 6, objective, 6, 0.02F, &original_loss);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWCheckpointSize(model, optimizer, &capacity);
    if (status == UMI_STATUS_OK) {
        checkpoint = malloc(capacity);
        comparison = malloc(capacity);
        if (checkpoint == NULL || comparison == NULL) status = UMI_STATUS_OUT_OF_MEMORY;
    }
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWCheckpointEncode(model, optimizer,
            checkpoint, capacity, &written);
    /* Decoding publishes independently owned handles. Keep both originals
     * alive so identical future inputs can demonstrate the continuation rule. */
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWCheckpointDecode(checkpoint, written,
            &resumed, &resumed_optimizer);
    for (size_t step = 0; status == UMI_STATUS_OK && step < 20; ++step) {
        status = UmiAiTrainingDecoderTrainAdamWPaddedStep(model, optimizer,
            input, target, 6, attention, 6, objective, 6, 0.02F, &original_loss);
        if (status == UMI_STATUS_OK)
            status = UmiAiTrainingDecoderTrainAdamWPaddedStep(resumed, resumed_optimizer,
                input, target, 6, attention, 6, objective, 6, 0.02F, &resumed_loss);
        if (status == UMI_STATUS_OK && original_loss != resumed_loss)
            status = UMI_STATUS_INVALID_STATE;
    }
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWCheckpointEncode(model, optimizer,
            checkpoint, capacity, &written);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWCheckpointEncode(resumed, resumed_optimizer,
            comparison, capacity, &compared);
    if (status == UMI_STATUS_OK &&
        (written != compared || memcmp(checkpoint, comparison, written) != 0))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderEvaluatePadded(model, input, target, 6,
            attention, 6, objective, 6, &final);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingDecoderMemoryInspect(model, &after);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingAdamWInspect(optimizer, &steps, &final_bytes);
    if (status == UMI_STATUS_OK &&
        (!isfinite(final) || final >= initial || steps != 40 ||
         state_bytes != final_bytes ||
         after.currentBytes != initial_memory.currentBytes ||
         after.tensorCount != initial_memory.tensorCount ||
         after.auxiliaryBytes != initial_memory.auxiliaryBytes))
        status = UMI_STATUS_INVALID_STATE;
    if (status == UMI_STATUS_OK &&
        printf("Umicom selected AdamW laboratory\n"
               "scored_rows=2 total_rows=6 completed_steps=%llu\n"
               "initial_loss=%.6f final_loss=%.6f\n"
               "checkpoint_bytes=%zu resumed_state=identical\n"
               "retained_graph_bytes=%zu optimizer_state_bytes=%zu\n",
               (unsigned long long)steps, initial, final, written,
               after.currentBytes, final_bytes) < 0)
        status = UMI_STATUS_IO_ERROR;
    if (status == UMI_STATUS_OK && fflush(stdout) != 0) status = UMI_STATUS_IO_ERROR;
    free(comparison);
    free(checkpoint);
    /* Optimizers borrow their decoder's parameter handles: release them first. */
    UmiAiTrainingAdamWDestroy(resumed_optimizer);
    UmiAiTrainingDecoderDestroy(resumed);
    UmiAiTrainingAdamWDestroy(optimizer);
    UmiAiTrainingDecoderDestroy(model);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Selected AdamW laboratory refused the operation (status %d).\n", (int)status);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
