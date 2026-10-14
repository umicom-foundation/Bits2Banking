/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * PURPOSE: Offline fictional service-maintenance review and recovery.
 * No operating-system service, file, Git repository or network is touched.
 *---------------------------------------------------------------------------*/
#include "maintenance_review.h"
#include <stdio.h>

static int MakeSummary(uint64_t captureId, BtbAdminState storageState,
                       BtbServiceSummary *summary)
{
    BtbServiceGraph graph;
    const BtbServiceSpec storage = {1U, 0U, UINT32_C(1), "Notes storage"};
    const BtbServiceSpec notes = {2U, UINT32_C(1), UINT32_C(1), "Notes application"};
    if (BtbServiceGraphInit(&graph, captureId) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &storage) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &notes) != BTB_SERVICE_OK) return 0;
    for (uint32_t id = 1U; id <= 2U; ++id) {
        BtbAdminReview review;
        BtbAdminObservation check = {0};
        if (BtbAdminReviewInit(&review, captureId) != BTB_ADMIN_OK) return 0;
        check.checkId = 1U;
        check.captureId = captureId;
        check.state = id == 1U ? storageState : BTB_ADMIN_PASS;
        (void)snprintf(check.label, sizeof check.label, "Safe training check %u", id);
        if (BtbAdminReviewAdd(&review, &check) != BTB_ADMIN_OK ||
            BtbServiceGraphAttach(&graph, id, &review) != BTB_SERVICE_OK) return 0;
    }
    return BtbServiceGraphEvaluate(&graph, summary) == BTB_SERVICE_OK;
}
int main(void)
{
    BtbServiceSummary baseline;
    BtbServiceSummary failedPost;
    BtbServiceSummary restored;
    BtbMaintenanceReview change;
    char message[BTB_MAINTENANCE_SUMMARY_BYTES];
    const char *revision = "0123456789abcdef0123456789abcdef01234567";
    if (!MakeSummary(100U, BTB_ADMIN_PASS, &baseline) ||
        !MakeSummary(200U, BTB_ADMIN_FAILURE, &failedPost) ||
        !MakeSummary(300U, BTB_ADMIN_PASS, &restored) ||
        BtbMaintenanceInit(&change, "UmiNotesMaintenance", revision, "OperatorA",
            &baseline) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceApprove(&change, "ReviewerB", 1, 1) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceStart(&change) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceObserveAfter(&change, &failedPost) != BTB_MAINTENANCE_OK)
        return 1;
    (void)printf("Fictional post-change decision: %s\n",
                 BtbMaintenanceStateText(change.state));
    if (change.state != BTB_MAINTENANCE_ROLLBACK_REQUIRED ||
        BtbMaintenanceConfirmRestored(&change, &restored) != BTB_MAINTENANCE_OK ||
        BtbMaintenanceExplain(&change, message, sizeof message) != BTB_MAINTENANCE_OK)
        return 2;
    (void)printf("%s", message);
    return change.state == BTB_MAINTENANCE_RESTORED ? 0 : 3;
}
