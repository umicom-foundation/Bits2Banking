# Umicom OS from Scratch

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## System layers and service plans

Read a real OS component, then reason about dependency order and rejected plans.

1. [A system has several layers](01-system-boundaries.md)
1. [Build one real OS component](02-build-the-parser.md)
1. [Plan startup before executing it](03-service-dependencies.md)
1. [Keep rejected state separate from recovery](04-failure-and-recovery.md)

## Boot identity and ownership

Identify what was booted, review qualification evidence and track ownership beyond a process identifier.

1. [Know which bytes you booted](05-image-and-firmware-identity.md)
1. [Separate a check from a release claim](06-read-qualification-evidence.md)
1. [Make recovery decisions testable](07-boot-admission.md)
1. [Verify the guest environment](08-guest-environment.md)
1. [Keep service process and stream ownership](09-service-process-ownership.md)
1. [Understand why a process ID is not ownership](10-understand-why-a-process-id-is-not-ownership.md)

## Project: service recovery

Keep accepted results through faults and retries, then stop only after active work is resolved.

1. [Separate accepted and in-flight work](11-separate-accepted-and-in-flight-work.md)
1. [Reject overlapping service work](12-reject-overlapping-service-work.md)
1. [Publish after completion checks](13-publish-after-completion-checks.md)
1. [Fault without replacing the last result](14-fault-without-replacing-the-last-result.md)
1. [Recover before retrying a revision](15-recover-before-retrying-a-revision.md)
1. [Keep revisions moving forward](16-keep-revisions-moving-forward.md)
1. [Stop after active work is resolved](17-stop-after-active-work-is-resolved.md)
1. [Design a service-recovery checklist](18-design-a-service-recovery-checklist.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Umicom OS from Scratch

Follow the reading order below. Each lesson gives its own setup recap and links to supporting material. Later lessons use the ideas introduced earlier; return to the named prerequisite when a term is unfamiliar.

## Reading order

1. [A system has several layers](01-system-boundaries.md)
2. [Build one real OS component](02-build-the-parser.md)
3. [Plan startup before executing it](03-service-dependencies.md)
4. [Keep rejected state separate from recovery](04-failure-and-recovery.md)
5. [Know which bytes you booted](05-image-and-firmware-identity.md)
6. [Separate a check from a release claim](06-read-qualification-evidence.md)
7. [Make recovery decisions testable](07-boot-admission.md)
8. [Verify the guest environment](08-guest-environment.md)
9. [Keep service process and stream ownership](09-service-process-ownership.md)
10. [Understand why a process ID is not ownership](10-understand-why-a-process-id-is-not-ownership.md)

[Open the illustrated course](../../../courses/umicom-os-from-scratch/index.html).

- [Separate accepted and in-flight work](11-separate-accepted-and-in-flight-work.md)

- [Reject overlapping service work](12-reject-overlapping-service-work.md)

- [Publish after completion checks](13-publish-after-completion-checks.md)

- [Fault without replacing the last result](14-fault-without-replacing-the-last-result.md)

- [Recover before retrying a revision](15-recover-before-retrying-a-revision.md)

- [Keep revisions moving forward](16-keep-revisions-moving-forward.md)

- [Stop after active work is resolved](17-stop-after-active-work-is-resolved.md)

- [Design a service-recovery checklist](18-design-a-service-recovery-checklist.md)

</details>
