/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/mobile/iphone-framework-profile/profile_bridge.c
 *
 * PURPOSE:
 *   Forward a Swift-friendly C span boundary to Framework without reproducing name rules.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "profile_bridge.h"
int BtbProfileCanonical(const unsigned char *input, size_t length,
    char output[UMI_LOCAL_PROFILE_NAME_CAPACITY])
{
    return UmiLocalProfileNameBytes((const char *)input, length, output) == UMI_STATUS_OK ? 1 : 0;
}
