/* Bits2Banking physical frame ownership regression tests, C23. */
#include "frame_pool.h"
#include <stdio.h>
#include <string.h>
#define CHECK(expr) do { if (!(expr)) { \
  fprintf(stderr,"FAIL %s:%d: %s\n",__FILE__,__LINE__,#expr); return 1; \
} } while(0)
int main(void)
{
    BtbFramePool pool;
    CHECK(BtbFramePoolInit(&pool, UINT64_C(0x80000000)) == BTB_FRAME_OK);
    CHECK(pool.reservedCount == 8U && pool.ownedCount == 0U);
    CHECK(BtbFramePoolReserve(&pool, 12U, 4U) == BTB_FRAME_OK);
    CHECK(pool.reservedCount == 12U);
    BtbFramePool old = pool;
    CHECK(BtbFramePoolReserve(&pool, 10U, 4U) == BTB_FRAME_NOT_AVAILABLE);
    CHECK(memcmp(&old, &pool, sizeof old) == 0);
    CHECK(BtbFramePoolReserve(&pool, 127U, 2U) == BTB_FRAME_INVALID);
    CHECK(BtbFramePoolInit(&pool, UINT64_MAX - 1U) != BTB_FRAME_OK);
    CHECK(memcmp(&old, &pool, sizeof old) == 0);
    uint64_t previous = UINT64_C(0xbeef);
    CHECK(BtbFramePoolRelease(&pool, UINT64_C(0x80000000)) == BTB_FRAME_NOT_OWNED);
    uint64_t allocated[BTB_FRAME_COUNT] = {0};
    size_t count = 0U;
    while (count < BTB_FRAME_COUNT &&
           BtbFramePoolAllocate(&pool, &allocated[count]) == BTB_FRAME_OK) ++count;
    CHECK(count == BTB_FRAME_COUNT - pool.reservedCount);
    CHECK(pool.ownedCount == count);
    CHECK(BtbFramePoolAllocate(&pool, &previous) == BTB_FRAME_NOT_AVAILABLE);
    CHECK(previous == UINT64_C(0xbeef));
    CHECK(allocated[0] == UINT64_C(0x80008000));
    CHECK(BtbFramePoolRelease(&pool, allocated[0]) == BTB_FRAME_OK);
    CHECK(BtbFramePoolRelease(&pool, allocated[0]) == BTB_FRAME_NOT_OWNED);
    CHECK(pool.ownedCount == count - 1U);
    CHECK(BtbFramePoolAllocate(&pool, &previous) == BTB_FRAME_OK);
    CHECK(previous == allocated[0]);
    CHECK(pool.ownedCount == count);
    puts("[OK] Reserved, allocated, exhausted, reissued and refusal-atomic physical frames.");
    return 0;
}
