<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/132-read-the-scope-of-a-kernel-build-identity.md

PURPOSE:
Read the scope of a Kernel build identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read the scope of a Kernel build identity

An Umicom Kernel build identity is a saved record of source files and built ELF files, a format the Kernel uses for executable code. A checksum helps identify the bytes in a file. Two fields in the record tell you which additional claims the record makes. In this lesson you will read four lines of JSON and practise deciding what evidence to look for next. You only need this page or a piece of paper.

If you are new to build records, start with the short example in Learning Build Systems. The earlier Kernel lesson follows the records for a host tool and a separate guest.

## 1. Read the two scope fields

Here is a shortened example in JSON, a text format for named values. The complete record also needs source and ELF checksums and file lists.

```json
{
  "schema": "umicom.kernel.build-identity",
  "version": 1,
  "sourceStableDuringBuildVerified": false,
  "runtimePassed": false
}
```

`sourceStableDuringBuildVerified` set to `false` means this record makes no claim that someone observed the source staying unchanged throughout compilation. Capturing a snapshot checks the source at the time it is read. Answering a question about the whole build interval requires evidence that covers that interval.

`runtimePassed` set to `false` means this record makes no claim that a runtime test passed. A separate test log can still show a pass or a failure for a matching executable and test environment.

Both values must be JSON Booleans. A Boolean is a value with two possibilities, `true` and `false`. Writing `"false"` creates text, which has a different type. A missing field leaves the required value unstated.

## 2. Follow the verification order

The Kernel build-identity verifier first checks that the saved record has the expected schema and version and that the file identities agree. It then checks that both scope fields are present Booleans with the value `false`. Each step answers a different question. Matching file identities cannot supply a scope claim, and correctly written scope flags cannot make changed files match.

Start from an imagined complete record in which all file identities agree and both scope fields are `false`. Make one change at a time in your notes. Use the right column to check which rule you applied.

| Change to the example | Expected verification decision |
| --- | --- |
| Leave both fields as Boolean `false` | The scope check can pass. |
| Set `runtimePassed` to Boolean `true` | Refuse the runtime claim because it exceeds the scope of this record. |
| Set `sourceStableDuringBuildVerified` to Boolean `true` | Refuse the build-stability claim because it exceeds the scope of this record. |
| Write `"false"` for `runtimePassed` | Refuse that field because it is text. |
| Omit `sourceStableDuringBuildVerified` | Refuse the record because the field is missing. |
| Keep both values `false` and change the ELF checksum | Refuse the mismatched file identity before checking the scope fields. |

## 3. Match evidence to the next question

If you need to know whether a test passed, look for a separate test result that identifies the executable by checksum, the target and the test outcome. The target might be a host process or a guest running under a virtual machine. Keep the test result alongside the build identity so that readers can check the connection.

If the question is whether files stayed unchanged during compilation, look for a separate record of what was monitored and when. Equal checksums from before and after the build establish what matched at those two times. A claim about the full interval needs a method that covers the interval.

If a verifier refuses a saved record, keep the original. Compare its schema, version and intended source and ELF files. For a missing or mistyped scope field, ask for the original capture or follow the Kernel guide to capture a new identity for the reviewed files. Keep new captures with their own build outputs. Hand-editing a flag would lose the connection to what the capture actually recorded. These practice decisions describe saved data only and do not involve launching Umicom Kernel or a guest.

## Where to find the implementation

In the Umicom Kernel checkout, `docs/BUILD_IDENTITY.md` explains when to capture or verify a saved record. `cmake/QualificationEvidence.cmake` implements these checks. `tests/qualification/check_evidence.cmake` includes cases for a true flag, a wrong value type and a missing value.

[Course contents](index.md) · [Previous lesson · Check the front message header](131-check-the-front-message-header.md) · [Distinguish input identity from guest evidence](../../../courses/umicom-kernel-from-scratch/lessons/108-distinguish-input-identity-from-guest-evidence.html) · [Record enough evidence to understand a build result](../../05-engineering/learning-build-systems/08-record-build-identity.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/132-read-the-scope-of-a-kernel-build-identity.html)
