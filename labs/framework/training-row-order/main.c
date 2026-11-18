/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/training-row-order/main.c
 *
 * PURPOSE:
 *   Visit a fixed training partition exactly once, including its shorter final batch.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/ai/training/sample_order.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Row indices belong to this already-selected training partition. The
     * held-out IDs are deliberately outside it; shuffling cannot choose them. */
    const unsigned trainingIds[7] = {10U,20U,30U,40U,50U,60U,70U};
    const unsigned evaluationIds[2] = {80U,90U};
    const uint32_t expected[7] = {2U,0U,6U,3U,4U,5U,1U};
    uint32_t order[7], replay[7];
    unsigned char visited[7] = {0};
    const uint64_t seed = 48U;
    if (UmiAiTrainingSampleOrder(7U, seed, order, 7U) != UMI_STATUS_OK ||
        UmiAiTrainingSampleOrder(7U, seed, replay, 7U) != UMI_STATUS_OK ||
        memcmp(order, replay, sizeof order) || memcmp(order, expected, sizeof order))
        return 1;
    puts("Umicom row-order laboratory: no model training occurs.");
    size_t batches = 0U, rows = 0U;
    for (size_t start = 0U; start < 7U;) {
        /* Subtract before choosing the batch length; the last batch contains
         * one row. Fixed-size padding or dropping the tail is a separate policy. */
        size_t remaining = 7U - start;
        size_t take = remaining < 3U ? remaining : 3U;
        printf("batch %zu:", ++batches);
        for (size_t j = 0U; j < take; ++j) {
            uint32_t row = order[start + j];
            if (row >= 7U || visited[row]) return 2;
            visited[row] = 1U;
            printf(" %u", trainingIds[row]);
            ++rows;
        }
        putchar('\n');
        start += take;
    }
    for (size_t i = 0U; i < 7U; ++i) if (!visited[i]) return 3;
    printf("rows=%zu batches=%zu seed=%llu temporary-payload=%zu bytes\n",
        rows, batches, (unsigned long long)seed, sizeof order);
    printf("held out: %u %u; source row order unchanged\n", evaluationIds[0], evaluationIds[1]);
    return rows == 7U && batches == 3U ? 0 : 4;
}
