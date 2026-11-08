<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-filter-results-and-failure-atomicity.md

PURPOSE:
Keep an object unchanged when an operation fails

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep an object unchanged when an operation fails

This module starts with a small command-line program and follows its calls into Umicom Framework. Each lesson includes the setup needed to begin independently. You will inspect real source while learning how document names, memory boundaries and editing capabilities fit together.

A terminal is a window that runs written commands. PowerShell is one such terminal on Windows; Bash is common on Linux. A compiler translates C into a program your machine can run. CMake describes the build; Ninja performs the work. An SDK supplies the headers that describe a library and the compiled library files.

Install a C23-capable compiler, CMake and Ninja. Install the Umicom Framework SDK containing the document and editor components. These steps assume Windows tools in C:\msys64\ucrt64\bin and SDK files in C:\umicom\installed\framework; replace those paths if your installation differs. No GTK window or broker connection is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-language-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\language-inspection.exe cpu.vhd app.zig CMakeLists.txt
```

On Linux, use the same lab from your checkout and your installed SDK:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/native/framework-language-inspection
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework"
cmake --build build
./build/language-inspection cpu.vhd app.zig CMakeLists.txt
```

Stop if configure or build reports an error. The first output line should be `cpu.vhd: vhdl`, followed by its choice, comment style and matching filters. This program examines the name only; the named files need not exist. [Learning C](../../courses/learning-c/index.html) and [Learning CMake](../../courses/learning-cmake/index.html) provide longer setup explanations.

## Failure should leave a clear state

An operation is failure-atomic when it either completes its promised change or leaves the original state intact. This helps callers recover without guessing which fields were partly updated.

Imagine a filter containing two patterns. An attempt to append an overlong third pattern should not increase the count to three. Otherwise another function may read an entry that was never created.

## Find the mutation point

Find umi_document_file_filter_add_pattern in Framework. Read down to the increment of pattern_count. Every rejecting condition comes before that mutation. The destination slot is chosen only after capacity checks.

Now inspect UmiDocumentLanguageChoiceIdentity in languages.c. It obtains a candidate in a local result, checks that its ID matches the selected catalogue entry, and copies the result to the caller only on success. This is the same ownership idea at another boundary.

## Design a regression

1. Create a filter with one valid pattern.
2. Copy the complete filter to a variable called before.
3. Try adding a pattern that fills the text capacity without a terminator.
4. Expect an error.
5. Compare the original fields with before.
6. Repeat with an already full pattern array.

The bounded-add and full-capacity tests follow this reasoning. The overlap case also exercises adding a pattern that already belongs to the filter.

The test compares the count, name array and pattern arrays separately. Structures can contain padding bytes whose values are not part of the logical object. Comparing defined fields avoids making a rejection check depend on those padding bytes.

## Explain the result

An error status is not a complete recovery plan. The caller also needs to know which objects changed, who owns returned memory and whether it may retry.

For an editor's Open dialog, a refused filter update should retain the previously valid configuration. For a bank transfer or saved file, additional persistence and transaction rules are needed. Do not infer disk or database atomicity from this in-memory example.

## Practice

Write down preconditions, success result and failure state for a function in your program. Mark the first line that changes caller-owned memory. Move validation before that line where the contract permits it. Add a test that checks rejection preserves the original values.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Bound a character buffer before reading it](language-filters-and-bounded-c-strings.md) · [Next: Share file-opening categories between applications](language-filter-categories-and-open-dialogs.md)
