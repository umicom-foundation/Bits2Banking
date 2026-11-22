/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/classroom-chain/test_chain.c
 *
 * PURPOSE:
 *   Check deterministic proof bytes, replay rules, refusal and ABI parity.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ATTEMPTS = 65536 };
static const ClassroomTransfer first_payment = {0, 1, 5};

#define EXPECT(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "line %d: %s\n", __LINE__, #condition); \
        return EXIT_FAILURE; \
    } \
} while (0)

static int ledger(void)
{
    ClassroomChain chain = {0};
    ClassroomBalance balances;
    EXPECT(classroom_replay(&chain, &balances));
    EXPECT(balances.units[0] == 12U && balances.units[1] == 0U && balances.units[2] == 0U);
    EXPECT(classroom_append(&chain, first_payment, 2U, ATTEMPTS));

    /* Pin output from an independent byte encoding and SHA-256 calculation.
     * A self-consistent change to miner and verifier must not pass this check. */
    EXPECT(chain.blocks[0].nonce == 82U);
    char digest[UMI_SHA256_HEX_CAPACITY];
    UmiSha256Hex(chain.blocks[0].digest, digest);
    EXPECT(strcmp(digest, "00c69665618e37387b5d75ec8ed21fdd849df7d8beaab2398d10e5a0a2b33043") == 0);
    EXPECT(classroom_append(&chain, (ClassroomTransfer){1, 2, 2}, 0U, ATTEMPTS));
    EXPECT(classroom_replay(&chain, &balances));
    EXPECT(balances.units[0] == 9U && balances.units[1] == 3U && balances.units[2] == 4U);
    return EXIT_SUCCESS;
}

static int refusal(void)
{
    ClassroomChain chain = {0};
    unsigned char before[sizeof(chain)];
    memcpy(before, &chain, sizeof(chain));
    /* Nonce zero is a known failing proof, and an exhausted search may not
     * publish a partially filled block or consume any ledger units. */
    EXPECT(!classroom_append(&chain, first_payment, 2U, 1U));
    EXPECT(!classroom_append(&chain, first_payment, 2U, ATTEMPTS + 1U));
    EXPECT(!classroom_append(&chain, (ClassroomTransfer){1, 0, 2}, 1U, ATTEMPTS));
    EXPECT(!classroom_append(&chain, (ClassroomTransfer){0, 1, UINT32_MAX}, 2U, ATTEMPTS));
    EXPECT(!classroom_append(&chain, (ClassroomTransfer){0, 0, 1}, 2U, ATTEMPTS));
    EXPECT(!classroom_append(&chain, (ClassroomTransfer){0, 3, 1}, 2U, ATTEMPTS));
    EXPECT(!classroom_append(&chain, first_payment, 3U, ATTEMPTS));
    EXPECT(memcmp(before, &chain, sizeof(chain)) == 0);

    for (size_t position = 0; position < CLASSROOM_BLOCK_LIMIT; ++position) {
        const uint32_t sender = (uint32_t)(position % 2U);
        EXPECT(classroom_append(&chain, (ClassroomTransfer){sender, 1U - sender, 1}, 2U, ATTEMPTS));
    }
    memcpy(before, &chain, sizeof(chain));
    EXPECT(!classroom_append(&chain, first_payment, 2U, ATTEMPTS));
    EXPECT(memcmp(before, &chain, sizeof(chain)) == 0);
    return EXIT_SUCCESS;
}

static int tamper(void)
{
    ClassroomChain chain = {0};
    EXPECT(classroom_append(&chain, first_payment, 2U, ATTEMPTS));
    EXPECT(classroom_append(&chain, (ClassroomTransfer){1, 2, 2}, 0U, ATTEMPTS));
    const ClassroomBalance prior = {{42, 42, 42}};
    ClassroomBalance balances = prior;

    /* Change one component at a time. The verifier must refuse to publish
     * a replacement balance even when later blocks were present. */
    ClassroomChain changed = chain;
    ++changed.blocks[0].transfer.units;
    EXPECT(!classroom_replay(&changed, &balances));
    changed = chain;
    changed.blocks[1].parent[1] ^= 1U;
    EXPECT(!classroom_replay(&changed, &balances));
    changed = chain;
    changed.blocks[1].digest[31] ^= 1U;
    EXPECT(!classroom_replay(&changed, &balances));
    changed = chain;
    changed.length = CLASSROOM_BLOCK_LIMIT + 1U;
    EXPECT(!classroom_replay(&changed, &balances));
    EXPECT(memcmp(prior.units, balances.units, sizeof(balances.units)) == 0);
    return EXIT_SUCCESS;
}

static int forks(void)
{
    ClassroomChain current = {0};
    EXPECT(classroom_append(&current, first_payment, 2U, ATTEMPTS));
    ClassroomChain alternative = current;
    EXPECT(classroom_append(&current, (ClassroomTransfer){1, 2, 2}, 0U, ATTEMPTS));
    EXPECT(classroom_append(&alternative, (ClassroomTransfer){1, 0, 3}, 2U, ATTEMPTS));
    EXPECT(classroom_choose(&current, &alternative) == CLASSROOM_KEEP_CURRENT);
    EXPECT(classroom_append(&alternative, (ClassroomTransfer){0, 1, 1}, 1U, ATTEMPTS));
    EXPECT(classroom_choose(&current, &alternative) == CLASSROOM_ADOPT_CANDIDATE);

    ClassroomChain spliced = alternative;
    /* A valid block from a sibling history does not make a valid successor. */
    spliced.blocks[1] = current.blocks[1];
    EXPECT(classroom_choose(&current, &spliced) == CLASSROOM_KEEP_CURRENT);
    EXPECT(classroom_choose(&spliced, &alternative) == CLASSROOM_ADOPT_CANDIDATE);
    EXPECT(classroom_choose(&spliced, NULL) == CLASSROOM_NO_VALID_HISTORY);
    return EXIT_SUCCESS;
}

#ifdef CLASSROOM_TEST_ASM
int classroom_meets_target_asm(const uint8_t digest[CLASSROOM_DIGEST_BYTES]);

static int assembly(void)
{
    uint8_t bytes[CLASSROOM_DIGEST_BYTES];
    memset(bytes, 0xE3, sizeof(bytes));
    /* Hold later bytes nonzero and compare every possible leading byte. */
    for (unsigned value = 0; value <= UINT8_MAX; ++value) {
        bytes[0] = (uint8_t)value;
        EXPECT(classroom_meets_target(bytes) == classroom_meets_target_asm(bytes));
    }
    EXPECT(classroom_meets_target(NULL) == classroom_meets_target_asm(NULL));
    return EXIT_SUCCESS;
}
#endif

int main(int argc, char **argv)
{
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "ledger") == 0) {
        return ledger();
    }
    if (strcmp(argv[1], "refusal") == 0) {
        return refusal();
    }
    if (strcmp(argv[1], "tamper") == 0) {
        return tamper();
    }
    if (strcmp(argv[1], "forks") == 0) {
        return forks();
    }
#ifdef CLASSROOM_TEST_ASM
    if (strcmp(argv[1], "assembly") == 0) {
        return assembly();
    }
#endif
    return EXIT_FAILURE;
}
