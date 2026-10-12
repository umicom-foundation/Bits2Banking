/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/journalled-notes/main.c
 * PURPOSE: Demonstrate an interrupted Notes save and checked WAL replay.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "journal.h"
#include <stdio.h>

int main(void)
{
    BtbBlockStore storage;
    BtbStorageInit(&storage);
    const BtbJournalStatus interrupted =
        BtbJournalCommit(&storage, 0U, "Training notes for the treasury team",
                         BTB_STOP_AFTER_JOURNAL_FLUSH);
    if (interrupted != BTB_JOURNAL_INTERRUPTED) return 1;
    BtbNote recovered = {0};
    if (BtbJournalRecover(&storage, &recovered) != BTB_JOURNAL_OK) return 1;
    printf("Recovered revision: %llu\n", (unsigned long long)recovered.revision);
    printf("Recovered note: %s\n", recovered.text);
    printf("The stable-state simulation is not a production filesystem.\n");
    return 0;
}
