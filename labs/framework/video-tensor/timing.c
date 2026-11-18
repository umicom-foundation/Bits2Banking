/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/video-tensor/timing.c
 *
 * PURPOSE:
 *   Compare explicit presentation-time sampling with index stepping and pack selected borrowed pixels.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/video_timing.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    /* Four original one-pixel frames and their microsecond presentation times.
     * This array is already decoded; no media file or model is opened. */
    const uint8_t pixels[4][3]={{0,0,0},{255,0,0},{0,255,0},{0,0,255}};
    const uint64_t sourceTimes[4]={0U,40000U,100000U,160000U};
    const uint64_t queries[4]={0U,50000U,100000U,150000U};
    const size_t expected[4]={0U,1U,2U,2U};
    size_t byTime[4],byIndex[4];
    if(UmiAiTrainingVideoSelectAtOrBefore(sourceTimes,4U,queries,4U,byTime,4U)!=UMI_STATUS_OK ||
        memcmp(byTime,expected,sizeof expected)!=0)return 1;
    if(UmiAiTrainingVideoSelectFrames(4U,0U,1U,4U,byIndex,4U)!=UMI_STATUS_OK)return 2;
    for(size_t i=0U;i<4U;++i)if(byIndex[i]!=i)return 3;
    UmiAiTrainingVideoFrame frames[4];
    for(size_t i=0U;i<4U;++i)frames[i]=(UmiAiTrainingVideoFrame){pixels[byTime[i]],3U,3U};
    float tensor[12];const float expectedTensor[12]={0,0,0,1,0,0,0,1,0,0,1,0};
    if(UmiAiTrainingVideoPackRgb8(frames,4U,1U,1U,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,tensor,12U)!=UMI_STATUS_OK ||
        memcmp(tensor,expectedTensor,sizeof tensor)!=0)return 4;
    const uint64_t outside[2]={50000U,200000U};size_t before[4];memcpy(before,byTime,sizeof before);
    if(UmiAiTrainingVideoSelectAtOrBefore(sourceTimes,4U,outside,2U,byTime,4U)!=UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(before,byTime,sizeof before)!=0)return 5;
    if(puts("Index step: 0 1 2 3")<0 || puts("Time hold: 0 1 2 2")<0 ||
        puts("The green frame is selected twice; source pixels remain borrowed.")<0 ||
        printf("Tensor: 12 values, %zu bytes; late out-of-range query refused atomically.\n",sizeof tensor)<0 ||
        puts("No decoder, timestamp conversion, model or training was run.")<0)return 6;
    return 0;
}
