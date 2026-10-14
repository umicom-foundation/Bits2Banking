/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/maintenance-review/test_maintenance.c
 * PURPOSE: Named, deterministic C23 negative and positive review tests.
 *---------------------------------------------------------------------------*/
#include "maintenance_review.h"
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do { if (!(condition)) { \
    (void)fprintf(stderr, "FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition); \
    return 1; } } while (0)
static const char Revision[] = "0123456789abcdef0123456789abcdef01234567";

static int BuildSummary(uint64_t captureId, BtbAdminState storageState,
                        BtbAdminState appState, int optionalWarning,
                        BtbServiceSummary *summary)
{
    BtbServiceGraph graph;
    const BtbServiceSpec storage = {1U, 0U, UINT32_C(1), "Notes storage"};
    const BtbServiceSpec notes = {2U, UINT32_C(1), UINT32_C(1), "Notes desktop"};
    if (BtbServiceGraphInit(&graph, captureId) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &storage) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &notes) != BTB_SERVICE_OK) return 0;
    for (uint32_t i = 0U; i < 2U; ++i) {
        BtbAdminReview review;
        BtbAdminObservation check = {0};
        if (BtbAdminReviewInit(&review, captureId) != BTB_ADMIN_OK) return 0;
        check.checkId = 1U;
        check.captureId = captureId;
        check.state = i == 0U ? storageState : appState;
        (void)snprintf(check.label, sizeof check.label, "%s",
                       i == 0U ? "Practice store check" : "Notes request check");
        if (BtbAdminReviewAdd(&review, &check) != BTB_ADMIN_OK) return 0;
        if (optionalWarning && i == 1U) {
            BtbAdminObservation optional = {0};
            optional.checkId = 2U;
            optional.captureId = captureId;
            optional.state = BTB_ADMIN_WARNING;
            (void)snprintf(optional.label, sizeof optional.label, "%s",
                           "Optional display warning");
            if (BtbAdminReviewAdd(&review, &optional) != BTB_ADMIN_OK) return 0;
        }
        if (BtbServiceGraphAttach(&graph, i + 1U, &review) != BTB_SERVICE_OK)
            return 0;
    }
    return BtbServiceGraphEvaluate(&graph, summary) == BTB_SERVICE_OK;
}

static int Prepare(BtbMaintenanceReview *review, int throughStart)
{
    BtbServiceSummary before;
    if (!BuildSummary(100U, BTB_ADMIN_PASS, BTB_ADMIN_PASS, 0, &before) ||
        BtbMaintenanceInit(review, "UmiNotesMaintenance", Revision, "OperatorA", &before)
            != BTB_MAINTENANCE_OK) return 0;
    if (throughStart) {
        if (BtbMaintenanceApprove(review, "ReviewerB", 1, 1) != BTB_MAINTENANCE_OK ||
            BtbMaintenanceStart(review) != BTB_MAINTENANCE_OK) return 0;
    }
    return 1;
}

static int Scenario(const char *name)
{
    BtbMaintenanceReview review;
    BtbMaintenanceReview saved;
    BtbServiceSummary after;
    BtbServiceSummary baseline;
    BtbServiceSummary restore;
    char description[BTB_MAINTENANCE_SUMMARY_BYTES];
    if (strcmp(name, "baseline") == 0) {
        CHECK(BuildSummary(100U, BTB_ADMIN_FAILURE, BTB_ADMIN_PASS, 0, &baseline));
        (void)memset(&review, 0x5A, sizeof review);
        saved = review;
        CHECK(BtbMaintenanceInit(&review, "ChangeA", Revision, "OperatorA", &baseline)
                  == BTB_MAINTENANCE_INVALID);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "revision-invalid") == 0) {
        CHECK(BuildSummary(100U, BTB_ADMIN_PASS, BTB_ADMIN_PASS, 0, &baseline));
        (void)memset(&review, 0x5A, sizeof review);
        saved = review;
        CHECK(BtbMaintenanceInit(&review, "ChangeA", "not-a-revision", "OperatorA", &baseline)
                  == BTB_MAINTENANCE_INVALID);
        CHECK(BtbMaintenanceInit(&review, "../file", Revision, "OperatorA", &baseline)
                  == BTB_MAINTENANCE_INVALID);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    CHECK(Prepare(&review, 0));
    saved = review;
    if (strcmp(name, "approval-identity") == 0) {
        CHECK(BtbMaintenanceApprove(&review, "OperatorA", 1, 1)
                  == BTB_MAINTENANCE_INVALID);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "backup-required") == 0 ||
        strcmp(name, "rollback-plan") == 0) {
        CHECK(BtbMaintenanceApprove(&review, "ReviewerB",
                  strcmp(name, "backup-required") == 0 ? 0 : 1,
                  strcmp(name, "rollback-plan") == 0 ? 0 : 1)
                  == BTB_MAINTENANCE_PRECONDITION);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "premature-start") == 0) {
        CHECK(BtbMaintenanceStart(&review) == BTB_MAINTENANCE_STATE_ERROR);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "cancel") == 0) {
        CHECK(BtbMaintenanceCancel(&review) == BTB_MAINTENANCE_OK);
        CHECK(review.state == BTB_MAINTENANCE_CANCELLED);
        CHECK(BtbMaintenanceApprove(&review, "ReviewerB", 1, 1)
                  == BTB_MAINTENANCE_STATE_ERROR);
        return 0;
    }
    CHECK(BtbMaintenanceApprove(&review, "ReviewerB", 1, 1)
              == BTB_MAINTENANCE_OK);
    if (strcmp(name, "approved-start") == 0) {
        CHECK(review.state == BTB_MAINTENANCE_APPROVED);
        CHECK(BtbMaintenanceStart(&review) == BTB_MAINTENANCE_OK);
        CHECK(review.state == BTB_MAINTENANCE_STARTED);
        return 0;
    }
    CHECK(BtbMaintenanceStart(&review) == BTB_MAINTENANCE_OK);
    if (strcmp(name, "cancel-after-start") == 0) {
        saved = review;
        CHECK(BtbMaintenanceCancel(&review) == BTB_MAINTENANCE_STATE_ERROR);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "recovery-premature") == 0) {
        CHECK(BuildSummary(300U, BTB_ADMIN_PASS, BTB_ADMIN_PASS, 0, &restore));
        saved = review;
        CHECK(BtbMaintenanceConfirmRestored(&review, &restore)
                  == BTB_MAINTENANCE_STATE_ERROR);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    CHECK(BuildSummary(200U, BTB_ADMIN_PASS,
          strcmp(name, "blocked-post") == 0 || strcmp(name, "recovery-failed") == 0 ||
          strcmp(name, "recovery-success") == 0 || strcmp(name, "recovery-capture") == 0
          ? BTB_ADMIN_FAILURE : BTB_ADMIN_PASS,
          strcmp(name, "warning-post") == 0, &after));
    if (strcmp(name, "stale-post") == 0) after.captureId = review.before.captureId;
    if (strcmp(name, "changed-service") == 0) after.items[1].serviceId = 3U;
    if (strcmp(name, "invalid-post") == 0) after.items[0].decision = (BtbAdminDecision)99;
    if (strcmp(name, "preserve") == 0) after.ready = 90U;
    if (strcmp(name, "late-post") == 0) {
        CHECK(BtbMaintenanceObserveAfter(&review, &after) == BTB_MAINTENANCE_OK);
        saved = review;
        CHECK(BtbMaintenanceObserveAfter(&review, &after)
                 == BTB_MAINTENANCE_STATE_ERROR);
        CHECK(memcmp(&review, &saved, sizeof review) == 0);
        return 0;
    }
    if (strcmp(name, "stale-post") == 0 || strcmp(name, "changed-service") == 0 ||
        strcmp(name, "invalid-post") == 0 || strcmp(name, "preserve") == 0) {
        const BtbMaintenanceResult result = BtbMaintenanceObserveAfter(&review, &after);
        CHECK(result == ((strcmp(name, "invalid-post") == 0 || strcmp(name, "preserve") == 0)
                 ? BTB_MAINTENANCE_INVALID : BTB_MAINTENANCE_EVIDENCE_MISMATCH));
        CHECK(review.state == BTB_MAINTENANCE_STARTED && review.hasAfter == 0);
        return 0;
    }
    CHECK(BtbMaintenanceObserveAfter(&review, &after) == BTB_MAINTENANCE_OK);
    if (strcmp(name, "ready-post") == 0 || strcmp(name, "complete") == 0 ||
        strcmp(name, "explanation-capacity") == 0) {
        CHECK(review.state == BTB_MAINTENANCE_VERIFIED);
        if (strcmp(name, "complete") == 0)
            CHECK(BtbMaintenanceComplete(&review) == BTB_MAINTENANCE_OK);
        if (strcmp(name, "explanation-capacity") == 0) {
            char tiny[8] = "RETAIN";
            CHECK(BtbMaintenanceExplain(&review, tiny, sizeof tiny)
                == BTB_MAINTENANCE_CAPACITY);
            CHECK(strcmp(tiny, "RETAIN") == 0);
            CHECK(BtbMaintenanceExplain(&review, description, sizeof description)
                == BTB_MAINTENANCE_OK);
            CHECK(strstr(description, "VERIFIED") != NULL);
        }
        return 0;
    }
    if (strcmp(name, "warning-post") == 0 || strcmp(name, "blocked-post") == 0 ||
        strcmp(name, "recovery-failed") == 0 || strcmp(name, "recovery-success") == 0 ||
        strcmp(name, "recovery-capture") == 0) {
        CHECK(review.state == BTB_MAINTENANCE_ROLLBACK_REQUIRED);
        CHECK(BtbMaintenanceComplete(&review) == BTB_MAINTENANCE_STATE_ERROR);
        if (strcmp(name, "warning-post") == 0 || strcmp(name, "blocked-post") == 0)
            return 0;
        CHECK(BuildSummary(300U,
            strcmp(name, "recovery-failed") == 0 ? BTB_ADMIN_NOT_RUN : BTB_ADMIN_PASS,
            BTB_ADMIN_PASS, 0, &restore));
        if (strcmp(name, "recovery-capture") == 0)
            restore.captureId = review.after.captureId;
        saved = review;
        if (strcmp(name, "recovery-failed") == 0) {
            CHECK(BtbMaintenanceConfirmRestored(&review, &restore)
                == BTB_MAINTENANCE_PRECONDITION);
            CHECK(memcmp(&saved, &review, sizeof review) == 0);
        } else if (strcmp(name, "recovery-capture") == 0) {
            CHECK(BtbMaintenanceConfirmRestored(&review, &restore)
                == BTB_MAINTENANCE_EVIDENCE_MISMATCH);
            CHECK(memcmp(&saved, &review, sizeof review) == 0);
        } else {
            CHECK(BtbMaintenanceConfirmRestored(&review, &restore)
                == BTB_MAINTENANCE_OK);
            CHECK(review.state == BTB_MAINTENANCE_RESTORED);
            CHECK(review.restorationCaptureId == 300U);
        }
        return 0;
    }
    if (strcmp(name, "mutation") == 0) {
        uint32_t value = UINT32_C(0x12345678);
        for (size_t i = 0U; i < 30000U; ++i) {
            value = value * UINT32_C(1664525) + UINT32_C(1013904223);
            BtbMaintenanceReview each;
            BtbServiceSummary fresh;
            CHECK(Prepare(&each, 1));
            CHECK(BuildSummary((uint64_t)i + 200U,
                (value & UINT32_C(1)) ? BTB_ADMIN_PASS : BTB_ADMIN_NOT_RUN,
                BTB_ADMIN_PASS, (value & UINT32_C(2)) != 0U, &fresh));
            CHECK(BtbMaintenanceObserveAfter(&each, &fresh) == BTB_MAINTENANCE_OK);
            if (fresh.ready == fresh.count)
                CHECK(each.state == BTB_MAINTENANCE_VERIFIED);
            else CHECK(each.state == BTB_MAINTENANCE_ROLLBACK_REQUIRED);
        }
        return 0;
    }
    (void)fprintf(stderr, "Unknown case: %s\n", name);
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1] == NULL) {
        (void)fprintf(stderr, "Use one CTest scenario name.\n");
        return 2;
    }
    return Scenario(argv[1]);
}
