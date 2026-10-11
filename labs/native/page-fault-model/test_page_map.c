/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT */
#include "page_map.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(x) do {if (!(x)) {fprintf(stderr,"FAIL %s:%d %s\n",__FILE__,__LINE__,#x);return 1;}}while(0)
static int Basic(void)
{
    BtbAddressSpace space;
    BtbAddressSpaceInit(&space);
    uint64_t physical = UINT64_C(0xdeadbeef);
    CHECK(BtbPageMap(&space, UINT64_C(0x1000), UINT64_C(0x80001000),
                     BTB_PAGE_READ | BTB_PAGE_EXECUTE) == BTB_PAGE_OK);
    CHECK(BtbPageMap(&space, UINT64_C(0x2000), UINT64_C(0x80002000),
                     BTB_PAGE_READ | BTB_PAGE_WRITE) == BTB_PAGE_OK);
    CHECK(BtbPageAccessAddress(&space, 0x102aU, BTB_ACCESS_READ, &physical) == BTB_PAGE_OK);
    CHECK(physical == UINT64_C(0x8000102a));
    CHECK(BtbPageAccessAddress(&space, 0x102aU, BTB_ACCESS_WRITE, &physical)
          == BTB_PAGE_PROTECTION_FAULT);
    CHECK(physical == UINT64_C(0x8000102a));
    CHECK(BtbPageAccessAddress(&space, 0x3000U, BTB_ACCESS_EXECUTE, &physical)
          == BTB_PAGE_NOT_MAPPED);
    CHECK(physical == UINT64_C(0x8000102a));
    CHECK(BtbPageAccessAddress(&space, 0x2010U, BTB_ACCESS_WRITE, &physical) == BTB_PAGE_OK);
    CHECK(physical == UINT64_C(0x80002010));
    CHECK(BtbPageUnmap(&space, 0x2000U) == BTB_PAGE_OK);
    CHECK(BtbPageAccessAddress(&space, 0x2010U, BTB_ACCESS_READ, &physical)
          == BTB_PAGE_NOT_MAPPED);
    CHECK(space.mappingCount == 1U);
    return 0;
}
static int Boundaries(void)
{
    BtbAddressSpace space;
    BtbAddressSpaceInit(&space);
    CHECK(BtbPageMap(&space, 0x1000U, 0x2000U, BTB_PAGE_WRITE) == BTB_PAGE_INVALID_ARGUMENT);
    CHECK(BtbPageMap(&space, 0x1000U, 0x2000U, 7U) == BTB_PAGE_INVALID_ARGUMENT);
    CHECK(BtbPageMap(&space, 0x1001U, 0x2000U, BTB_PAGE_READ) == BTB_PAGE_INVALID_ARGUMENT);
    CHECK(BtbPageMap(&space, UINT64_C(1) << 39U, 0x2000U, BTB_PAGE_READ)
          == BTB_PAGE_NON_CANONICAL);
    for (uint64_t i = 0U; i < BTB_MAX_PAGE_MAPPINGS; ++i)
        CHECK(BtbPageMap(&space, i * BTB_PAGE_BYTES, (i + 100U) * BTB_PAGE_BYTES,
                         BTB_PAGE_READ) == BTB_PAGE_OK);
    BtbAddressSpace old = space;
    CHECK(BtbPageMap(&space, 0x100000U, 0x200000U, BTB_PAGE_READ) == BTB_PAGE_OUT_OF_SPACE);
    CHECK(BtbPageMap(&space, 0x1000U, 0x200000U, BTB_PAGE_READ) == BTB_PAGE_ALREADY_MAPPED);
    CHECK(memcmp(&old, &space, sizeof old) == 0);
    CHECK(BtbPageUnmap(&space, 0U) == BTB_PAGE_OK);
    CHECK(BtbPageMap(&space, UINT64_C(0xffffffc000001000), 0x200000U,
                     BTB_PAGE_READ) == BTB_PAGE_OK);
    uint64_t physical = 123U;
    CHECK(BtbPageAccessAddress(&space, UINT64_C(0xffffffc000001055), BTB_ACCESS_READ,
                               &physical) == BTB_PAGE_OK);
    CHECK(physical == 0x200055U);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    const int passed = strcmp(argv[1], "basic") == 0 ? Basic() :
                       strcmp(argv[1], "boundaries") == 0 ? Boundaries() : 2;
    if (passed == 0) puts("[OK] Simulated Sv39 page access and refusal.");
    return passed;
}
