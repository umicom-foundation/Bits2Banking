/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/maintenance-review/maintenance_review.c
 * PURPOSE: Review a simulated maintenance window without touching the host.
 *
 * Source preservation: This is an additive composition of the existing
 * readiness/evidence teaching modules, not a replacement for Framework
 * supervision, approval, audit, or deployment services.
 *---------------------------------------------------------------------------*/
#include "maintenance_review.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* IDs are concise printable labels, not filesystem paths or credentials. */
static int ValidLabel(const char *value, size_t maximum)
{
    if (value == NULL || maximum < 2U) return 0;
    const char *end = memchr(value, '\0', maximum);
    if (end == NULL || end == value) return 0;
    for (const char *p = value; p != end; ++p) {
        const unsigned char c = (unsigned char)*p;
        if (!((c >= (unsigned char)'a' && c <= (unsigned char)'z') ||
              (c >= (unsigned char)'A' && c <= (unsigned char)'Z') ||
              (c >= (unsigned char)'0' && c <= (unsigned char)'9') ||
              c == (unsigned char)'_' || c == (unsigned char)'-' ||
              c == (unsigned char)'.')) return 0;
    }
    return 1;
}

static int ValidRevision(const char *value)
{
    if (value == NULL) return 0;
    const char *end = memchr(value, '\0', BTB_MAINTENANCE_REVISION_BYTES);
    if (end == NULL) return 0;
    const size_t length = (size_t)(end - value);
    if (length != 40U && length != 64U) return 0;
    for (size_t i = 0U; i < length; ++i) {
        const unsigned char c = (unsigned char)value[i];
        if (!isxdigit((int)c)) return 0;
    }
    return 1;
}

/* Reject malformed summaries rather than trusting caller-maintained totals.
 * This checks only educational evidence shape, not the identity of the host. */
static int ValidSummary(const BtbServiceSummary *summary)
{
    uint32_t seen = 0U;
    size_t ready = 0U;
    size_t review = 0U;
    size_t blocked = 0U;
    if (summary == NULL || summary->captureId == 0U ||
        summary->count == 0U || summary->count > BTB_SERVICE_MAX) return 0;
    for (size_t i = 0U; i < summary->count; ++i) {
        const BtbServiceOutcome *item = &summary->items[i];
        if (item->serviceId == 0U || item->serviceId > BTB_SERVICE_ID_MAX) return 0;
        const uint32_t bit = UINT32_C(1) << (item->serviceId - 1U);
        if ((seen & bit) != 0U) return 0;
        seen |= bit;
        if (item->decision == BTB_ADMIN_READY) {
            if (item->missingChecks != 0U || item->staleChecks != 0U ||
                item->blockedByDependency || item->degradedByDependency) return 0;
            ++ready;
        } else if (item->decision == BTB_ADMIN_REVIEW) {
            ++review;
        } else if (item->decision == BTB_ADMIN_BLOCKED) {
            ++blocked;
        } else return 0;
    }
    return summary->ready == ready && summary->review == review &&
           summary->blocked == blocked;
}

static int FullyReady(const BtbServiceSummary *summary)
{
    if (!ValidSummary(summary) || summary->ready != summary->count ||
        summary->review != 0U || summary->blocked != 0U) return 0;
    return 1;
}

static int SameServices(const BtbServiceSummary *first,
                        const BtbServiceSummary *second)
{
    if (!ValidSummary(first) || !ValidSummary(second) ||
        first->count != second->count) return 0;
    for (size_t i = 0U; i < first->count; ++i) {
        int found = 0;
        for (size_t j = 0U; j < second->count; ++j) {
            if (first->items[i].serviceId == second->items[j].serviceId) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

BtbMaintenanceResult BtbMaintenanceInit(BtbMaintenanceReview *review,
                                         const char *changeId,
                                         const char *sourceRevision,
                                         const char *operatorId,
                                         const BtbServiceSummary *before)
{
    BtbMaintenanceReview candidate = {0};
    if (review == NULL || !ValidLabel(changeId, sizeof candidate.changeId) ||
        !ValidRevision(sourceRevision) ||
        !ValidLabel(operatorId, sizeof candidate.operatorId) ||
        !FullyReady(before)) return BTB_MAINTENANCE_INVALID;
    (void)strcpy(candidate.changeId, changeId);
    (void)strcpy(candidate.sourceRevision, sourceRevision);
    (void)strcpy(candidate.operatorId, operatorId);
    candidate.before = *before;
    candidate.state = BTB_MAINTENANCE_PLANNED;
    *review = candidate;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceApprove(BtbMaintenanceReview *review,
                                            const char *approverId,
                                            int backupVerified,
                                            int rollbackDocumented)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_PLANNED)
        return BTB_MAINTENANCE_STATE_ERROR;
    if (!ValidLabel(approverId, sizeof review->approverId) ||
        strcmp(approverId, review->operatorId) == 0)
        return BTB_MAINTENANCE_INVALID;
    if (backupVerified != 1 || rollbackDocumented != 1)
        return BTB_MAINTENANCE_PRECONDITION;
    BtbMaintenanceReview candidate = *review;
    (void)strcpy(candidate.approverId, approverId);
    candidate.backupVerified = 1;
    candidate.rollbackDocumented = 1;
    candidate.state = BTB_MAINTENANCE_APPROVED;
    *review = candidate;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceStart(BtbMaintenanceReview *review)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_APPROVED)
        return BTB_MAINTENANCE_STATE_ERROR;
    review->state = BTB_MAINTENANCE_STARTED;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceObserveAfter(BtbMaintenanceReview *review,
                                                 const BtbServiceSummary *after)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_STARTED)
        return BTB_MAINTENANCE_STATE_ERROR;
    if (!ValidSummary(after)) return BTB_MAINTENANCE_INVALID;
    if (after->captureId == review->before.captureId ||
        !SameServices(&review->before, after)) return BTB_MAINTENANCE_EVIDENCE_MISMATCH;
    BtbMaintenanceReview candidate = *review;
    candidate.after = *after;
    candidate.hasAfter = 1;
    candidate.state = FullyReady(after) ? BTB_MAINTENANCE_VERIFIED
                                         : BTB_MAINTENANCE_ROLLBACK_REQUIRED;
    *review = candidate;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceComplete(BtbMaintenanceReview *review)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_VERIFIED)
        return BTB_MAINTENANCE_STATE_ERROR;
    review->state = BTB_MAINTENANCE_COMPLETE;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceConfirmRestored(BtbMaintenanceReview *review,
                                                   const BtbServiceSummary *restored)
{
    if (review == NULL || review->state != BTB_MAINTENANCE_ROLLBACK_REQUIRED)
        return BTB_MAINTENANCE_STATE_ERROR;
    if (!ValidSummary(restored)) return BTB_MAINTENANCE_INVALID;
    if (!review->hasAfter || restored->captureId == review->before.captureId ||
        restored->captureId == review->after.captureId ||
        !SameServices(&review->before, restored))
        return BTB_MAINTENANCE_EVIDENCE_MISMATCH;
    if (!FullyReady(restored)) return BTB_MAINTENANCE_PRECONDITION;
    review->restorationCaptureId = restored->captureId;
    review->state = BTB_MAINTENANCE_RESTORED;
    return BTB_MAINTENANCE_OK;
}

BtbMaintenanceResult BtbMaintenanceCancel(BtbMaintenanceReview *review)
{
    if (review == NULL || (review->state != BTB_MAINTENANCE_PLANNED &&
        review->state != BTB_MAINTENANCE_APPROVED))
        return BTB_MAINTENANCE_STATE_ERROR;
    review->state = BTB_MAINTENANCE_CANCELLED;
    return BTB_MAINTENANCE_OK;
}

const char *BtbMaintenanceStateText(BtbMaintenanceState state)
{
    switch (state) {
        case BTB_MAINTENANCE_PLANNED: return "PLANNED";
        case BTB_MAINTENANCE_APPROVED: return "APPROVED";
        case BTB_MAINTENANCE_STARTED: return "STARTED";
        case BTB_MAINTENANCE_VERIFIED: return "VERIFIED";
        case BTB_MAINTENANCE_ROLLBACK_REQUIRED: return "ROLLBACK_REQUIRED";
        case BTB_MAINTENANCE_COMPLETE: return "COMPLETE";
        case BTB_MAINTENANCE_RESTORED: return "RESTORED";
        case BTB_MAINTENANCE_CANCELLED: return "CANCELLED";
        default: return "UNKNOWN";
    }
}
const char *BtbMaintenanceResultText(BtbMaintenanceResult result)
{
    switch (result) {
        case BTB_MAINTENANCE_OK: return "OK";
        case BTB_MAINTENANCE_INVALID: return "INVALID";
        case BTB_MAINTENANCE_STATE_ERROR: return "STATE_ERROR";
        case BTB_MAINTENANCE_PRECONDITION: return "PRECONDITION";
        case BTB_MAINTENANCE_EVIDENCE_MISMATCH: return "EVIDENCE_MISMATCH";
        case BTB_MAINTENANCE_CAPACITY: return "CAPACITY";
        default: return "UNKNOWN";
    }
}

BtbMaintenanceResult BtbMaintenanceExplain(const BtbMaintenanceReview *review,
                                            char *output, size_t capacity)
{
    char candidate[BTB_MAINTENANCE_SUMMARY_BYTES];
    int length;
    if (review == NULL || output == NULL || capacity == 0U ||
        !ValidLabel(review->changeId, sizeof review->changeId) ||
        !ValidRevision(review->sourceRevision) ||
        !ValidLabel(review->operatorId, sizeof review->operatorId) ||
        !FullyReady(&review->before)) return BTB_MAINTENANCE_INVALID;
    length = snprintf(candidate, sizeof(candidate),
        "Change: %s\nRevision: %s\nOperator: %s\nState: %s\n"
        "Baseline capture: %llu\nAfter capture: %llu\nRestore capture: %llu\n",
        review->changeId, review->sourceRevision, review->operatorId,
        BtbMaintenanceStateText(review->state),
        (unsigned long long)review->before.captureId,
        (unsigned long long)(review->hasAfter ? review->after.captureId : 0U),
        (unsigned long long)review->restorationCaptureId);
    if (length < 0 || (size_t)length >= sizeof(candidate))
        return BTB_MAINTENANCE_CAPACITY;
    if ((size_t)length >= capacity) return BTB_MAINTENANCE_CAPACITY;
    (void)memcpy(output, candidate, (size_t)length + 1U);
    return BTB_MAINTENANCE_OK;
}
