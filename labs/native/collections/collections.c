/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/collections.c
 *
 * PURPOSE:
 *   Implement small teaching containers with explicit failure boundaries.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "collections.h"

BtbResult BtbListAppend(BtbList *list, int value)
{
    if (list == NULL || list->count > BTB_COLLECTION_CAPACITY) return BTB_INVALID;
    if (list->count == BTB_COLLECTION_CAPACITY) return BTB_FULL;
    list->values[list->count] = value;
    ++list->count;
    return BTB_OK;
}

BtbResult BtbStackPop(BtbList *list, int *value)
{
    if (list == NULL || value == NULL || list->count > BTB_COLLECTION_CAPACITY)
        return BTB_INVALID;
    if (list->count == 0) return BTB_EMPTY;
    --list->count;
    *value = list->values[list->count];
    return BTB_OK;
}

static int QueueValid(const BtbQueue *queue)
{
    return queue != NULL && queue->head < BTB_COLLECTION_CAPACITY &&
           queue->count <= BTB_COLLECTION_CAPACITY;
}

BtbResult BtbQueuePush(BtbQueue *queue, int value)
{
    if (!QueueValid(queue)) return BTB_INVALID;
    if (queue->count == BTB_COLLECTION_CAPACITY) return BTB_FULL;
    /* Both operands are bounded by capacity; wrap reuses released slots. */
    const size_t tail = (queue->head + queue->count) % BTB_COLLECTION_CAPACITY;
    queue->values[tail] = value;
    ++queue->count;
    return BTB_OK;
}

BtbResult BtbQueuePop(BtbQueue *queue, int *value)
{
    if (!QueueValid(queue) || value == NULL) return BTB_INVALID;
    if (queue->count == 0) return BTB_EMPTY;
    *value = queue->values[queue->head];
    queue->head = (queue->head + 1U) % BTB_COLLECTION_CAPACITY;
    --queue->count;
    return BTB_OK;
}

BtbResult BtbListFind(const BtbList *list, int value, size_t *index)
{
    if (list == NULL || index == NULL || list->count > BTB_COLLECTION_CAPACITY)
        return BTB_INVALID;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->values[i] == value) {
            *index = i;
            return BTB_OK;
        }
    }
    return BTB_NOT_FOUND;
}

BtbResult BtbListSort(BtbList *list)
{
    if (list == NULL || list->count > BTB_COLLECTION_CAPACITY) return BTB_INVALID;
    /* Insertion sort maintains a sorted prefix and moves only greater values.
       This makes equal values stable, useful when later sorting records. */
    for (size_t i = 1; i < list->count; ++i) {
        const int saved = list->values[i];
        size_t j = i;
        while (j > 0 && list->values[j - 1U] > saved) {
            list->values[j] = list->values[j - 1U];
            --j;
        }
        list->values[j] = saved;
    }
    return BTB_OK;
}

BtbResult BtbListFindSorted(const BtbList *list, int value, size_t *index)
{
    if (list == NULL || index == NULL || list->count > BTB_COLLECTION_CAPACITY)
        return BTB_INVALID;
    size_t first = 0;
    size_t last = list->count;
    /* Half-open interval [first,last) permits an empty search without
       count - 1 underflow. Subtraction also avoids first + last overflow. */
    while (first < last) {
        const size_t middle = first + (last - first) / 2U;
        if (list->values[middle] < value) first = middle + 1U;
        else last = middle;
    }
    if (first == list->count || list->values[first] != value) return BTB_NOT_FOUND;
    *index = first;
    return BTB_OK;
}
