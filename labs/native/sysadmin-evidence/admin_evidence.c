/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-evidence/admin_evidence.c
 * PURPOSE: Fixed-capacity, failure-atomic observation and qualification model.
 *---------------------------------------------------------------------------*/
#include "admin_evidence.h"
#include <string.h>

/* A bounded terminator check prevents reading past a caller-owned label. */
static int ValidLabel(const char text[BTB_ADMIN_LABEL_CAPACITY])
{
    const void *end = memchr(text, '\0', BTB_ADMIN_LABEL_CAPACITY);
    return end != NULL && text[0] != '\0';
}

static int ValidState(BtbAdminState state)
{
    return state >= BTB_ADMIN_PASS && state <= BTB_ADMIN_NOT_RUN;
}

static int ValidReview(const BtbAdminReview *review)
{
    return review != NULL && review->captureId != 0U &&
           review->count <= BTB_ADMIN_MAX_CHECKS;
}

BtbAdminResult BtbAdminReviewInit(BtbAdminReview *review, uint64_t captureId)
{
    if (review == NULL || captureId == 0U) return BTB_ADMIN_INVALID;
    BtbAdminReview fresh = {0};
    fresh.captureId = captureId;
    *review = fresh;
    return BTB_ADMIN_OK;
}

BtbAdminResult BtbAdminReviewAdd(BtbAdminReview *review,
                                 const BtbAdminObservation *observation)
{
    if (!ValidReview(review) || observation == NULL ||
        observation->checkId == 0U ||
        observation->checkId > BTB_ADMIN_MAX_CHECK_ID ||
        observation->captureId == 0U ||
        !ValidState(observation->state) || !ValidLabel(observation->label))
        return BTB_ADMIN_INVALID;

    /* Never replace a previously recorded check implicitly. */
    for (size_t i = 0U; i < review->count; ++i) {
        if (review->observations[i].checkId == observation->checkId)
            return BTB_ADMIN_DUPLICATE;
    }
    if (review->count >= BTB_ADMIN_MAX_CHECKS) return BTB_ADMIN_FULL;

    review->observations[review->count] = *observation;
    ++review->count;
    return BTB_ADMIN_OK;
}

BtbAdminResult BtbAdminReviewEvaluate(const BtbAdminReview *review,
                                      uint32_t requiredMask,
                                      BtbAdminReport *outReport)
{
    /* All 32 ID bits are valid even though only 16 observations fit. */
    uint32_t passingRequired = 0U;
    int badRequired = 0;
    int needsReview = 0;
    BtbAdminReport candidate = {0};
    if (!ValidReview(review) || outReport == NULL || requiredMask == 0U) return BTB_ADMIN_INVALID;

    candidate.requiredMask = requiredMask;
    for (size_t i = 0U; i < review->count; ++i) {
        const BtbAdminObservation *observation = &review->observations[i];
        if (observation->checkId == 0U ||
            observation->checkId > BTB_ADMIN_MAX_CHECK_ID ||
            !ValidState(observation->state) ||
            !ValidLabel(observation->label) || observation->captureId == 0U)
            return BTB_ADMIN_INVALID;
        const uint32_t bit = UINT32_C(1) << (observation->checkId - 1U);
        if ((candidate.presentMask & bit) != 0U) return BTB_ADMIN_INVALID;
        candidate.presentMask |= bit;
        const int required = (requiredMask & bit) != 0U;
        if (observation->captureId != review->captureId) {
            ++candidate.stale;
            if (required) badRequired = 1;
            else needsReview = 1;
            continue;
        }
        switch (observation->state) {
            case BTB_ADMIN_PASS:
                ++candidate.passed;
                if (required) passingRequired |= bit;
                break;
            case BTB_ADMIN_WARNING:
                ++candidate.warnings;
                if (required) badRequired = 1;
                else needsReview = 1;
                break;
            case BTB_ADMIN_FAILURE:
                ++candidate.failed;
                if (required) badRequired = 1;
                else needsReview = 1;
                break;
            case BTB_ADMIN_NOT_RUN:
                ++candidate.notRun;
                if (required) badRequired = 1;
                else needsReview = 1;
                break;
            default: return BTB_ADMIN_INVALID;
        }
    }
    /* Count every missing required check separately to make omissions visible. */
    for (uint32_t id = 1U; id <= BTB_ADMIN_MAX_CHECK_ID; ++id) {
        const uint32_t bit = UINT32_C(1) << (id - 1U);
        if ((requiredMask & bit) != 0U && (candidate.presentMask & bit) == 0U)
            ++candidate.missingRequired;
    }
    if (badRequired || candidate.missingRequired != 0U ||
        (passingRequired & requiredMask) != requiredMask)
        candidate.decision = BTB_ADMIN_BLOCKED;
    else if (needsReview)
        candidate.decision = BTB_ADMIN_REVIEW;
    else
        candidate.decision = BTB_ADMIN_READY;
    *outReport = candidate;
    return BTB_ADMIN_OK;
}

const char *BtbAdminDecisionText(BtbAdminDecision decision)
{
    switch (decision) {
        case BTB_ADMIN_READY: return "READY (classroom model only)";
        case BTB_ADMIN_REVIEW: return "REVIEW: inspect non-blocking issues";
        case BTB_ADMIN_BLOCKED: return "BLOCKED: required evidence missing or adverse";
        default: return "INVALID";
    }
}
