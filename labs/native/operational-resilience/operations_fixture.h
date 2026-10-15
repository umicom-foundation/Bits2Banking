/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/operational-resilience/operations_fixture.h
 * PURPOSE: Deterministic, fictional operations evidence for unit tests.
 *---------------------------------------------------------------------------*/
#ifndef BTB_OPS_FIXTURE_H
#define BTB_OPS_FIXTURE_H
#include "operations_review.h"

/* Upstream mode: 0=reviewable, 1=failed change, 2=restored old generation. */
int BtbOpsTrainingPolicy(BtbOpsPolicy *policy);
int BtbOpsTrainingEvidence(BtbOpsEvidence *evidence);
int BtbOpsTrainingReview(BtbOpsReview *review, int upstreamMode, int attachEvidence);
#endif
