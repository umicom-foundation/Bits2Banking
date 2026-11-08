/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/run-restart/main.c
 *
 * PURPOSE:
 *   Observe deferred restart and result handover through the installed Framework session service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/build/run_current.h"
#include "umicom/build/run_restart.h"
#include "umicom/platform/filesystem.h"
#include "umicom/platform/threading.h"
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Probe { atomic_int entered, finish; } Probe;
/* This transport does not execute the selected file. Framework owns the worker
 * and results while the exercise makes the stop/completion gap observable. */
static UmiStatus Execute(const UmiBuildProfile *profile, UmiBuildPhase phase,
    UmiCancellationToken *token, UmiBuildResult *result, void *context)
{
    (void)profile;
    if (phase != UMI_BUILD_PHASE_RUN) return UMI_STATUS_INVALID_STATE;
    Probe *probe = context;
    atomic_fetch_add(&probe->entered, 1);
    while (!atomic_load(&probe->finish)) {
        if (umi_cancellation_token_is_requested(token)) {
            strcpy(result->output, "The controlled executor observed cancellation.\n");
            return UMI_STATUS_CANCELLED;
        }
        umi_thread_sleep_ms(1U);
    }
    strcpy(result->output, "The replacement controlled executor completed.\n");
    return UMI_STATUS_OK;
}
static UmiStatus Wait(UmiBuildProjectSession *session, UmiBuildProjectSessionSnapshot *out)
{
    for (unsigned attempt = 0U; attempt < 5000U; ++attempt) {
        UmiStatus status = umi_build_project_session_snapshot(session, out);
        if (status != UMI_STATUS_OK || !out->active) return status;
        umi_thread_sleep_ms(1U);
    }
    return UMI_STATUS_BUSY;
}
#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "Contract refused at line %d: %s\n", __LINE__, #condition); \
    goto cleanup; } } while (0)
int main(int argc, char **argv)
{
    if (argc != 3 || (strcmp(argv[2], "restart") && strcmp(argv[2], "handover") &&
        strcmp(argv[2], "stop") && strcmp(argv[2], "revoke"))) {
        fprintf(stderr, "Usage: run-restart ABSOLUTE_EXISTING_FILE restart|handover|stop|revoke\n");
        return 2;
    }
    int exit_code = 1;
    Probe probe = {0};
    UmiBuildProjectSession *session = NULL;
    UmiBuildResult *result = NULL;
    UmiBuildProfile *profile = malloc(sizeof *profile);
    REQUIRE(profile != NULL);
    umi_build_profile_init(profile);
    REQUIRE(umi_fs_current_directory(profile->source_directory, sizeof profile->source_directory) == UMI_STATUS_OK);
    REQUIRE(umi_path_is_absolute(argv[1]) && strlen(argv[1]) < sizeof profile->run_program);
    strcpy(profile->run_program, argv[1]);
    strcpy(profile->run_working_directory, ".");
    UmiBuildProjectSessionConfig config = {NULL, Execute, &probe};
    REQUIRE(umi_build_project_session_create(&config, &session) == UMI_STATUS_OK);
    REQUIRE(UmiBuildProjectSessionRunCurrent(session, profile, true, NULL) == UMI_STATUS_OK);
    for (unsigned i = 0U; i < 5000U && atomic_load(&probe.entered) == 0; ++i) umi_thread_sleep_ms(1U);
    REQUIRE(atomic_load(&probe.entered) == 1);
    REQUIRE(UmiBuildRunRestartRequest(session, profile, profile->source_directory, true) == UMI_STATUS_OK);
    UmiBuildProjectSessionSnapshot first;
    REQUIRE(Wait(session, &first) == UMI_STATUS_OK && first.status == UMI_STATUS_CANCELLED);
    REQUIRE(first.completed_phase_count == 1U);
    bool submitted = false;
    if (!strcmp(argv[2], "handover")) {
        REQUIRE(UmiBuildRunRestartAdvance(session, profile, profile->source_directory,
            true, 0U, &submitted) == UMI_STATUS_BUSY && !submitted);
        puts("The session waited for the old result to be retained.");
    }
    REQUIRE(umi_build_result_create(&result) == UMI_STATUS_OK);
    REQUIRE(umi_build_project_session_result_at(session, 0U, result) == UMI_STATUS_OK);
    REQUIRE(result->status == UMI_STATUS_CANCELLED);
    /* The app retains the old result in its own object. A GUI appends it to
     * history before acknowledging the same per-operation result count. */
    if (!strcmp(argv[2], "stop")) umi_build_project_session_cancel(session);
    bool trusted = strcmp(argv[2], "revoke") != 0;
    atomic_store(&probe.finish, 1);
    UmiStatus advanced = UmiBuildRunRestartAdvance(session, profile,
        profile->source_directory, trusted, 1U, &submitted);
    bool expected_launch = strcmp(argv[2], "stop") && strcmp(argv[2], "revoke");
    REQUIRE(submitted == expected_launch);
    if (expected_launch) {
        REQUIRE(advanced == UMI_STATUS_OK);
        UmiBuildProjectSessionSnapshot next;
        REQUIRE(Wait(session, &next) == UMI_STATUS_OK && next.status == UMI_STATUS_OK);
        REQUIRE(next.operation_id == first.operation_id + 1U && next.completed_phase_count == 1U);
        REQUIRE(atomic_load(&probe.entered) == 2);
    } else {
        REQUIRE(advanced == (trusted ? UMI_STATUS_NOT_FOUND : UMI_STATUS_PERMISSION_DENIED));
        REQUIRE(atomic_load(&probe.entered) == 1);
    }
    printf("scenario=%s old-results=1 executor-calls=%d child-processes=0\n", argv[2], atomic_load(&probe.entered));
    exit_code = 0;
cleanup:
    umi_build_project_session_destroy(session);
    umi_build_result_destroy(result);
    free(profile);
    return exit_code;
}
