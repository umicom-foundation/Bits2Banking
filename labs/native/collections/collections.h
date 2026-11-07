/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/collections/collections.h
 *
 * PURPOSE:
 *   Teach bounded sequences, a queue and search contracts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_COLLECTIONS_H
#define BTB_COLLECTIONS_H
#include <stddef.h>
#define BTB_COLLECTION_CAPACITY 8U
typedef enum { BTB_OK, BTB_INVALID, BTB_FULL, BTB_EMPTY, BTB_NOT_FOUND } BtbResult;
typedef struct { int values[BTB_COLLECTION_CAPACITY]; size_t count; } BtbList;
typedef struct {
    int values[BTB_COLLECTION_CAPACITY];
    size_t head;
    size_t count;
} BtbQueue;
/* Start both models with = {0}. Outputs are changed only on success.
   The caller owns each model; this lesson has no allocation or threads.
   Output pointers must address writable objects outside the model storage. */
BtbResult BtbListAppend(BtbList *list, int value);
BtbResult BtbStackPop(BtbList *list, int *value);
BtbResult BtbQueuePush(BtbQueue *queue, int value);
BtbResult BtbQueuePop(BtbQueue *queue, int *value);
BtbResult BtbListFind(const BtbList *list, int value, size_t *index);
BtbResult BtbListSort(BtbList *list);
/* Precondition: values are sorted in ascending order, for example by Sort.
   Returns the first equal value. The empty list is permitted.
   Validation of sortedness is a separate O(n) task, not hidden in this search. */
BtbResult BtbListFindSorted(const BtbList *list, int value, size_t *index);
#endif
