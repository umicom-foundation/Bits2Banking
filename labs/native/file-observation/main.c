/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/file-observation/main.c
 *
 * PURPOSE:
 *   Inspect explicitly selected file bytes through the installed Framework evidence API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/toolchain/file_observation.h"
#include "umicom/platform/native_arguments.h"
#include <stdio.h>
#include <stdlib.h>
static int Observe(int argc, char **argv)
{
    if (argc < 2 || argc > (int)UMI_FILE_OBSERVATION_MAX_FILES + 1) {
        (void)fputs("Usage: file-observation ABSOLUTE_FILE [ABSOLUTE_FILE ...]\n", stderr);
        return 2;
    }
    const char *paths[UMI_FILE_OBSERVATION_MAX_FILES];
    for (int i = 1; i < argc; ++i) paths[i - 1] = argv[i];
    UmiFileObservation *observation = NULL;
    size_t failedIndex;
    /* The lab chooses one MiB per file. Framework also enforces its total limit.
     * The observation owns its paths and digests; input files are never written. */
    UmiStatus status = UmiFileObservationCapture(paths, (size_t)argc - 1U, 1024U * 1024U,
        &observation, &failedIndex);
    if (status != UMI_STATUS_OK) {
        (void)fprintf(stderr, "Capture refused: %s; selected index=%zu\n", umi_status_text(status), failedIndex);
        return 1;
    }
    char *json = malloc(UMI_FILE_OBSERVATION_JSON_CAPACITY);
    if (json == NULL) { UmiFileObservationDestroy(observation); return 1; }
    size_t length;
    status = UmiFileObservationFormat(observation, json, UMI_FILE_OBSERVATION_JSON_CAPACITY, &length);
    if (status == UMI_STATUS_OK && fwrite(json, 1U, length, stdout) != length) status = UMI_STATUS_IO_ERROR;
    free(json);
    UmiFileObservationDestroy(observation);
    return status == UMI_STATUS_OK ? 0 : 1;
}
int main(int argc, char **argv)
{
    int result = 1;
    UmiStatus status = UmiNativeArgumentsDispatch(argc, argv, Observe, &result);
    if (status != UMI_STATUS_OK) (void)fprintf(stderr, "Argument capture failed: %s\n", umi_status_text(status));
    return status == UMI_STATUS_OK ? result : 1;
}
