/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/studio-build-evidence/evidence.c
 *
 * PURPOSE:
 *   Validate digest spelling before comparing saved and observed identities.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "evidence.h"
#include <stddef.h>
#include <string.h>

enum { SHA256_TEXT_DIGITS = 64 };

static int DigestText(const char *text)
{
    if (text == NULL)
        return 0;

    /* A NUL in the first 64 positions is refused before any later byte is read. */
    for (size_t index = 0U; index < SHA256_TEXT_DIGITS; ++index) {
        const char digit = text[index];
        if ((digit < '0' || digit > '9') && (digit < 'a' || digit > 'f'))
            return 0;
    }
    return text[SHA256_TEXT_DIGITS] == '\0';
}

enum UmicomLabEvidence UmicomLabCompareEvidence(const char *expected, const char *observed)
{
    if (!DigestText(expected) || !DigestText(observed))
        return UMICOM_LAB_EVIDENCE_INVALID;

    /* Keep a malformed record distinct from a valid record for other bytes. */
    return memcmp(expected, observed, SHA256_TEXT_DIGITS) == 0
        ? UMICOM_LAB_EVIDENCE_MATCH : UMICOM_LAB_EVIDENCE_CHANGED;
}
