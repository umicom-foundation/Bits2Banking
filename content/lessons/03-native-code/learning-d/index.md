# Learning D Language

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## First programme and sequences

Install the toolchain, use contracts and distinguish a slice from independent storage.

1. [Install D and compile a first program](01-install-and-run.md)
1. [Describe a contract and run D unit tests](02-contracts-and-unit-tests.md)
1. [Apply an existing function to a sequence](03-apply-a-function-to-a-sequence.md)
1. [Distinguish a slice from independent storage](04-distinguish-a-slice-from-independent-storage.md)

## Modules and bounded iteration

Share functions and check related lengths before visiting elements.

1. [Name a module and import a function](05-name-a-module-and-import-a-function.md)
1. [Understand a read-only slice](06-understand-a-read-only-slice.md)
1. [Check related lengths together](07-check-related-lengths-together.md)
1. [Read a half-open loop range](08-read-a-half-open-loop-range.md)

## Complete batch results

Allocate once, follow partial failure and test the empty-input case.

1. [Allocate output storage once](09-allocate-output-storage-once.md)
1. [Trace an exception partway through a batch](10-trace-an-exception-partway-through-a-batch.md)
1. [Test empty input as a valid case](11-test-empty-input-as-a-valid-case.md)
1. [Keep checks enabled during learning](12-keep-checks-enabled-during-learning.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Learning D Language

Create a native program with the D compiler. Learn how source becomes an executable, then check a function with input validation and unit tests.

## Start here

No previous course is required. You may read without installing tools. To do the practical work: Install the DMD compiler for your operating system and confirm dmd --version in a new terminal. Choose an empty practice folder. Lesson 1 shows source creation, compilation and execution in PowerShell and bash.

For a slower introduction to commands and files, use [the terminal setup lab](../../learning-c/terminal-lab.md). Return here afterwards; it is a reference, not another required course to finish first.

## Follow these lessons in order

1. [Install D and compile a first program](01-install-and-run.md)
2. [Describe a contract and run D unit tests](02-contracts-and-unit-tests.md)
- [Apply an existing function to a sequence](03-apply-a-function-to-a-sequence.md)
- [Distinguish a slice from independent storage](04-distinguish-a-slice-from-independent-storage.md)

## What you will practise

Create and locate a source file, follow the build or run command, read the output, change one behaviour and check the result. Each lesson includes a setup recap and recovery steps. Use a separate practice directory so experiments do not overwrite the repository example.

## Continue after these lessons

Arrays, strings, modules, ownership, error handling and reviewed C interoperability. These are planned topics; the two introductory lessons do not constitute a complete language or platform course.

[Subject guide](../../../courses/course-series.html) · [Learning C](../../learning-c/index.md) · [Framework Development](../../umicom-development/index.md)


- [Name a module and import a function](05-name-a-module-and-import-a-function.md)

- [Understand a read-only slice](06-understand-a-read-only-slice.md)

- [Check related lengths together](07-check-related-lengths-together.md)

- [Read a half-open loop range](08-read-a-half-open-loop-range.md)

- [Allocate output storage once](09-allocate-output-storage-once.md)

- [Trace an exception partway through a batch](10-trace-an-exception-partway-through-a-batch.md)

- [Test empty input as a valid case](11-test-empty-input-as-a-valid-case.md)

- [Keep checks enabled during learning](12-keep-checks-enabled-during-learning.md)

</details>

## Types, reflection and native boundaries

Continue from the introductory lessons into typed values, memory contracts, compile-time reflection and C interoperability.

Install a supported D compiler and record its version. The C boundary needs a compatible C object toolchain. Ordinary D and BetterC have different runtime contracts.

1. [Read D values, types and expressions](13-values-types-and-expressions.md)
1. [Choose paths and traverse D collections](14-control-flow-and-collections.md)
1. [Choose a struct, class or interface](15-structs-classes-and-interfaces.md)
1. [Understand D memory management and safety attributes](16-garbage-collection-and-memory-contracts.md)
1. [Use templates and compile-time evaluation](17-templates-and-compile-time-work.md)
1. [Inspect fields with compile-time reflection](18-reflection-and-field-catalogues.md)
1. [Separate C linkage from the BetterC subset](19-c-abi-and-betterc.md)
1. [Navigate D keywords and language concepts](20-keyword-and-concept-map.md)

## Further practical exercises

1. [Distinguish function pointers, delegates and C callbacks](21-functions-delegates-and-callback-lifetimes.md)
1. [Use scope guards to make cleanup paths visible](22-scope-guards-and-native-cleanup.md)

1. [Inspect types and check conversions without guessing](23-type-inspection-and-checked-casts.md)

1. [Use a C callback without capturing a D delegate](24-use-an-explicit-c-callback-context.md)

1. [Declare field metadata and inspect it at compile time](25-declare-and-inspect-field-metadata.md)

1. [Select code before the program runs](26-select-code-before-the-program-runs.md)

1. [Separate read-only views from independent copies](27-separate-read-only-views-from-independent-copies.md)

1. [Look up records without confusing storage with learning](28-look-up-records-with-associative-arrays.md)

1. [Turn field metadata into explicit checks](29-turn-field-metadata-into-explicit-checks.md)

1. [State the effects of a binary reader](30-state-the-effects-of-a-binary-reader.md)

1. [Follow the lifetime of input-range data](31-follow-the-lifetime-of-input-range-data.md)

1. [Publish results deliberately with ref and out](32-publish-results-with-ref-and-out.md)

1. [Admit enumerated states before exhaustive dispatch](33-admit-enumerated-states-before-dispatch.md)

1. [Distinguish lazy evaluation from caching](34-distinguish-lazy-evaluation-from-caching.md)

1. [Separate invariants from input validation](35-separate-invariants-from-input-validation.md)

1. [Separate modules, visible names and linked code](36-separate-modules-names-and-linked-code.md)

1. [Reuse typed declarations with template mixins](37-reuse-typed-declarations-with-template-mixins.md)

1. [Follow nested static-array copies](38-follow-nested-static-array-copies.md)

1. [Separate text bytes, code points and display](39-separate-text-bytes-code-points-and-display.md)

1. [Preserve qualifiers when returning a borrowed view](40-preserve-qualifiers-when-returning-a-borrowed-view.md)

1. [Inspect layout without serializing padding](41-inspect-layout-without-serializing-padding.md)

1. [Separate atomic access from thread lifetime](42-separate-atomic-access-from-thread-lifetime.md)

1. [Separate union reflection from active-value state](43-separate-union-reflection-from-active-value-state.md)

1. [Distinguish conditional selection from argument evaluation](44-distinguish-conditional-selection-from-argument-evaluation.md)

1. [Separate local static storage from caller ownership](45-separate-local-static-storage-from-caller-ownership.md)

1. [Separate runtime dispatch from type reflection](46-separate-runtime-dispatch-from-type-reflection.md)

1. [Validate bytes before converting to bool](47-validate-bytes-before-converting-to-bool.md)

1. [Separate rounding from checked integer conversion](48-separate-rounding-from-checked-integer-conversion.md)

1. [Constrain operator templates and test their meaning](49-constrain-operator-templates-and-test-their-meaning.md)

1. [Follow comment and string boundaries](50-follow-comment-and-string-boundaries.md)

1. [Admit values before exhaustive state dispatch](51-admit-values-before-exhaustive-state-dispatch.md)
