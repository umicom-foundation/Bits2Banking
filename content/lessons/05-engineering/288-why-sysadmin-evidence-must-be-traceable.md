# Chapter 288 — Why administration observations need ownership and revision identity

**Bits to Banking · Advanced Engineering · Umicom Foundation**  
**Implementation language:** C23.  
**Prerequisite:** System Administration Chapters 1–36 and Engineering Chapter 287.

## Why this matters

A report that says “all checks passed” is meaningless unless we know **which** checks, on **which** system, at **which** point in time. This chapter connects the practical administration course to the engineering idea of evidence provenance.

## The operational question

An engineer sees a green build status from Monday and a new Framework commit from Tuesday. The two pieces of evidence do not establish that Tuesday’s source compiles. The same problem occurs with services: a healthy service status captured before a configuration change is not proof that the new configuration works. Every observation needs a subject and a capture identity.

In the classroom `sysadmin-evidence` model, an observation records `checkId`, `captureId`, `state` and a short `label`. The check ID names one step in an agreed runbook. The capture ID binds that step to the specific training session being reviewed. Without those fields, a report could accidentally mix a test run from another machine or an earlier configuration.

## Data ownership and safe calls

Open `labs/native/sysadmin-evidence/admin_evidence.h`. The caller owns a `BtbAdminReview` and passes pointers to short-lived observations. `BtbAdminReviewAdd` copies each record into fixed-capacity storage rather than retaining borrowed pointers. This makes the result independent of a temporary input buffer. Invalid observations do not modify the existing review.

```c
BtbAdminReview review;
BtbAdminObservation item = {
    1U, 100U, BTB_ADMIN_PASS, "Training workspace readable"
};
if (BtbAdminReviewInit(&review, 100U) != BTB_ADMIN_OK) {
    /* Report invalid training capture ID. */
}
if (BtbAdminReviewAdd(&review, &item) != BTB_ADMIN_OK) {
    /* The previous evidence remains available. */
}
```

The sample identifier `100` is **not** a real security identity, Git SHA or timestamp. A production system must record authoritative versions using its own Framework contracts.

## Why this belongs in Umicom Framework in real products

Umicom Framework already exposes working-tree observations through `UmiVcsWorkingTreeRead`, build planning through `umi_build_automation_evaluate`, and compiler diagnostics through the shared parser. The educational structure is deliberately isolated and does not replace those services. In Studio, an administrator would consume Framework evidence rather than parsing ad-hoc shell output in a GTK callback.

## Practical questions

1. Why is the same service named “Running” in two different capture sessions not automatically one continuous observation?
2. What happens if `BtbAdminReviewAdd` is called twice with the same check ID?
3. Why must the runbook define a meaning for every check ID before evidence is collected?

**Answers:** A service can change state between sessions. Duplicate IDs are refused rather than silently replaced. Stable meanings prevent misleading comparisons.


## The Umicom Framework ownership rule

This chapter teaches a reproducible concept and, where applicable, uses a stand-alone learning-only model. Production tools must reuse Framework-owned VCS, build, diagnostics, process, security, storage and observability contracts before any new shared functionality is proposed. No PowerShell or Python implementation files are introduced.

## Safe completion criterion

Write one short paragraph distinguishing **observed facts**, **policy decisions** and **not-yet-verified outcomes**. Preserve the previous source and comments. If you cannot reproduce a result on your operating system, state the limitation rather than guessing.
