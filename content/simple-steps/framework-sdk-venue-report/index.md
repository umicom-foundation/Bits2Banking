<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/index.md

PURPOSE:
Guide readers through a checked C23 application that uses an installed Framework SDK.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a venue shift report with Umicom Framework

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A venue supervisor receives a CSV after each event. The report needs three numbers for the handover and a way to check which source file supplied them. You will build and test a small command-line program for that job.

Use the [first Framework lab](../../lessons/umicom-development/sdk-practical-lab.md) if you have never built an installed SDK client. You will need its C23 compiler, CMake and Ninja setup. All examples use fictional entries. Work in your own practice directory when creating receipts.

1. [Select an installed SDK and build the project](01-select-the-sdk.md).
2. [Read the sample as CSV and predict its totals](02-check-the-input-shape.md).
3. [Admit whole numbers and enforce the venue limits](03-check-whole-numbers.md).
4. [Keep the last accepted result when a row fails](04-preserve-the-last-report.md).
5. [Compare the receipt’s fingerprint with the original file](05-check-the-source-fingerprint.md).
6. [Fit the whole report into a known amount of space](06-render-a-complete-report.md).
7. [Create a new receipt and check that existing work is preserved](07-publish-a-new-receipt.md).
8. [Run the checks and make one controlled change](08-run-and-change-one-check.md).
9. [Check the caller and the display separately](09-reuse-the-report-in-a-client.md).
10. [Find the installed component behind a linker diagnostic](10-find-a-missing-implementation.md).

The application begins from an explicitly selected local file. Its file access, CSV parsing, whole-number conversions and SHA-256 come from the installed Framework. The venue rules and report wording belong to this teaching project. The project prepares a local text receipt and runs without a graphical application, database or web service.

[Learning in Simple Steps](../index.md) · [Full Framework course](../../courses/umicom-development/index.html)
