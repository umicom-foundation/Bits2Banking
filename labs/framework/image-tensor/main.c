/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-tensor/main.c
 *
 * PURPOSE:
 *   Inspect one original RGB image as HWC and CHW arrays using the shared Framework converter.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_tensor.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Top row: red, green. Bottom row: blue, white. The two padding bytes
     * between rows are not pixels; no final-row padding is present. */
    const uint8_t rgb[] = {255,0,0, 0,255,0, 99,88, 0,0,255, 255,255,255};
    float hwc[12], chw[12];
    const float expectedHwc[] = {1,0,0, 0,1,0, 0,0,1, 1,1,1};
    const float expectedChw[] = {1,-1,-1,1, -1,1,-1,1, -1,-1,1,1};
    if (UmiAiTrainingImagePackRgb8(rgb,sizeof rgb,2,2,8,
            UMI_AI_TRAINING_IMAGE_HWC,UMI_AI_TRAINING_IMAGE_UNIT,hwc,12) != UMI_STATUS_OK ||
        UmiAiTrainingImagePackRgb8(rgb,sizeof rgb,2,2,8,
            UMI_AI_TRAINING_IMAGE_CHW,UMI_AI_TRAINING_IMAGE_SIGNED_UNIT,chw,12) != UMI_STATUS_OK)
        return 1;
    if (memcmp(hwc,expectedHwc,sizeof hwc) != 0 ||
        memcmp(chw,expectedChw,sizeof chw) != 0) return 2;
    printf("HWC unit:");
    for(size_t i=0;i<12;++i)printf(" %.0f",(double)hwc[i]);
    putchar('\n');
    printf("CHW signed:");
    for(size_t i=0;i<12;++i)printf(" %.0f",(double)chw[i]);
    putchar('\n');
    /* A short input must not overwrite the previous complete tensor. */
    float before[12];
    memcpy(before,chw,sizeof before);
    if (UmiAiTrainingImagePackRgb8(rgb,sizeof rgb-1U,2,2,8,
            UMI_AI_TRAINING_IMAGE_CHW,UMI_AI_TRAINING_IMAGE_SIGNED_UNIT,chw,12) != UMI_STATUS_CAPACITY_EXCEEDED ||
        memcmp(before,chw,sizeof chw) != 0) return 3;
    puts("Short input refused; previous tensor unchanged.");
    puts("No image decoder, model or training operation was run.");
    return 0;
}
