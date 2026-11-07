/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-build-stages/runner.h
 *
 * PURPOSE:
 *   Declare a small hosted consumer of the existing Umicom C compiler and runtime.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef BTB_BUILD_STAGES_RUNNER_H
#define BTB_BUILD_STAGES_RUNNER_H
#include <stddef.h>
#include <stdint.h>
/* The source is borrowed for this call. A failed call leaves value unchanged. */
int LessonEvaluate(const char *source, size_t length, int32_t *value);
#endif
