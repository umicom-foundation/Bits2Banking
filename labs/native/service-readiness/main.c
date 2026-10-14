/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * PURPOSE: Read-only fictional Umicom Notes readiness demonstration.
 *---------------------------------------------------------------------------*/
#include "service_readiness.h"
#include <stdio.h>

static int AddPassingCheck(BtbServiceGraph *graph, uint32_t serviceId,
                           uint32_t checkId, const char *name)
{
    BtbAdminReview review;
    BtbAdminObservation item = {0};
    if (BtbAdminReviewInit(&review, graph->captureId) != BTB_ADMIN_OK) return 0;
    item.checkId = checkId;
    item.captureId = graph->captureId;
    item.state = BTB_ADMIN_PASS;
    /* All demonstration labels are constants shorter than the public bound. */
    if (snprintf(item.label, sizeof(item.label), "%s", name) < 0) return 0;
    if (BtbAdminReviewAdd(&review, &item) != BTB_ADMIN_OK) return 0;
    return BtbServiceGraphAttach(graph, serviceId, &review) == BTB_SERVICE_OK;
}

int main(void)
{
    BtbServiceGraph graph;
    BtbServiceSummary summary;
    const BtbServiceSpec filesystem = {1U, 0U, UINT32_C(1), "Notes document storage"};
    const BtbServiceSpec application = {2U, UINT32_C(1), UINT32_C(1), "Notes application"};
    if (BtbServiceGraphInit(&graph, UINT64_C(20261014)) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &filesystem) != BTB_SERVICE_OK ||
        BtbServiceGraphRegister(&graph, &application) != BTB_SERVICE_OK ||
        !AddPassingCheck(&graph, 1U, 1U, "Practice folder readable") ||
        !AddPassingCheck(&graph, 2U, 1U, "Simulated Notes request complete") ||
        BtbServiceGraphEvaluate(&graph, &summary) != BTB_SERVICE_OK) return 1;
    printf("Fictional Umicom Notes readiness (no host inspection):\n");
    printf("Ready: %zu, review: %zu, blocked: %zu\n",
           summary.ready, summary.review, summary.blocked);
    return summary.ready == 2U && summary.blocked == 0U ? 0 : 2;
}
