<!--
Umicom Bits2Banking
File: content/lessons/learning-c/25-check-file-digests-independently.md

PURPOSE:
Explain the lesson: Check a result using known answers and another tool.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a result using known answers and another tool

## Why one matching result is not enough

A test compares observed behaviour with an expectation. If the expectation is calculated using the same defective path, both sides can agree incorrectly. This lesson separates independent known answers from tests of how pieces fit together.

## Setup recap

Follow the [checksum lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/README.md) with a C23 compiler, CMake, Ninja and the Framework base SDK. Tests use temporary files and do not need a network account. Keep a disposable text file for command-line comparisons.

## Read the two kinds of check

The test includes fixed SHA-256 answers for an empty input and the three bytes `abc`. These answers are not calculated by the function being checked.

It also creates a pattern of 8,193 bytes. For several lengths around the 4,096-byte chunk boundary, it compares the stream adapter against Framework's one-buffer call. Both use the same hash engine. Agreement checks the adapter's byte selection and chunking, not the independent correctness of all cryptographic arithmetic.

~~~text
known bytes -> fixed published answer       : known-answer check
same bytes  -> one buffer / stream chunks   : adapter comparison
same file   -> Umicom / operating-system tool: external comparison
~~~

## Lab

1. Read the two fixed-answer strings in `test_checksum.c`.
2. Trace why lengths 4095, 4096 and 4097 exercise different final-read cases.
3. Build and run the tests.
4. Run the executable on your disposable file.
5. Use `Get-FileHash -Algorithm SHA256` in PowerShell or `sha256sum` in Bash on the same file.
6. Change one byte, save, and compare again.

Copy the digest itself when comparing. Some tools print the filename too. Uppercase and lowercase hexadecimal letters represent the same values.

## What this does not establish

These checks do not demonstrate crash-safe storage, signature validation or trusted software provenance. They also do not simulate every filesystem read error. A test report should identify which behaviours were exercised and which remain untested.

## Troubleshooting

An unexpected answer can come from line endings, a final newline, a byte-order mark or reading a different path. The visible text `abc` plus a newline is not the three-byte known-answer input. Inspect byte counts before changing the hash implementation.

## Exercise with an answer

If two files have identical visible paragraphs but different digests, is the hash necessarily broken? No. Their encoded bytes may differ. Explain the distinction between what an editor displays and what the file stores, then inspect the files rather than dismissing the mismatch.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/test_checksum.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](24-status-values-and-complete-results.md)

