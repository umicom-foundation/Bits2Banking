/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/arena-allocator/main.c
 * PURPOSE: Assemble a short, temporary Notes report in caller-owned storage.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "arena.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    unsigned char workspace[512];
    BtbArena arena;
    if (BtbArenaInitialise(&arena, workspace, sizeof(workspace)) != BTB_ARENA_OK)
        return 1;

    const char *heading = "Umicom Notes — Weekly Review";
    const char *detail = "3 notes reviewed; 0 notes lost.";
    char *title = NULL, *body = NULL;
    size_t checkpoint = BtbArenaCheckpoint(&arena);
    if (BtbArenaAllocate(&arena, strlen(heading) + 1U, 1U, (void **)&title) != BTB_ARENA_OK ||
        BtbArenaAllocate(&arena, strlen(detail) + 1U, 1U, (void **)&body) != BTB_ARENA_OK)
        return 1;
    (void)strcpy(title, heading);
    (void)strcpy(body, detail);
    printf("%s\n%s\nTemporary bytes used: %zu\n", title, body, arena.used);
    /* Both pointers become invalid as report allocations after this rewind. */
    if (BtbArenaRewind(&arena, checkpoint) != BTB_ARENA_OK) return 1;
    printf("Bytes after review: %zu\n", arena.used);
    return 0;
}
