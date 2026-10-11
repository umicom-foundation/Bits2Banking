/*-----------------------------------------------------------------------------
 * Bits2Banking Sv39 demo — read-only simulation, not kernel address space.
 * AUTHOR: Sammy Hegab, Umicom Foundation | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "sv39.h"
#include <stdio.h>

int main(void)
{
    BtbSv39Space space;
    const uint64_t virtualFrame = UINT64_C(0x40201000);
    const uint64_t physicalFrame = UINT64_C(0x9000);
    if (BtbSv39MapOne(&space, virtualFrame, physicalFrame,
                      BTB_SV39_READ | BTB_SV39_WRITE) != BTB_SV39_OK)
        return 1;
    uint64_t physical = 0U;
    if (BtbSv39Translate(&space, virtualFrame + 0x120U,
                         BTB_SV39_READ, &physical) != BTB_SV39_OK)
        return 1;
    printf("Virtual address: 0x%llx\nPhysical address: 0x%llx\n",
           (unsigned long long)(virtualFrame + 0x120U),
           (unsigned long long)physical);
    return physical == 0x9120U ? 0 : 1;
}
