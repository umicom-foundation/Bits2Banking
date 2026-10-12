/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT
 * A queue is full when all completion slots are occupied; unrelated request
 * work must not overwrite an older accepted completion. */
#include "queue.h"
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL line %d: %s\n",__LINE__,#x); return 1; } } while (0)
int main(void)
{
    BtbCompletionQueue queue;
    CHECK(BtbCompletionQueueInit(&queue)==BTB_QUEUE_OK);
    BtbCompletion empty = {.requestId=99U,.bytesTransferred=7U,.result=BTB_COMPLETION_SUCCESS};
    CHECK(BtbCompletionQueuePop(&queue,&empty)==BTB_QUEUE_EMPTY);
    CHECK(empty.requestId==99U && empty.bytesTransferred==7U);
    for(uint32_t id=1U; id<=BTB_COMPLETION_CAPACITY; ++id) {
        BtbCompletion item = {.requestId=id,.bytesTransferred=id,.result=BTB_COMPLETION_SUCCESS};
        CHECK(BtbCompletionQueuePush(&queue,item)==BTB_QUEUE_OK);
    }
    BtbCompletion extra = {.requestId=123U,.result=BTB_COMPLETION_FAILURE};
    CHECK(BtbCompletionQueuePush(&queue,extra)==BTB_QUEUE_FULL);
    CHECK(BtbCompletionQueueCount(&queue)==BTB_COMPLETION_CAPACITY);
    for(uint32_t id=1U; id<=2U; ++id) {
        BtbCompletion item={0}; CHECK(BtbCompletionQueuePop(&queue,&item)==BTB_QUEUE_OK);
        CHECK(item.requestId==id && item.bytesTransferred==id);
    }
    CHECK(BtbCompletionQueuePush(&queue,extra)==BTB_QUEUE_OK);
    for(uint32_t id=3U; id<=4U; ++id) {
        BtbCompletion item={0}; CHECK(BtbCompletionQueuePop(&queue,&item)==BTB_QUEUE_OK);
        CHECK(item.requestId==id);
    }
    BtbCompletion item={0}; CHECK(BtbCompletionQueuePop(&queue,&item)==BTB_QUEUE_OK);
    CHECK(item.requestId==123U && item.result==BTB_COMPLETION_FAILURE);
    CHECK(BtbCompletionQueueCount(&queue)==0U);
    extra.requestId=0U;
    CHECK(BtbCompletionQueuePush(&queue,extra)==BTB_QUEUE_INVALID_ARGUMENT);
    CHECK(BtbCompletionQueueCount(&queue)==0U);
    puts("Completion FIFO: full/empty handling, copied results and wraparound passed.");
    return 0;
}
