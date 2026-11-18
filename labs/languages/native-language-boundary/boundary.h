/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/boundary.h
 *
 * PURPOSE:
 *   Teach and verify a fixed-width C ABI without transferring allocation ownership.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_LESSON_BOUNDARY_H
#define UMICOM_LESSON_BOUNDARY_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Caller owns percent. Failure returns 1 without modifying it. No allocation. */
int32_t bounded_progress(int32_t completed, int32_t total, int32_t *percent);

/* The visitor runs synchronously on the calling thread and is never retained.
 * index and percent are values; context is borrowed caller-owned state. Return
 * zero to accept this row, nonzero to stop. Never unwind a language exception
 * through C. The callback may already have side effects when it asks to stop.
 */
typedef int32_t (*ProgressVisitor)(int32_t index, int32_t percent, void *context);

/* Validate up to64 pairs before invoking any callback. Reuse bounded_progress
 * and snapshot percentages so callbacks cannot change later calculations.
 * Return0 on completion,1 on invalid input,2 when the visitor asks to stop.
 * accepted is initialized to0 whenever nonnull and counts only callbacks that
 * returned0. Callback side effects cannot be rolled back. Negative/over-limit
 * count is refused; count0 allows NULL arrays and visitor. No allocation,
 * thread creation or retained pointer. Inputs, accepted and callback state
 * must be valid separate objects for the duration of this call.
 */
int32_t bounded_progress_visit(const int32_t *completed, const int32_t *total,
    int32_t count, ProgressVisitor visitor, void *context, int32_t *accepted);
#ifdef __cplusplus
}
#endif
#endif
