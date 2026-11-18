/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/denoising-objective/main.c
 *
 * PURPOSE:
 *   Teach native noise-prediction training, bounded graph reuse and a measurable generalisation failure.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/denoising.h"
#include "umicom/ai/training/tape.h"
#include <math.h>
#include <stdio.h>

enum { ROWS = 5, STEPS = 500 };
/* The checked status has a distinct name from the application exit result so strict shadow diagnostics remain enabled. The original macro is retained for review. The former implementation is retained for owner review. */
#if 0
#define CHECK(call) do { \
    UmiStatus result = (call); \
    if (result != UMI_STATUS_OK) { \
        fprintf(stderr, "%s failed: status %d\n", #call, (int)result); \
        goto cleanup; \
    } \
} while (0)
#endif
#define CHECK(call) do { \
    UmiStatus checkedStatus = (call); \
    if (checkedStatus != UMI_STATUS_OK) { \
        fprintf(stderr, "%s failed: status %d\n", #call, (int)checkedStatus); \
        goto cleanup; \
    } \
} while (0)

int main(void)
{
    int result = 1;
    UmiAiTrainingTape *tape = NULL;
    UmiAiTrainingTensor *inputs = NULL, *targets = NULL, *weights = NULL;
    const float clean[ROWS] = {0.25F, 0.25F, 0.25F, 0.25F, 0.25F};
    const float noise[ROWS] = {-1.0F, -0.5F, 0.0F, 0.5F, 1.0F};
    const float initialWeights[2] = {0.0F, 0.0F};
    float noisy[ROWS], features[ROWS * 2];
    float firstLoss = 0.0F, finalLoss = 0.0F;
    UmiAiTrainingTapeMemory leaves, current;
    size_t firstPeak = 0U;

    /* This fixture deliberately has only one clean value. It teaches the loss
     * and exposes memorisation; fixed noise values are not a Gaussian sampler. */
    CHECK(UmiAiDenoisingMix(clean, noise, ROWS, 0.5F, noisy, ROWS));
    for (size_t row = 0U; row < ROWS; ++row) {
        features[row * 2U] = noisy[row];
        features[row * 2U + 1U] = 1.0F;
    }

    CHECK(UmiAiTrainingTapeCreate(&tape));
    CHECK(UmiAiTrainingTensorCreate(tape, ROWS, 2U, features, ROWS * 2U, 0, &inputs));
    CHECK(UmiAiTrainingTensorCreate(tape, ROWS, 1U, noise, ROWS, 0, &targets));
    CHECK(UmiAiTrainingTensorCreate(tape, 2U, 1U, initialWeights, 2U, 1, &weights));
    CHECK(UmiAiTrainingTapeMemoryInspect(tape, &leaves));
    /* The budget covers committed graph memory, not allocator overhead or
     * process RSS. This fixed lesson has ample headroom for two small nodes. */
    CHECK(UmiAiTrainingTapeSetMemoryBudget(tape, leaves.currentBytes + 8192U));

    for (size_t step = 0U; step < STEPS; ++step) {
        UmiAiTrainingTensor *prediction = NULL, *loss = NULL;
        CHECK(UmiAiTrainingMatmul(tape, inputs, weights, &prediction));
        CHECK(UmiAiTrainingMeanSquaredError(tape, prediction, targets, &loss));
        CHECK(UmiAiTrainingTensorValues(loss, &finalLoss, 1U));
        if (step == 0U) firstLoss = finalLoss;
        CHECK(UmiAiTrainingBackward(tape, loss));
        CHECK(UmiAiTrainingSgdStep(tape, weights, 0.1F));
        CHECK(UmiAiTrainingTapeMemoryInspect(tape, &current));
        if (step == 0U) firstPeak = current.peakBytes;
        if (current.tensorCount != 5U || current.peakBytes != firstPeak) {
            fputs("The fixed training graph grew between iterations.\n", stderr);
            goto cleanup;
        }
        /* Preserve three leaf tensors and their updated parameter values.
         * prediction and loss become invalid here. Never reuse either handle. */
        CHECK(UmiAiTrainingTapeRewind(tape, 3U));
        CHECK(UmiAiTrainingTapeMemoryInspect(tape, &current));
        if (current.currentBytes != leaves.currentBytes || current.tensorCount != 3U) {
            fputs("Rewind did not restore the persistent leaf footprint.\n", stderr);
            goto cleanup;
        }
    }

    float learned[2], heldNoisy[2], heldFeatures[4], predictedNoise[2], reconstructed[2];
    const float heldClean[2] = {0.25F, 0.8F}, heldNoise[2] = {0.35F, 0.35F};
    UmiAiTrainingTensor *heldInput = NULL, *heldPrediction = NULL;
    CHECK(UmiAiTrainingTensorValues(weights, learned, 2U));
    CHECK(UmiAiDenoisingMix(heldClean, heldNoise, 2U, 0.5F, heldNoisy, 2U));
    for (size_t row = 0U; row < 2U; ++row) {
        heldFeatures[row * 2U] = heldNoisy[row];
        heldFeatures[row * 2U + 1U] = 1.0F;
    }
    CHECK(UmiAiTrainingTensorCreate(tape, 2U, 2U, heldFeatures, 4U, 0, &heldInput));
    CHECK(UmiAiTrainingMatmul(tape, heldInput, weights, &heldPrediction));
    CHECK(UmiAiTrainingTensorValues(heldPrediction, predictedNoise, 2U));
    CHECK(UmiAiDenoisingRecover(heldNoisy, predictedNoise, 2U, 0.5F, reconstructed, 2U));
    printf("Umicom denoising objective: %u fixed CPU training steps\n", (unsigned)STEPS);
    printf("Noise prediction MSE: %.8f -> %.8f\n", (double)firstLoss, (double)finalLoss);
    printf("Learned slope %.6f and bias %.6f\n", (double)learned[0], (double)learned[1]);
    printf("Retained leaf bytes: %zu; fixed training peak: %zu\n", leaves.currentBytes, firstPeak);
    printf("Familiar clean value %.2f reconstructs as %.6f\n",
        (double)heldClean[0], (double)reconstructed[0]);
    printf("Unseen clean value %.2f reconstructs as %.6f (expected generalisation failure)\n",
        (double)heldClean[1], (double)reconstructed[1]);
    if (!(finalLoss < 0.0000001F && finalLoss < firstLoss &&
          fabsf(reconstructed[0] - heldClean[0]) < 0.001F &&
          fabsf(reconstructed[1] - heldClean[1]) > 0.3F)) {
        fputs("The lesson's convergence or deliberate overfitting check failed.\n", stderr);
        goto cleanup;
    }
    puts("Checks passed: decreasing loss, bounded graph reuse, and visible overfitting.");
    result = 0;
cleanup:
    /* Tape owns every tensor. One destroy releases leaves and operations on
     * both success and any failed call; application code frees no tensor. */
    UmiAiTrainingTapeDestroy(tape);
    return result;
}
