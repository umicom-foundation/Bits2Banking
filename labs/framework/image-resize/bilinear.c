/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-resize/bilinear.c
 *
 * PURPOSE:
 *   Compare explicit nearest and bilinear image policies through shared bounded Framework services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_resize.h"
#include <stdio.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr,"Check failed: %s\n",#x); return 1; } } while (0)
int main(void)
{
    /* This constant array is already decoded RGB data. Its view borrows it;
     * every output has separate storage and the source remains alive. */
    const uint8_t pixels[]={0,10,20, 100,110,120, 200,210,220, 240,250,255};
    const UmiAiTrainingRgb8View source={pixels,sizeof pixels,2,2,6};
    uint8_t nearest[3],bilinear[3],saved[3];
    REQUIRE(UmiAiTrainingImageResizeNearestRgb8(&source,1,1,nearest,sizeof nearest)==UMI_STATUS_OK);
    REQUIRE(UmiAiTrainingImageResizeBilinearRgb8(&source,1,1,bilinear,sizeof bilinear)==UMI_STATUS_OK);
    REQUIRE(nearest[0]==240 && nearest[1]==250 && nearest[2]==255);
    REQUIRE(bilinear[0]==135 && bilinear[1]==145 && bilinear[2]==154);
    printf("Nearest center: %u %u %u\n",(unsigned)nearest[0],(unsigned)nearest[1],(unsigned)nearest[2]);
    printf("Bilinear center: %u %u %u\n",(unsigned)bilinear[0],(unsigned)bilinear[1],(unsigned)bilinear[2]);
    memcpy(saved,bilinear,sizeof saved);
    REQUIRE(UmiAiTrainingImageResizeBilinearRgb8(&source,1,1,bilinear,2)==UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(saved,bilinear,sizeof saved)==0);
    puts("Short output leaves the previous image unchanged.");
    /* The four-neighbor footprint does not widen when shrinking. Six
     * alternating columns shrink onto exact centers 1 and 4. */
    const uint8_t stripe[]={0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255};
    const UmiAiTrainingRgb8View stripes={stripe,sizeof stripe,6,1,18};
    uint8_t reduced[6];
    REQUIRE(UmiAiTrainingImageResizeBilinearRgb8(&stripes,2,1,reduced,sizeof reduced)==UMI_STATUS_OK);
    REQUIRE(reduced[0]==255 && reduced[3]==0);
    printf("Six stripes to two: %u %u; no area antialiasing.\n",(unsigned)reduced[0],(unsigned)reduced[3]);
    return 0;
}
