/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/arena-allocator/test_arena.c
 * PURPOSE: Exercise allocator failures, alignment, rollback and reset.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "arena.h"
#include <stdint.h>
#include <stdio.h>

#define CHECK(c) do { if (!(c)) { \
    fprintf(stderr, "arena failure line %d: %s\n", __LINE__, #c); return 1; \
} } while (0)

int main(void)
{
    unsigned char memory[128];
    BtbArena arena = {0};
    CHECK(BtbArenaInitialise(&arena, memory, sizeof(memory)) == BTB_ARENA_OK);
    size_t mark = BtbArenaCheckpoint(&arena);
    CHECK(mark == 0U);
    void *first = NULL, *second = NULL;
    CHECK(BtbArenaAllocate(&arena, 7U, 1U, &first) == BTB_ARENA_OK);
    CHECK(first == (void *)memory);
    CHECK(BtbArenaAllocate(&arena, sizeof(uint64_t), _Alignof(uint64_t), &second) == BTB_ARENA_OK);
    CHECK(((uintptr_t)second % (uintptr_t)_Alignof(uint64_t)) == 0U);
    CHECK((unsigned char *)second >= memory + 7);
    CHECK(arena.used <= sizeof(memory));
    size_t before = arena.used;
    void *sentinel = (void *)memory;
    CHECK(BtbArenaAllocate(&arena, 1024U, 1U, &sentinel) == BTB_ARENA_NO_SPACE);
    CHECK(sentinel == (void *)memory && arena.used == before);
    CHECK(BtbArenaAllocate(&arena, 1U, 3U, &sentinel) == BTB_ARENA_INVALID);
    CHECK(arena.used == before);
    CHECK(BtbArenaAllocate(&arena, 0U, 1U, &sentinel) == BTB_ARENA_INVALID);
    CHECK(arena.used == before);
    CHECK(BtbArenaRewind(&arena, before + 1U) == BTB_ARENA_INVALID);
    CHECK(arena.used == before);
    CHECK(BtbArenaRewind(&arena, mark) == BTB_ARENA_OK);
    CHECK(arena.used == 0U);
    CHECK(BtbArenaAllocate(&arena, 32U, 16U, &sentinel) == BTB_ARENA_OK);
    CHECK(((uintptr_t)sentinel % 16U) == 0U);
    CHECK(BtbArenaAllocate(NULL, 12U, 1U, &sentinel) == BTB_ARENA_INVALID);
    CHECK(BtbArenaInitialise(NULL, memory, sizeof(memory)) == BTB_ARENA_INVALID);
    puts("Arena test passed: alignment, rollback, power-of-two validation, capacity.");
    return 0;
}
