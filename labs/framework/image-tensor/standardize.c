/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/image-tensor/standardize.c
 *
 * PURPOSE:
 *   Apply explicit RGB channel preprocessing with the shared Framework packer and demonstrate atomic refusal.
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
    /* These two original pixels avoid a decoder or dataset download. The
     * parameters are a teaching contract, not recommendations for any model. */
    const uint8_t rgb[] = {0, 0, 0, 255, 255, 255};
    const UmiAiTrainingImageStandardization parameters = {
        .mean = {0.5f, 0.0f, 1.0f}, .scale = {0.5f, 1.0f, 0.25f}
    };
    const float expectedHwc[] = {-1, 0, -4, 1, 1, 0};
    const float expectedChw[] = {-1, 1, 0, 1, -4, 0};
    float hwc[6], chw[6];
    if (UmiAiTrainingImagePackRgb8Standardized(rgb, sizeof rgb, 2, 1, 6,
            UMI_AI_TRAINING_IMAGE_HWC, &parameters, hwc, 6) != UMI_STATUS_OK ||
        UmiAiTrainingImagePackRgb8Standardized(rgb, sizeof rgb, 2, 1, 6,
            UMI_AI_TRAINING_IMAGE_CHW, &parameters, chw, 6) != UMI_STATUS_OK)
        return 1;
    if (memcmp(hwc, expectedHwc, sizeof hwc) != 0 ||
        memcmp(chw, expectedChw, sizeof chw) != 0) return 2;
    printf("HWC standardized:");
    for (size_t i = 0; i < 6; ++i) printf(" %.0f", (double)hwc[i]);
    putchar('\n');
    printf("CHW standardized:");
    for (size_t i = 0; i < 6; ++i) printf(" %.0f", (double)chw[i]);
    putchar('\n');

    /* A previous valid result belongs to the caller. Rejecting a malformed
     * request must not replace that result with a partly transformed array. */
    UmiAiTrainingImageStandardization invalid = parameters;
    invalid.scale[2] = 0.0f;
    float before[6];
    memcpy(before, chw, sizeof before);
    if (UmiAiTrainingImagePackRgb8Standardized(rgb, sizeof rgb, 2, 1, 6,
            UMI_AI_TRAINING_IMAGE_CHW, &invalid, chw, 6) != UMI_STATUS_INVALID_ARGUMENT ||
        memcmp(before, chw, sizeof chw) != 0) return 3;
    puts("Zero scale refused; previous tensor unchanged.");
    puts("Parameters are an example, not a model recommendation.");
    return 0;
}
