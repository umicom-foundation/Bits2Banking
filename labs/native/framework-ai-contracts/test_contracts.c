/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-ai-contracts/test_contracts.c
 *
 * PURPOSE:
 *   Check real Framework output preservation and numerical contracts from a small client.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "umicom/ai/training/byte_tokenizer.h"
#include "umicom/ai/training/gradient_clipping.h"

#define CHECK(expression) do { if (!(expression)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expression); return 1; \
} } while (0)

static int TokenCase(const char *name)
{
    const uint8_t input[] = {65U, 0U, 255U};
    uint32_t tokens[3] = {111U, 222U, 333U};
    uint8_t bytes[3] = {7U, 8U, 9U};
    size_t count = 99U;
    if (strcmp(name, "empty") == 0) {
        CHECK(UmiAiByteEncode(NULL, 0U, NULL, 0U, &count) == UMI_STATUS_OK);
        CHECK(count == 0U);
        count = 99U;
        CHECK(UmiAiByteDecode(NULL, 0U, NULL, 0U, &count) == UMI_STATUS_OK);
        CHECK(count == 0U);
    } else if (strcmp(name, "encode-capacity") == 0) {
        CHECK(UmiAiByteEncode(input, 3U, tokens, 2U, &count) == UMI_STATUS_CAPACITY_EXCEEDED);
        CHECK(count == 99U && tokens[0] == 111U && tokens[1] == 222U && tokens[2] == 333U);
    } else if (strcmp(name, "bytes") == 0) {
        CHECK(UmiAiByteEncode(input, 3U, tokens, 3U, &count) == UMI_STATUS_OK);
        CHECK(count == 3U && tokens[0] == 69U && tokens[1] == 4U && tokens[2] == 259U);
        CHECK(UmiAiByteDecode(tokens, 3U, bytes, 3U, &count) == UMI_STATUS_OK);
        CHECK(count == 3U && memcmp(input, bytes, 3U) == 0);
    } else {
        tokens[0] = 69U; tokens[1] = 4U; tokens[2] = 259U;
        if (strcmp(name, "decode-capacity") == 0) {
            CHECK(UmiAiByteDecode(tokens, 3U, bytes, 2U, &count) == UMI_STATUS_CAPACITY_EXCEEDED);
        } else if (strcmp(name, "reserved") == 0) {
            tokens[2] = UMI_AI_BYTE_EOS;
            CHECK(UmiAiByteDecode(tokens, 3U, bytes, 3U, &count) == UMI_STATUS_INVALID_ARGUMENT);
        } else if (strcmp(name, "invalid-id") == 0) {
            tokens[2] = UMI_AI_BYTE_VOCABULARY;
            CHECK(UmiAiByteDecode(tokens, 3U, bytes, 3U, &count) == UMI_STATUS_INVALID_ARGUMENT);
        } else {
            return 2;
        }
        CHECK(count == 99U && bytes[0] == 7U && bytes[1] == 8U && bytes[2] == 9U);
    }
    return 0;
}

static int GradientCase(const char *name)
{
    float values[] = {3.0F, 4.0F};
    const float *groups[] = {values, values + 1};
    size_t counts[] = {2U, 1U};
    size_t groupCount = 1U;
    UmiAiTrainingGradientClipReport report = {13.0, 0.5, 7U, 1};
    if (strcmp(name, "nonfinite") == 0) {
        values[1] = NAN;
        CHECK(UmiAiTrainingGradientGlobalNorm(groups, counts, groupCount, 2.0F, &report) ==
              UMI_STATUS_INVALID_ARGUMENT);
        /* Compare defined fields, not structure padding bytes. */
        CHECK(report.globalNorm == 13.0 && report.appliedScale == 0.5 &&
              report.gradientElements == 7U && report.wasClipped == 1);
        CHECK(values[0] == 3.0F && isnan(values[1]));
        return 0;
    }
    if (strcmp(name, "zero") == 0) {
        values[0] = 0.0F; values[1] = 0.0F;
    } else if (strcmp(name, "split") == 0) {
        counts[0] = 1U; groupCount = 2U;
    } else if (strcmp(name, "norm") != 0) {
        return 2;
    }
    CHECK(UmiAiTrainingGradientGlobalNorm(groups, counts, groupCount, 2.0F, &report) == UMI_STATUS_OK);
    CHECK(report.gradientElements == 2U);
    if (strcmp(name, "zero") == 0) {
        CHECK(report.globalNorm == 0.0 && report.appliedScale == 1.0 && report.wasClipped == 0);
        CHECK(values[0] == 0.0F && values[1] == 0.0F);
    } else {
        CHECK(fabs(report.globalNorm - 5.0) < 1e-12 &&
              fabs(report.appliedScale - 0.4) < 1e-12 && report.wasClipped == 1);
        CHECK(values[0] == 3.0F && values[1] == 4.0F);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Supply one registered contract case.\n", stderr);
        return 2;
    }
    int result = TokenCase(argv[1]);
    if (result == 2) result = GradientCase(argv[1]);
    if (result == 2) fputs("Unknown contract case.\n", stderr);
    return result;
}
