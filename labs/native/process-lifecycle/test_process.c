/* Bits2Banking | Sammy Hegab | Umicom Foundation | MIT */
#include "process.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(x) do {if (!(x)) {fprintf(stderr,"FAIL %s:%d %s\n",__FILE__,__LINE__,#x);return 1;}}while(0)
static int Lifecycle(void)
{
    BtbProcess p;
    CHECK(BtbProcessInit(&p, 34U) == BTB_PROCESS_OK);
    CHECK(p.state == BTB_PROCESS_NEW && p.revision == 1U);
    CHECK(BtbProcessApply(&p, BTB_EVENT_ADMIT, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_DISPATCH, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_YIELD, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_DISPATCH, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_WAIT, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_WAKE, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_DISPATCH, 0) == BTB_PROCESS_OK);
    CHECK(BtbProcessApply(&p, BTB_EVENT_EXIT, 17) == BTB_PROCESS_OK);
    CHECK(p.state == BTB_PROCESS_TERMINATED && p.exitCode == 17);
    CHECK(p.revision == 9U);
    BtbProcess copy = p;
    CHECK(BtbProcessApply(&p, BTB_EVENT_ADMIT, 0) == BTB_PROCESS_ILLEGAL_TRANSITION);
    CHECK(memcmp(&copy, &p, sizeof p) == 0);
    return 0;
}
static int Refusals(void)
{
    BtbProcess p = {0};
    CHECK(BtbProcessInit(&p, 0U) == BTB_PROCESS_INVALID_ARGUMENT);
    CHECK(BtbProcessInit(&p, 1U) == BTB_PROCESS_OK);
    BtbProcess copy = p;
    CHECK(BtbProcessApply(&p, BTB_EVENT_EXIT, 0) == BTB_PROCESS_ILLEGAL_TRANSITION);
    CHECK(BtbProcessApply(&p, BTB_EVENT_WAIT, 0) == BTB_PROCESS_ILLEGAL_TRANSITION);
    CHECK(BtbProcessApply(&p, BTB_EVENT_ADMIT, 1) == BTB_PROCESS_INVALID_ARGUMENT);
    CHECK(BtbProcessApply(&p, (BtbProcessEvent)99, 0) == BTB_PROCESS_INVALID_ARGUMENT);
    CHECK(memcmp(&copy, &p, sizeof p) == 0);
    p.revision = UINT32_MAX;
    copy = p;
    CHECK(BtbProcessApply(&p, BTB_EVENT_ADMIT, 0) == BTB_PROCESS_REVISION_EXHAUSTED);
    CHECK(memcmp(&copy, &p, sizeof p) == 0);
    return 0;
}
int main(int argc, char **argv)
{
    if (argc != 2) return 2;
    const int result = strcmp(argv[1], "lifecycle") == 0 ? Lifecycle() :
                       strcmp(argv[1], "refusals") == 0 ? Refusals() : 2;
    if (result == 0) puts("[OK] Simulated process transitions and atomic refusal.");
    return result;
}
