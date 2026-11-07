/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/profile-name-boundary/main.c
 *
 * PURPOSE:
 *   Use the Framework byte-span validator without collecting a password.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/security/local_profile.h"
#include <stdio.h>

int main(void)
{
    /* A protocol field can contain bytes without a trailing zero. The length
     * belongs to the field, so this example does not invent a terminator. */
    const char field[] = {'A', 'l', 'i', 'c', 'e', '_', '7'};
    char canonical[UMI_LOCAL_PROFILE_NAME_CAPACITY];
    UmiStatus status = UmiLocalProfileNameBytes(field, sizeof(field), canonical);
    if (status != UMI_STATUS_OK) {
        fputs("The profile name is invalid.\n", stderr);
        return 1;
    }
    printf("Canonical name: %s\n", canonical);
    return 0;
}
