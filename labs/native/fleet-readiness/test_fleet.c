/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/fleet-readiness/test_fleet.c
 * PURPOSE: Deterministic positive, adversarial and failure-atomic C23 checks.
 *---------------------------------------------------------------------------*/
#include "fleet_fixture.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void ExpectedStatus(const BtbFleetReview *review, BtbFleetStatus status,
                           uint32_t requiredIssues)
{
    BtbFleetDecision decision = {0};
    assert(BtbFleetEvaluate(review, &decision) == BTB_FLEET_OK);
    assert(decision.status == status);
    assert((decision.issues & requiredIssues) == requiredIssues);
}

static void FillValid(BtbFleetReview *review)
{
    assert(BtbFleetTrainingReview(review, 2U, 0));
}

static void RunSimple(const char *caseName)
{
    BtbFleetReview review;
    BtbFleetPolicy policy;
    BtbFleetHostEvidence host;
    BtbFleetDecision decision;
    assert(BtbFleetTrainingPolicy(&policy));

    if (strcmp(caseName, "ready") == 0) {
        FillValid(&review);
        ExpectedStatus(&review, BTB_FLEET_REVIEWABLE, 0U);
        assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_OK);
        assert(decision.readyCount == 2U && decision.observedCount == 2U);
    } else if (strcmp(caseName, "pending") == 0) {
        assert(BtbFleetTrainingReview(&review, 1U, 0));
        ExpectedStatus(&review, BTB_FLEET_PENDING, BTB_FLEET_MISSING_HOST);
    } else if (strcmp(caseName, "empty") == 0) {
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_OK);
        ExpectedStatus(&review, BTB_FLEET_PENDING, BTB_FLEET_MISSING_HOST);
    } else if (strcmp(caseName, "stale") == 0) {
        FillValid(&review);
        review.hosts[0].observedSeconds = 1479U;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_STALE_EVIDENCE);
    } else if (strcmp(caseName, "future") == 0) {
        FillValid(&review);
        review.hosts[1].observedSeconds = 1700U;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_FUTURE_EVIDENCE);
    } else if (strcmp(caseName, "revision") == 0) {
        FillValid(&review);
        review.hosts[1].observedSourceRevision[0] = 'a';
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_REVISION_MISMATCH);
    } else if (strcmp(caseName, "package") == 0) {
        FillValid(&review);
        review.hosts[0].observedPackageSha256[0] = 'b';
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_PACKAGE_MISMATCH);
    } else if (strcmp(caseName, "storage") == 0) {
        FillValid(&review);
        review.hosts[0].filesystemReadable = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_STORAGE_FAILURE);
    } else if (strcmp(caseName, "operation") == 0) {
        FillValid(&review);
        review.hosts[1].applicationOperationVerified = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_SERVICE_FAILURE);
    } else if (strcmp(caseName, "clock") == 0) {
        FillValid(&review);
        review.hosts[0].clockSynchronised = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_CLOCK_UNVERIFIED);
    } else if (strcmp(caseName, "provenance") == 0) {
        FillValid(&review);
        review.hosts[0].packageProvenanceReviewed = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_PACKAGE_UNVERIFIED);
    } else if (strcmp(caseName, "reviewer") == 0) {
        FillValid(&review);
        review.hosts[1].independentReviewerAssigned = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_REVIEWER_MISSING);
    } else if (strcmp(caseName, "privacy") == 0) {
        FillValid(&review);
        review.hosts[0].evidenceRedacted = 0;
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_PRIVACY_UNVERIFIED);
    } else if (strcmp(caseName, "upstream-blocked") == 0) {
        assert(BtbFleetTrainingReview(&review, 2U, 1));
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_OPERATIONS_BLOCKED);
    } else if (strcmp(caseName, "restored-only") == 0) {
        assert(BtbFleetTrainingReview(&review, 2U, 2));
        ExpectedStatus(&review, BTB_FLEET_RESTORED_ONLY, BTB_FLEET_RESTORED_PREVIOUS);
    } else if (strcmp(caseName, "independent-host") == 0) {
        FillValid(&review);
        review.hosts[0].applicationOperationVerified = 0;
        assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_OK);
        assert(decision.blockedCount == 1U && decision.readyCount == 1U);
    } else if (strcmp(caseName, "missing-host") == 0) {
        assert(BtbFleetTrainingReview(&review, 1U, 0));
        assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_OK);
        assert(decision.missingCount == 1U && decision.readyCount == 1U);
    } else if (strcmp(caseName, "unknown") == 0) {
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_OK);
        assert(BtbFleetTrainingHost(&host, "outsider", 0, 1));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_UNKNOWN_HOST);
        assert(review.observedCount == 0U);
    } else if (strcmp(caseName, "duplicate") == 0) {
        assert(BtbFleetTrainingReview(&review, 1U, 0));
        assert(BtbFleetTrainingHost(&host, "notes-gateway", 0, 1));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_DUPLICATE_HOST);
        assert(review.observedCount == 1U);
    } else if (strcmp(caseName, "invalid-name") == 0) {
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_OK);
        assert(BtbFleetTrainingHost(&host, "notes-gateway", 0, 1));
        host.hostId[0] = '!';
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_INVALID);
    } else if (strcmp(caseName, "invalid-policy") == 0) {
        policy.hostCount = 0U;
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_INVALID);
    } else if (strcmp(caseName, "invalid-hex") == 0) {
        policy.expectedPackageSha256[0] = 'X';
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_INVALID);
    } else if (strcmp(caseName, "atomic-init") == 0) {
        BtbFleetReview before;
        (void)memset(&review, 0x5c, sizeof review);
        before = review;
        policy.requiredHosts[1][0] = '!';
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_INVALID);
        assert(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(caseName, "atomic-attach") == 0) {
        BtbFleetReview before;
        assert(BtbFleetTrainingReview(&review, 1U, 0));
        before = review;
        assert(BtbFleetTrainingHost(&host, "notes-gateway", 0, 1));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_DUPLICATE_HOST);
        assert(memcmp(&review, &before, sizeof review) == 0);
    } else if (strcmp(caseName, "atomic-evaluate") == 0) {
        BtbFleetDecision before;
        FillValid(&review);
        review.hosts[0].clockSynchronised = 3;
        (void)memset(&decision, 0x5c, sizeof decision);
        before = decision;
        assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_INVALID);
        assert(memcmp(&decision, &before, sizeof decision) == 0);
    } else if (strcmp(caseName, "tampered-host") == 0) {
        FillValid(&review);
        review.hosts[1].hostId[0] = '!';
        assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_INVALID);
    } else if (strcmp(caseName, "pending-upstream") == 0) {
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_OK);
        assert(BtbFleetTrainingHost(&host, "notes-gateway", 0, 0));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_OK);
        ExpectedStatus(&review, BTB_FLEET_BLOCKED, BTB_FLEET_OPERATIONS_BLOCKED);
    } else if (strcmp(caseName, "out-of-order") == 0) {
        assert(BtbFleetInit(&review, &policy) == BTB_FLEET_OK);
        assert(BtbFleetTrainingHost(&host, "notes-storage", 0, 1));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_OK);
        assert(BtbFleetTrainingHost(&host, "notes-gateway", 0, 1));
        assert(BtbFleetAttach(&review, &host) == BTB_FLEET_OK);
        ExpectedStatus(&review, BTB_FLEET_REVIEWABLE, 0U);
    } else if (strcmp(caseName, "mutations") == 0) {
        uint32_t rng = UINT32_C(39175);
        unsigned iterations;
        FillValid(&review);
        for (iterations = 0U; iterations < 30000U; ++iterations) {
            unsigned mask;
            rng = rng * UINT32_C(1664525) + UINT32_C(1013904223);
            mask = rng % 7U;
            review.hosts[0].clockSynchronised = mask == 0U ? 0 : 1;
            review.hosts[1].filesystemReadable = mask == 1U ? 0 : 1;
            review.hosts[0].applicationOperationVerified = mask == 2U ? 0 : 1;
            review.hosts[0].observedSeconds = mask == 3U ? 1700U : 1550U;
            assert(BtbFleetEvaluate(&review, &decision) == BTB_FLEET_OK);
            assert(decision.status == (mask <= 3U ? BTB_FLEET_BLOCKED :
                                      BTB_FLEET_REVIEWABLE));
        }
        (void)printf("30,000 deterministic fleet transitions passed.\n");
    } else {
        (void)fprintf(stderr, "Unknown test case: %s\n", caseName);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1] == NULL) return 2;
    RunSimple(argv[1]);
    return 0;
}
