<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/62-keep-template-looking-text-as-data.md

PURPOSE:
Keep template-looking text as data

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep template-looking text as data

Build configuration contains text that can resemble another language's instructions. A path or flag might include an at-sign token. Serializing that value must not reinterpret it as a template.

## Reproduce the reasoning error

CMake file(CONFIGURE) is designed to substitute variables. That is useful when generating a deliberate template. It is unsuitable for a JSON record whose values have already been resolved and must remain literal. A value such as @UNDECLARED_VARIABLE@ can disappear during a second substitution pass.

Read the preserved disabled writer in cmake/InputIdentity.cmake, then the active umc_input_write_data helper. The replacement compares existing bytes and writes the content directly when needed. It does not run another template expansion over the record.

## Inspect the regression

The literal-configuration-token fixture uses string(ASCII 64) to construct an at sign, places a token and a semicolon in a recipe value, captures the record, and verifies it unchanged. Constructing the character deliberately also keeps the test authoring step from accidentally expanding the very token under test.

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R '^umicom.c.input-identity.literal-configuration-token$' --output-on-failure --no-tests=error
~~~

Expected result: one passing regression. The recorded value keeps its token, spaces and semicolon. The record remains data even when it resembles CMake source.

## Distinguish escaping from substitution

JSON escaping makes quotes and backslashes representable inside a string. Template substitution replaces recognized tokens with values. These are different operations. Escaping JSON correctly does not make a later template-expansion pass safe for literal data.

The checker also refuses appended content and altered claims. It compares the canonical representation produced by capture rather than accepting arbitrary reformatted JSON. This narrow contract is appropriate for a generated local record and should be explained to users.

## Exercise and answer

Suppose a recipe has a path called build/@PROFILE@/compiler. Should the recorder replace PROFILE with the current build type? No. Resolve deliberate build variables before constructing the recipe; once the path is a data value, preserve it. If you intended an unresolved template, it belongs in a separate template field and workflow.

A related failure occurs when a program evaluates a receipt as configuration code. The receipt-as-code regression confirms that the verifier does not create a marker requested by injected CMake text. Reviewers should look for forbidden include or execute operations on untrusted receipt contents, not merely for correct checksums.

CMake documents substitution and direct writing separately in its [file command reference](https://cmake.org/cmake/help/v3.24/command/file.html). The lesson's repair uses those existing build-system facilities; it does not add another product runtime.

[Course contents](index.md) · [Previous lesson](61-refuse-stale-input-records-without-repairing-them.md) · [Next lesson](63-compare-operations-without-running-programs.md)
