/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/llm-checkpoint-inspection/main.c
 *
 * PURPOSE:
 *   Inspect a small Framework decoder checkpoint and demonstrate rejected corruption.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/ai/training/checkpoint.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    const UmiAiTrainingDecoderConfig config = {4U, 2U, 4U, 8U, 2U, UINT64_C(13)};
    UmiAiTrainingDecoder *model = NULL;
    UmiAiTrainingDecoderCheckpointInfo info;
    uint8_t *bytes = NULL;
    size_t size = 0U, written = 0U;
    int result = EXIT_FAILURE;
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "--corrupt") != 0)) {
        fputs("Usage: checkpoint-inspection [--corrupt]\n", stderr);
        return result;
    }
    UmiStatus status = UmiAiTrainingDecoderCreate(&config, &model);
    if (status != UMI_STATUS_OK) goto cleanup;
    status = UmiAiTrainingDecoderCheckpointSize(model, &size);
    if (status != UMI_STATUS_OK) goto cleanup;
    bytes = malloc(size);
    if (bytes == NULL) { status = UMI_STATUS_OUT_OF_MEMORY; goto cleanup; }
    status = UmiAiTrainingDecoderCheckpointEncode(model, bytes, size, &written);
    if (status != UMI_STATUS_OK) goto cleanup;
    if (argc == 2) bytes[written - 1U] ^= 1U;
    status = UmiAiTrainingDecoderCheckpointInspect(bytes, written, &info);
    if (status != UMI_STATUS_OK) goto cleanup;
    printf("Format: %" PRIu32 "\nVocabulary: %" PRIu32 "\nContext: %" PRIu32 "\n",
           info.formatVersion, info.config.vocabularySize, info.config.contextLength);
    printf("Tensors: %" PRIu32 "\nWeights: %zu\nBytes: %zu\nCompleted steps: %" PRIu64 "\n",
           info.tensorCount, info.weightCount, info.byteCount, info.completedSteps);
    result = EXIT_SUCCESS;
cleanup:
    if (result != EXIT_SUCCESS) fprintf(stderr, "Checkpoint operation rejected (status %d).\n", (int)status);
    free(bytes);
    UmiAiTrainingDecoderDestroy(model);
    return result;
}
