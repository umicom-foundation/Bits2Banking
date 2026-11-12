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

## Read and compare boot evidence

- [Read a captured boot observation](19-read-a-captured-boot-observation.md)
- [Follow the boot-report parser](20-follow-the-boot-report-parser.md)
- [Validate caller-owned report fields](21-validate-caller-owned-report-fields.md)
- [Compare fields with a change mask](22-compare-fields-with-a-change-mask.md)
- [Preserve the last accepted comparison](23-preserve-the-last-accepted-comparison.md)
- [Run the OS report-comparison command](24-run-the-os-report-comparison-command.md)
- [Interpret source and service-count changes](25-interpret-source-and-service-count-changes.md)
- [Design repeatable boot-evidence checks](26-design-repeatable-boot-evidence-checks.md)

## Native runtime tools and boot integration

27. [Separate the host, target and image](27-separate-host-target-and-image.md)
28. [Run a fixed runtime trace probe](28-run-a-fixed-runtime-trace-probe.md)
29. [Reuse the Framework preview command](29-reuse-the-framework-preview-command.md)
30. [Distinguish installation from boot integration](30-distinguish-installation-from-boot-integration.md)

## Inspect source-build plans before execution

Eight connected exercises cover cross-toolchain identities, portable file claims, dependency graphs, owner lifetime, native inspection and the evidence needed before reproducible execution.

- [Describe a source build before running it](31-describe-a-source-build-before-running-it.md)
- [Distinguish build, host and target identities](32-distinguish-build-host-and-target-identities.md)
- [Admit portable source and output paths](33-admit-portable-source-and-output-paths.md)
- [Resolve stage dependencies through Framework](34-resolve-stage-dependencies-through-framework.md)
- [Own recipes and projected tasks separately](35-own-recipes-and-projected-tasks-separately.md)
- [Use native recipe inspection and exit status](36-use-native-recipe-inspection-and-exit-status.md)
- [Distinguish digest claims from provenance](37-distinguish-digest-claims-from-provenance.md)
- [Plan reproducible build and resume evidence](38-plan-reproducible-build-and-resume-evidence.md)

## Build a reviewed media-copy application

Use real Framework APIs for file-only inspection, review, transfer and verification, then plan the remaining distribution evidence.

- [Inspect an image without booting it](39-inspect-an-image-without-booting-it.md)
- [Own a reviewed media plan](40-own-a-reviewed-media-plan.md)
- [Refuse a changed media review](41-refuse-a-changed-media-review.md)
- [Copy and verify regular-file media](42-copy-and-verify-regular-file-media.md)
- [Prepare an ISO through native services](43-prepare-an-iso-through-native-services.md)
- [Plan boot and distribution evidence](44-plan-boot-and-distribution-evidence.md)

## Inspect optical records through Framework

- [Share a read-only image inspector](45-share-a-read-only-image-inspector.md)
- [Decode optical records and byte order](46-decode-optical-records-and-byte-order.md)
- [Interpret UEFI boot catalogue counts](47-interpret-uefi-boot-catalogue-counts.md)
- [Qualify produced images in stages](48-qualify-produced-images-in-stages.md)


## Laboratory: preserve device selection and Unicode labels

Follow explicit inventory bindings in the existing Windows interface and qualify presentation without opening devices.

1. [Bind device rows to inventory identity](49-bind-device-rows-to-inventory-identity.md)
1. [Format device labels without splitting UTF-8](50-format-device-labels-without-splitting-utf8.md)

## Inspect partition tables through an installed Framework client

Own a byte source, understand geometry and preserve observations through a failed inspection. The lab uses actual installed Framework APIs and no devices.

- [Connect an owned image read port](51-connect-an-owned-image-read-port.md)
- [Keep partition address units explicit](52-keep-partition-address-units-explicit.md)
- [Reserve table space before partitions](53-reserve-table-space-before-partitions.md)
- [Preserve an observation on refusal](54-preserve-an-observation-on-refusal.md)
- [Distinguish checksums from trust](55-distinguish-checksums-from-trust.md)
- [Qualify an installed image client](56-qualify-an-installed-image-client.md)

[Build the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Record qualification](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

## Own media effects, cancellation and recovery

Use the existing installed C23 media client to distinguish creation, payload writes, checked release and later verification.

- [Read file effects separately from status](57-read-file-effects-separately-from-status.md)
- [Own a synchronous progress context](58-own-a-synchronous-progress-context.md)
- [Cancel before the first payload write](59-cancel-before-the-first-payload-write.md)
- [Interpret cancellation after payload writing](60-interpret-cancellation-after-payload-writing.md)
- [Check native release without retrying handles](61-check-native-release-without-retrying-handles.md)
- [Retain failed media artifacts for recovery](62-retain-failed-media-artifacts-for-recovery.md)
- [Qualify installed media recovery behaviour](63-qualify-installed-media-recovery-behaviour.md)
