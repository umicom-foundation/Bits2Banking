/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/shared-signed-delta/main.c
 *
 * PURPOSE:
 *   Check a signed difference before passing it to a Windows x64 assembly leaf.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>

extern int32_t UmiLessonBalanceDelta(int32_t received, int32_t booked);

/* Widen before subtracting. The assembly leaf receives only cases whose
 * mathematical answer fits the 32-bit result promised by the C interface. */
static bool CheckedDelta(int32_t received, int32_t booked, int32_t *out)
{
    if (out == NULL) return false;
    const int64_t wide = (int64_t)received - (int64_t)booked;
    if (wide < INT32_MIN || wide > INT32_MAX) return false;
    *out = UmiLessonBalanceDelta(received, booked);
    return true;
}

int main(void)
{
    static const struct {
        int32_t received;
        int32_t booked;
        int32_t difference;
        bool accepted;
    } cases[] = {
        {120, 78, 42, true},
        {17, 59, -42, true},
        {24, 24, 0, true},
        {INT32_MIN, 0, INT32_MIN, true},
        {INT32_MAX, 0, INT32_MAX, true},
        {INT32_MAX, -1, 77, false},
        {INT32_MIN, 1, 77, false}
    };

    /* The marker is a previous caller value. Both refusing rows leave it intact. */
    const size_t count = sizeof cases / sizeof cases[0];
    for (size_t index = 0U; index < count; ++index) {
        int32_t output = 77;
        const bool accepted = CheckedDelta(cases[index].received, cases[index].booked, &output);
        if (accepted != cases[index].accepted || output != cases[index].difference) {
            fprintf(stderr, "Unexpected status or output on row %zu.\n", index + 1U);
            return 1;
        }
    }

    /* The same precondition rejects an absent output before any result is made. */
    if (CheckedDelta(120, 78, NULL)) return 2;
    printf("Verified %zu signed delta rows and an absent output.\n", count);
    return 0;
}
