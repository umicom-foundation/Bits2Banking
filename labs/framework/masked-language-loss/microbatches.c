/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/microbatches.c
 *
 * PURPOSE:
 *   Measure selected-target reduction and graph lifetime through the canonical decoder.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/gradient_accumulation.h"
#include "umicom/ai/training/capacity_plan.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Keep one owner for each borrowed model/optimizer pair. Cleanup is valid even
 * after partial creation; the optimizer must be released before the decoder. */
typedef struct Experiment {
    UmiAiTrainingDecoder *model;
    UmiAiTrainingAdamW *optimizer;
} Experiment;
static UmiStatus create(Experiment *experiment)
{
    const UmiAiTrainingDecoderConfig geometry={8,3,4,8,2,42};
    UmiAiTrainingAdamWConfig options;
    UmiStatus status=UmiAiTrainingAdamWDefaults(&options);
    *experiment=(Experiment){0};
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderCreate(&geometry,&experiment->model);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderAdamWCreate(experiment->model,&options,&experiment->optimizer);
    return status;
}
static void destroy(Experiment *experiment)
{
    UmiAiTrainingAdamWDestroy(experiment->optimizer);
    UmiAiTrainingDecoderDestroy(experiment->model);
}
int main(void)
{
    const size_t input[15]={1,2,3,4,5,6,1,3,5,2,4,6,0,2,4};
    const size_t target[15]={2,3,4,5,6,7,2,4,6,3,5,7,1,3,5};
    const unsigned char attention[15]={1,0,1,1,0,1,1,1,1,0,1,1,1,0,1};
    const unsigned char objective[15]={0,0,0,1,0,0,1,1,1,0,1,1,0,0,0};
    Experiment whole={0},micro={0};
    float full_loss=0,first_loss=0,last_loss=0;
    UmiAiTrainingTapeMemory full_memory={0},micro_memory={0},after={0};
    uint64_t updates=0;
    size_t optimizer_bytes=0;
    const UmiAiTrainingDecoderConfig geometry={8,3,4,8,2,42};
    UmiAiTrainingAccumulationPlan plan;
    UmiStatus status=UmiAiTrainingAccumulationPlanCompute(&geometry,5,1,&plan);
    if(status==UMI_STATUS_OK) status=create(&whole);
    if(status==UMI_STATUS_OK) status=create(&micro);
    /* The first and final sequences have no scored targets. One call still
     * represents all five sequences and publishes exactly one weight update. */
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderTrainAdamWPaddedStep(whole.model,whole.optimizer,
            input,target,15,attention,15,objective,15,0.02F,&full_loss);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderTrainAdamWPaddedAccumulated(micro.model,micro.optimizer,
            input,target,15,1,attention,15,objective,15,0.02F,&first_loss);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderMemoryInspect(whole.model,&full_memory);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingDecoderMemoryInspect(micro.model,&micro_memory);
    if(status==UMI_STATUS_OK &&
       (fabsf(full_loss-first_loss)>2e-6F || micro_memory.peakBytes>=full_memory.peakBytes ||
        micro_memory.currentBytes!=full_memory.currentBytes))
        status=UMI_STATUS_INVALID_STATE;
    for(size_t i=0;status==UMI_STATUS_OK && i<40;++i) {
        status=UmiAiTrainingDecoderTrainAdamWPaddedAccumulated(micro.model,micro.optimizer,
            input,target,15,1,attention,15,objective,15,0.02F,&last_loss);
        if(status==UMI_STATUS_OK)
            status=UmiAiTrainingDecoderMemoryInspect(micro.model,&after);
        if(status==UMI_STATUS_OK &&
           (after.currentBytes!=micro_memory.currentBytes ||
            after.tensorCount!=micro_memory.tensorCount ||
            after.auxiliaryBytes!=micro_memory.auxiliaryBytes))
            status=UMI_STATUS_INVALID_STATE;
    }
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingAdamWInspect(micro.optimizer,&updates,&optimizer_bytes);
    if(status==UMI_STATUS_OK &&
       (updates!=41U || !isfinite(last_loss) || last_loss>=first_loss))
        status=UMI_STATUS_INVALID_STATE;
    if(status==UMI_STATUS_OK && printf(
        "Umicom selected microbatch laboratory\n"
        "sequences=5 scored_targets=6 microbatch_sequences=1 updates=%llu\n"
        "first_loss=%.6f last_preupdate_loss=%.6f\n"
        "full_tape_peak=%zu micro_tape_peak=%zu retained_tape=%zu\n"
        "optimizer_state=%zu (additional to tape; reducer and allocator memory excluded)\n",
        (unsigned long long)updates,first_loss,last_loss,
        full_memory.peakBytes,micro_memory.peakBytes,micro_memory.currentBytes,
        optimizer_bytes)<0) status=UMI_STATUS_IO_ERROR;
    if(status==UMI_STATUS_OK && printf("planned_reducer_payload=%zu maximum_graphs=%zu largest_parameter=%zu\n",
        plan.peakReductionPayloadBytes,plan.maximumGraphs,plan.largestParameterElements)<0)
        status=UMI_STATUS_IO_ERROR;
    if(status==UMI_STATUS_OK && fflush(stdout)!=0) status=UMI_STATUS_IO_ERROR;
    destroy(&micro);destroy(&whole);
    if(status!=UMI_STATUS_OK) {
        fprintf(stderr,"Microbatch laboratory failed with status %d.\n",(int)status);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
