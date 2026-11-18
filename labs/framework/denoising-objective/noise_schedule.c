/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/noise_schedule.c
 *
 * PURPOSE:
 *   Distinguish per-step beta from cumulative signal and compose the shared forward-noise services.
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

enum { STEPS = 4 };
int main(void)
{
    const float betas[STEPS] = {0.1F, 0.2F, 0.3F, 0.4F};
    const float expected[STEPS] = {0.9F, 0.72F, 0.504F, 0.3024F};
    const float clean[1] = {0.25F}, knownNoise[1] = {1.0F};
    float cumulative[STEPS];
    UmiStatus status = UmiAiDenoisingScheduleFromBetas(betas, STEPS, cumulative, STEPS);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Schedule refused: status %d\n", (int)status);
        return 1;
    }
    puts("step  beta      alphaBar  noisy     recovered");
    for (size_t step = 0U; step < STEPS; ++step) {
        float noisy[1], recovered[1];
        status = UmiAiDenoisingMix(clean, knownNoise, 1U, cumulative[step], noisy, 1U);
        if (status == UMI_STATUS_OK)
            status = UmiAiDenoisingRecover(noisy, knownNoise, 1U, cumulative[step], recovered, 1U);
        if (status != UMI_STATUS_OK || fabsf(cumulative[step] - expected[step]) > 0.000001F) {
            fprintf(stderr, "Step %zu failed its coefficient contract: status %d\n", step, (int)status);
            return 1;
        }
        if (fabsf(recovered[0] - clean[0]) > 0.000001F) {
            fputs("The known-noise arithmetic did not recover the clean scalar.\n", stderr);
            return 1;
        }
        printf("%zu     %.6f  %.6f  %.6f  %.6f\n", step,
            (double)betas[step], (double)cumulative[step], (double)noisy[0], (double)recovered[0]);
    }
    /* Every row uses the same original clean scalar and known noise. The
     * example is a marginal forward-noise calculation, not a reverse sampler
     * or a recursively noised trajectory. No predicted noise is learned. */
    puts("Checks passed: cumulative products and known-noise reconstruction.");
    puts("No model was trained; known noise is not a learned prediction.");
    return 0;
}
