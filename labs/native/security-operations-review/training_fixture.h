/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/security-operations-review/training_fixture.h
 * PURPOSE: Fictitious evidence only, for reproducible labs and tests.
 *---------------------------------------------------------------------------*/
#ifndef BTB_SECURITY_TRAINING_FIXTURE_H
#define BTB_SECURITY_TRAINING_FIXTURE_H
#include "security_operations_review.h"

/* Modes: 0 = successful maintenance, 1 = failed change, 2 = restored only. */
int BtbSecurityTrainingRemote(BtbRemoteReview *remote, int mode);
int BtbSecurityTrainingPlan(BtbSecurityPlan *plan);
int BtbSecurityTrainingEvidence(BtbSecurityEvidence *evidence);
int BtbSecurityTrainingReview(BtbSecurityReview *review, int mode);
int BtbSecurityTrainingComplete(BtbSecurityReview *review, int mode);
#endif
