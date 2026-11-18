/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/guidance.c
 *
 * PURPOSE:
 *   Compare guidance scales on compatible synthetic epsilon predictions without claiming model inference.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/ai/training/denoising.h"
#include <math.h>
#include <stdio.h>

int main(void)
{
    const float clean[4] = {-0.5F, 0.0F, 0.5F, 1.0F};
    const float exactNoise[4] = {0.2F, -0.4F, 0.1F, 0.8F};
    const float unconditioned[4] = {-0.1F, 0.0F, 0.5F, -0.2F};
    const float scales[4] = {0.0F, 0.5F, 1.0F, 3.0F};
    float noisy[4], guided[4], recovered[4];
    double errors[4] = {0};
    UmiStatus status = UmiAiDenoisingMix(clean, exactNoise, 4U, 0.25F, noisy, 4U);
    if (status != UMI_STATUS_OK) return 1;
    puts("Synthetic epsilon predictions, not image generation:");
    for (size_t s = 0U; s < 4U; ++s) {
        /* The conditioned predictor is deliberately perfect in this fixture.
         * No real learned network or text encoder produced these arrays. */
        status = UmiAiDenoisingGuideNoise(unconditioned, exactNoise, 4U,
            scales[s], guided, 4U);
        if (status != UMI_STATUS_OK) return 1;
        status = UmiAiDenoisingRecover(noisy, guided, 4U, 0.25F, recovered, 4U);
        if (status != UMI_STATUS_OK) return 1;
        for (size_t i = 0U; i < 4U; ++i) {
            double difference = (double)recovered[i] - (double)clean[i];
            errors[s] += difference * difference / 4.0;
        }
        printf("scale %.1f -> epsilon [%.3f, %.3f, %.3f, %.3f], reconstruction MSE %.6f\n",
            scales[s], guided[0], guided[1], guided[2], guided[3], errors[s]);
    }
    if (!isfinite(errors[2]) || errors[2] > 1e-10 || errors[3] <= errors[2]) {
        fputs("Unexpected result for the fixed arithmetic fixture.\n", stderr);
        return 1;
    }
    puts("Scale 1 preserves the exact predictor; scale 3 worsens this fixture.");
    return 0;
}
