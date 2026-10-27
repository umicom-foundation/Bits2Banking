/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/framework-activity/console.c
 *
 * PURPOSE:
 *   Use an installed Framework SDK from a small C23 console application.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "activity.h"
#include <stdio.h>
int main(void)
{
    unsigned completed = 0U;
    UmiStatus status = BtbActivityAdvance(completed, &completed);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Could not record exercise: %s\n", umi_status_text(status));
        return 1;
    }
    printf("Completed exercises: %u\n", completed);
    return 0;
}
