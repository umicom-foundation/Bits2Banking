/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/video-tensor/output.c
 *
 * PURPOSE:
 *   Convert two explicit output frames and demonstrate whole-clip refusal without a decoder or model.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/video_tensor.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    /* Two two-pixel frames in THWC order. These are teaching values, not a
     * generated model result. Each frame borrows a separate writable buffer. */
    float values[12]={1,0,0,0,1,0,0,0,1,0.5f,0.5f,0.5f};
    uint8_t first[8],second[8];memset(first,91,sizeof first);memset(second,91,sizeof second);
    const UmiAiTrainingVideoRgb8Output frames[2]={{first,sizeof first,6},{second,sizeof second,6}};
    const uint8_t expectedFirst[8]={255,0,0,0,255,0,91,91};
    const uint8_t expectedSecond[8]={0,0,255,128,128,128,91,91};
    if(UmiAiTrainingVideoUnpackRgb8(values,12,2,2,1,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,UMI_AI_TRAINING_IMAGE_REJECT_OUTSIDE,frames)!=UMI_STATUS_OK ||
        memcmp(first,expectedFirst,sizeof first)!=0 || memcmp(second,expectedSecond,sizeof second)!=0)return 1;
    uint8_t savedFirst[8],savedSecond[8];memcpy(savedFirst,first,sizeof first);memcpy(savedSecond,second,sizeof second);
    /* Changing the first proposed pixel makes partial publication detectable.
     * A bad final channel must preserve BOTH previously displayed frames. */
    values[0]=0;values[11]=NAN;
    if(UmiAiTrainingVideoUnpackRgb8(values,12,2,2,1,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,UMI_AI_TRAINING_IMAGE_CLIP_OUTSIDE,frames)!=UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(first,savedFirst,sizeof first)!=0 || memcmp(second,savedSecond,sizeof second)!=0)return 2;
    if(puts("Frame 0: red, green")<0 || puts("Frame 1: blue, gray (128)")<0 ||
        puts("A bad final value preserved both earlier output buffers.")<0 ||
        puts("Padding stayed unchanged. No video file or model was produced.")<0)return 3;
    return 0;
}
