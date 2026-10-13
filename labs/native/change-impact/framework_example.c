/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/change-impact/framework_example.c
 * PURPOSE: Read-only C23 consumer of existing Framework VCS, BUILD AUTOMATION
 *          and compiler diagnostic contracts. No replacement implementation.
 *
 * This optional binary requires a COMPATIBLE INSTALLED Framework SDK.
 * It never invokes Git itself, stages files, compiles a real application,
 * changes the repository, or certifies a production release.
 *---------------------------------------------------------------------------*/
#include "umicom/base/status.h"
#include "umicom/build/automation.h"
#include "umicom/build/parser.h"
#include "umicom/vcs/working_tree.h"

#include <stdio.h>

static int RegisterScope(UmiBuildAutomation *automation, const char *name,
                         const char *prefix, UmiBuildAutomationScopeFlags flags)
{
    UmiBuildAutomationScope scope;
    UmiStatus status;
    umi_build_automation_scope_init(&scope, name, name, prefix);
    scope.flags = flags;
    status = umi_build_automation_register_scope(automation, &scope);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Framework scope registration failed for %s: %d\n",
                name, (int)status);
        return 0;
    }
    return 1;
}

static int DemonstrateNativeFrameworkPlanner(void)
{
    UmiBuildAutomation *automation = NULL;
    UmiBuildAutomationChange change;
    UmiBuildAutomationSnapshot snapshot;
    UmiStatus status = umi_build_automation_create(&automation);
    if (status != UMI_STATUS_OK) return 0;

    /* The scopes and path below are FICTIONAL teaching inputs. The planner,
     * unlike the tiny standalone bitset model, is actual Framework code. */
    if (!RegisterScope(automation, "framework", "framework",
                       UMI_BUILD_AUTOMATION_SCOPE_SHARED_PROVIDER) ||
        !RegisterScope(automation, "studio", "applications/studio",
                       UMI_BUILD_AUTOMATION_SCOPE_CONSUMES_SHARED) ||
        !RegisterScope(automation, "trader", "applications/trader",
                       UMI_BUILD_AUTOMATION_SCOPE_CONSUMES_SHARED)) {
        umi_build_automation_destroy(automation);
        return 0;
    }
    umi_build_automation_change_init(&change,
        "framework/include/umicom/build/automation.h", 0);
    status = umi_build_automation_add_change(automation, &change);
    if (status == UMI_STATUS_OK) status = umi_build_automation_evaluate(automation);
    if (status == UMI_STATUS_OK)
        status = umi_build_automation_snapshot(automation, &snapshot);
    if (status == UMI_STATUS_OK) {
        printf("Framework automation: %zu selected, %zu direct, %zu inherited\n",
               snapshot.selected_count, snapshot.direct_count, snapshot.inherited_count);
        for (size_t index = 0U; index < umi_build_automation_count(automation); ++index) {
            UmiBuildAutomationPlanItem item;
            status = umi_build_automation_item_at(automation, index, &item);
            if (status != UMI_STATUS_OK) break;
            printf("  %s: direct=%d inherited=%d actions=0x%x\n",
                   item.scope_id, item.direct_change, item.inherited_change,
                   (unsigned)item.actions);
        }
    }
    umi_build_automation_destroy(automation);
    return status == UMI_STATUS_OK && snapshot.selected_count == 3U;
}

int main(int argc, char **argv)
{
    UmiVcsWorkingTreeRequest request = {0};
    UmiVcsWorkingTree *observation = NULL;
    UmiVcsWorkingTreeSummary summary = {0};
    UmiBuildDiagnostic diagnostic = {0};
    UmiStatus status;

    request.repository_root = argc > 1 ? argv[1] : ".";
    request.git_program = "git";
    request.timeout_ms = 30000U;
    status = UmiVcsWorkingTreeRead(&request, &observation);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Framework Git observation failed: %d\n", (int)status);
        return 2;
    }
    status = UmiVcsWorkingTreeDescribe(observation, &summary);
    if (status == UMI_STATUS_OK) {
        printf("Repository branch known: %d; detached: %d; staged: %zu; untracked: %zu\n",
               summary.branch_known, summary.detached,
               summary.staged, summary.untracked);
        printf("Submodule commit changes: %zu; dirty children: %zu\n",
               summary.child_commits, summary.dirty_children);
    }
    UmiVcsWorkingTreeDestroy(observation);
    if (status != UMI_STATUS_OK) return 3;

    /* Only real Framework's compiler parser interprets tool text. */
    status = umi_build_parse_diagnostic_line(
        "C:/umicom/Umicom-Applications/framework/src/example.c:12:4: "
        "error: missing required declaration", &diagnostic);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Framework diagnostic parser unavailable: %d\n", (int)status);
        return 4;
    }
    printf("Fictional compiler diagnostic: %s:%zu:%zu: %s\n", diagnostic.file,
           diagnostic.line, diagnostic.column, diagnostic.message);

    if (!DemonstrateNativeFrameworkPlanner()) return 5;
    return 0;
}
