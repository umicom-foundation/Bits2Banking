/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT */
#include "page_map.h"
#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    BtbAddressSpace process;
    uint64_t physical = 0U;
    BtbAddressSpaceInit(&process);
    if (BtbPageMap(&process, UINT64_C(0x1000), UINT64_C(0x80001000),
                   BTB_PAGE_READ | BTB_PAGE_EXECUTE) != BTB_PAGE_OK ||
        BtbPageMap(&process, UINT64_C(0x2000), UINT64_C(0x80002000),
                   BTB_PAGE_READ | BTB_PAGE_WRITE) != BTB_PAGE_OK)
        return 1;
    BtbPageStatus status = BtbPageAccessAddress(&process, UINT64_C(0x1018),
                                                BTB_ACCESS_EXECUTE, &physical);
    printf("Execute instruction: %s, fictional physical address 0x%" PRIx64 "\n",
           BtbPageStatusText(status), physical);
    status = BtbPageAccessAddress(&process, UINT64_C(0x1018), BTB_ACCESS_WRITE, &physical);
    printf("Write to code page: %s\n", BtbPageStatusText(status));
    status = BtbPageAccessAddress(&process, UINT64_C(0x3000), BTB_ACCESS_READ, &physical);
    printf("Read unmapped address: %s\n", BtbPageStatusText(status));
    return status == BTB_PAGE_NOT_MAPPED ? 0 : 1;
}
