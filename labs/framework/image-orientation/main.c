/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-orientation/main.c
 *
 * PURPOSE:
 *   Compose borrowed crops, explicit RGB orientation and tensor packing through Framework services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_flip.h"
#include <stdio.h>
#include <string.h>
int main(void)
{
    const uint8_t pixels[]={
        255,0,0, 0,255,0, 0,0,255, 19,20,21,
        0,255,255, 255,0,255, 255,255,0
    };
    const UmiAiTrainingRgb8View source={pixels,sizeof pixels,3U,2U,12U};
    UmiAiTrainingRgb8View crop={0};uint8_t flipped[12],restored[12];float tensor[12];
    if(UmiAiTrainingImageCropRgb8(&source,1U,0U,2U,2U,&crop)!=UMI_STATUS_OK)return 1;
    if(UmiAiTrainingImageFlipRgb8(&crop,UMI_AI_TRAINING_FLIP_HORIZONTAL,
        flipped,sizeof flipped)!=UMI_STATUS_OK)return 2;
    const uint8_t expected[]={0,0,255, 0,255,0, 255,255,0, 255,0,255};
    if(memcmp(flipped,expected,sizeof expected)!=0)return 3;
    /* The output is packed. Its stride is crop.width*3, not source stride. */
    if(UmiAiTrainingImagePackRgb8(flipped,sizeof flipped,crop.width,crop.height,
        crop.width*3U,UMI_AI_TRAINING_IMAGE_HWC,UMI_AI_TRAINING_IMAGE_UNIT,
        tensor,12U)!=UMI_STATUS_OK)return 4;
    const float expectedTensor[]={0,0,1, 0,1,0, 1,1,0, 1,0,1};
    if(memcmp(tensor,expectedTensor,sizeof expectedTensor)!=0)return 5;
    const UmiAiTrainingRgb8View packed={flipped,sizeof flipped,2U,2U,6U};
    if(UmiAiTrainingImageFlipRgb8(&packed,UMI_AI_TRAINING_FLIP_HORIZONTAL,
        restored,sizeof restored)!=UMI_STATUS_OK)return 6;
    if(memcmp(restored,pixels+3U,6U)!=0 || memcmp(restored+6U,pixels+15U,6U)!=0)return 7;
    uint8_t before[sizeof flipped];memcpy(before,flipped,sizeof flipped);
    if(UmiAiTrainingImageFlipRgb8(&crop,8U,flipped,sizeof flipped)!=UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(before,flipped,sizeof flipped)!=0)return 8;
    printf("Borrowed crop: %zux%zu, stride %zu, readable span %zu bytes\n",
        crop.width,crop.height,crop.row_stride_bytes,crop.bytes);
    printf("Packed flipped RGB: %zu bytes, stride %zu\n",sizeof flipped,crop.width*3U);
    printf("HWC:");for(size_t i=0;i<12U;++i)printf(" %.0f",(double)tensor[i]);puts("");
    puts("Two horizontal flips restore the visible crop.");
    puts("Unknown transform refused without changing output.");
    puts("Synthetic pixels only: no decoder, caption rewrite, RNG, model or training.");
    return 0;
}
