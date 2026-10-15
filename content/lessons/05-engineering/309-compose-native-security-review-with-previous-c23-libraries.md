# Chapter 309 — Compose native security review from existing C23 libraries

**Bits to Banking · Native C23 engineering · Umicom Foundation**  
**Prerequisite:** Chapter 308 and successful earlier laboratories from Updates 39–43.

## Reuse before adding a new component

A common source of technical debt is implementing the same state machine independently in several applications. Umicom's guiding rule is to put reusable functionality in the Framework and compose it through narrow public contracts. This educational sequence uses the same principle on a smaller scale: Update 44 links the pre-existing library targets and calls their original public functions. It does not copy their implementations into a new source file.

The dependency chain is explicit:

```text
sysadmin-evidence (Update 39)
    -> service-readiness (40)
    -> maintenance-review (41)
    -> deployment-rehearsal (42)
    -> remote-access-review (43)
    -> security-operations-review (44)
```

Each arrow indicates that the next example needs the earlier results. The previous source files, authorship headers, tests and behaviour are retained unchanged. CMake registers the earlier tests so that a later batch cannot accidentally break an older lesson without it being noticed.

## Build targets and memory ownership

Open the new `CMakeLists.txt` and find the `add_subdirectory` for `remote-access-review`. That earlier directory recursively adds the preceding C23 targets. The new library links `btb-remote-access-review-lib` through `target_link_libraries(... PUBLIC ...)`. CMake therefore supplies the correct public include and linking dependencies without manually compiling duplicate `.c` files.

The new `BtbSecurityReview` stores a **value copy** of `BtbRemoteReview`. This avoids a dangling pointer when a caller destroys a stack-local temporary or passes a borrowed view. The caller owns the resulting review and must not share it concurrently without separate synchronisation. No function retains pointers into a `BtbSecurityEvidence` passed by the caller.

## Read the API before following implementation

```c
BtbSecurityReview review;
BtbSecurityPlan plan;
BtbRemoteReview remote;
/* Initialise plan and remote using the documented, separately checked APIs. */
BtbSecurityResult result = BtbSecurityInit(&review, &plan, &remote);
if (result != BTB_SECURITY_OK) {
    /* Report a typed failure; review's previous value was not overwritten. */
}
```

This excerpt intentionally omits example initialisation; use `training_fixture.c` for the complete executable setup. It calls real `BtbMaintenanceInit`, `BtbDeploymentInit`, `BtbRemoteInit`, and related earlier functions. The fixture creates **fictional records only**. It is linked into the demo and tests but is not part of the core review library.

## Identity of a revision and a configuration

The new plan identifies the source revision, a SHA-256 configuration digest, a policy revision, a fictional change ticket and an interval for review. The evidence must match those identities. A changed release should use a **new review**, not silently replace an old immutable observation. The library rejects a mismatched identifier before mutating the destination.

There is an important limitation: comparing two submitted digest strings is not the same as hashing a real file. In production, trusted Framework filesystem/cryptography services and audit controls would have to establish provenance. The educational model records only the asserted comparison.

## Guided source walkthrough

1. Start with `security_operations_review.h` and identify the fixed buffer capacities.
2. Follow `BtbSecurityInit` to the existing `BtbRemoteEvaluate` call; verify it does not bypass the upstream policy.
3. Follow `BtbSecurityAttach` to the immutable-one-attachment rule.
4. Find where `BtbSecurityEvaluate` sets each missing-reason bit without changing the caller's input.
5. Compare `training_fixture.c` with the previous laboratories and locate real reuse rather than reimplementation.

**Question:** Why is CMake target reuse safer than copying previous `.c` files? **Answer:** A single owned implementation avoids diverging fixes, duplicate definitions and inconsistent tests.

**Question:** Can `REVIEWABLE` automatically turn into “rotate credential now”? **Answer:** No; a real privileged action requires independently authenticated observations and governed authorisation from Framework/OS services.

**Next:** Chapter 310 — demonstrate negative, stale and restored-only outcomes.
