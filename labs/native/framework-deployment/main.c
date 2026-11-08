/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-deployment/main.c
 *
 * PURPOSE:
 *   Rehearse the installed Framework deployment controller with explicit
 * fictional provider outcomes and no host changes.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/build/deployment_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int Same(const char *a, const char *b) { return strcmp(a, b) == 0; }
static int Require(UmiStatus status, const char *operation) {
  if (status == UMI_STATUS_OK)
    return 1;
  fprintf(stderr, "%s: %s\n", operation, umi_status_text(status));
  return 0;
}
int main(int argc, char **argv) {
  if (argc != 2 || (!Same(argv[1], "complete") && !Same(argv[1], "fail") &&
                    !Same(argv[1], "rollback") && !Same(argv[1], "cancel") &&
                    !Same(argv[1], "revise"))) {
    fputs("Usage: btb-framework-deployment "
          "complete|fail|rollback|cancel|revise\n",
          stderr);
    return 2;
  }
  UmiBuildArtifactManifest artifact;
  UmiBuildDeploymentTargetSnapshot target;
  umi_build_artifact_manifest_init(&artifact, "lesson-package",
                                   "fictional/package.zip", "archive");
  artifact.flags |= UMI_BUILD_ARTIFACT_DEPLOYABLE;
  umi_build_deployment_target_init(&target, "lesson-stage", "Lesson stage",
                                   UMI_BUILD_DEPLOYMENT_LOCAL_DIRECTORY);
  strcpy(target.destination, "fictional/stage");
  target.flags |= UMI_BUILD_DEPLOYMENT_TARGET_REQUIRES_APPROVAL |
                  UMI_BUILD_DEPLOYMENT_TARGET_SUPPORTS_ROLLBACK;
  UmiBuildDeploymentPlan *plan = calloc(1U, sizeof(*plan));
  if (plan == NULL)
    return 1;
  umi_build_deployment_plan_init(plan, "lesson-plan");
  int ok = Require(
      umi_build_deployment_plan_compose_default(plan, &artifact, &target, 1),
      "compose");
  if (ok)
    ok = Require(umi_build_deployment_plan_approve(plan),
                 "approve fictional plan");
  if (ok && Same(argv[1], "revise")) {
    UmiBuildDeploymentStepSnapshot extra;
    umi_build_deployment_step_init(&extra, "review-notes", "Review notes",
                                   UMI_BUILD_DEPLOYMENT_STEP_CLEANUP);
    ok = Require(umi_build_deployment_plan_add_step(plan, &extra),
                 "append step");
    printf("Approval after edit: %d\n", plan->approved);
    if (plan->approved)
      ok = 0;
    puts("No provider called; the edited plan needs a fresh approval.");
    free(plan);
    return ok ? 0 : 1;
  }
  UmiBuildDeploymentController *owner = NULL;
  if (ok)
    ok = Require(umi_build_deployment_controller_create(&owner), "create");
  if (ok)
    ok = Require(umi_build_deployment_controller_load(owner, plan), "load");
  if (ok)
    ok = Require(umi_build_deployment_controller_begin(owner), "begin model");
  UmiBuildDeploymentStepSnapshot step;
  size_t outcomes = 0U;
  while (ok) {
    UmiStatus next = umi_build_deployment_controller_next_step(owner, &step);
    if (next == UMI_STATUS_INVALID_STATE || next == UMI_STATUS_NOT_FOUND)
      break;
    if (!Require(next, "next")) {
      ok = 0;
      break;
    }
    printf("Model step: %s\n", step.step_id);
    ok =
        Require(umi_build_deployment_controller_start_step(owner, step.step_id),
                "start model step");
    if (!ok)
      break;
    if (outcomes == 0U && Same(argv[1], "cancel"))
      ok = Require(umi_build_deployment_controller_request_stop(owner),
                   "request stop");
    int exit_code =
        outcomes == 0U && (Same(argv[1], "fail") || Same(argv[1], "rollback"))
            ? 7
            : 0;
    if (ok)
      ok = Require(umi_build_deployment_controller_complete_step(
                       owner, step.step_id, exit_code),
                   "record fictional outcome");
    ++outcomes;
  }
  if (ok && Same(argv[1], "rollback")) {
    ok = Require(umi_build_deployment_controller_begin_rollback(owner),
                 "begin rollback model");
    while (ok) {
      UmiStatus next = umi_build_deployment_controller_next_step(owner, &step);
      if (next == UMI_STATUS_NOT_FOUND)
        break;
      if (!Require(next, "next rollback")) {
        ok = 0;
        break;
      }
      printf("Rollback model step: %s\n", step.step_id);
      ok = Require(
          umi_build_deployment_controller_start_step(owner, step.step_id),
          "start rollback step");
      if (ok)
        ok = Require(umi_build_deployment_controller_complete_step(
                         owner, step.step_id, 0),
                     "record fictional restoration");
    }
    if (ok)
      ok = Require(umi_build_deployment_controller_complete_rollback(owner, 0),
                   "finish rollback model");
  }
  UmiBuildDeploymentControllerSnapshot snapshot;
  if (ok)
    ok = Require(umi_build_deployment_controller_snapshot(owner, &snapshot),
                 "snapshot");
  if (ok) {
    printf("Model state: %s\nProgress: %u/10000\nCompleted: %zu; failed: %zu; "
           "cancelled: %zu\nLast exit: %d\n",
           umi_build_deployment_run_state_text(snapshot.state),
           (unsigned)snapshot.progress_basis_points,
           snapshot.completed_step_count, snapshot.failed_step_count,
           snapshot.cancelled_step_count, snapshot.last_exit_code);
    UmiBuildDeploymentRunState expected =
        Same(argv[1], "complete")   ? UMI_BUILD_DEPLOYMENT_SUCCEEDED
        : Same(argv[1], "fail")     ? UMI_BUILD_DEPLOYMENT_FAILED
        : Same(argv[1], "rollback") ? UMI_BUILD_DEPLOYMENT_ROLLED_BACK
                                    : UMI_BUILD_DEPLOYMENT_CANCELLED;
    ok = snapshot.state == expected;
  }
  puts("Teaching model only: no artifact read, installation, network request "
       "or process launch.");
  umi_build_deployment_controller_destroy(owner);
  free(plan);
  return ok ? 0 : 1;
}
