/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/host-cache-budget/main.c
 *
 * PURPOSE:
 *   Calculate a dense-cache token budget from synthetic fixed costs and memory observations, then demonstrate unavailable plans.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/local_models/memory_plan.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const uint64_t mib=UINT64_C(1048576);
    UmiDesktopSystemSnapshot *snapshot=calloc(1U,sizeof *snapshot);
    if(snapshot==NULL)return 1;
    /* These are synthetic numbers used to exercise arithmetic. Setting the
     * fixture flag below shows why stored examples cannot admit a real model. */
    snapshot->memoryStatus=UMI_STATUS_OK;
    snapshot->memory.totalBytes=16U*1024U*mib;
    snapshot->memory.availableBytes=8U*1024U*mib;
    UmiModelMemoryRequirements costs={6U*1024U*mib,0U,512U*mib,256U*mib,
        UMI_MODEL_MEMORY_WEIGHTS|UMI_MODEL_MEMORY_WORKSPACE|UMI_MODEL_MEMORY_RUNTIME};
    UmiModelDenseKvShape shape={4096U,2U,32U,8U,8U,128U,128U,2U,2U};
    UmiModelHostKvPlan plan;
    UmiStatus status=UmiModelDenseKvPlanHostMemory(&costs,&shape,snapshot,10U,1000U,512U*mib,&plan);
    if(status!=UMI_STATUS_OK || !plan.cache_plan_available ||
        plan.cache.affordable_tokens!=3072U || plan.cache.bytes_per_token!=262144U ||
        plan.selected_memory.remaining_bytes!=0U || plan.cache.request_fits) {
        free(snapshot);return 1;
    }
    printf("Umicom synthetic host/cache exercise\n"
        "Requested token capacity: %" PRIu64 "\n"
        "Affordable token capacity: %" PRIu64 "\n"
        "Bytes per token across both sequences: %" PRIu64 "\n"
        "Selected cache bytes: %" PRIu64 "\n",
        plan.cache.requested_tokens,plan.cache.affordable_tokens,
        plan.cache.bytes_per_token,plan.cache.cache_bytes);
    snapshot->fixture=1;
    status=UmiModelDenseKvPlanHostMemory(&costs,&shape,snapshot,10U,1000U,512U*mib,&plan);
    if(status!=UMI_STATUS_OK || plan.cache_plan_available || plan.fixed_memory.verdict!=UMI_MODEL_MEMORY_FIXTURE) {
        free(snapshot);return 1;
    }
    puts("Fixture observation: no token plan");
    snapshot->fixture=0;
    status=UmiModelDenseKvPlanHostMemory(&costs,&shape,snapshot,1001U,1000U,512U*mib,&plan);
    if(status!=UMI_STATUS_OK || plan.cache_plan_available || plan.fixed_memory.verdict!=UMI_MODEL_MEMORY_STALE) {
        free(snapshot);return 1;
    }
    puts("Stale observation: no token plan");
    costs.runtime_bytes=0U;costs.known_components&=~UMI_MODEL_MEMORY_RUNTIME;
    status=UmiModelDenseKvPlanHostMemory(&costs,&shape,snapshot,10U,1000U,512U*mib,&plan);
    free(snapshot);
    if(status!=UMI_STATUS_OK || plan.cache_plan_available || plan.fixed_memory.verdict!=UMI_MODEL_MEMORY_INCOMPLETE)return 1;
    puts("Unknown runtime cost: no token plan\nNo model loaded; no memory reserved.");
    return 0;
}
