/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-histogram/moments.c
 *
 * PURPOSE:
 *   Measure RGB channel distributions without confusing variance with brightness or training normalization.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_moments.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const uint8_t pixels[]={0U,10U,255U,255U,30U,255U};
    const UmiAiTrainingRgb8View view={pixels,sizeof(pixels),2U,1U,6U};
    UmiAiTrainingRgb8Moments moments;
    if(UmiAiTrainingImageMeasureRgb8(&view,&moments)!=UMI_STATUS_OK)return 1;
    if(moments.pixel_count!=2U || moments.mean[0]!=127.5 ||
        moments.population_variance[0]!=16256.25 || moments.mean[1]!=20.0 ||
        moments.population_variance[1]!=100.0 || moments.mean[2]!=255.0 ||
        moments.population_variance[2]!=0.0)return 2;
    const char *channels[]={"red","green","blue"};
    puts("Umicom RGB channel statistics");
    for(size_t c=0U;c<3U;++c)
        printf("%s: mean=%.2f; population variance=%.2f; minimum=%u; maximum=%u\n",
            channels[c],moments.mean[c],moments.population_variance[c],
            (unsigned)moments.minimum[c],(unsigned)moments.maximum[c]);
    puts("Blue is constant. Dividing by its zero standard deviation is not a normalization policy.");
    /* A histogram may be caller-supplied, so inconsistent later-channel counts
     * must fail without replacing a previously complete result. */
    UmiAiTrainingRgb8Histogram histogram;
    if(UmiAiTrainingImageHistogramRgb8(&view,&histogram)!=UMI_STATUS_OK)return 3;
    UmiAiTrainingRgb8Moments before=moments;
    ++histogram.bins[2][0];
    if(UmiAiTrainingImageHistogramMoments(&histogram,&moments)!=UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(&before,&moments,sizeof(moments))!=0)return 4;
    puts("Inconsistent histogram refused; prior moments preserved.");
    puts("No image normalization, model fitting or training was performed.");
    return ferror(stdout)?5:0;
}
