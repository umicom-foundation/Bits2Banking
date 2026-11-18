/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-tensor/quantize.c
 *
 * PURPOSE:
 *   Demonstrate explicit Framework output range policy and unchanged pixels after nonfinite input.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/image_tensor.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
static int Print(const char *name, const uint8_t *bytes, size_t count)
{
    if (printf("%s:",name)<0) return 1;
    for(size_t i=0U;i<count;++i) if(printf(" %u",(unsigned)bytes[i])<0) return 1;
    return putchar('\n')==EOF;
}
int main(void)
{
    /* Original numerical fixture: no image file, generator or model is run.
     * Keeping a pixel gap makes output ownership visible in the checks. */
    const float unit[6]={0.0F,0.5F,1.0F,0.25F,0.75F,0.0F};
    uint8_t rgb[8];
    memset(rgb,0xA5,sizeof rgb);
    if(UmiAiTrainingImageUnpackRgb8(unit,6,2,1,6,
        UMI_AI_TRAINING_IMAGE_HWC,UMI_AI_TRAINING_IMAGE_UNIT,
        UMI_AI_TRAINING_IMAGE_REJECT_OUTSIDE,rgb,sizeof rgb)!=UMI_STATUS_OK) return 1;
    const uint8_t expected[6]={0,128,255,64,191,0};
    if(memcmp(rgb,expected,sizeof expected)!=0 || rgb[6]!=0xA5 || rgb[7]!=0xA5) return 2;
    if(Print("Strict unit RGB",rgb,6))return 3;
    const float clipped[3]={-4.0F,0.0F,8.0F};
    uint8_t before[8];
    memcpy(before,rgb,sizeof before);
    if(UmiAiTrainingImageUnpackRgb8(clipped,3,1,1,3,0,
        UMI_AI_TRAINING_IMAGE_SIGNED_UNIT,UMI_AI_TRAINING_IMAGE_REJECT_OUTSIDE,
        rgb,sizeof rgb)!=UMI_STATUS_INVALID_ARGUMENT || memcmp(before,rgb,sizeof rgb)!=0) return 4;
    if(puts("Outside values refused; previous pixels unchanged.")<0)return 5;
    if(UmiAiTrainingImageUnpackRgb8(clipped,3,1,1,3,0,
        UMI_AI_TRAINING_IMAGE_SIGNED_UNIT,UMI_AI_TRAINING_IMAGE_CLIP_OUTSIDE,
        rgb,sizeof rgb)!=UMI_STATUS_OK) return 6;
    if(Print("Explicitly clipped signed RGB",rgb,3))return 7;
    memcpy(before,rgb,sizeof before);
    const float invalid[3]={0.0F,0.5F,NAN};
    if(UmiAiTrainingImageUnpackRgb8(invalid,3,1,1,3,0,0,
        UMI_AI_TRAINING_IMAGE_CLIP_OUTSIDE,rgb,sizeof rgb)!=UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(before,rgb,sizeof rgb)!=0) return 8;
    if(puts("NaN refused even when clipping is selected.")<0)return 9;
    if(puts("This converts code values; it does not decode a latent or train a model.")<0)return 10;
    return 0;
}
