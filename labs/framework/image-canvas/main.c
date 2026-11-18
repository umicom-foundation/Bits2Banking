/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-canvas/main.c
 *
 * PURPOSE:
 *   Observe explicit border pixels and tensor values through shared Framework services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/image_canvas.h"
#include "umicom/ai/training/image_histogram.h"
#include <stdio.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr,"Check failed: %s\n",#x); return 1; } } while(0)

int main(void)
{
    const uint8_t sourcePixels[6]={255,255,255,255,255,255};
    const uint8_t border[3]={0,0,0};
    const UmiAiTrainingRgb8View source={sourcePixels,sizeof sourcePixels,2,1,6};
    uint8_t canvas[36],saved[36];
    float tensor[36];
    REQUIRE(UmiAiTrainingImageCanvasRgb8(&source,4,3,1,1,border,
        canvas,sizeof canvas)==UMI_STATUS_OK);
    const UmiAiTrainingRgb8View prepared={canvas,sizeof canvas,4,3,12};
    UmiAiTrainingRgb8Histogram counts;
    REQUIRE(UmiAiTrainingImageHistogramRgb8(&prepared,&counts)==UMI_STATUS_OK);
    REQUIRE(counts.bins[0][0]==10 && counts.bins[0][255]==2);
    printf("Canvas: 12 pixels, red bin 0=%u, red bin 255=%u\n",
        (unsigned)counts.bins[0][0],(unsigned)counts.bins[0][255]);
    REQUIRE(UmiAiTrainingImagePackRgb8(canvas,sizeof canvas,4,3,12,
        UMI_AI_TRAINING_IMAGE_CHW,UMI_AI_TRAINING_IMAGE_SIGNED_UNIT,
        tensor,36)==UMI_STATUS_OK);
    for(size_t c=0;c<3;++c) for(size_t p=0;p<12;++p)
        REQUIRE(tensor[c*12+p]==((p==5||p==6)?1.0f:-1.0f));
    puts("Black border becomes -1 in the signed-unit tensor, not a loss mask.");
    for(size_t i=0;i<sizeof sourcePixels;++i) REQUIRE(sourcePixels[i]==255);
    memcpy(saved,canvas,sizeof saved);
    REQUIRE(UmiAiTrainingImageCanvasRgb8(&source,4,3,1,1,border,
        canvas,sizeof canvas-1)==UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(saved,canvas,sizeof canvas)==0);
    puts("A short output span was refused; the previous canvas is unchanged.");
    return 0;
}
