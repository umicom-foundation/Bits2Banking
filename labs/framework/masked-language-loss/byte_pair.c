/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/byte_pair.c
 *
 * PURPOSE:
 *   Train a tiny copied byte-pair example through Framework preparation and padded decoder services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/byte_pair_sequence.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const uint8_t prompt[]={'Q',':'}, completion[]={'A'};
    UmiAiTrainingBytePairSequence sample;
    UmiStatus status=UmiAiTrainingBytePairPrepare(prompt,sizeof prompt,
        completion,sizeof completion,8U,&sample);
    if(status!=UMI_STATUS_OK) return EXIT_FAILURE;
    printf("Context rows: %zu; valid rows: %zu; selected targets: %zu\n",
        sample.context_length,sample.valid_rows,sample.selected_rows);
    puts("row input target attention selected");
    for(size_t i=0U;i<sample.context_length;++i)
        printf("%zu %zu %zu %u %u\n",i,sample.inputs[i],sample.targets[i],
            (unsigned)sample.attention[i],(unsigned)sample.selected[i]);
    if(sample.valid_rows!=4U || sample.selected_rows!=2U ||
        sample.targets[2]!=69U || sample.targets[3]!=UMI_AI_BYTE_EOS ||
        sample.selected[1]!=0U || sample.selected[2]!=1U) return EXIT_FAILURE;

    /* This is a new tiny byte-vocabulary model, not an imported coding LLM.
     * The sample already owns shifted targets; do not shift them a second time. */
    const UmiAiTrainingDecoderConfig config={UMI_AI_BYTE_VOCABULARY,8U,4U,8U,2U,42U};
    UmiAiTrainingDecoder *model=NULL;
    UmiAiTrainingTapeMemory initial,after;
    float first=0.0F,last=0.0F,preUpdate=0.0F;
    status=UmiAiTrainingDecoderCreate(&config,&model);
    if(status==UMI_STATUS_OK)status=UmiAiTrainingDecoderMemoryInspect(model,&initial);
    if(status==UMI_STATUS_OK)status=UmiAiTrainingDecoderEvaluatePadded(model,
        sample.inputs,sample.targets,sample.context_length,sample.attention,sample.context_length,
        sample.selected,sample.context_length,&first);
    for(size_t step=0U;status==UMI_STATUS_OK && step<40U;++step) {
        status=UmiAiTrainingDecoderTrainPaddedStep(model,sample.inputs,sample.targets,
            sample.context_length,sample.attention,sample.context_length,
            sample.selected,sample.context_length,0.03F,&preUpdate);
        if(status==UMI_STATUS_OK)status=UmiAiTrainingDecoderMemoryInspect(model,&after);
        if(status==UMI_STATUS_OK && (after.currentBytes!=initial.currentBytes ||
            after.tensorCount!=initial.tensorCount || after.auxiliaryBytes!=initial.auxiliaryBytes))
            status=UMI_STATUS_INVALID_STATE;
    }
    if(status==UMI_STATUS_OK)status=UmiAiTrainingDecoderEvaluatePadded(model,
        sample.inputs,sample.targets,sample.context_length,sample.attention,sample.context_length,
        sample.selected,sample.context_length,&last);
    if(status==UMI_STATUS_OK && (!isfinite(first)||!isfinite(last)||last>=first))
        status=UMI_STATUS_INVALID_STATE;
    if(status==UMI_STATUS_OK) {
        printf("Selected loss before: %.6f; after: %.6f\n",(double)first,(double)last);
        printf("Forty steps retained %zu tape bytes after graph cleanup.\n",initial.currentBytes);
        puts("This repeats one example; lower training loss is not held-out quality or a trained assistant.");
    } else fprintf(stderr,"Byte-pair lesson refused with status %d\n",(int)status);
    UmiAiTrainingDecoderDestroy(model);
    return status==UMI_STATUS_OK?EXIT_SUCCESS:EXIT_FAILURE;
}
