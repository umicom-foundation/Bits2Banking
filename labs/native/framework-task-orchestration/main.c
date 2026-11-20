/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-task-orchestration/main.c
 *
 * PURPOSE:
 *   Demonstrate selected dependency closure, parallel admission and cooperative
 *   stop through the installed Framework orchestrator.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <umicom/build/task_orchestrator.h>
static UmiStatus Add(UmiBuildTaskRegistry *r, const char *id, const char *dep) {
  UmiBuildTaskSnapshot task;
  umi_build_task_init(&task, id, id, UMI_BUILD_TASK_BUILD);
  task.maximum_attempts = 2U;
  UmiStatus s = dep ? umi_build_task_add_dependency(&task, dep) : UMI_STATUS_OK;
  return s == UMI_STATUS_OK ? umi_build_task_registry_upsert(r, &task) : s;
}
static UmiStatus Complete(UmiBuildTaskOrchestrator *owner, const char *id) {
  UmiStatus s = umi_build_task_orchestrator_start(owner, id);
  return s == UMI_STATUS_OK ? umi_build_task_orchestrator_complete(owner, id, 0)
                            : s;
}
int main(int argc, char **argv) {
  if (argc != 2) {
    fputs("Usage: btb-framework-task-orchestration "
          "selected|parallel|stop|retry|reject|stop-retry|blocked-retry\n",
          stderr);
    return 2;
  }
  const char *mode = argv[1];
  /* Extend the existing stop and retry journeys with two observable boundaries. */
  const bool stop_retry = strcmp(mode, "stop-retry") == 0;
  const bool blocked_retry = strcmp(mode, "blocked-retry") == 0;
  const bool stop_case = strcmp(mode, "stop") == 0 || stop_retry;
  if (strcmp(mode, "selected") && strcmp(mode, "parallel") &&
      !stop_case && strcmp(mode, "retry") && strcmp(mode, "reject") && !blocked_retry)
    return 2;
  UmiBuildTaskRegistry *registry = NULL;
  UmiBuildTaskOrchestrator *owner = NULL;
  int result = 1;
#define DO(call)                                                               \
  do {                                                                         \
    UmiStatus s = (call);                                                      \
    if (s != UMI_STATUS_OK) {                                                  \
      fprintf(stderr, "line %d: status %d\n", __LINE__, (int)s);               \
      goto cleanup;                                                            \
    }                                                                          \
  } while (0)
  DO(umi_build_task_registry_create(&registry));
  DO(Add(registry, "configure", NULL));
  DO(Add(registry, "left", "configure"));
  DO(Add(registry, "right", "configure"));
  DO(Add(registry, "link", "left"));
  UmiBuildTaskSnapshot task;
  DO(umi_build_task_registry_find(registry, "link", &task));
  DO(umi_build_task_add_dependency(&task, "right"));
  DO(umi_build_task_registry_upsert(registry, &task));
  DO(umi_build_task_orchestrator_create(registry, 2U, &owner));
  DO(umi_build_task_orchestrator_plan(
      owner, "lesson", strcmp(mode, "selected") == 0 ? "left" : "link"));
  if (strcmp(mode, "reject") == 0) {
    UmiBuildTaskOperationSnapshot before, after;
    DO(umi_build_task_orchestrator_snapshot(owner, &before));
    DO(Add(registry, "link", "missing"));
    if (umi_build_task_orchestrator_plan(owner, "replacement", "link") !=
        UMI_STATUS_NOT_FOUND)
      goto cleanup;
    DO(umi_build_task_orchestrator_snapshot(owner, &after));
    if (memcmp(&before, &after, sizeof before) != 0)
      goto cleanup;
    puts("Rejected plan; previous operation retained.");
  }
  DO(umi_build_task_orchestrator_begin(owner));
  if (stop_case) {
    DO(umi_build_task_orchestrator_start(owner, "configure"));
    DO(umi_build_task_orchestrator_request_stop(owner));
    if (stop_retry) {
      /* A queued retry cannot erase the accepted stop while configure is active. */
      UmiBuildTaskOperationSnapshot stopping, after;
      DO(umi_build_task_orchestrator_snapshot(owner, &stopping));
      if (umi_build_task_orchestrator_retry(owner, "left") != UMI_STATUS_BUSY)
        goto cleanup;
      DO(umi_build_task_orchestrator_snapshot(owner, &after));
      if (after.revision != stopping.revision || after.graph.revision != stopping.graph.revision ||
          after.active_count != 1U || !after.stop_requested || after.retry_count != 0U)
        goto cleanup;
      puts("Retry is busy while configure drains. The stop and graph are unchanged.");
    }
    DO(umi_build_task_orchestrator_complete(owner, "configure", 0));
  } else if (strcmp(mode, "parallel") == 0) {
    DO(Complete(owner, "configure"));
    DO(umi_build_task_orchestrator_start(owner, "left"));
    DO(umi_build_task_orchestrator_start(owner, "right"));
    if (umi_build_task_orchestrator_next_ready(owner, &task) != UMI_STATUS_BUSY)
      goto cleanup;
    puts("Two active tasks; parallel limit respected.");
    DO(umi_build_task_orchestrator_complete(owner, "left", 0));
    DO(umi_build_task_orchestrator_complete(owner, "right", 0));
    DO(Complete(owner, "link"));
  } else {
    if (strcmp(mode, "retry") == 0 || blocked_retry) {
      DO(umi_build_task_orchestrator_start(owner, "configure"));
      DO(umi_build_task_orchestrator_fail(owner, "configure",
                                          UMI_STATUS_INTERNAL_ERROR, 7));
      if (blocked_retry) {
        /* The request can succeed even if the same failure blocks the task
         * again. Read the graph before assuming there is a ready task. */
        UmiBuildTaskOperationSnapshot waiting;
        DO(umi_build_task_orchestrator_retry(owner, "left"));
        DO(umi_build_task_orchestrator_snapshot(owner, &waiting));
        if (waiting.state != UMI_BUILD_TASK_OPERATION_FAILED || waiting.graph.ready_count != 0U ||
            waiting.retry_count != 1U)
          goto cleanup;
        puts("Left is still blocked. Retry its failed configure prerequisite first.");
      }
      DO(umi_build_task_orchestrator_retry(owner, "configure"));
    }
    /* This example supplies immediate fictional outcomes. A real runner
     * starts supervised processes and reports their actual completion. */
    for (;;) {
      UmiBuildTaskOperationSnapshot current;
      DO(umi_build_task_orchestrator_snapshot(owner, &current));
      if (current.state != UMI_BUILD_TASK_OPERATION_RUNNING)
        break;
      DO(umi_build_task_orchestrator_next_ready(owner, &task));
      DO(Complete(owner, task.task_id));
    }
  }
  DO(umi_build_task_orchestrator_finish(owner));
  UmiBuildTaskOperationSnapshot snapshot;
  DO(umi_build_task_orchestrator_snapshot(owner, &snapshot));
  printf("Operation: %s; planned: %zu; succeeded: %zu; cancelled: %zu; "
         "retries: %zu\n",
         umi_build_task_operation_state_text(snapshot.state),
         snapshot.planned_count, snapshot.graph.succeeded_count,
         snapshot.graph.cancelled_count, snapshot.retry_count);
  if (stop_case)
    result = snapshot.state == UMI_BUILD_TASK_OPERATION_CANCELLED &&
                     snapshot.graph.cancelled_count == 3U
                 ? 0
                 : 1;
  else
    result = snapshot.state == UMI_BUILD_TASK_OPERATION_SUCCEEDED &&
                     snapshot.planned_count ==
                         (strcmp(mode, "selected") == 0 ? 2U : 4U)
                 ? 0
                 : 1;
cleanup:
  umi_build_task_orchestrator_destroy(owner);
  umi_build_task_registry_destroy(registry);
  if (result == 0)
    puts("No operating-system process was started by the task model.");
  return result;
#undef DO
}
