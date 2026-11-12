<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/14-test-refused-edits-and-sdk-identity.md

PURPOSE:
Teach check refused edits, preserved state and sdk identity.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Check refused edits, preserved state and SDK identity

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
[Course contents](index.md) · [Complete source](../../../../labs/native/shared-editor/document.c) · [Build and run](../../../../labs/native/shared-editor/README.md)
-->
[Course contents](index.md) · [Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/document.c) · [Build and run](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md)

A refusal is useful only if it leaves the document in a defined state. Returning an error after changing text or consuming history would make retrying dangerous. The remaining lab scenarios compare both the returned status and the working state after an unsuccessful request.

## 1. Capture the right baseline

stale-plan prepares a plan for original, then applies a newer edit that changes the document to newer. Only then does it capture the baseline for the expected refusal. Applying the old plan must fail with INVALID_STATE and retain newer. Comparing against original would incorrectly ask the service to undo the legitimate intervening edit.

SameWorkingState compares documented fields individually: identity, revision, text length, Undo and Redo counts, dirty flag, path state and view ID. It does not memcmp an entire C structure, because padding bytes are not part of the logical contract. HasText independently compares the complete owned text copy.

## 2. Separate different refusal causes

- stale-plan: the captured draft is no longer current; preserve the newer edit.
- consumed-plan: a successfully applied plan cannot be applied a second time.
- read-only: selection and capture are permitted, but changing the document is refused.
- invalid-replacement: malformed UTF-8 and an embedded zero byte are refused without changing text or history.

The invalid-replacement scenario then applies corrected valid text through the same still-current capture. That retry is allowed because neither failed request consumed it or changed its source. In contrast, retrying a stale or consumed plan cannot make it current. A new user action needs a newly prepared plan.

## 3. Run each named observation

~~~powershell
& .\build\shared-editor\shared-editor.exe stale-plan
& .\build\shared-editor\shared-editor.exe consumed-plan
& .\build\shared-editor\shared-editor.exe read-only
& .\build\shared-editor\shared-editor.exe invalid-replacement
ctest --test-dir .\build\shared-editor --output-on-failure --no-tests=error
~~~

Run one command at a time and stop on an unexpected failure. A successful process prints its scenario name and returns zero. CTest should register twelve named scenarios when BUILD_TESTING is enabled. A zero-test listing is missing coverage, not twelve passes. The QUALIFICATION guide gives the complete observation checklist.

## 4. Identify what actually ran

Record the compiler, build directory, installed SDK prefix, installed package metadata and executable you launched. The lab checks that its selected package configuration belongs under the requested SDK prefix and asks the SDK to validate its exported layout. These checks reduce accidental mixing, but they do not prove that a later runtime loader selected every intended dependency.

An undefined symbol usually calls for checking the installed archive and export set before changing a correct function name. A missing declaration calls for checking the specific translation unit and its direct headers. document.c includes umicom/document/edit.h explicitly. A symbol found somewhere in another repository is not evidence that this source file can see its declaration.

## Exercise and worked explanation

Suppose a log says all checks passed, but the binary was built before the newest scenario was registered. Can it validate the new refusal? No. Record the source and binary identities and rebuild through the owner’s qualification workflow. Preserve the old log as historical evidence, then label the new case unexecuted until the matching binary runs.

## Scope and next steps

The twelve scenarios cover deterministic in-memory calls. Allocation exhaustion, the full history byte-budget boundary, native keyboard input, text shaping, IME composition, clipboard services and file saving require additional tests. The course can now connect buffer ownership, exact positions, source ranges and document history without claiming a complete graphical editor. Use the existing Studio design and shared Framework APIs when moving to the native adapter.


[Previous lesson](13-traverse-one-shared-document-history.md)
