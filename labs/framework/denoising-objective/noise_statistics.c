/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/noise_statistics.c
 *
 * PURPOSE:
 *   Measure a native normal-noise sample before using it in a denoising experiment.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/initialisation.h"
#include <math.h>
#include <stdio.h>

enum { SAMPLE_COUNT = 8192, BIN_COUNT = 10 };
int main(void)
{
    UmiAiTrainingRandomState random;
    float samples[SAMPLE_COUNT];
    size_t bins[BIN_COUNT] = {0};
    const char *labels[BIN_COUNT] = {"below -4","[-4,-3)","[-3,-2)","[-2,-1)",
        "[-1,0)","[0,1)","[1,2)","[2,3)","[3,4)","at least 4"};
    if (UmiAiTrainingRandomSeed(&random, 42U) != UMI_STATUS_OK ||
        UmiAiTrainingRandomFillNormal(&random, 0.0F, 1.0F,
            samples, SAMPLE_COUNT) != UMI_STATUS_OK)
        return 1;
    double sum = 0.0, squares = 0.0;
    for (size_t i = 0U; i < SAMPLE_COUNT; ++i) {
        float value = samples[i];
        if (!isfinite(value)) return 2;
        size_t bin = value < -4.0F ? 0U : value >= 4.0F ? 9U
            : (size_t)(floorf(value) + 5.0F);
        ++bins[bin];
        sum += value;
        squares += (double)value * value;
    }
    double mean = sum / SAMPLE_COUNT;
    double variance = squares / SAMPLE_COUNT - mean * mean;
    printf("Umicom native noise: %u samples, seed 42\n", (unsigned)SAMPLE_COUNT);
    printf("Observed mean %.6f; variance %.6f\n", mean, variance);
    size_t total = 0U;
    for (size_t i = 0U; i < BIN_COUNT; ++i) {
        printf("%-12s %zu\n", labels[i], bins[i]);
        total += bins[i];
    }
    if (total != SAMPLE_COUNT || fabs(mean) >= 0.1 || fabs(variance - 1.0) >= 0.2)
        return 3;
    puts("Noise checks passed; no model or image was trained or generated.");
    return 0;
}
