/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-gpt-inspection/main.c
 *
 * PURPOSE:
 *   Exercise actual installed GPT inspection and preserve observations across controlled refusals.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#define REQUIRE(x) do { if (!(x)) { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); \
    result = 1; goto cleanup; } } while (0)

int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    static const char *const scenarios[] = { "valid-512", "valid-4096", "reservation", "stride", "overlap", "backup", "read-failure", "retry" };
    int known = 0, result = 0;
    for (size_t i = 0U; i < sizeof(scenarios) / sizeof(scenarios[0]); ++i)
        if (!strcmp(argv[1], scenarios[i])) known = 1;
    if (!known) return 2;
    LabImage image = {0};
    uint32_t block = !strcmp(argv[1], "valid-4096") ? 4096U : 512U;
    UmiGptImageInfo observation = {0}, previous;
    REQUIRE(LabImageCreate(&image, block));
    UmiStatus status = UmiGptImageInspect(LabReadAt, &image, image.length, block, &observation);
    REQUIRE(status == UMI_STATUS_OK && image.reads == 4U && observation.partitions == 1U);
    REQUIRE(observation.logicalBlockBytes == block &&
        observation.firstUsableLba == 2U + 16384U / block);
    printf("Synthetic table: %u partition, block %" PRIu32 ", usable %" PRIu64 "..%" PRIu64 "\n",
        observation.partitions, observation.logicalBlockBytes,
        observation.firstUsableLba, observation.lastUsableLba);
    if (!strncmp(argv[1], "valid-", 6U)) goto cleanup;
    memcpy(&previous, &observation, sizeof(previous));
    image.reads = 0U;
    if (!strcmp(argv[1], "read-failure")) image.failRead = 3U;
    else REQUIRE(LabImageChange(&image, argv[1]));
    status = UmiGptImageInspect(LabReadAt, &image, image.length, block, &observation);
    REQUIRE(status == (!strcmp(argv[1], "read-failure") ? UMI_STATUS_IO_ERROR : UMI_STATUS_PARSE_ERROR));
    REQUIRE(memcmp(&previous, &observation, sizeof(observation)) == 0);
    printf("Controlled refusal: status %d; previous observation unchanged.\n", (int)status);
    if (!strcmp(argv[1], "retry")) {
        LabImageDestroy(&image);
        REQUIRE(LabImageCreate(&image, block));
        REQUIRE(UmiGptImageInspect(LabReadAt, &image, image.length, block, &observation) == UMI_STATUS_OK);
        REQUIRE(image.reads == 4U && observation.partitions == 1U);
        puts("Fresh synthetic source accepted after refusal.");
    }
cleanup:
    LabImageDestroy(&image);
    return result;
}
