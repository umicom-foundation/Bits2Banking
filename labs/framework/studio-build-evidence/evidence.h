/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/framework/studio-build-evidence/evidence.h
 *
 * PURPOSE:
 *   Give a C23 client exact statuses for comparing two recorded digests.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_LAB_BUILD_EVIDENCE_H
#define UMICOM_LAB_BUILD_EVIDENCE_H

enum UmicomLabEvidence {
    UMICOM_LAB_EVIDENCE_MATCH = 0,
    UMICOM_LAB_EVIDENCE_CHANGED = 2,
    UMICOM_LAB_EVIDENCE_INVALID = 3
};

/* Inputs are NUL-terminated SHA-256 text in lowercase hexadecimal. Matching
 * text establishes agreement with the supplied record. Trust in the record
 * and the process that computed each digest is decided separately. */
enum UmicomLabEvidence UmicomLabCompareEvidence(const char *expected, const char *observed);

#endif
