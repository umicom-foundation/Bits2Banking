/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/lifecycle-execution/main.c
 *
 * PURPOSE:
 *   Exercise shared workflow admission and progress reports with controlled adapters that never run external commands.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/developer/lifecycle_execution.h"
#include <stdio.h>
#include <string.h>

typedef struct LabHost { unsigned calls; int fail_build; } LabHost;
static int Explain(void *data, const UmiDeveloperLifecycleExecutionRequest *request,
    UmiDeveloperLifecycleAction action)
{
    LabHost *host = data;
    (void)request;
    ++host->calls;
    (void)printf("adapter %u: %s\n", host->calls, umi_developer_lifecycle_action_text(action));
    return host->fail_build && action == UMI_DEVELOPER_ACTION_BUILD ? 23 : 0;
}
int main(int argc, char **argv)
{
    UmiDeveloperLifecycleExecutionRequest request;
    UmiDeveloperLifecycleExecutionHost host = {0};
    UmiDeveloperLifecycleExecutionReport report;
    LabHost fixture = {0};
    UmiStatus expected = UMI_STATUS_OK, status;
    unsigned expected_calls = 8U;
    if (argc != 2) {
        (void)fputs("Usage: lifecycle-execution preview|complete|fail-build|missing-backend|missing-message\n", stderr);
        return 2;
    }
    umi_developer_lifecycle_execution_request_init(&request, UMI_DEVELOPER_LIFECYCLE_COMPLETE);
    request.source = "illustrative-project";
    request.message = "Describe a reviewed change";
    host.user_data = &fixture;
    for (size_t i = 1U; i < UMI_DEVELOPER_ACTION_COUNT; ++i) host.execute[i] = Explain;
    if (!strcmp(argv[1], "preview")) { request.preview = 1; request.message = NULL; expected_calls = 0U; }
    else if (!strcmp(argv[1], "complete")) { /* All callbacks only explain their action. */ }
    else if (!strcmp(argv[1], "fail-build")) { fixture.fail_build = 1; expected = UMI_STATUS_IO_ERROR; expected_calls = 5U; }
    else if (!strcmp(argv[1], "missing-backend")) { host.execute[UMI_DEVELOPER_ACTION_REPOSITORY_PUBLISH] = NULL; expected = UMI_STATUS_UNAVAILABLE; expected_calls = 0U; }
    else if (!strcmp(argv[1], "missing-message")) { request.message = NULL; expected = UMI_STATUS_INVALID_ARGUMENT; expected_calls = 0U; }
    else return 2;
    status = umi_developer_lifecycle_execute(&request, &host, &report);
    (void)printf("scenario=%s planned=%zu attempted=%zu completed=%zu status=%d external-commands=0\n",
        argv[1], report.action_count, report.attempted_count, report.completed_count, (int)status);
    if (status != expected || fixture.calls != expected_calls || report.attempted_count != fixture.calls) return 1;
    if (fixture.fail_build && (report.completed_count != 4U || report.backend_result != 23 ||
        report.failed_action != UMI_DEVELOPER_ACTION_BUILD)) return 1;
    if (status == UMI_STATUS_OK && !request.preview && report.completed_count != 8U) return 1;
    return 0;
}
