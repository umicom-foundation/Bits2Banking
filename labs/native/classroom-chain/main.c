/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/main.c
 *
 * PURPOSE:
 *   Demonstrate independent acceptance of finite classroom chain histories.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "chain.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    enum { ATTEMPTS = 65536 };
    ClassroomChain current = {0};
    if (!classroom_append(&current, (ClassroomTransfer){0, 1, 5}, 2, ATTEMPTS)) {
        fputs("Could not prepare the shared classroom block.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Give both histories the same first record. Different valid transfers
     * after that point make independent histories for a replay exercise. */
    ClassroomChain candidate = current;
    if (!classroom_append(&current, (ClassroomTransfer){1, 2, 2}, 0, ATTEMPTS) ||
        !classroom_append(&candidate, (ClassroomTransfer){1, 0, 3}, 2, ATTEMPTS) ||
        !classroom_append(&candidate, (ClassroomTransfer){0, 1, 1}, 1, ATTEMPTS)) {
        fputs("Could not prepare the classroom histories.\n", stderr);
        return EXIT_FAILURE;
    }

    ClassroomChain damaged = candidate;
    ++damaged.blocks[0].transfer.units;
    if (classroom_choose(&current, &damaged) != CLASSROOM_KEEP_CURRENT ||
        classroom_choose(&current, &candidate) != CLASSROOM_ADOPT_CANDIDATE) {
        fputs("Unexpected classroom branch choice.\n", stderr);
        return EXIT_FAILURE;
    }

    ClassroomBalance balance;
    if (!classroom_replay(&candidate, &balance)) {
        return EXIT_FAILURE;
    }
    const uint32_t total = balance.units[0] + balance.units[1] + balance.units[2];
    puts("Altered history rejected before comparing work.");
    printf("accepted branch: %zu blocks, %" PRIu32 " classroom units\n", candidate.length, total);
    printf("A=%" PRIu32 " B=%" PRIu32 " C=%" PRIu32 "\n", balance.units[0], balance.units[1], balance.units[2]);
    return EXIT_SUCCESS;
}
