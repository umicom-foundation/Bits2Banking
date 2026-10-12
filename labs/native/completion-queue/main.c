/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT */
#include "queue.h"
#include <stdio.h>
int main(void)
{
    BtbCompletionQueue queue={0};
    if(BtbCompletionQueueInit(&queue)!=BTB_QUEUE_OK)return 1;
    BtbCompletion value={.requestId=42U,.bytesTransferred=128U,.result=BTB_COMPLETION_SUCCESS};
    if(BtbCompletionQueuePush(&queue,value)!=BTB_QUEUE_OK)return 1;
    BtbCompletion received={0};
    if(BtbCompletionQueuePop(&queue,&received)!=BTB_QUEUE_OK)return 1;
    printf("Collected completion for request %u: %u bytes.\n",
        (unsigned)received.requestId,(unsigned)received.bytesTransferred);
    return 0;
}
