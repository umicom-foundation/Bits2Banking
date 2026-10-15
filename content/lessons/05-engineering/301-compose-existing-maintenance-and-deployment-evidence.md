# Chapter 301 — Compose maintenance state with explicit deployment evidence

**Bits to Banking · Native engineering · Umicom Foundation**  
**Prerequisites:** Chapters 297–300; C structures, enums, pointers and fixed-width integers.  
**Laboratory:** `labs/native/deployment-rehearsal`

## Why this matters

A deployed executable has a source revision, package identity, configuration, runtime dependencies, installation location and post-change outcome. Mixing these responsibilities inside an oversized controller makes it difficult to identify which observation was missing or who owned a failed operation.

Updates 39–41 already introduced the responsible educational owners:

- `BtbAdminReview` records **fictional administration observations**.
- `BtbServiceGraph` evaluates service dependency readiness.
- `BtbMaintenanceReview` models approval, start, after-change verification and restoration.
- Update 42's `BtbDeploymentReview` records the additional **staging and package evidence only**.

A real application must use Umicom Framework's existing build, VCS, installer, status, observability and repository interfaces. This lab is a **teaching composition**, not another production deployment subsystem.

![Private stage to reviewed outcome](../../assets/diagrams/sysadmin-rollback-gates-update42.svg)

## Step 1 — inspect the C23 contract

Open `deployment_review.h`. The caller owns three main data types: `BtbDeploymentPlan`, `BtbDeploymentEvidence` and `BtbDeploymentReview`. Every string has an explicit capacity, and the review stores a **copy** of the maintenance state and the stage evidence. It retains no caller pointer. This matters because a GUI panel or CLI command may discard its temporary buffers after returning.

```c
BtbDeploymentReview review;
BtbDeploymentPlan plan = {0};
BtbMaintenanceReview maintenance = {0};

/* The learner must initialise `plan` and `maintenance` with valid, fictional
 * training values before calling this operation. No host state is queried. */
BtbDeploymentResult result = BtbDeploymentInit(&review, &plan, &maintenance);
```

Do not copy this fragment into a standalone executable and expect it to succeed. The required fields are intentionally omitted to focus attention on the contract. The complete, compiling examples are in `main.c` and `test_deployment.c`.

A plan carries a release ID, source revision (40 or 64 hexadecimal characters), claimed 64-digit SHA-256 package digest, claimed configuration digest and a private **label** beginning with `practice-`. This label is not used as a real filesystem path. Rejecting a value like `C:/production` prevents it from being mistaken for an approved learning destination; the actual CMake staging path remains separately selected and reviewed by the user.

## Step 2 — distinguish claims from verification

The C23 module checks **syntax and consistency**: digest text lengths, hex characters, matching source revisions and matching claimed package hashes. It **does not compute any hash from a file**. The flags `packageHashCompared`, `configurationReviewed`, `runtimeDependenciesChecked`, `privateStageInspected` and `entryPointProbed` are fictional input evidence.

This distinction matters. A checkbox cannot substitute for a cryptographic verification routine, and a source revision string is not proof that the installed binary was built from that revision. A production implementation requires independently obtained evidence, signed-package policy and a verified installer. Those facilities belong to Umicom Framework.

## Step 3 — attach evidence without losing prior state

`BtbDeploymentAttachStage` first validates the entire proposed record. If it is invalid, a different revision, or an old replay of stage evidence, the operation refuses the update. The existing review is retained byte-for-byte. This is called **failure atomicity**. It prevents an aborted operation from half-updating the release history.

The evidence also has two monotonic *capture identifiers*: one for staging and one for its later verification. The simple ordering constraint is that a post-change verification must be newer than both staging and the service observations it claims to support. If the ordering is stale, the review remains **BLOCKED**, even when every boolean flag says “complete”.

## Step 4 — preserve maintenance ownership

`BtbDeploymentUpdateMaintenance` accepts a newer snapshot from the existing maintenance model. It refuses a different change ID, initial baseline, operator or source revision. It also refuses a state regression. Deployment logic does not invent a service-ready decision: it consumes one made by the existing service/readiness owners.

Consider a fictional Notes release with a healthy baseline. Its replacement fails to access document storage. The maintenance module enters `BTB_MAINTENANCE_ROLLBACK_REQUIRED`. A later independent restore check may move to `BTB_MAINTENANCE_RESTORED`. The deployment result must then be `RESTORED_ONLY`, never `QUALIFIED`. Recovery is useful, but it does not retroactively turn the failed new release into a success.

## Build and inspect

Run the full instructions in `labs/native/deployment-rehearsal/README.md`, then inspect:

```powershell
ctest --test-dir ".\output\learning-build\deployment-rehearsal" `
  -R "bits2banking.deployment-review" `
  --no-tests=error --output-on-failure
```

**Expected:** only the Update 42 deployment-review tests execute; the full suite additionally includes inherited Update 39–41 tests. Run a complete suite before declaring integration acceptance.

## Assessment

1. Why does the review copy a `BtbMaintenanceReview` rather than borrow its pointer? — To preserve ownership and lifetime independently from the caller's temporary state.
2. Why is a SHA-256-looking string not enough? — String validation proves format, not file content or authenticity.
3. Why is RESTORED_ONLY distinct from QUALIFIED? — Because the old service was recovered after a failed change; the new release did not succeed.
4. How does this relate to Umicom Framework? — The production deployment pipeline should consume Framework-owned VCS, build, security, service, package and audit contracts; this lab introduces none of those competing runtimes.

**Next:** Chapter 302, test stale, mismatched and failed stage observations.
