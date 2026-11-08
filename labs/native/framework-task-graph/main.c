/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-task-graph/main.c
 *
 * PURPOSE:
 *   Rehearse shared dependency-graph policies and transactional rebuild without
 * executing stored commands.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <umicom/build/task_graph.h>
static UmiStatus Add(UmiBuildTaskRegistry *registry, const char *id,
                     const char *dependency) {
  UmiBuildTaskSnapshot task;
  umi_build_task_init(&task, id, id, UMI_BUILD_TASK_BUILD);
  task.maximum_attempts = 2U;
  UmiStatus status = dependency
                         ? umi_build_task_add_dependency(&task, dependency)
                         : UMI_STATUS_OK;
  return status == UMI_STATUS_OK
             ? umi_build_task_registry_upsert(registry, &task)
             : status;
}
static UmiStatus Complete(UmiBuildTaskGraph *graph, const char *id) {
  UmiStatus status = umi_build_task_graph_start(graph, id);
  return status == UMI_STATUS_OK ? umi_build_task_graph_complete(graph, id, 0)
                                 : status;
}
/* A single cleanup path keeps ownership clear when any graph operation refuses
 * its proposed transition. Reported outcomes are fictional provider results. */
int main(int argc, char **argv) {
  if (argc != 2) {
    fputs("Usage: btb-framework-task-graph complete|fail|retry|cancel|reject\n",
          stderr);
    return 2;
  }
  const char *mode = argv[1];
  if (strcmp(mode, "complete") && strcmp(mode, "fail") &&
      strcmp(mode, "retry") && strcmp(mode, "cancel") && strcmp(mode, "reject"))
    return 2;
  UmiBuildTaskRegistry *registry = NULL;
  UmiBuildTaskGraph *graph = NULL;
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
  DO(Add(registry, "build", "configure"));
  DO(Add(registry, "test", "build"));
  DO(umi_build_task_graph_create(&graph));
  DO(umi_build_task_graph_rebuild(graph, registry));
  DO(umi_build_task_graph_start(graph, "configure"));
  if (strcmp(mode, "reject") == 0) {
    UmiBuildTaskGraphSnapshot before, after;
    DO(umi_build_task_graph_snapshot(graph, &before));
    DO(Add(registry, "build", "missing"));
    if (umi_build_task_graph_rebuild(graph, registry) != UMI_STATUS_NOT_FOUND)
      goto cleanup;
    DO(umi_build_task_graph_snapshot(graph, &after));
    if (memcmp(&before, &after, sizeof before) != 0)
      goto cleanup;
    puts("Rejected replacement; running graph preserved.");
    result = 0;
    goto cleanup;
  }
  if (strcmp(mode, "fail") == 0 || strcmp(mode, "retry") == 0) {
    DO(umi_build_task_graph_fail(graph, "configure", UMI_STATUS_INTERNAL_ERROR,
                                 7));
    if (strcmp(mode, "retry") == 0) {
      DO(umi_build_task_graph_retry(graph, "configure"));
      DO(Complete(graph, "configure"));
    }
  } else {
    if (strcmp(mode, "cancel") == 0)
      DO(umi_build_task_graph_cancel_waiting(graph));
    DO(umi_build_task_graph_complete(graph, "configure", 0));
  }
  if (strcmp(mode, "complete") == 0 || strcmp(mode, "retry") == 0) {
    DO(Complete(graph, "build"));
    DO(Complete(graph, "test"));
  }
  UmiBuildTaskGraphSnapshot snapshot;
  DO(umi_build_task_graph_snapshot(graph, &snapshot));
  printf("Succeeded: %zu; failed: %zu; blocked: %zu; cancelled: %zu\n",
         snapshot.succeeded_count, snapshot.failed_count,
         snapshot.blocked_count, snapshot.cancelled_count);
  if (strcmp(mode, "fail") == 0)
    result =
        snapshot.failed_count == 1U && snapshot.blocked_count == 2U ? 0 : 1;
  else if (strcmp(mode, "cancel") == 0)
    result = snapshot.succeeded_count == 1U && snapshot.cancelled_count == 2U
                 ? 0
                 : 1;
  else
    result = snapshot.succeeded_count == 3U ? 0 : 1;
cleanup:
  umi_build_task_graph_destroy(graph);
  umi_build_task_registry_destroy(registry);
  if (result == 0)
    puts("Only task state was modeled; no build command ran.");
  return result;
#undef DO
}
