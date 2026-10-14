/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-evidence/test_evidence.c
 * PURPOSE: Independent deterministic correctness and failure-atomicity tests.
 *---------------------------------------------------------------------------*/
#include "admin_evidence.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #expr); return 1; \
} } while (0)

static BtbAdminObservation Observation(uint32_t id, uint64_t capture, BtbAdminState state)
{
    BtbAdminObservation item = {0};
    item.checkId = id;
    item.captureId = capture;
    item.state = state;
    (void)snprintf(item.label, sizeof(item.label), "training check %u", id);
    return item;
}

static int Core(const char *test)
{
    BtbAdminReview review;
    BtbAdminReport report;
    BtbAdminObservation item;
    CHECK(BtbAdminReviewInit(&review, 42U) == BTB_ADMIN_OK);
    item = Observation(1U, 42U, BTB_ADMIN_PASS);
    CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_OK);
    item = Observation(2U, 42U, BTB_ADMIN_PASS);
    CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_OK);
    if (strcmp(test, "ready") == 0) {
        CHECK(BtbAdminReviewEvaluate(&review, 3U, &report) == BTB_ADMIN_OK);
        CHECK(report.decision == BTB_ADMIN_READY && report.passed == 2U);
    } else if (strcmp(test, "warning") == 0 || strcmp(test, "optional-fail") == 0 ||
               strcmp(test, "optional-notrun") == 0) {
        item = Observation(3U, 42U, strcmp(test, "warning") == 0 ?
                           BTB_ADMIN_WARNING : strcmp(test, "optional-fail") == 0 ?
                           BTB_ADMIN_FAILURE : BTB_ADMIN_NOT_RUN);
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_OK);
        CHECK(BtbAdminReviewEvaluate(&review, 3U, &report) == BTB_ADMIN_OK);
        CHECK(report.decision == BTB_ADMIN_REVIEW);
    } else if (strcmp(test, "missing") == 0) {
        CHECK(BtbAdminReviewEvaluate(&review, 7U, &report) == BTB_ADMIN_OK);
        CHECK(report.decision == BTB_ADMIN_BLOCKED && report.missingRequired == 1U);
    } else if (strcmp(test, "failure") == 0 || strcmp(test, "notrun") == 0 ||
               strcmp(test, "required-warning") == 0 || strcmp(test, "stale") == 0) {
        CHECK(BtbAdminReviewInit(&review, 42U) == BTB_ADMIN_OK);
        BtbAdminState state = strcmp(test, "failure") == 0 ? BTB_ADMIN_FAILURE :
             strcmp(test, "notrun") == 0 ? BTB_ADMIN_NOT_RUN :
             strcmp(test, "required-warning") == 0 ? BTB_ADMIN_WARNING : BTB_ADMIN_PASS;
        item = Observation(1U, strcmp(test, "stale") == 0 ? 41U : 42U, state);
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_OK);
        CHECK(BtbAdminReviewEvaluate(&review, 1U, &report) == BTB_ADMIN_OK);
        CHECK(report.decision == BTB_ADMIN_BLOCKED);
        if (strcmp(test, "stale") == 0) CHECK(report.stale == 1U);
    } else if (strcmp(test, "duplicate") == 0) {
        const BtbAdminReview before = review;
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_DUPLICATE);
        CHECK(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(test, "full") == 0) {
        CHECK(BtbAdminReviewInit(&review, 42U) == BTB_ADMIN_OK);
        for (uint32_t id = 1U; id <= BTB_ADMIN_MAX_CHECKS; ++id) {
            item = Observation(id, 42U, BTB_ADMIN_PASS);
            CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_OK);
        }
        const BtbAdminReview before = review;
        item = Observation(17U, 42U, BTB_ADMIN_PASS);
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_FULL);
        CHECK(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(test, "invalid") == 0) {
        const BtbAdminReview before = review;
        item = Observation(0U, 42U, BTB_ADMIN_PASS);
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_INVALID);
        CHECK(memcmp(&review, &before, sizeof review) == 0);
        item = Observation(3U, 42U, BTB_ADMIN_PASS);
        memset(item.label, 'x', sizeof item.label);
        CHECK(BtbAdminReviewAdd(&review, &item) == BTB_ADMIN_INVALID);
        CHECK(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(test, "preserve") == 0) {
        memset(&report, 0x5a, sizeof report);
        const BtbAdminReport before = report;
        CHECK(BtbAdminReviewEvaluate(&review, 0U, &report) == BTB_ADMIN_INVALID);
        CHECK(memcmp(&report, &before, sizeof report) == 0);
        CHECK(BtbAdminReviewEvaluate(NULL, 3U, &report) == BTB_ADMIN_INVALID);
        CHECK(memcmp(&report, &before, sizeof report) == 0);
    } else if (strcmp(test, "capture") == 0) {
        const BtbAdminReview before = review;
        CHECK(BtbAdminReviewInit(&review, 0U) == BTB_ADMIN_INVALID);
        CHECK(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(test, "repeated") == 0) {
        for (uint32_t i = 0U; i < 20000U; ++i) {
            CHECK(BtbAdminReviewEvaluate(&review, 3U, &report) == BTB_ADMIN_OK);
            CHECK(report.decision == BTB_ADMIN_READY);
        }
    } else return 1;
    return 0;
}

int main(int argc, char **argv)
{
    return argc == 2 ? Core(argv[1]) : 2;
}
