/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/chain.h
 *
 * PURPOSE:
 *   Describe a bounded, offline proof-of-work ledger for classroom experiments.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_CLASSROOM_CHAIN_H
#define BTB_CLASSROOM_CHAIN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum {
    CLASSROOM_ACCOUNT_COUNT = 3,
    CLASSROOM_BLOCK_LIMIT = 12,
    CLASSROOM_DIGEST_BYTES = 32,
    CLASSROOM_INITIAL_UNITS = 12,
    CLASSROOM_REWARD_UNITS = 2
};

typedef struct ClassroomTransfer {
    uint32_t sender;
    uint32_t receiver;
    uint32_t units;
} ClassroomTransfer;

typedef struct ClassroomBlock {
    uint32_t height;
    uint8_t parent[CLASSROOM_DIGEST_BYTES];
    ClassroomTransfer transfer;
    uint32_t reward_account;
    uint32_t nonce;
    uint8_t digest[CLASSROOM_DIGEST_BYTES];
} ClassroomBlock;

typedef struct ClassroomChain {
    size_t length;
    ClassroomBlock blocks[CLASSROOM_BLOCK_LIMIT];
} ClassroomChain;

typedef struct ClassroomBalance {
    uint32_t units[CLASSROOM_ACCOUNT_COUNT];
} ClassroomBalance;

typedef enum ClassroomChoice {
    CLASSROOM_NO_VALID_HISTORY,
    CLASSROOM_KEEP_CURRENT,
    CLASSROOM_ADOPT_CANDIDATE
} ClassroomChoice;

/* A zero-initialised chain starts with the fixed classroom opening balance.
 * Validate independently before publishing a new summary. Caller-owned inputs
 * and outputs stay disjoint, and failure leaves the output unchanged. */
bool classroom_replay(const ClassroomChain *chain, ClassroomBalance *balance);

/* Add one valid transfer and its fixed reward. Attempts start at nonce zero.
 * A bounded search prevents an unending lesson and never mutates on refusal. */
bool classroom_append(ClassroomChain *chain, ClassroomTransfer transfer,
                      uint32_t reward_account, uint32_t attempts);

/* A fixed target gives every valid block the same work score. Equal work
 * keeps the current branch. This function does not alter either history. */
ClassroomChoice classroom_choose(const ClassroomChain *current, const ClassroomChain *candidate);

/* This narrow C ABI lets another language check the classroom target on a
 * copied 32-byte digest. It establishes only the target comparison. */
int classroom_meets_target(const uint8_t digest[CLASSROOM_DIGEST_BYTES]);

#endif
