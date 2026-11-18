/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/masked-language-loss/attention.c
 *
 * PURPOSE:
 *   Compare padding exclusion in attention with selection of objective terms using shared Framework operators.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/tape.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* The fixture supplies Q and K as zero, so every permitted key receives an
 * equal probability. The three scalar values make the effect hand-checkable.
 * Framework owns arithmetic and graph storage; this client owns only arrays. */
static int inspect(float padding, int hide_padding, float *prediction,
                   float *objective, float derivative[3])
{
    UmiAiTrainingTape *tape = NULL;
    UmiAiTrainingTensor *q = NULL, *k = NULL, *v = NULL;
    UmiAiTrainingTensor *attention = NULL, *target = NULL, *loss = NULL;
    const float zero[3] = {0, 0, 0};
    const float values[3] = {2, padding, 6};
    const unsigned char attention_selection[3] = {1, 0, 1};
    const unsigned char loss_selection[3] = {0, 0, 1};
    float result[3] = {0};
    UmiStatus status = UmiAiTrainingTapeCreate(&tape);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorCreate(tape, 3, 1, zero, 3, 1, &q);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorCreate(tape, 3, 1, zero, 3, 1, &k);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorCreate(tape, 3, 1, values, 3, 1, &v);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorCreate(tape, 3, 1, zero, 3, 0, &target);
    if (status == UMI_STATUS_OK) {
        status = hide_padding
            ? UmiAiTrainingMaskedMultiHeadCausalAttention(tape, q, k, v,
                3, 1, attention_selection, 3, &attention)
            : UmiAiTrainingMultiHeadCausalAttention(tape, q, k, v,
                3, 1, &attention);
    }
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorValues(attention, result, 3);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingMaskedMeanSquaredError(tape, attention, target,
                                                    loss_selection, 3, &loss);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorValues(loss, objective, 1);
    if (status == UMI_STATUS_OK) status = UmiAiTrainingBackward(tape, loss);
    if (status == UMI_STATUS_OK)
        status = UmiAiTrainingTensorGradients(v, derivative, 3);
    if (status == UMI_STATUS_OK && hide_padding && result[1] != 0)
        status = UMI_STATUS_INVALID_ARGUMENT;
    if (status == UMI_STATUS_OK) *prediction = result[2];
    UmiAiTrainingTapeDestroy(tape);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Attention exercise refused with status %d\n", (int)status);
        return 1;
    }
    return 0;
}
static int close_to(float actual, float expected)
{
    return fabsf(actual - expected) < 0.001F;
}
int main(void)
{
    float prediction, loss, gradient[3];
    if (inspect(100, 0, &prediction, &loss, gradient)) return EXIT_FAILURE;
    if (!close_to(prediction, 36) || !close_to(loss, 1296) ||
        !close_to(gradient[0], 24) || !close_to(gradient[1], 24) ||
        !close_to(gradient[2], 24)) return EXIT_FAILURE;
    printf("Loss selection only: prediction %.1f, objective %.1f, padding gradient %.1f\n",
           (double)prediction, (double)loss, (double)gradient[1]);
    if (inspect(100, 1, &prediction, &loss, gradient)) return EXIT_FAILURE;
    if (!close_to(prediction, 4) || !close_to(loss, 16) ||
        !close_to(gradient[0], 4) || gradient[1] != 0 ||
        !close_to(gradient[2], 4)) return EXIT_FAILURE;
    printf("Attention and loss selection: prediction %.1f, objective %.1f, padding gradient %.1f\n",
           (double)prediction, (double)loss, (double)gradient[1]);
    /* Prompt data stays available to attention even when its own objective term
     * is excluded. Changing only padding must leave the selected answer intact. */
    for (size_t iteration = 0; iteration < 32; ++iteration) {
        if (inspect((float)iteration * 1000, 1, &prediction, &loss, gradient))
            return EXIT_FAILURE;
        if (!close_to(prediction, 4) || !close_to(loss, 16) ||
            !close_to(gradient[0], 4) || gradient[1] != 0 ||
            !close_to(gradient[2], 4)) return EXIT_FAILURE;
    }
    puts("Prompt value contributes; padding does not. All tapes released.");
    return EXIT_SUCCESS;
}
