<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/17-publish-a-contract-only-after-validation.md

PURPOSE:
  Present "Publish a kernel contract only after validation" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a kernel contract only after validation

A native program asks a kernel what services and data sizes it supports. Several queries can succeed before a later query fails. This lab follows the code that keeps a partly discovered contract from becoming a caller's accepted result.

Source to open: `umicom-kernel/programs/support/native_contract.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\umicom-kernel\programs\support\native_contract.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../umicom-kernel/programs/support/native_contract.c'
```

## Understand the idea

An output structure groups several values, such as a version, word size and page size. A caller may already hold a previous result in that structure. Publishing means copying a newly accepted result into the caller's storage. In the discovery function, queried values are checked before the final output fields are written. This gives the caller a clear boundary between success and failure. A compatible version alone is insufficient: the program must also understand data sizes and limits. The details belong to this kernel interface and should be read from the current header and implementation.

```text
query -> validate version -> validate sizes -> validate limits -> publish
                  |                 |                |
                  +-- failure ------+----------------+-> keep old output
```

## Work through the lab

1. Locate the discovery function and its argument checks. Find the queries for version, features, wordBits, byteOrder, pageBytes, copyLimit and callLimit. Draw a box around the final assignments to the output structure.
2. Create a paper output structure with distinctive old values. Walk through a version query that succeeds, then a word-size query that reports an unsupported value. Mark the return path and check whether any final assignment has occurred.
3. Repeat with compatible size fields but copyLimit equal to zero. Follow the validation branch. Explain why successfully receiving a value does not establish that it is acceptable.
4. Trace a fully accepted set of fields to the final assignments. Write a proposed regression case for each rejection: expected status, input response sequence, and an unchanged-output comparison. Keep the fake query mechanism separate from real kernel execution.

## Expected result

Rejected discovery should leave the caller's old output untouched along the paths reviewed here. Accepted discovery publishes the checked fields together. Your exercise should identify the exact validation condition, rather than describing every failure as a boot problem.

## If the result differs

If a test later sees changed output on failure, compare the first write with the first possible failing query. Do not hide the issue by clearing the caller's result before every call. A fake-query test verifies this function's control flow, not privilege transitions or emulator behaviour.

## Explain it yourself

Why is it useful to choose distinctive old output values instead of initialising every field to zero?

<details>
<summary>Worked explanation</summary>

Distinctive values reveal an accidental partial write more clearly. Zero can happen to equal a newly queried value, hiding the mutation. The expected failure result includes both the status and the preserved fields.

</details>

## Use the idea in Umicom

Keep kernel contract discovery in the kernel library that defines the interface. Shared application tooling can present the returned status, but should not invent a different compatibility rule. A source-level trace is one part of qualification; execution still needs the matching kernel and native-program builds.

[HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/17-publish-a-contract-only-after-validation.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](16-discover-the-native-program-contract.md) · [Course contents](index.md)


[Next: Read a memory-mapped timer](18-read-a-memory-mapped-timer.md)
