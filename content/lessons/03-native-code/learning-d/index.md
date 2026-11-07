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
