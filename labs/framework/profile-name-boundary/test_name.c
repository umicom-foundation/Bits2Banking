/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/profile-name-boundary/test_name.c
 *
 * PURPOSE:
 *   Check exact spans, rejected bytes, output preservation and overlapping buffers.
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
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; } } while (0)

int main(void)
{
    char result[UMI_LOCAL_PROFILE_NAME_CAPACITY];
    char saved[UMI_LOCAL_PROFILE_NAME_CAPACITY];
    const char plain[] = {'S', 'a', 'm'};
    REQUIRE(UmiLocalProfileNameBytes(plain, sizeof(plain), result) == UMI_STATUS_OK);
    REQUIRE(strcmp(result, "sam") == 0);
    memset(result, 'Q', sizeof(result));
    memcpy(saved, result, sizeof(saved));
    const char invalid[] = {'S', '\0', 'm'};
    REQUIRE(UmiLocalProfileNameBytes(invalid, sizeof(invalid), result) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(memcmp(result, saved, sizeof(result)) == 0);
    REQUIRE(UmiLocalProfileNameBytes(NULL, 3U, result) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(UmiLocalProfileNameBytes(plain, 2U, result) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(memcmp(result, saved, sizeof(result)) == 0);
    char alias[UMI_LOCAL_PROFILE_NAME_CAPACITY] = "Sam";
    REQUIRE(UmiLocalProfileNameBytes(alias, 3U, alias) == UMI_STATUS_OK);
    REQUIRE(strcmp(alias, "sam") == 0);
    return 0;
}
