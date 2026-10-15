# Chapter 305 — Compose prior C23 deployment evidence into remote review

**Bits to Banking · Engineering track · C23 · Umicom Foundation**  
**Laboratory:** `labs/native/remote-access-review/`  
**Previous source:** `labs/native/deployment-rehearsal/deployment_review.h` and earlier evidence laboratories.

## The design objective

A robust modular system avoids representing the same business state in multiple incompatible structures. Update 39 introduced observation evidence; Update 40 composed service readiness; Update 41 added maintenance review; Update 42 examined staged deployment. This chapter adds an **additional layer**—remote access preflight—without rewriting any of those definitions.

The code links `btb-deployment-review-lib`, which in turn links its earlier dependencies. That gives new code access to the actual existing public contracts, not a second reimplementation hidden inside the newest batch.

![Evidence lineage from deployment to access decision](../../assets/diagrams/sysadmin-remote-support-evidence-update43.svg)

## Source walk-through

`BtbRemoteReview` contains a copied `BtbDeploymentReview` and two bounded records: a plan and an optional evidence observation. This allows the reviewer to answer a simple question: *Is the declared access review bound to the exact source revision of the deployment being discussed?*

A plan is valid only when its service, host, requester, independent reviewer and source revision have valid bounded representations. It also needs a nonzero change ticket and an ordered start/end window. The requester and reviewer labels must differ. A label is only a teaching placeholder; it does **not** prove either person's real-world authority.

`BtbRemoteInit` calls:

```c
BtbDeploymentDecision deploymentDecision;
if (BtbDeploymentEvaluate(deployment, &deploymentDecision) != BTB_DEPLOYMENT_OK) {
    /* Refuse malformed upstream evidence. */
}
```

It then checks the source revision against the deployment snapshot. **Only after every check succeeds** does it copy a fully prepared `BtbRemoteReview` into caller storage. If a mismatch is found, the destination remains byte-for-byte unchanged.

The `Attach` function repeats structural validation, rejects a second evidence attachment and checks that the observed revision matches the immutable plan. It does not fetch host keys or authenticate anyone. The model intentionally uses a single-owner thread policy and never retains borrowed pointers.

## Bounded fields and explicit trust

The plan supports 64-byte service/operator labels, a 96-byte host label and a 40- or 64-hex-digit source revision. Those sizes are teaching limits, not a claim about the maximum real DNS name or Git revision presentation. In particular, no host label should be treated as a validated network endpoint simply because it fits into a buffer.

Externally supplied evidence is represented by booleans such as `hostIdentityIndependentlyChecked`, `leastPrivilegeReviewed` and `credentialsExcludedFromLogs`. Each boolean is **claimed** evidence; the lab has no proof mechanism. It rejects invalid values such as 3 instead of silently treating any nonzero byte as true.

A separate capture ID orders the fictional observation after the deployment's verification capture. A time window is also checked against a **claimed observation timestamp**, without reading the system clock. An actual production design would require authenticated time, binding to a session and trustworthy evidence provenance.

## Practice using named tests

From the configured course build, run:

```powershell
ctest --test-dir ".\output\learning-build\remote-access-review" -R "bits2banking\.remote-review\.(mismatched-plan|revision|repeat|bad-flag)$" --no-tests=error --output-on-failure
```

Each test checks a different invariant: immutable revision identity, refusal of conflicting evidence, denial of repeated attachment and rejection of malformed flag data. A passing test does not make a real host reachable.

## Questions and answers

1. What does “failure atomic” mean? Invalid input leaves the previously accepted record unchanged.
2. Why reject repeated evidence attachment? It prevents silent replacement of the observation on which a decision was based.
3. Why does the batch avoid platform key-management code? That belongs in a reviewed Framework adapter, not an isolated educational policy model.

**Next:** Chapter 306 — negative cases, stale captures and rollback boundaries.
