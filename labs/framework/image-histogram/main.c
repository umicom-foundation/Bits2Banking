/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-histogram/main.c
 *
 * PURPOSE:
 *   Measure a small RGB fixture through Framework and explain whole-image versus crop frequencies.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/image_histogram.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    const uint8_t pixels[]={0,10,255,64,20,255,64,20,128,
        128,30,128,255,40,0,255,40,0};
    const UmiAiTrainingRgb8View image={pixels,sizeof pixels,3U,2U,9U};
    UmiAiTrainingRgb8Histogram full;
    if(UmiAiTrainingImageHistogramRgb8(&image,&full)!=UMI_STATUS_OK)return 1;
    if(full.pixel_count!=6U || full.bins[0][0]!=1U || full.bins[0][64]!=2U ||
        full.bins[0][128]!=1U || full.bins[0][255]!=2U)return 2;
    puts("Umicom RGB histogram laboratory");
    printf("pixels=%zu\n",full.pixel_count);
    printf("red: 0=%" PRIu32 " 64=%" PRIu32 " 128=%" PRIu32 " 255=%" PRIu32 "\n",
        full.bins[0][0],full.bins[0][64],full.bins[0][128],full.bins[0][255]);
    /* A weighted count illustrates arithmetic on the shared report; it does
     * not reimplement histogram collection or estimate a whole dataset. */
    uint64_t redSum=0U;size_t redCount=0U;
    for(size_t value=0U;value<UMI_AI_TRAINING_RGB8_BINS;++value){
        redSum+=(uint64_t)value*full.bins[0][value];
        redCount+=full.bins[0][value];
    }
    if(redSum!=766U || redCount!=full.pixel_count)return 3;
    printf("red sum=%" PRIu64 "; mean=%.6f code units\n",redSum,(double)redSum/(double)redCount);
    UmiAiTrainingRgb8View crop;
    if(UmiAiTrainingImageCropRgb8(&image,1U,0U,2U,2U,&crop)!=UMI_STATUS_OK)return 4;
    UmiAiTrainingRgb8Histogram cropped;
    if(UmiAiTrainingImageHistogramRgb8(&crop,&cropped)!=UMI_STATUS_OK)return 5;
    if(cropped.pixel_count!=4U || cropped.bins[0][64]!=2U || cropped.bins[0][255]!=2U)return 6;
    printf("crop pixels=%zu; red 64=%" PRIu32 " 255=%" PRIu32 "\n",
        cropped.pixel_count,cropped.bins[0][64],cropped.bins[0][255]);
    UmiAiTrainingRgb8View shortImage=image;
    shortImage.bytes--;
    if(UmiAiTrainingImageHistogramRgb8(&shortImage,&cropped)!=UMI_STATUS_CAPACITY_EXCEEDED)return 7;
    if(cropped.pixel_count!=4U || cropped.bins[0][64]!=2U || cropped.bins[0][255]!=2U)return 8;
    puts("incomplete image refused; previous crop report retained");
    return 0;
}
