/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/test_collections.c
 *
 * PURPOSE:
 *   Check container boundaries and compare searches over all small inputs.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "collections.h"
#include <limits.h>
#include <stdio.h>
#define CHECK(expression) do { if (!(expression)) { \
    fprintf(stderr, "Line %d: %s\n", __LINE__, #expression); return 1; } } while (0)
int main(void)
{
    BtbList list = {0};
    int output = 99;
    CHECK(BtbStackPop(&list, &output) == BTB_EMPTY && output == 99);
    CHECK(BtbListAppend(NULL, 1) == BTB_INVALID);
    for (size_t i = 0; i < BTB_COLLECTION_CAPACITY; ++i)
        CHECK(BtbListAppend(&list, (int)i) == BTB_OK);
    CHECK(BtbListAppend(&list, 20) == BTB_FULL);
    CHECK(list.count == BTB_COLLECTION_CAPACITY && list.values[7] == 7);
    for (size_t i = BTB_COLLECTION_CAPACITY; i > 0; --i) {
        CHECK(BtbStackPop(&list, &output) == BTB_OK);
        CHECK(output == (int)(i - 1U));
    }
    BtbQueue queue = {0};
    CHECK(BtbQueuePop(&queue, &output) == BTB_EMPTY);
    for (int i = 0; i < 8; ++i) CHECK(BtbQueuePush(&queue, i) == BTB_OK);
    CHECK(BtbQueuePush(&queue, 100) == BTB_FULL);
    for (int i = 0; i < 4; ++i) {
        CHECK(BtbQueuePop(&queue, &output) == BTB_OK && output == i);
        CHECK(BtbQueuePush(&queue, i + 8) == BTB_OK);
    }
    for (int i = 4; i < 12; ++i)
        CHECK(BtbQueuePop(&queue, &output) == BTB_OK && output == i);
    queue.head = BTB_COLLECTION_CAPACITY;
    CHECK(BtbQueuePush(&queue, 1) == BTB_INVALID);
    CHECK(BtbQueuePop(&queue, &output) == BTB_INVALID);
    list.count = BTB_COLLECTION_CAPACITY + 1U;
    CHECK(BtbListSort(&list) == BTB_INVALID);
    size_t index = 42;
    CHECK(BtbListFind(&list, 0, &index) == BTB_INVALID && index == 42);
    CHECK(BtbListFindSorted(&list, 0, &index) == BTB_INVALID && index == 42);
    CHECK(BtbStackPop(&list, &output) == BTB_INVALID);
    CHECK(BtbListFind(NULL, 1, &index) == BTB_INVALID);
    list.count = 0;
    CHECK(BtbListFindSorted(&list, 0, &index) == BTB_NOT_FOUND && index == 42);
    CHECK(BtbListFind(&list, 0, NULL) == BTB_INVALID);
    CHECK(BtbStackPop(&list, NULL) == BTB_INVALID);
    /* Enumerate all 81 four-element inputs over {-1,0,1}. A simple frequency
       count is an independent oracle for sorting; linear search checks the
       binary result, including duplicate values and absent targets. */
    for (unsigned encoding = 0; encoding < 81U; ++encoding) {
        unsigned remaining = encoding;
        int counts[3] = {0};
        list.count = 0;
        for (unsigned i = 0; i < 4U; ++i) {
            unsigned digit = remaining % 3U;
            remaining /= 3U;
            ++counts[digit];
            CHECK(BtbListAppend(&list, (int)digit - 1) == BTB_OK);
        }
        CHECK(BtbListSort(&list) == BTB_OK);
        size_t cursor = 0;
        for (int value = -1; value <= 1; ++value)
            for (int n = 0; n < counts[value + 1]; ++n)
                CHECK(list.values[cursor++] == value);
        for (int target = -2; target <= 2; ++target) {
            size_t linear = 42, binary = 42;
            const BtbResult expected = BtbListFind(&list, target, &linear);
            CHECK(BtbListFindSorted(&list, target, &binary) == expected);
            CHECK(linear == binary);
        }
    }
    list = (BtbList){ .values = {INT_MAX, 0, INT_MIN}, .count = 3 };
    CHECK(BtbListSort(&list) == BTB_OK);
    CHECK(list.values[0] == INT_MIN && list.values[2] == INT_MAX);
    return 0;
}
