/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/arena-allocator/arena.c
 * PURPOSE: Demonstrate checked pointer alignment without hidden allocations.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "arena.h"
#include <stdint.h>

BtbArenaStatus BtbArenaInitialise(BtbArena *arena, void *storage, size_t capacity)
{
    if (arena == NULL || storage == NULL || capacity == 0U) return BTB_ARENA_INVALID;
    /* Publish only after validating every field. */
    *arena = (BtbArena){(unsigned char *)storage, capacity, 0U};
    return BTB_ARENA_OK;
}

BtbArenaStatus BtbArenaAllocate(BtbArena *arena, size_t byteCount,
                                size_t alignment, void **outMemory)
{
    if (arena == NULL || outMemory == NULL || arena->storage == NULL ||
        arena->used > arena->capacity || byteCount == 0U ||
        alignment == 0U || (alignment & (alignment - 1U)) != 0U)
        return BTB_ARENA_INVALID;

    /* uintptr_t is an optional C type; it is available on our supported
     * targets. Check each integer addition before calculating an address. */
    uintptr_t base = (uintptr_t)arena->storage;
    if (arena->used > UINTPTR_MAX - base) return BTB_ARENA_NO_SPACE;
    uintptr_t current = base + arena->used;
    uintptr_t mask = (uintptr_t)(alignment - 1U);
    if (current > UINTPTR_MAX - mask) return BTB_ARENA_NO_SPACE;
    uintptr_t aligned = (current + mask) & ~mask;
    size_t padding = (size_t)(aligned - current);
    size_t available = arena->capacity - arena->used;
    if (padding > available || byteCount > available - padding)
        return BTB_ARENA_NO_SPACE;

    size_t start = arena->used + padding;
    /* Derive the resulting pointer from the original array. Never create a
     * C pointer from an arbitrary address supplied by the caller. */
    *outMemory = (void *)(arena->storage + start);
    arena->used = start + byteCount;
    return BTB_ARENA_OK;
}

size_t BtbArenaCheckpoint(const BtbArena *arena)
{
    return arena == NULL ? 0U : arena->used;
}

BtbArenaStatus BtbArenaRewind(BtbArena *arena, size_t checkpoint)
{
    if (arena == NULL || arena->storage == NULL || checkpoint > arena->used)
        return BTB_ARENA_INVALID;
    /* Rewind invalidates all allocations beyond the checkpoint. Their bytes
     * have not been freed or zeroed. Do not dereference their old pointers. */
    arena->used = checkpoint;
    return BTB_ARENA_OK;
}
