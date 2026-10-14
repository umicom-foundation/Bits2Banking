# Chapter 296 — Observations, approval and change boundaries

**Bits to Banking · Engineering track · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** ISO C23  
**Prerequisites:** System Administration Chapters 45, 46, 48–50; Engineering Chapters 288–295.

## The engineering problem

A Windows service reports `Running`, a Linux unit reports `active`, and a CTest run reports `Passed`. These are three different kinds of evidence. They may refer to different times and different revisions. A maintenance engineer must not take the first green result as a substitute for the other two. Imagine that a Notes service was ready at 09:00, a new package was installed at 09:15, and the only test report was generated the previous evening. That test report cannot establish that the new package is safe to release.

The first task in this chapter is **classification**. An *observation* records a fact produced by a known command or service. A *decision* interprets one or more observations against a documented requirement. An *action* changes the computer or the repository. An approval authorises an action under the organisation's policy; it is not a Boolean value that automatically grants an operating-system privilege. The educational review layer never runs a command on the host.

![A controlled change separates baseline, approval, verification and recovery](../../assets/diagrams/sysadmin-maintenance-lifecycle-update41.svg)

## Read the existing contracts before writing new ones

Earlier Bits2Banking laboratories already provide the core evidence mechanisms:

| Source | Owned responsibility | Key contract |
|---|---|---|
| `labs/native/sysadmin-evidence/admin_evidence.h` | Copied observations with check ID, capture ID and PASS/WARNING/FAILURE/NOT_RUN | `BtbAdminReviewEvaluate` |
| `labs/native/service-readiness/service_readiness.h` | Propagate readiness through declared dependencies | `BtbServiceGraphEvaluate` |
| `labs/native/maintenance-review/maintenance_review.h` | Apply the change-window teaching policy to already evaluated evidence | `BtbMaintenanceObserveAfter` |

The third contract is new to this batch. It does not replace the other two and does not read raw Windows Event Log messages. `BtbServiceSummary` is already an owned result: we copy that value into the maintenance review record rather than retaining a pointer to a temporary graph.

## Design a fictional Notes change

Suppose the change identifier is `UmiNotesMaintenance`. The proposed source revision is the literal 40-digit hexadecimal training value `0123456789abcdef0123456789abcdef01234567`. The *operator label* is `OperatorA`, and the *reviewer label* is `ReviewerB`. The labels teach segregation of duties but do not perform authentication. In a production system, real identity and permissions belong to Framework security services and a separately enforced approval workflow.

Before a change can begin, the model requires a baseline with every registered service READY, an explicit indication that a recoverable backup was verified, a documented rollback plan and a distinct reviewer. If any input is missing, the transition is rejected. A rejected request does not partially change the caller-owned record.

```c
/* These values were already prepared using BtbServiceGraphEvaluate. */
BtbServiceSummary before;
BtbMaintenanceReview review;
const char *revision = "0123456789abcdef0123456789abcdef01234567";

/* Check the result after the caller constructs a valid 'before' summary. */
BtbMaintenanceResult result = BtbMaintenanceInit(
    &review, "UmiNotesMaintenance", revision, "OperatorA", &before);
if (result != BTB_MAINTENANCE_OK) {
    /* Stop: the baseline or source identity cannot be trusted. */
}
```

This excerpt cannot be compiled alone because `before` needs an actual value from the earlier library. That is deliberate: a lesson about composition must not pretend that an uninitialised output is valid. Open the complete executable `main.c` in the new laboratory for a buildable example.

## The difference between documentation and proof

A `backupVerified` flag in this teaching model means that the **caller claims** the backup requirement was checked. It is not a cryptographically verified backup or an operating-system restore. A real system needs a trusted evidence producer, signed/restricted policy where appropriate, an audit trail and an authorised operator. We model the *logic* of a gate rather than its administrative authority.

Create a one-page imaginary change record containing its scope, source revision, owner, reviewer, baseline capture ID, planned verification and rollback path. Do not include real usernames, credentials, IP addresses or finance customer data.

## Failure scenario

At the end of the maintenance window the Notes application's process still exists, but the storage dependency fails. The older readiness library correctly blocks the dependent Notes service. The maintenance-review layer must distinguish this from a successfully completed upgrade. It records `ROLLBACK_REQUIRED`; only a separately verified restoration capture may move it to `RESTORED`.

## Laboratory questions

1. Which part of the design *observes*, which part *decides*, and which part would perform a real action?
2. Why must the baseline capture identify one inspection session?
3. Would a source commit ID alone establish that a binary was built from that commit?
4. What security checks would be needed before accepting `ReviewerB` as an actual approving person?

**Suggested answers:** (1) Earlier evidence modules observe supplied data and derive readiness; the new module decides an offline transition; real action is deliberately absent. (2) It prevents mixing old and current checks. (3) No; build provenance and artefact identity are additional evidence. (4) Authenticated identity, permissions, maker/checker policy and auditable approval.

**Next:** [297 — Compose the existing C23 libraries](297-compose-existing-c23-evidence-into-maintenance-review.md).
