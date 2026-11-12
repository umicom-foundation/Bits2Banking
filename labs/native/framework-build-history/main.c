/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-build-history/main.c
 *
 * PURPOSE:
 *   Observe real build preparation refusal and bounded history through the installed Framework C API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/build/runner.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int KnownScenario(const char *name)
{
    return strcmp(name, "single") == 0 || strcmp(name, "rolling") == 0 ||
        strcmp(name, "shared") == 0 || strcmp(name, "no-history") == 0 ||
        strcmp(name, "invalid") == 0 || strcmp(name, "copy") == 0;
}
static int ObserveRefusal(UmiBuildRunner *runner, UmiBuildResult *result, uint64_t expected)
{
    UmiStatus status = umi_build_runner_run(runner, UMI_BUILD_PHASE_RUN, result);
    if (status != UMI_STATUS_INVALID_STATE || result->operation_id != expected ||
        result->state != UMI_BUILD_STATE_FAILED || result->exit_code != -1 ||
        result->duration_ms != 0U || result->output[0] != '\0') {
        fprintf(stderr, "Unexpected preparation result: status=%d operation=%" PRIu64 "\n",
            (int)status, result->operation_id);
        return 0;
    }
    printf("Operation: %" PRIu64 "; status: INVALID_STATE; exit: -1\n", result->operation_id);
    return 1;
}
int main(int argc, char **argv)
{
    if (argc != 2 || !KnownScenario(argv[1])) {
        fputs("Usage: btb-framework-build-history single|rolling|shared|no-history|invalid|copy\n", stderr);
        return 2;
    }
    const char *name = argv[1];
    UmiBuildHistory *history = NULL;
    UmiBuildRunner *first = NULL, *second = NULL;
    UmiBuildResult *result = NULL, *retained = NULL, *saved = NULL;
    UmiBuildRunnerConfig config = {0};
    int exit_code = 1;
    if (umi_build_result_create(&result) != UMI_STATUS_OK ||
        umi_build_result_create(&retained) != UMI_STATUS_OK ||
        umi_build_result_create(&saved) != UMI_STATUS_OK ||
        umi_build_history_create(2U, &history) != UMI_STATUS_OK) goto finished;
    umi_build_profile_init(&config.profile);
    /* The root is an absolute illustrative path, not a request to create or
     * inspect it. An empty Run program fails the launch plan before any child
     * process or filesystem operation. Keep it empty in every scenario. */
#ifdef _WIN32
    strcpy(config.profile.source_directory, "C:/umicom-learning/history-example");
#else
    strcpy(config.profile.source_directory, "/umicom-learning/history-example");
#endif
    config.history = strcmp(name, "no-history") == 0 ? NULL : history;
    if (umi_build_runner_create(&config, &first) != UMI_STATUS_OK) goto finished;
    if (strcmp(name, "shared") == 0 &&
        umi_build_runner_create(&config, &second) != UMI_STATUS_OK) goto finished;
    printf("Scenario: %s\n", name);
    if (strcmp(name, "invalid") == 0) {
        umi_build_result_init(result, 77U, UMI_BUILD_PHASE_BUILD, "unchanged");
        *saved = *result;
        if (umi_build_runner_run(NULL, UMI_BUILD_PHASE_RUN, result) != UMI_STATUS_INVALID_ARGUMENT ||
            memcmp(result, saved, sizeof(*result)) != 0 ||
            umi_build_history_count(history) != 0U) goto finished;
        puts("Invalid call: no admitted operation; caller output unchanged.");
    } else {
        unsigned attempts = strcmp(name, "rolling") == 0 ? 3U :
            strcmp(name, "shared") == 0 ? 2U : 1U;
        for (unsigned attempt = 1U; attempt <= attempts; ++attempt) {
            UmiBuildRunner *selected = second != NULL && attempt == 2U ? second : first;
            if (!ObserveRefusal(selected, result, attempt)) goto finished;
        }
        if (config.history != NULL) {
            if (umi_build_history_latest(history, retained) != UMI_STATUS_OK ||
                memcmp(result, retained, sizeof(*result)) != 0) goto finished;
            if (strcmp(name, "copy") == 0) {
                *saved = *retained;
                umi_build_result_init(result, 99U, UMI_BUILD_PHASE_BUILD, "local-reuse");
                if (umi_build_history_latest(history, retained) != UMI_STATUS_OK ||
                    memcmp(saved, retained, sizeof(*saved)) != 0) goto finished;
                puts("Caller reuse: retained observation unchanged.");
            }
        } else if (umi_build_history_count(history) != 0U) goto finished;
    }
    size_t count = umi_build_history_count(history);
    printf("Retained records: %zu\n", count);
    for (size_t index = 0U; index < count; ++index) {
        if (umi_build_history_at(history, index, retained) != UMI_STATUS_OK) goto finished;
        printf("History[%zu]: %" PRIu64 "\n", index, retained->operation_id);
    }
    puts("Preparation observations only; no compiler, test runner or application launched.");
    exit_code = 0;
finished:
    /* Runners borrow history. Release both clients before their shared owner,
     * then free the separate caller-owned result records. */
    umi_build_runner_destroy(second);
    umi_build_runner_destroy(first);
    umi_build_history_destroy(history);
    umi_build_result_destroy(saved);
    umi_build_result_destroy(retained);
    umi_build_result_destroy(result);
    return exit_code;
}
