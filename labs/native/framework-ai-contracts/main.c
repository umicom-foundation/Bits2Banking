/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-ai-contracts/main.c
 *
 * PURPOSE:
 *   Demonstrate Framework byte tokenization and a prospective gradient clipping report.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <inttypes.h>
#include <stdio.h>
#include "umicom/ai/training/byte_tokenizer.h"
#include "umicom/ai/training/gradient_clipping.h"

int main(void)
{
    const uint8_t input[] = {65U, 0U, 255U};
    uint32_t tokens[3] = {0U};
    uint8_t decoded[3] = {0U};
    size_t count = 0U;
    const float gradient[] = {3.0F, 4.0F};
    const float *groups[] = {gradient};
    const size_t sizes[] = {2U};
    UmiAiTrainingGradientClipReport report = {0};

    if (UmiAiByteEncode(input, 3U, tokens, 3U, &count) != UMI_STATUS_OK ||
        count != 3U ||
        UmiAiByteDecode(tokens, count, decoded, 3U, &count) != UMI_STATUS_OK ||
        count != 3U) {
        fputs("Token conversion failed.\n", stderr);
        return 1;
    }
    for (size_t index = 0U; index < count; ++index) {
        printf("byte %u -> token %" PRIu32 " -> byte %u\n",
               (unsigned)input[index], tokens[index], (unsigned)decoded[index]);
    }
    if (UmiAiTrainingGradientGlobalNorm(groups, sizes, 1U, 2.0F, &report) != UMI_STATUS_OK) {
        fputs("Gradient measurement failed.\n", stderr);
        return 1;
    }
    /* The report proposes a scale; the borrowed gradient stays unchanged. */
    printf("norm=%.1f scale=%.1f elements=%zu clipped=%d\n",
           report.globalNorm, report.appliedScale, report.gradientElements, report.wasClipped);
    return 0;
}
