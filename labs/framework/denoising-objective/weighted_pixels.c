/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/weighted_pixels.c
 *
 * PURPOSE:
 *   Compare binary exclusion and normalized weights through actual native gradients and one update.
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
#include <stdlib.h>

int main(void)
{
    const float predictions[4]={1,2,3,4},targets[4]={0,0,0,0};
    float weights[4]={1,0,3,0};
    const unsigned char selection[4]={1,0,1,0};
    UmiAiTrainingTape *tape=NULL;
    UmiAiTrainingTensor *prediction=NULL,*target=NULL,*loss=NULL,*masked=NULL;
    UmiStatus status=UmiAiTrainingTapeCreate(&tape);
    float initial=0,selected=0,final=0,gradient[4]={0};
    UmiAiTrainingTapeMemory retained={0},weighted={0},after={0};
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingTensorCreate(tape,1,4,predictions,4,1,&prediction);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingTensorCreate(tape,1,4,targets,4,0,&target);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTapeMemoryInspect(tape,&retained);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingWeightedMeanSquaredError(tape,prediction,target,weights,4,&loss);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTensorValues(loss,&initial,1);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTapeMemoryInspect(tape,&weighted);
    /* The operator owns its own copy. Changes below must not change backward. */
    for(size_t i=0;i<4;++i)weights[i]=0;
    if(status==UMI_STATUS_OK) status=UmiAiTrainingBackward(tape,loss);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTensorGradients(prediction,gradient,4);
    if(status==UMI_STATUS_OK &&
       (initial!=7 || gradient[0]!=0.5F || gradient[1]!=0 ||
        gradient[2]!=4.5F || gradient[3]!=0 ||
        weighted.auxiliaryBytes-retained.auxiliaryBytes!=4U*sizeof(float)))
        status=UMI_STATUS_INVALID_STATE;
/* SGD updates an explicitly chosen trainable leaf. The earlier omitted-handle call is retained for review; the corrected call names the prediction parameter. The former implementation is retained for owner review. */
#if 0
    if(status==UMI_STATUS_OK) status=UmiAiTrainingSgdStep(tape,0.1F);
#endif
    if(status==UMI_STATUS_OK) status=UmiAiTrainingSgdStep(tape,prediction,0.1F);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTapeRewind(tape,2);
    weights[0]=1;weights[2]=3;
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingWeightedMeanSquaredError(tape,prediction,target,weights,4,&loss);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTensorValues(loss,&final,1);
    if(status==UMI_STATUS_OK && (!isfinite(final)||final>=initial)) status=UMI_STATUS_INVALID_STATE;
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTapeRewind(tape,2);
    if(status==UMI_STATUS_OK) status=UmiAiTrainingTapeMemoryInspect(tape,&after);
    if(status==UMI_STATUS_OK && (after.currentBytes!=retained.currentBytes ||
        after.auxiliaryBytes!=retained.auxiliaryBytes))status=UMI_STATUS_INVALID_STATE;
    /* A separate tape compares the initial binary selection, before any update. */
    UmiAiTrainingTapeDestroy(tape);tape=NULL;
    if(status==UMI_STATUS_OK)status=UmiAiTrainingTapeCreate(&tape);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingTensorCreate(tape,1,4,predictions,4,0,&prediction);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingTensorCreate(tape,1,4,targets,4,0,&target);
    if(status==UMI_STATUS_OK)
        status=UmiAiTrainingMaskedMeanSquaredError(tape,prediction,target,selection,4,&masked);
    if(status==UMI_STATUS_OK)status=UmiAiTrainingTensorValues(masked,&selected,1);
    if(status==UMI_STATUS_OK && selected!=5)status=UMI_STATUS_INVALID_STATE;
    if(status==UMI_STATUS_OK && printf(
        "Umicom weighted objective laboratory\n"
        "binary_selected_loss=%.6f normalized_weighted_loss=%.6f\n"
        "prediction_gradients=%.2f %.2f %.2f %.2f\n"
        "after_one_update=%.6f owned_weight_bytes=%zu\n",
        selected,initial,gradient[0],gradient[1],gradient[2],gradient[3],
        final,weighted.auxiliaryBytes-retained.auxiliaryBytes)<0)
        status=UMI_STATUS_IO_ERROR;
    if(status==UMI_STATUS_OK && fflush(stdout)!=0)status=UMI_STATUS_IO_ERROR;
    UmiAiTrainingTapeDestroy(tape);
    if(status!=UMI_STATUS_OK) {
        fprintf(stderr,"Weighted objective failed with status %d.\n",(int)status);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
