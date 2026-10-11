/* Bits2Banking physical memory — fictional frame inventory, C23. */
#include "frame_pool.h"
#include <stdio.h>
int main(void)
{
    BtbFramePool pool;
    if (BtbFramePoolInit(&pool, UINT64_C(0x80000000)) != BTB_FRAME_OK) return 1;
    uint64_t frame = 0U;
    if (BtbFramePoolAllocate(&pool, &frame) != BTB_FRAME_OK) return 1;
    printf("First available frame: 0x%llx\nReserved frames: %zu\nOwned frames: %zu\n",
           (unsigned long long)frame, pool.reservedCount, pool.ownedCount);
    if (frame != UINT64_C(0x80008000)) return 1;
    return BtbFramePoolRelease(&pool, frame) == BTB_FRAME_OK ? 0 : 1;
}
