<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-filters-and-bounded-c-strings.md

PURPOSE:
Bound a character buffer before reading it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Bound a character buffer before reading it

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

## Characters occupy a finite object

A C string stores characters followed by a zero byte. A buffer is the region of memory available to hold them. A buffer of 128 bytes holds at most 127 nonzero bytes if it must also hold the terminator.

A buffer overflow writes beyond that region. Reading beyond it is also a defect. A function cannot safely call strlen on an array that might have no terminator inside its accessible storage.

## Examine a real Framework boundary

Open include/umicom/document/file_filter.h and src/document/file_filter.c. A filter stores a bounded number of patterns. Each pattern has a fixed character capacity. The matcher first validates the pattern count, then checks that each stored pattern has a terminator inside that capacity.

Checking every pattern before matching prevents an early wildcard from hiding a malformed later entry. Validation describes the complete input object, rather than only the first convenient field.

## Follow the add operation

1. Check the filter and pattern pointers.
2. Reject an empty pattern.
3. Check that another entry fits before indexing the array.
4. Scan only up to the pattern capacity for the terminator.
5. Copy the characters and terminator into the next slot.
6. Increment the count only after the copy.

This order keeps a failed addition from advertising a partially written entry. The function uses memmove because input may refer to a pattern inside the same filter. memmove supports overlap; memcpy requires non-overlap.

## A paper exercise

Draw eight boxes numbered 0 through 7. Store five letters and put a zero in box 5: six bytes are used. Eight letters plus a terminator require nine bytes, so the operation must refuse the request or use a larger destination.

A capacity check does not make an arbitrary pointer valid. The caller must supply readable storage for the operation's stated bounds. C cannot discover an allocation size from a plain pointer.

## Review regression cases

Read bounded-add, unterminated-pattern, malformed-count and full-capacity in tests/document/test_file_filter_boundaries.c. They prepare bounded objects and check rejection; they do not depend on provoking an actual out-of-bounds access.

These checks require a configured Framework build. The standalone lab demonstrates public operations; its success would not prove that every Framework boundary test passed.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Separate a filename from its directories](language-basename-and-suffix-matching.md) · [Next: Keep an object unchanged when an operation fails](language-filter-results-and-failure-atomicity.md)
