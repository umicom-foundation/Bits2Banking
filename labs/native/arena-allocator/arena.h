/*-----------------------------------------------------------------------------
 * Bits to Banking — Native Learning
 * File: labs/native/arena-allocator/arena.h
 * PURPOSE: Teach bounded, caller-owned allocation from one memory region.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_LEARNING_ARENA_H
#define BITS2BANKING_LEARNING_ARENA_H

#include <stddef.h>

typedef enum BtbArenaStatus {
    BTB_ARENA_OK = 0,
    BTB_ARENA_INVALID = 1,
    BTB_ARENA_NO_SPACE = 2
} BtbArenaStatus;

typedef struct BtbArena {
    unsigned char *storage; /* Borrowed: caller owns these bytes. */
    size_t capacity;
    size_t used;
} BtbArena;

/* No heap allocation. Keep storage alive for the arena and every borrowed
 * result. Failure leaves the existing arena unchanged. */
BtbArenaStatus BtbArenaInitialise(BtbArena *arena, void *storage, size_t capacity);

/* Reserve byteCount bytes with a power-of-two address alignment. On failure,
 * both *outMemory and the used count remain unchanged. Do not retain pointers
 * after rewinding past their allocation or after releasing the backing buffer. */
BtbArenaStatus BtbArenaAllocate(BtbArena *arena, size_t byteCount,
                                size_t alignment, void **outMemory);

/* Checkpoints are offsets within this arena. A checkpoint must not be
 * transferred between two arenas or reused after an unrelated rewind. */
size_t BtbArenaCheckpoint(const BtbArena *arena);
BtbArenaStatus BtbArenaRewind(BtbArena *arena, size_t checkpoint);

#endif
