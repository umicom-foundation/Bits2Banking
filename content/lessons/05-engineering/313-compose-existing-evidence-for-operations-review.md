# Chapter 313 — Compose existing C23 evidence for operational resilience

**Bits to Banking · Native Engineering · ISO C23**  
**Source:** `labs/native/operational-resilience`  
**Prerequisites:** Updates 39–44 educational libraries and Chapter 312.

## Build on the previous design, not beside it

Update 39 introduced a bounded observation model. Update 40 built service-readiness evaluation from it. Update 41 added maintenance-review state, Update 42 deployment evidence, Update 43 remote-access review and Update 44 security-operations review. Each later laboratory imports the earlier CMake targets. Update 45 follows the same rule. The new `BtbOpsReview` **contains a copied `BtbSecurityReview`** and delegates upstream qualification to `BtbSecurityEvaluate`. No code from the previous implementations is removed or replaced.

The new layer asks whether operational observations make a planned review **explainable**: was a heartbeat recent, a practice backup verified, an independent restore drill recorded, a response owner named, a queued-work threshold exceeded and a logical recovery objective missed?

```c
/* A short excerpt: inspect the complete header before implementing a caller. */
typedef struct BtbOpsReview {
    BtbOpsPolicy policy;
    BtbSecurityReview security;
    BtbOpsEvidence evidence;
    int hasEvidence;
} BtbOpsReview;
```

Notice the ownership decision: the struct stores **copies**. It does not borrow pointers to a temporary `BtbSecurityReview` or temporary evidence. The caller owns the complete `BtbOpsReview`. Each call is synchronous and single-owner. The example does not claim thread safety.

## Trace the three public operations

**Initialise:** `BtbOpsInit` validates the review plan and the existing security review, and requires their `serviceId` and full source revision to match. Invalid input cannot alter the destination. Use a new review when the planned release changes.

**Attach:** `BtbOpsAttach` accepts one bounded fictional observation. It validates boolean fields, timestamp order and exact source identity before copying. A second attempt is rejected rather than silently overwriting the first observation. This makes evidence provenance obvious in a debugger.

**Evaluate:** `BtbOpsEvaluate` calls the existing `BtbSecurityEvaluate`, then evaluates local operational conditions. It returns a status and an independent missing-evidence bitmask. The output is copied only after all validation succeeds. If the upstream review reports `RESTORED_ONLY`, the new review also reports `RESTORED_ONLY`. A successful rollback of the *old* application cannot rewrite a failed *new* deployment as a success.

## Error handling example

```c
BtbOpsReview review;
BtbOpsDecision decision;

/* The fixture builds fictional evidence through already delivered C23 APIs. */
if (!BtbOpsTrainingReview(&review, 0, 1)) {
    /* Record that the teaching fixture could not be constructed. */
    return 1;
}
if (BtbOpsEvaluate(&review, &decision) != BTB_OPS_OK) {
    /* Do not read a result from an unsuccessful call. */
    return 1;
}
if (decision.status != BTB_OPS_REVIEWABLE) {
    /* Inspect missingEvidence; do not bypass the missing gate. */
    return 1;
}
```

The snippet is from a demonstration program, not a privileged service. `REVIEWABLE` means the supplied **fictional** records satisfied the classroom rules; it never grants operational authority.

## Observe composition in CMake

The new project imports `../security-operations-review/CMakeLists.txt`, which imports the earlier chain. Its new static library links to `btb-security-operations-lib`, and its fixture links to the existing `btb-security-fixture`. This prevents accidental duplication of previous source files. Do not flatten the six labs into one large implementation or regenerate the earlier source from short examples.

## Guided exercise

Run the `ready`, `pending`, `upstream-blocked` and `upstream-restored` tests. In a debugger inspect `review.security`, `review.policy.sourceRevision`, `review.evidence.observedSourceRevision` and `decision.missingEvidence`. Explain why copying source revision text is not sufficient for real Git provenance: production must obtain it through the Framework VCS authority and bind the actual build/test evidence to the same revision.

**Next:** [Chapter 314 — Negative tests and safe operational decisions](314-negative-tests-for-operational-resilience.md).
