/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/test_operations.c
 * PURPOSE: Named positive, negative, ownership, age and mutation scenarios.
 *---------------------------------------------------------------------------*/
#include "operations_fixture.h"
#include "training_fixture.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CHECK(expr) do { if (!(expr)) { \
    (void)fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
    return 1; } } while (0)

static int HasDecision(const BtbOpsReview *review, BtbOpsStatus status,
                       uint32_t bit)
{
    BtbOpsDecision decision;
    if (BtbOpsEvaluate(review, &decision) != BTB_OPS_OK ||
        decision.status != status) return 0;
    if (bit != 0U && (decision.missingEvidence & bit) == 0U) return 0;
    return 1;
}

static int Scenario(const char *name)
{
    BtbOpsReview review;
    BtbOpsDecision decision;
    BtbOpsPolicy policy;
    BtbOpsEvidence evidence;
    BtbSecurityReview security;
    if (strcmp(name,"ready") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        CHECK(HasDecision(&review, BTB_OPS_REVIEWABLE, 0U));
        CHECK(BtbOpsEvaluate(&review, &decision) == BTB_OPS_OK);
        CHECK(decision.missingEvidence == 0U);
        CHECK(decision.operationsCaptureId == 450U);
    } else if (strcmp(name,"pending") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 0));
        CHECK(HasDecision(&review, BTB_OPS_PENDING, BTB_OPS_MISSING_EVIDENCE));
    } else if (strcmp(name,"missing-heartbeat") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastHealthySeconds = 0U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_MISSING_HEARTBEAT));
    } else if (strcmp(name,"stale-heartbeat") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastHealthySeconds = 1000U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_STALE_HEARTBEAT));
    } else if (strcmp(name,"missing-backup") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastVerifiedBackupSeconds = 0U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_MISSING_BACKUP));
    } else if (strcmp(name,"stale-backup") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastVerifiedBackupSeconds = 10U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_STALE_BACKUP));
    } else if (strcmp(name,"missing-restore") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastSuccessfulRestoreDrillSeconds = 0U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_MISSING_RESTORE_DRILL));
    } else if (strcmp(name,"stale-restore") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.lastSuccessfulRestoreDrillSeconds = 10U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_STALE_RESTORE_DRILL));
    } else if (strcmp(name,"rpo") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.estimatedDataLossSeconds = 301U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_RPO_EXCEEDED));
    } else if (strcmp(name,"rto") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.measuredRecoverySeconds = 301U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_RTO_EXCEEDED));
    } else if (strcmp(name,"queue") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.queuedJobs = 6U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_QUEUE_CAPACITY));
    } else if (strcmp(name,"alert-owner") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.onCallOwnerAssigned = 0;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_ON_CALL_UNASSIGNED));
    } else if (strcmp(name,"alert-route") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.alertRouteTested = 0;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_ALERT_ROUTE_UNVERIFIED));
    } else if (strcmp(name,"privacy") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.auditEvidenceRedacted = 0;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_PRIVACY_UNVERIFIED));
    } else if (strcmp(name,"independent-restore") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.independentRestoreVerified = 0;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_RESTORE_UNVERIFIED));
    } else if (strcmp(name,"outside-window") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.observedSeconds = 1900U;
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_OUTSIDE_REVIEW_WINDOW));
    } else if (strcmp(name,"upstream-blocked") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 1, 1));
        CHECK(HasDecision(&review,BTB_OPS_BLOCKED,BTB_OPS_UPSTREAM_NOT_READY));
    } else if (strcmp(name,"upstream-restored") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 2, 1));
        CHECK(HasDecision(&review,BTB_OPS_RESTORED_ONLY,BTB_OPS_UPSTREAM_NOT_READY));
    } else if (strcmp(name,"source-mismatch") == 0) {
        BtbOpsReview before;
        CHECK(BtbOpsTrainingReview(&review, 0, 0));
        CHECK(BtbOpsTrainingEvidence(&evidence));
        before = review;
        evidence.observedSourceRevision[0] = 'f';
        CHECK(BtbOpsAttach(&review,&evidence) == BTB_OPS_MISMATCH);
        CHECK(memcmp(&review,&before,sizeof before)==0);
    } else if (strcmp(name,"repeat-attach") == 0) {
        BtbOpsReview before;
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        CHECK(BtbOpsTrainingEvidence(&evidence));
        before = review;
        CHECK(BtbOpsAttach(&review,&evidence) == BTB_OPS_STATE_ERROR);
        CHECK(memcmp(&review,&before,sizeof before)==0);
    } else if (strcmp(name,"invalid-flag") == 0) {
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        review.evidence.alertRouteTested = 7;
        decision = (BtbOpsDecision){.status=BTB_OPS_PENDING,.missingEvidence=0x65U};
        BtbOpsDecision before = decision;
        CHECK(BtbOpsEvaluate(&review,&decision) == BTB_OPS_INVALID);
        CHECK(memcmp(&decision,&before,sizeof before)==0);
    } else if (strcmp(name,"future-timestamp") == 0) {
        BtbOpsReview before;
        CHECK(BtbOpsTrainingReview(&review, 0, 0));
        CHECK(BtbOpsTrainingEvidence(&evidence));
        evidence.lastVerifiedBackupSeconds = evidence.observedSeconds + 1U;
        before = review;
        CHECK(BtbOpsAttach(&review,&evidence) == BTB_OPS_INVALID);
        CHECK(memcmp(&review,&before,sizeof before)==0);
    } else if (strcmp(name,"policy-invalid") == 0) {
        CHECK(BtbOpsTrainingPolicy(&policy));
        policy.maximumDataLossSeconds = 0U;
        CHECK(BtbSecurityTrainingComplete(&security,0));
        CHECK(BtbOpsInit(&review,&policy,&security)==BTB_OPS_INVALID);
    } else if (strcmp(name,"atomic-init") == 0) {
        BtbOpsReview before;
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        before = review;
        CHECK(BtbOpsTrainingPolicy(&policy));
        CHECK(BtbSecurityTrainingComplete(&security,0));
        policy.serviceId[0]='X';
        CHECK(BtbOpsInit(&review,&policy,&security) == BTB_OPS_MISMATCH);
        CHECK(memcmp(&review,&before,sizeof before)==0);
    } else if (strcmp(name,"atomic-attach") == 0) {
        BtbOpsReview before;
        CHECK(BtbOpsTrainingReview(&review, 0, 0));
        CHECK(BtbOpsTrainingEvidence(&evidence));
        before = review;
        evidence.captureId=0U;
        CHECK(BtbOpsAttach(&review,&evidence)==BTB_OPS_INVALID);
        CHECK(memcmp(&review,&before,sizeof before)==0);
    } else if (strcmp(name,"atomic-evaluate") == 0) {
        BtbOpsDecision before;
        CHECK(BtbOpsTrainingReview(&review, 0, 1));
        (void)memset(review.policy.serviceId, 'a', sizeof review.policy.serviceId);
        decision=(BtbOpsDecision){.status=BTB_OPS_BLOCKED,.missingEvidence=0xA5U};
        before=decision;
        CHECK(BtbOpsEvaluate(&review,&decision)==BTB_OPS_INVALID);
        CHECK(memcmp(&decision,&before,sizeof before)==0);
    } else if (strcmp(name,"cadence") == 0) {
        uint64_t next=0U;
        CHECK(BtbOpsNextDue(100U,10U,&next)==BTB_OPS_OK);
        CHECK(next==110U);
        CHECK(BtbOpsNextDue(0U,1U,&next)==BTB_OPS_OK);
        CHECK(next==1U);
    } else if (strcmp(name,"cadence-overflow") == 0) {
        uint64_t next=0x123456789U;
        CHECK(BtbOpsNextDue(UINT64_MAX,1U,&next)==BTB_OPS_INVALID);
        CHECK(next==0x123456789U);
        CHECK(BtbOpsNextDue(1U,0U,&next)==BTB_OPS_INVALID);
        CHECK(next==0x123456789U);
        CHECK(BtbOpsNextDue(1U,1U,NULL)==BTB_OPS_INVALID);
    } else if (strcmp(name,"mutations") == 0) {
        unsigned state=0x93bc18U;
        unsigned i;
        for (i=0U;i<30000U;++i) {
            CHECK(BtbOpsTrainingReview(&review, 0, 1));
            state=state*1664525U+1013904223U;
            switch (state%12U) {
                case 0U: review.evidence.lastHealthySeconds=0U; break;
                case 1U: review.evidence.lastHealthySeconds=1U; break;
                case 2U: review.evidence.lastVerifiedBackupSeconds=0U; break;
                case 3U: review.evidence.lastVerifiedBackupSeconds=2U; break;
                case 4U: review.evidence.lastSuccessfulRestoreDrillSeconds=0U; break;
                case 5U: review.evidence.lastSuccessfulRestoreDrillSeconds=3U; break;
                case 6U: review.evidence.estimatedDataLossSeconds=400U; break;
                case 7U: review.evidence.measuredRecoverySeconds=400U; break;
                case 8U: review.evidence.queuedJobs=6U; break;
                case 9U: review.evidence.alertRouteTested=0; break;
                case 10U: review.evidence.onCallOwnerAssigned=0; break;
                default: review.evidence.independentRestoreVerified=0; break;
            }
            CHECK(BtbOpsEvaluate(&review,&decision)==BTB_OPS_OK);
            CHECK(decision.status==BTB_OPS_BLOCKED);
            CHECK(decision.missingEvidence!=0U);
        }
    } else return 2;
    return 0;
}

int main(int argc,char **argv)
{
    int result;
    if (argc!=2) {
        (void)fprintf(stderr,"Usage: btb-operations-test <case-name>\n");
        return 2;
    }
    result=Scenario(argv[1]);
    if (result==0) (void)printf("PASS: %s\n",argv[1]);
    return result;
}
