/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/contributor-notes/framework_planner_example.c
 * PURPOSE: Optional real C23 consumer of Framework's existing build planner.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * This programme is NOT a second impact planner. It only calls public
 * Umicom Framework APIs using fictional training paths. It never runs tools.
 *---------------------------------------------------------------------------*/
#include "umicom/build/automation.h"
#include "umicom/base/status.h"
#include <stdio.h>
#include <string.h>

static int RegisterScope(UmiBuildAutomation *planner, const char *id,
                         const char *prefix, UmiBuildAutomationScopeFlags flags)
{
    UmiBuildAutomationScope scope;
    umi_build_automation_scope_init(&scope, id, id, prefix);
    scope.flags = flags;
    return umi_build_automation_register_scope(planner, &scope) == UMI_STATUS_OK;
}

int main(void)
{
    UmiBuildAutomation *planner = NULL;
    UmiBuildAutomationChange changedFile;
    UmiBuildAutomationSnapshot snapshot = {0};
    UmiBuildAutomationPlanItem item;
    UmiStatus status = umi_build_automation_create(&planner);
    if (status != UMI_STATUS_OK) return 1;

    if (!RegisterScope(planner, "framework", "framework",
                       UMI_BUILD_AUTOMATION_SCOPE_SHARED_PROVIDER) ||
        !RegisterScope(planner, "notes", "applications/notes",
                       UMI_BUILD_AUTOMATION_SCOPE_CONSUMES_SHARED)) {
        umi_build_automation_destroy(planner);
        return 2;
    }
    umi_build_automation_change_init(&changedFile,
                                     "framework/include/umicom/build/automation.h", 0);
    status = umi_build_automation_add_change(planner, &changedFile);
    if (status == UMI_STATUS_OK) status = umi_build_automation_evaluate(planner);
    if (status == UMI_STATUS_OK) status = umi_build_automation_snapshot(planner, &snapshot);
    if (status == UMI_STATUS_OK) {
        printf("Real Framework change planner selected %zu scopes:\n", snapshot.selected_count);
        for (size_t index = 0U; index < umi_build_automation_count(planner); ++index) {
            status = umi_build_automation_item_at(planner, index, &item);
            if (status != UMI_STATUS_OK) break;
            printf("  %s (direct=%d inherited=%d)\n",
                   item.scope_id, item.direct_change, item.inherited_change);
        }
    }
    const int valid = status == UMI_STATUS_OK && snapshot.selected_count == 2U &&
                      snapshot.direct_count == 1U && snapshot.inherited_count == 1U;
    umi_build_automation_destroy(planner);
    return valid ? 0 : 3;
}
