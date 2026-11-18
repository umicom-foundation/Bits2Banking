/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/borrowed-image-crop/main.c
 *
 * PURPOSE:
 *   Follow a borrowed RGB crop into shared tensor packing without an intermediate image.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_view.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Two rows of three RGB pixels. The first row has three padding bytes;
     * the final row needs no padding. These are original synthetic colors. */
    const uint8_t pixels[]={
        255,0,0, 0,255,0, 0,0,255, 19,20,21,
        0,255,255, 255,0,255, 255,255,0
    };
    const UmiAiTrainingRgb8View source={pixels,sizeof pixels,3U,2U,12U};
    UmiAiTrainingRgb8View crop={0};
    if(UmiAiTrainingImageCropRgb8(&source,1U,0U,2U,2U,&crop)!=UMI_STATUS_OK)
        return 1;
    if(crop.pixels!=pixels+3U || crop.bytes!=18U || crop.row_stride_bytes!=12U)
        return 2;
    printf("Source: %zu bytes; crop starts at byte 3\n",sizeof pixels);
    printf("Crop: %zu visible RGB bytes; %zu readable span bytes\n",
        crop.width*crop.height*3U,crop.bytes);
    printf("Original row stride: %zu bytes\n",crop.row_stride_bytes);

    /* Only the model-facing float tensor is materialized. The input image
     * remains owned by this stack frame throughout the synchronous call. */
    float tensor[12];
    const float expected[]={0,1,0, 0,0,1, 1,0,1, 1,1,0};
    if(UmiAiTrainingImagePackRgb8(crop.pixels,crop.bytes,crop.width,crop.height,
        crop.row_stride_bytes,UMI_AI_TRAINING_IMAGE_HWC,
        UMI_AI_TRAINING_IMAGE_UNIT,tensor,12U)!=UMI_STATUS_OK)
        return 3;
    if(memcmp(tensor,expected,sizeof expected)!=0) return 4;
    printf("HWC:");
    for(size_t i=0;i<12U;++i) printf(" %.0f",(double)tensor[i]);
    printf("\nTensor storage: %zu bytes\n",sizeof tensor);

    const UmiAiTrainingRgb8View saved=crop;
    if(UmiAiTrainingImageCropRgb8(&source,3U,0U,1U,1U,&crop)!=UMI_STATUS_INVALID_ARGUMENT)
        return 5;
    if(crop.pixels!=saved.pixels || crop.bytes!=saved.bytes || crop.width!=saved.width ||
        crop.height!=saved.height || crop.row_stride_bytes!=saved.row_stride_bytes)
        return 6;
    puts("Outside rectangle refused; previous view retained.");
    puts("No decoder, pixel allocation, resize, model or training was run.");
    return 0;
}
