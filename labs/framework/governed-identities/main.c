/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/governed-identities/main.c
 *
 * PURPOSE:
 *   Explore public identity directory validation and atomic enablement changes through Framework.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/security/identity_directory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRE(expr) do { if (!(expr)) { fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #expr); result = 1; goto finish; } } while (0)

int main(void)
{
    int result = 0;
    UmiSecurityIdentityDirectory *directory = calloc(1U, sizeof *directory);
    UmiSecurityIdentityDirectory *snapshot = calloc(1U, sizeof *snapshot);
    UmiSecurityIdentityProfile identity = {0};
    if (directory == NULL || snapshot == NULL) { result = 1; goto finish; }
    (void)snprintf(identity.identity_id, sizeof identity.identity_id, "%s", "lesson.reader");
    (void)snprintf(identity.display_name, sizeof identity.display_name, "%s", "Lesson reader");
    identity.kind = UMI_IDENTITY_HUMAN;
    identity.enabled = true;
    REQUIRE(umi_security_identity_directory_add(directory, &identity) == UMI_STATUS_OK);
    REQUIRE(directory->count == 1U && directory->revision == 1U);
    const UmiSecurityIdentityProfile *borrowed =
        umi_security_identity_directory_find(directory, "lesson.reader");
    REQUIRE(borrowed != NULL && borrowed->enabled);
    puts("Profile added: one row, revision one.");

    /* A borrowed pointer follows the directory's storage. Copy the value when
     * an earlier observation must remain available for comparison. */
    const UmiSecurityIdentityProfile observed = *borrowed;
    REQUIRE(umi_security_identity_directory_set_enabled(directory, "lesson.reader", false) == UMI_STATUS_OK);
    REQUIRE(!borrowed->enabled && observed.enabled);
    REQUIRE(borrowed->revision == 2U && directory->revision == 2U);
    puts("Borrowed row changed; earlier copied observation stayed unchanged.");

    directory->revision = UINT64_MAX;
    memcpy(snapshot, directory, sizeof *snapshot);
    REQUIRE(umi_security_identity_directory_set_enabled(directory, "lesson.reader", true) == UMI_STATUS_CAPACITY_EXCEEDED);
    REQUIRE(memcmp(snapshot, directory, sizeof *snapshot) == 0);
    puts("Exhausted revision: edit refused with every byte preserved.");

    /* Inject a damaged count only in this disposable teaching directory. */
    directory->count = SIZE_MAX;
    memcpy(snapshot, directory, sizeof *snapshot);
    REQUIRE(umi_security_identity_directory_find(directory, "lesson.reader") == NULL);
    REQUIRE(umi_security_identity_directory_set_enabled(directory, "lesson.reader", true) == UMI_STATUS_INVALID_ARGUMENT);
    REQUIRE(memcmp(snapshot, directory, sizeof *snapshot) == 0);
    puts("Damaged count: lookup and edit refused before indexing.");
    puts("Governed identity lab passed.");
finish:
    free(snapshot);
    free(directory);
    return result;
}
