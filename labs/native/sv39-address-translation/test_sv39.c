/*-----------------------------------------------------------------------------
 * Bits2Banking Sv39 walker tests — no MMU or privileged operations.
 * AUTHOR: Sammy Hegab, Umicom Foundation | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "sv39.h"
#include <stdio.h>
#include <string.h>
#define CHECK(ok) do { if (!(ok)) { \
  fprintf(stderr,"FAILED %s:%d: %s\n",__FILE__,__LINE__,#ok); return 1; \
} } while (0)
int main(void)
{
    BtbSv39Space space = {0};
    const uint64_t virtualFrame = UINT64_C(0x40201000);
    uint64_t out = UINT64_C(0xdeadbeef);
    CHECK(BtbSv39Translate(&space, virtualFrame, BTB_SV39_READ, &out)
          == BTB_SV39_UNMAPPED && out == UINT64_C(0xdeadbeef));
    CHECK(BtbSv39MapOne(&space, virtualFrame, 0x9000U,
                        BTB_SV39_READ | BTB_SV39_WRITE) == BTB_SV39_OK);
    CHECK(BtbSv39Translate(&space, virtualFrame + 0x120U, BTB_SV39_READ, &out)
          == BTB_SV39_OK && out == 0x9120U);
    CHECK(BtbSv39Translate(&space, virtualFrame + 0xfffU, BTB_SV39_WRITE, &out)
          == BTB_SV39_OK && out == 0x9fffU);
    out = UINT64_C(0xdeadbeef);
    CHECK(BtbSv39Translate(&space, virtualFrame, BTB_SV39_EXEC, &out)
          == BTB_SV39_PERMISSION_DENIED && out == UINT64_C(0xdeadbeef));
    CHECK(BtbSv39Translate(&space, virtualFrame + 4096U, BTB_SV39_READ, &out)
          == BTB_SV39_UNMAPPED && out == UINT64_C(0xdeadbeef));
    CHECK(BtbSv39Translate(&space, UINT64_C(0x0000008000000000),
                           BTB_SV39_READ, &out) == BTB_SV39_INVALID_ADDRESS);
    const BtbSv39Space old = space;
    CHECK(BtbSv39MapOne(&space, virtualFrame, 0x9001U, BTB_SV39_READ)
          == BTB_SV39_INVALID_ADDRESS && memcmp(&old,&space,sizeof old)==0);
    CHECK(BtbSv39MapOne(&space, virtualFrame, 0x9000U, BTB_SV39_WRITE)
          == BTB_SV39_INVALID_ADDRESS && memcmp(&old,&space,sizeof old)==0);
    CHECK(BtbSv39MapOne(&space, virtualFrame+1U, 0x9000U, BTB_SV39_READ)
          == BTB_SV39_INVALID_ADDRESS && memcmp(&old,&space,sizeof old)==0);
    CHECK(BtbSv39MapOne(&space, virtualFrame, UINT64_MAX-4095U, BTB_SV39_READ)
          == BTB_SV39_INVALID_ADDRESS && memcmp(&old,&space,sizeof old)==0);
    /* Upper-half canonical virtual addresses are also supported. */
    CHECK(BtbSv39MapOne(&space, UINT64_C(0xffffffc000201000), 0xa000U,
                        BTB_SV39_READ | BTB_SV39_EXEC) == BTB_SV39_OK);
    CHECK(BtbSv39Translate(&space, UINT64_C(0xffffffc000201033),
                           BTB_SV39_EXEC, &out) == BTB_SV39_OK && out == 0xa033U);
    puts("[OK] Three-level page walk, canonical addresses, permissions and atomic mapping.");
    return 0;
}
