<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/98-require-the-intended-recovery-cause.md

PURPOSE:
Teach require the intended recovery cause through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Require the intended recovery cause

## A recovery marker is not automatically success

A negative test intentionally supplies bad input and checks a refusal. That does not mean every failure is acceptable. If a test intended to reject a malformed program instead fails during memory setup, reaching recovery has not demonstrated the intended check. The coordinator keeps expected selection separate from ordinary recovery reasons.

## Inspect the required-job evidence

For the dedicated malformed-startup profile, the expected result requires the first job to exhaust two attempts with a load error and the dependent job to remain unattempted. These observations demonstrate more than a generic failure. They link the selected recovery path to the intended cause and dependency policy.

~~~c
expected = umicomSystemServices.records[0].info.attempts == 2U &&
    umicomSystemServices.records[0].info.reason == UMICOM_SERVICE_LOAD_ERROR &&
    umicomSystemServices.records[1].info.attempts == 0U
        ? UMICOM_TRUE : UMICOM_FALSE;
~~~

## Distinguish direct recovery

The forced-recovery profile follows another contract: it selects recovery before memory allocation or job admission. Its precondition checks that the physical owner is uninitialised. If an owner already exists, the test must fail its selection check. A ready-looking recovery console cannot erase that unexpected earlier activity.

## Use mutations that challenge the expectation

The hosted retry profile changes one observation at a time: the attempt count, failure reason or dependent admission count. Each altered result must remain a failure and omit the expected-selection marker. The normal profile also rejects an unexpected required-job failure. These tests make accidental acceptance visible without launching a guest or fabricating successful user instructions.

## Exercise and recovery

A malformed-image test reports two attempts, but the reason is setup error rather than load error. Should the test pass because both are failures? No. Keep the result as a failed expectation and inspect the setup boundary. Do not broaden the accepted marker merely to obtain a green report. The original diagnostic images and real controller regressions remain necessary evidence.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](97-preserve-startup-stream-identity.md) · [Next lesson](99-qualify-normal-boot-at-separate-boundaries.md)
