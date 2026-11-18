/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/boundary.c
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

#include "boundary.h"
#include <stddef.h>
int32_t bounded_progress(int32_t completed, int32_t total, int32_t *percent)
{
    if (percent == NULL || total <= 0 || completed < 0 || completed > total)
        return 1;
    /* Widen before multiplying; publish only after validation. */
    const int64_t scaled = (int64_t)completed * 100;
    *percent = (int32_t)(scaled / total);
    return 0;
}

int32_t bounded_progress_visit(const int32_t *completed, const int32_t *total,
    int32_t count, ProgressVisitor visitor, void *context, int32_t *accepted)
{
    if (accepted == NULL) return 1;
    *accepted = 0;
    if (count < 0 || count > 64) return 1;
    if (count == 0) return 0;
    if (completed == NULL || total == NULL || visitor == NULL) return 1;
    int32_t percentages[64];
    /* Admission precedes side effects. The existing arithmetic owner checks
     * every pair; invalid later input cannot leave earlier callbacks applied. */
    for (int32_t index = 0; index < count; ++index)
        if (bounded_progress(completed[index], total[index], &percentages[index]) != 0)
            return 1;
    for (int32_t index = 0; index < count; ++index) {
        if (visitor(index, percentages[index], context) != 0) return 2;
        ++*accepted;
    }
    return 0;
}
