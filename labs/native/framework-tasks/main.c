/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-tasks/main.c
 *
 * PURPOSE:
 *   Demonstrate bounded task admission and owned copies through the installed
 * Framework SDK.
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
#include <umicom/build/task.h>
#define REQUIRE(x)                                                             \
  do {                                                                         \
    if (!(x)) {                                                                \
      fprintf(stderr, "line %d: %s\n", __LINE__, #x);                          \
      return 1;                                                                \
    }                                                                          \
  } while (0)
int main(int argc, char **argv) {
  if (argc != 2) {
    fputs("Usage: btb-framework-tasks atomic|shape|owned|reset|revision\n",
          stderr);
    return 2;
  }
  UmiBuildTaskSnapshot task, before, found;
  umi_build_task_init(&task, "build", "Build lesson", UMI_BUILD_TASK_BUILD);
  REQUIRE(umi_build_task_set_command(&task, "compiler source.c", "lesson") ==
          UMI_STATUS_OK);
  REQUIRE(umi_build_task_add_input(&task, "source.c") == UMI_STATUS_OK);
  REQUIRE(umi_build_task_add_output(&task, "build/source.o") == UMI_STATUS_OK);
  if (strcmp(argv[1], "atomic") == 0) {
    char oversized[UMI_BUILD_PATH_CAPACITY + 1U];
    memset(oversized, 'x', sizeof oversized - 1U);
    oversized[sizeof oversized - 1U] = '\0';
    before = task;
    REQUIRE(umi_build_task_set_command(&task, "replacement", oversized) ==
            UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(&before, &task, sizeof task) == 0);
    puts("Refused directory; command and revision preserved.");
  } else if (strcmp(argv[1], "shape") == 0) {
    task.input_count = SIZE_MAX;
    before = task;
    char message[256];
    REQUIRE(umi_build_task_validate(&task, message, sizeof message) ==
            UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(umi_build_task_add_output(&task, "other.o") ==
            UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(memcmp(&before, &task, sizeof task) == 0);
    puts("Malformed count refused before traversal.");
  } else if (strcmp(argv[1], "revision") == 0) {
    task.revision = UINT64_MAX;
    before = task;
    REQUIRE(umi_build_task_set_command(&task, "replacement", NULL) ==
            UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(&before, &task, sizeof task) == 0);
    puts("Exhausted revision refused without mutation.");
  } else if (strcmp(argv[1], "owned") == 0 || strcmp(argv[1], "reset") == 0) {
    UmiBuildTaskRegistry *registry = NULL;
    REQUIRE(umi_build_task_registry_create(&registry) == UMI_STATUS_OK);
    const UmiStatus inserted = umi_build_task_registry_upsert(registry, &task);
    if (inserted != UMI_STATUS_OK) {
      umi_build_task_registry_destroy(registry);
      return 1;
    }
    memset(&task, 0, sizeof task);
    const UmiStatus read =
        umi_build_task_registry_find(registry, "build", &found);
    int accepted = read == UMI_STATUS_OK &&
                   strcmp(found.command, "compiler source.c") == 0;
    if (strcmp(argv[1], "reset") == 0) {
      const uint64_t revision = umi_build_task_registry_revision(registry);
      accepted =
          accepted && umi_build_task_registry_reset(registry) == UMI_STATUS_OK;
      accepted = accepted && umi_build_task_registry_count(registry) == 0U &&
                 umi_build_task_registry_revision(registry) == revision + 1U;
    }
    umi_build_task_registry_destroy(registry);
    REQUIRE(accepted);
    puts(strcmp(argv[1], "owned") == 0
             ? "Registry owns the published task copy."
             : "Checked reset removed tasks and advanced revision.");
  } else
    return 2;
  puts("No compiler or task command was executed.");
  return 0;
}
