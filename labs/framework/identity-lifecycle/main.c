/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/identity-lifecycle/main.c
 *
 * PURPOSE:
 *   Follow synthetic identity, reference and session lifecycles through the Framework SDK.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/security/credential.h"
#include "umicom/security/identity.h"
#include "umicom/security/session.h"
#include <stdio.h>
#include <string.h>

#define EXPECT(expression) do { if (!(expression)) { \
    fprintf(stderr, "Contract check failed at line %d\n", __LINE__); \
    result = 1; goto finish; } } while (0)

int main(void)
{
    UmiIdentityRegistry *identities = NULL;
    UmiCredentialRegistry *credentials = NULL;
    UmiSessionRegistry *sessions = NULL;
    UmiIdentityRecord learner = {0}, current = {0};
    UmiCredentialRecord reference = {0}, retrieved = {0}, malformed;
    UmiSessionRecord issued = {0}, observed = {0}, untouched;
    int result = 0;

    /* These are synthetic identifiers. There is no password, account server or
     * authentication provider in this local lifecycle exercise. */
    (void)snprintf(learner.identity_id, sizeof learner.identity_id, "%s", "learning.reader");
    (void)snprintf(learner.display_name, sizeof learner.display_name, "%s", "Learning Reader");
    learner.kind = UMI_IDENTITY_HUMAN;
    learner.enabled = 1;
    learner.revision = 1U;
    (void)snprintf(reference.credential_id, sizeof reference.credential_id, "%s", "learning.reference");
    (void)snprintf(reference.principal_id, sizeof reference.principal_id, "%s", learner.identity_id);
    (void)snprintf(reference.provider_id, sizeof reference.provider_id, "%s", "example.vault");
    (void)snprintf(reference.secret_reference, sizeof reference.secret_reference, "%s", "example://reference-only");
    reference.active = 1;
    reference.expires_at_ns = 1000U;

    EXPECT(umi_identity_registry_create(&identities) == UMI_STATUS_OK);
    EXPECT(umi_credential_registry_create(&credentials) == UMI_STATUS_OK);
    EXPECT(umi_session_registry_create(&sessions) == UMI_STATUS_OK);
    EXPECT(umi_identity_registry_register(identities, &learner) == UMI_STATUS_OK);
    EXPECT(umi_credential_registry_register(credentials, &reference) == UMI_STATUS_OK);
    EXPECT(umi_credential_registry_get(credentials, reference.credential_id, &retrieved) == UMI_STATUS_OK);
    EXPECT(strcmp(retrieved.principal_id, learner.identity_id) == 0);
    EXPECT(retrieved.active && 100U < retrieved.expires_at_ns);

    malformed = reference;
    memset(malformed.secret_reference, 'x', sizeof malformed.secret_reference);
    EXPECT(umi_credential_registry_register(credentials, &malformed) == UMI_STATUS_INVALID_ARGUMENT);
    EXPECT(umi_credential_registry_count(credentials) == 1U);
    puts("Malformed credential reference rejected; registry retained.");

    /* Production calls this only after a trusted authentication result. A
     * registry identity or secret reference is not proof of authentication. */
    EXPECT(umi_session_registry_issue(sessions, learner.identity_id, 100U, 50U, &issued) == UMI_STATUS_OK);
    EXPECT(umi_session_registry_validate(sessions, issued.session_id, 120U, &observed) == UMI_STATUS_OK);
    EXPECT(strcmp(observed.principal_id, learner.identity_id) == 0);
    puts("Synthetic session valid before expiry.");

    EXPECT(umi_identity_registry_set_enabled(identities, learner.identity_id, 0) == UMI_STATUS_OK);
    EXPECT(umi_identity_registry_get(identities, observed.principal_id, &current) == UMI_STATUS_OK);
    EXPECT(!current.enabled);
    /* A valid session cannot override a disabled identity. The demonstration
     * performs no operation on protected data and explicitly revokes the handle. */
    EXPECT(umi_session_registry_revoke(sessions, issued.session_id) == UMI_STATUS_OK);
    memset(&observed, 0x5a, sizeof observed);
    memcpy(&untouched, &observed, sizeof untouched);
    EXPECT(umi_session_registry_validate(sessions, issued.session_id, 121U, &observed) == UMI_STATUS_PERMISSION_DENIED);
    EXPECT(memcmp(&observed, &untouched, sizeof observed) == 0);
    puts("Disabled identity denied; revoked handle refused.");

    EXPECT(umi_identity_registry_set_enabled(identities, learner.identity_id, 1) == UMI_STATUS_OK);
    EXPECT(umi_session_registry_issue(sessions, learner.identity_id, 200U, 50U, &issued) == UMI_STATUS_OK);
    EXPECT(umi_session_registry_validate(sessions, issued.session_id, 249U, &observed) == UMI_STATUS_OK);
    memcpy(&untouched, &observed, sizeof untouched);
    EXPECT(umi_session_registry_validate(sessions, issued.session_id, 250U, &observed) == UMI_STATUS_PERMISSION_DENIED);
    EXPECT(memcmp(&observed, &untouched, sizeof observed) == 0);
    EXPECT(umi_session_registry_cleanup(sessions, 250U) == 2U);
    EXPECT(umi_session_registry_count(sessions) == 0U);
    puts("Expiry boundary refused; inactive sessions removed.");
    puts("Local lifecycle exercise complete; no login service was contacted.");
finish:
    umi_session_registry_destroy(sessions);
    umi_credential_registry_destroy(credentials);
    umi_identity_registry_destroy(identities);
    return result;
}
