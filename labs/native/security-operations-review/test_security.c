/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/test_security.c
 * PURPOSE: Named negative, preservation, composition and mutation tests.
 *---------------------------------------------------------------------------*/
#include "training_fixture.h"
#include <stdio.h>
#include <string.h>

#define CHECK(expr) do { if (!(expr)) { \
    (void)fprintf(stderr,"FAILED %s:%d: %s\n",__FILE__,__LINE__,#expr); \
    return 1; } } while (0)

static int Blocked(BtbSecurityReview *review, uint32_t expectedBit)
{
    BtbSecurityDecision decision;
    CHECK(BtbSecurityEvaluate(review, &decision) == BTB_SECURITY_OK);
    CHECK(decision.status == BTB_SECURITY_BLOCKED);
    CHECK((decision.missingEvidence & expectedBit) != 0U);
    return 0;
}

static int Scenario(const char *name)
{
    BtbSecurityReview review;
    BtbSecurityReview original;
    BtbSecurityPlan plan;
    BtbSecurityEvidence evidence;
    BtbSecurityDecision decision;
    BtbSecurityDecision saved;
    BtbRemoteReview remote;

    CHECK(BtbSecurityTrainingReview(&review, 0));
    CHECK(BtbSecurityTrainingPlan(&plan));
    CHECK(BtbSecurityTrainingEvidence(&evidence));
    if (strcmp(name, "pending") == 0) {
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_OK);
        CHECK(decision.status == BTB_SECURITY_PENDING);
        CHECK((decision.missingEvidence & BTB_SECURITY_MISSING_OBSERVATION) != 0U);
    } else if (strcmp(name, "reviewable") == 0) {
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_OK);
        CHECK(decision.status == BTB_SECURITY_REVIEWABLE);
        CHECK(decision.missingEvidence == 0U);
        CHECK(decision.remoteStatus == BTB_REMOTE_REVIEWABLE);
        CHECK(strcmp(BtbSecurityStatusText(decision.status), "REVIEWABLE") == 0);
    } else if (strcmp(name, "accounts") == 0) {
        evidence.accountsReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_ACCOUNT_REVIEW) == 0);
    } else if (strcmp(name, "groups") == 0) {
        evidence.groupMembershipReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_GROUP_REVIEW) == 0);
    } else if (strcmp(name, "privilege") == 0) {
        evidence.leastPrivilegeReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_LEAST_PRIVILEGE) == 0);
    } else if (strcmp(name, "config") == 0) {
        evidence.configurationCompared = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_CONFIG_CHECK) == 0);
    } else if (strcmp(name, "drift") == 0) {
        evidence.unexplainedDriftAbsent = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_UNEXPLAINED_DRIFT) == 0);
    } else if (strcmp(name, "patch") == 0) {
        evidence.patchEvidenceReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_PATCH_EVIDENCE) == 0);
    } else if (strcmp(name, "restore") == 0) {
        evidence.independentRestoreTestRecorded = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_RESTORE_TEST) == 0);
    } else if (strcmp(name, "audit") == 0) {
        evidence.auditRetentionReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_AUDIT_REVIEW) == 0);
    } else if (strcmp(name, "credentials") == 0) {
        evidence.credentialsExcludedFromEvidence = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_CREDENTIAL_EXPOSURE_RISK) == 0);
    } else if (strcmp(name, "rotation") == 0) {
        evidence.credentialRotationPlanReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_ROTATION_REVIEW) == 0);
    } else if (strcmp(name, "certificate") == 0) {
        evidence.certificateExpiryReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_CERTIFICATE_REVIEW) == 0);
    } else if (strcmp(name, "reviewer") == 0) {
        evidence.independentApprovalRecorded = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_APPROVAL) == 0);
    } else if (strcmp(name, "response") == 0) {
        evidence.monitoringResponsePathReviewed = 0;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_MISSING_RESPONSE_PATH) == 0);
    } else if (strcmp(name, "stale") == 0) {
        evidence.captureId = 260U;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_STALE_CAPTURE) == 0);
    } else if (strcmp(name, "outside-window") == 0) {
        evidence.observationSeconds = 2000U;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        CHECK(Blocked(&review, BTB_SECURITY_OUTSIDE_REVIEW_WINDOW) == 0);
    } else if (strcmp(name, "revision") == 0) {
        evidence.observedSourceRevision[0] = 'f';
        original = review;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_MISMATCH);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "config-mismatch") == 0) {
        evidence.observedConfigurationSha256[0] = 'a';
        original = review;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_MISMATCH);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "policy-mismatch") == 0) {
        evidence.observedPolicyRevision[0] = 'x';
        original = review;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_MISMATCH);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "same-person") == 0) {
        CHECK(BtbSecurityTrainingRemote(&remote, 0));
        (void)snprintf(plan.independentReviewer,
                       sizeof plan.independentReviewer, "%s", "MakerA");
        original = review;
        CHECK(BtbSecurityInit(&review, &plan, &remote) == BTB_SECURITY_INVALID);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "bad-label") == 0) {
        CHECK(BtbSecurityTrainingRemote(&remote, 0));
        plan.serviceId[2] = '\n';
        original = review;
        CHECK(BtbSecurityInit(&review, &plan, &remote) == BTB_SECURITY_INVALID);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "bad-flag") == 0) {
        evidence.accountsReviewed = 2;
        original = review;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_INVALID);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "repeat") == 0) {
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        original = review;
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_STATE_ERROR);
        CHECK(memcmp(&review, &original, sizeof review) == 0);
    } else if (strcmp(name, "upstream-rollback") == 0) {
        CHECK(BtbSecurityTrainingComplete(&review, 1));
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_OK);
        CHECK(decision.status == BTB_SECURITY_BLOCKED);
        CHECK((decision.missingEvidence & BTB_SECURITY_UPSTREAM_UNQUALIFIED) != 0U);
    } else if (strcmp(name, "upstream-restored") == 0) {
        CHECK(BtbSecurityTrainingComplete(&review, 2));
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_OK);
        CHECK(decision.status == BTB_SECURITY_RESTORED_ONLY);
    } else if (strcmp(name, "tampered-window") == 0) {
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        (void)memset(&decision, 0xA5, sizeof decision);
        saved = decision;
        review.plan.reviewWindowEndSeconds += 1U;
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_MISMATCH);
        CHECK(memcmp(&decision, &saved, sizeof decision) == 0);
    } else if (strcmp(name, "fail-atomic") == 0) {
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        (void)memset(&decision, 0xA5, sizeof decision);
        saved = decision;
        review.plan.policyRevision[0] = '\n';
        CHECK(BtbSecurityEvaluate(&review, &decision) == BTB_SECURITY_INVALID);
        CHECK(memcmp(&decision, &saved, sizeof decision) == 0);
    } else if (strcmp(name, "mutations") == 0) {
        CHECK(BtbSecurityAttach(&review, &evidence) == BTB_SECURITY_OK);
        for (unsigned i = 0U; i < 25000U; ++i) {
            BtbSecurityReview changed = review;
            const unsigned selected = i % 15U;
            if (selected == 0U) changed.evidence.accountsReviewed = 0;
            if (selected == 1U) changed.evidence.groupMembershipReviewed = 0;
            if (selected == 2U) changed.evidence.leastPrivilegeReviewed = 0;
            if (selected == 3U) changed.evidence.configurationCompared = 0;
            if (selected == 4U) changed.evidence.unexplainedDriftAbsent = 0;
            if (selected == 5U) changed.evidence.patchEvidenceReviewed = 0;
            if (selected == 6U) changed.evidence.independentRestoreTestRecorded = 0;
            if (selected == 7U) changed.evidence.auditRetentionReviewed = 0;
            if (selected == 8U) changed.evidence.credentialsExcludedFromEvidence = 0;
            if (selected == 9U) changed.evidence.credentialRotationPlanReviewed = 0;
            if (selected == 10U) changed.evidence.certificateExpiryReviewed = 0;
            if (selected == 11U) changed.evidence.independentApprovalRecorded = 0;
            if (selected == 12U) changed.evidence.monitoringResponsePathReviewed = 0;
            if (selected == 13U) changed.evidence.captureId = 260U;
            if (selected == 14U) changed.evidence.observationSeconds = 2000U;
            CHECK(BtbSecurityEvaluate(&changed, &decision) == BTB_SECURITY_OK);
            CHECK(decision.status == BTB_SECURITY_BLOCKED);
            CHECK(decision.missingEvidence != 0U);
        }
    } else return 2;
    return 0;
}

int main(int argc, char **argv)
{
    int result;
    if (argc != 2) {
        (void)fprintf(stderr,"Usage: btb-security-operations-test <case>\n");
        return 2;
    }
    result = Scenario(argv[1]);
    if (result == 0) (void)printf("PASS: %s\n",argv[1]);
    return result;
}
