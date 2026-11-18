/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/training-groups/main.c
 *
 * PURPOSE:
 *   Use Framework group partitioning without duplicating the splitting algorithm.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <umicom/ai/training/dataset_split.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
    const uint64_t groups[] = {100, 100, 200, 300, 300, 400};
    unsigned char membership[6], repeat[6];
    if (UmiAiTrainingSplitGroups(groups, 6, 1, 42, membership, 6) != UMI_STATUS_OK)
        return 1;
    if (UmiAiTrainingSplitGroups(groups, 6, 1, 42, repeat, 6) != UMI_STATUS_OK ||
        memcmp(membership, repeat, sizeof membership) != 0)
        return 2;
    if (membership[0] != membership[1] || membership[3] != membership[4])
        return 3;
    size_t selectedGroups = 0;
    for (size_t i = 0; i < 6; ++i) {
        if (membership[i] > 1) return 4;
        if (membership[i] && (i == 0 || groups[i] != groups[i - 1])) ++selectedGroups;
        printf("row=%zu group=%" PRIu64 " partition=%s\n", i, groups[i],
               membership[i] ? "evaluation" : "training");
    }
    if (selectedGroups != 1) return 5;
    memset(repeat, 0xa5, sizeof repeat);
    if (UmiAiTrainingSplitGroups(groups, 6, 4, 42, repeat, 6) == UMI_STATUS_OK)
        return 6;
    for (size_t i = 0; i < sizeof repeat; ++i) if (repeat[i] != 0xa5) return 7;
    return 0;
}
