/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/budget-observations/main.c
 *
 * PURPOSE:
 *   Show finite observation admission and sequence exhaustion without confusing telemetry with memory enforcement.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/observability/performance/memory_budget.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    UmiPerformanceMemoryBudget report,before;
    UmiStatus status=umi_performance_memory_budget_init(&report,"training-memory","lesson");
    if(status!=UMI_STATUS_OK)return 1;
    /* The values are synthetic MiB measurements. The value record does not
     * capture host RAM or know the unit; the caller defines that meaning. */
    status=umi_performance_memory_budget_observe(&report,512.0,128.0,1U,100U);
    if(status!=UMI_STATUS_OK)return 1;
    printf("Synthetic used %.0f MiB, auxiliary %.0f MiB, sequence %llu\n",
        report.value,report.auxiliary,(unsigned long long)report.sequence);
    if(!umi_performance_memory_budget_within_budget(report.value,1024.0))return 1;
    if(umi_performance_memory_budget_within_budget(report.value,INFINITY))return 1;
    puts("Finite comparison passes; an infinite limit is refused.");

    memcpy(&before,&report,sizeof report);
    status=umi_performance_memory_budget_observe(&report,NAN,0.0,2U,200U);
    if(status!=UMI_STATUS_INVALID_ARGUMENT || memcmp(&report,&before,sizeof report)!=0)
        return 1;
    puts("Unavailable/invalid measurement cannot overwrite the accepted report.");

    /* Set up the last sequence explicitly as a boundary test, not a normal
     * application update. After exhaustion, an owner must choose a new record. */
    report.sequence=UINT64_MAX-1U;
    if(umi_performance_memory_budget_observe(&report,513,128,2U,200U)!=UMI_STATUS_OK)
        return 1;
    memcpy(&before,&report,sizeof report);
    status=umi_performance_memory_budget_observe(&report,514,128,3U,300U);
    if(status!=UMI_STATUS_CAPACITY_EXCEEDED || memcmp(&report,&before,sizeof report)!=0)
        return 1;
    puts("The final sequence is usable once; the next update preserves the record.");
    puts("No memory was captured, reserved or limited by this example.");
    return 0;
}
