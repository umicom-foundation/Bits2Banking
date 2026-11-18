/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-resize/main.c
 *
 * PURPOSE:
 *   Observe irreversible nearest-neighbor information loss through shared Framework resize and histogram services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_resize.h"
#include "umicom/ai/training/image_histogram.h"
#include <stdio.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr,"Check failed: %s\n",#x); return 1; } } while(0)
int main(void)
{
    /* Original decoded pixels stay alive while both borrowed views are used.
     * Separate arrays make the source/destination ownership contract visible. */
    const uint8_t stripes[]={0,0,0,255,255,255,0,0,0,255,255,255};
    const UmiAiTrainingRgb8View source={stripes,sizeof stripes,4,1,12};
    uint8_t small[6], restored[12], saved[6];
    REQUIRE(UmiAiTrainingImageResizeNearestRgb8(&source,2,1,small,sizeof small)==UMI_STATUS_OK);
    const UmiAiTrainingRgb8View reduced={small,sizeof small,2,1,6};
    UmiAiTrainingRgb8Histogram originalCounts,reducedCounts;
    REQUIRE(UmiAiTrainingImageHistogramRgb8(&source,&originalCounts)==UMI_STATUS_OK);
    REQUIRE(UmiAiTrainingImageHistogramRgb8(&reduced,&reducedCounts)==UMI_STATUS_OK);
    REQUIRE(originalCounts.bins[0][0]==2 && originalCounts.bins[0][255]==2);
    REQUIRE(reducedCounts.bins[0][0]==0 && reducedCounts.bins[0][255]==2);
    printf("Original red bins: 0=%u 255=%u\n",(unsigned)originalCounts.bins[0][0],
        (unsigned)originalCounts.bins[0][255]);
    printf("Reduced red bins: 0=%u 255=%u\n",(unsigned)reducedCounts.bins[0][0],
        (unsigned)reducedCounts.bins[0][255]);
    REQUIRE(UmiAiTrainingImageResizeNearestRgb8(&reduced,4,1,restored,sizeof restored)==UMI_STATUS_OK);
    REQUIRE(memcmp(restored,stripes,sizeof stripes)!=0);
    puts("Upsampling does not restore the missing dark pixels.");
    memcpy(saved,small,sizeof saved);
    REQUIRE(UmiAiTrainingImageResizeNearestRgb8(&source,2,1,small,sizeof small-1)==UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(small,saved,sizeof small)==0);
    puts("Insufficient output capacity was refused without changing the previous image.");
    return 0;
}
