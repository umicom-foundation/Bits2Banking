/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/video-tensor/main.c
 *
 * PURPOSE:
 *   Select two explicit decoded frames and inspect shared Framework temporal tensor layouts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/video_tensor.h"
#include <stdio.h>
#include <string.h>
static int print_values(const char *label, const float *values, size_t count)
{
    if (printf("%s",label)<0)return 1;
    for(size_t i=0;i<count;++i)if(printf(" %.0f",(double)values[i])<0)return 1;
    return puts("")<0?1:0;
}
int main(void)
{
    /* Four original two-pixel frames are already decoded RGB8. Real codecs
     * and source timing are outside this small array-based exercise. */
    const uint8_t pixels[4][6]={
        {0,0,0,0,0,0}, {255,0,0,0,255,0},
        {255,255,0,255,0,255}, {0,0,255,255,255,255}
    };
    size_t indices[2]={91U,93U};
    if(UmiAiTrainingVideoSelectFrames(4,1,2,2,indices,2)!=UMI_STATUS_OK ||
        indices[0]!=1U || indices[1]!=3U)return 1;
    UmiAiTrainingImageSpan span;
    if(UmiAiTrainingImageDescribeRgb8(2,1,6,&span)!=UMI_STATUS_OK ||
        span.required_bytes!=6U || span.value_count!=6U)return 2;
    UmiAiTrainingVideoFrame selected[2];
    for(size_t i=0;i<2;++i)selected[i]=(UmiAiTrainingVideoFrame){pixels[indices[i]],6,6};
    float values[12];
    const float thwc[]={1,0,0,0,1,0, 0,0,1,1,1,1};
    const float tchw[]={1,0,0,1,0,0, 0,1,0,1,1,1};
    if(printf("Selected source frames: %zu %zu\n",indices[0],indices[1])<0 ||
        printf("Float storage: %zu bytes (%zu values)\n",sizeof values,span.value_count*2U)<0)return 3;
    if(UmiAiTrainingVideoPackRgb8(selected,2,2,1,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,values,12)!=UMI_STATUS_OK ||
        memcmp(values,thwc,sizeof values)!=0 || print_values("THWC:",values,12))return 4;
    if(UmiAiTrainingVideoPackRgb8(selected,2,2,1,UMI_AI_TRAINING_IMAGE_CHW,
        UMI_AI_TRAINING_IMAGE_UNIT,values,12)!=UMI_STATUS_OK ||
        memcmp(values,tchw,sizeof values)!=0 || print_values("TCHW:",values,12))return 5;
    /* A later bad frame must not replace a previously successful tensor. */
    selected[1].rgb_bytes=5U;
    if(UmiAiTrainingVideoPackRgb8(selected,2,2,1,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,values,12)!=UMI_STATUS_CAPACITY_EXCEEDED ||
        memcmp(values,tchw,sizeof values)!=0)return 6;
    if(puts("Short final frame refused; previous tensor unchanged.")<0)return 7;
    if(puts("No decoder, frame-rate conversion, model or training was run.")<0)return 8;
    return 0;
}
