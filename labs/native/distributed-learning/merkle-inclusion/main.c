/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/distributed-learning/merkle-inclusion/main.c
 *
 * PURPOSE:
 *   Verify and corrupt synthetic audit-record inclusion evidence through
 *   Framework's portable, count-bound Merkle proof service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/record_chain/merkle.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    uint8_t syntheticDigests[3U * 32U] = {0};
    uint8_t anchoredRoot[32], corrupted[32];
    UmiRecordChainMerkleProof membership = {0};
    for (size_t i = 0U; i < 3U; ++i)
        syntheticDigests[i * 32U] = (uint8_t)(i + 21U);
    if (umi_record_chain_merkle_prove(syntheticDigests, 3U, 1U,
                                     &membership, anchoredRoot) != UMI_STATUS_OK)
        return 1;
    if (umi_record_chain_merkle_verify(syntheticDigests + 32U,
                                      &membership, anchoredRoot) != UMI_STATUS_OK)
        return 2;
    memcpy(corrupted, syntheticDigests + 32U, 32U);
    corrupted[15] = (uint8_t)(corrupted[15] ^ 1U);
    if (umi_record_chain_merkle_verify(corrupted, &membership,
                                      anchoredRoot) != UMI_STATUS_INVALID_STATE)
        return 3;
    puts("Verified one leaf of three against an independently preserved root.");
    puts("Mutated leaf rejected; this is not a blockchain consensus demonstration.");
    return 0;
}
