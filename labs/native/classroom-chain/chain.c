/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/chain.c
 *
 * PURPOSE:
 *   Mine and independently replay a small synthetic proof-of-work ledger.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "chain.h"
#include "umicom/base/sha256.h"

#include <string.h>

enum { CLASSROOM_ATTEMPT_LIMIT = 65536 };

/* Domain bytes distinguish this worksheet from other uses of SHA-256. The
 * opening allocations below are fixed by this lab's version-one rules. */
static const char opening_record[] = "Bits2Banking classroom chain v1: opening units 12,0,0";
static const char block_domain[] = "BTB1";

static bool hash_bytes(const void *data, size_t length, uint8_t digest[CLASSROOM_DIGEST_BYTES])
{
    UmiSha256 state;
    UmiSha256Init(&state);
    return UmiSha256Update(&state, data, length) == UMI_STATUS_OK &&
           UmiSha256Final(&state, digest) == UMI_STATUS_OK;
}

static void write_u32_le(uint8_t output[4], uint32_t value)
{
    /* Write the defined byte order explicitly so struct padding and host
     * endianness cannot affect the proof. */
    for (unsigned byte = 0; byte < 4; ++byte) {
        output[byte] = (uint8_t)(value >> (byte * 8U));
    }
}

static bool block_digest(const ClassroomBlock *block, uint8_t digest[CLASSROOM_DIGEST_BYTES])
{
    enum { SCALAR_COUNT = 6, PREFIX_BYTES = sizeof(block_domain) - 1 };
    const uint32_t fields[SCALAR_COUNT] = {
        block->height, block->transfer.sender, block->transfer.receiver,
        block->transfer.units, block->reward_account, block->nonce
    };
    uint8_t encoded[PREFIX_BYTES + CLASSROOM_DIGEST_BYTES + 4 * SCALAR_COUNT];
    memcpy(encoded, block_domain, PREFIX_BYTES);
    memcpy(encoded + PREFIX_BYTES, block->parent, CLASSROOM_DIGEST_BYTES);
    /* Commit the prior digest and all six scalar fields in one canonical
     * encoding. The cached digest itself stays outside the hashed bytes. */
    for (size_t field = 0; field < SCALAR_COUNT; ++field) {
        write_u32_le(encoded + PREFIX_BYTES + CLASSROOM_DIGEST_BYTES + field * 4U, fields[field]);
    }
    return hash_bytes(encoded, sizeof(encoded), digest);
}

int classroom_meets_target(const uint8_t digest[CLASSROOM_DIGEST_BYTES])
{
    /* One zero leading byte sets an easy fixed target. Its chance is 1/256
     * per attempt under the uniform-digest model. */
    return digest != NULL && digest[0] == 0U;
}

static bool apply_transfer(ClassroomBalance *balance, ClassroomTransfer transfer, uint32_t reward_account)
{
    if (transfer.sender >= CLASSROOM_ACCOUNT_COUNT || transfer.receiver >= CLASSROOM_ACCOUNT_COUNT ||
        reward_account >= CLASSROOM_ACCOUNT_COUNT || transfer.sender == transfer.receiver || transfer.units == 0U) {
        return false;
    }
    if (balance->units[transfer.sender] < transfer.units) {
        return false;
    }

    /* Check the sender before crediting the reward. The entire lab can issue
     * at most two units per block, so destination arithmetic stays bounded. */
    balance->units[transfer.sender] -= transfer.units;
    balance->units[transfer.receiver] += transfer.units;
    balance->units[reward_account] += CLASSROOM_REWARD_UNITS;
    return true;
}

bool classroom_replay(const ClassroomChain *chain, ClassroomBalance *balance)
{
    if (chain == NULL || balance == NULL || chain->length > CLASSROOM_BLOCK_LIMIT) {
        return false;
    }

    ClassroomBalance proposed = {{CLASSROOM_INITIAL_UNITS, 0, 0}};
    uint8_t expected_parent[CLASSROOM_DIGEST_BYTES];
    if (!hash_bytes(opening_record, sizeof(opening_record) - 1U, expected_parent)) {
        return false;
    }

    /* Replay in order, recomputing proof per block. Cached balances from a
     * peer would not tell a verifier whether any earlier transfer was valid. */
    for (size_t position = 0; position < chain->length; ++position) {
        const ClassroomBlock *block = &chain->blocks[position];
        uint8_t computed[CLASSROOM_DIGEST_BYTES];
        if (block->height != (uint32_t)(position + 1U) || block->nonce >= CLASSROOM_ATTEMPT_LIMIT ||
            memcmp(block->parent, expected_parent, sizeof(expected_parent)) != 0 ||
            !block_digest(block, computed) || !classroom_meets_target(computed) ||
            memcmp(block->digest, computed, sizeof(computed)) != 0 ||
            !apply_transfer(&proposed, block->transfer, block->reward_account)) {
            return false;
        }
        memcpy(expected_parent, computed, sizeof(expected_parent));
    }

    *balance = proposed;
    return true;
}

bool classroom_append(ClassroomChain *chain, ClassroomTransfer transfer,
                      uint32_t reward_account, uint32_t attempts)
{
    if (chain == NULL || chain->length >= CLASSROOM_BLOCK_LIMIT || attempts == 0U ||
        attempts > CLASSROOM_ATTEMPT_LIMIT) {
        return false;
    }

    ClassroomBalance staged_balance;
    if (!classroom_replay(chain, &staged_balance) || !apply_transfer(&staged_balance, transfer, reward_account)) {
        return false;
    }

    ClassroomBlock next = {0};
    next.height = (uint32_t)(chain->length + 1U);
    next.transfer = transfer;
    next.reward_account = reward_account;
    if (chain->length != 0U) {
        memcpy(next.parent, chain->blocks[chain->length - 1U].digest, sizeof(next.parent));
    } else if (!hash_bytes(opening_record, sizeof(opening_record) - 1U, next.parent)) {
        return false;
    }

    /* Work happens on a temporary block. Commit only a verified proof so a
     * refusal leaves the caller's existing history available for inspection. */
    for (uint32_t attempt = 0; attempt < attempts; ++attempt) {
        next.nonce = attempt;
        if (!block_digest(&next, next.digest)) {
            return false;
        }
        if (classroom_meets_target(next.digest)) {
            chain->blocks[chain->length] = next;
            ++chain->length;
            return true;
        }
    }
    return false;
}

ClassroomChoice classroom_choose(const ClassroomChain *current, const ClassroomChain *candidate)
{
    ClassroomBalance balance;
    const bool current_valid = classroom_replay(current, &balance);
    const bool candidate_valid = classroom_replay(candidate, &balance);
    if (candidate_valid && (!current_valid || candidate->length > current->length)) {
        return CLASSROOM_ADOPT_CANDIDATE;
    }
    return current_valid ? CLASSROOM_KEEP_CURRENT : CLASSROOM_NO_VALID_HISTORY;
}
