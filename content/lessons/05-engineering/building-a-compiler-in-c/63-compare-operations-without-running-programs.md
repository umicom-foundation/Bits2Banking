<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/63-compare-operations-without-running-programs.md

PURPOSE:
Compare operations without running programs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Compare operations without running programs

Two source files can look different yet compile into the same instruction sequence. Umicom C already has a library operation for that question. The compare-operations command exposes it without adding a second comparison engine or executing the programs.

## Before you begin

Follow the Umicom C execution guide to build the native command with the Windows UCRT64 preset, or select the corresponding native preset on another host. Know the actual executable path. This lesson uses two small source files and does not modify installed applications or publish a repository.

## Create a spelling experiment

Save these programs in two files:

~~~c
/* left.uc */
int main(void) { return 0x2a; }
~~~

~~~c
/* right.uc: different comments and source positions */
int main(void) { return 0b101010; }
~~~

From the Umicom C checkout, using its documented Windows preset:

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe compare-operations .\left.uc .\right.uc
$LASTEXITCODE
~~~

Expected result: operations=same, two instructions on each side, source-locations=not-compared, execution=not-performed and exit zero. Both literals become the same signed PUSH operand followed by RETURN. The command creates no output file.

## Follow ownership through the implementation

Open tools/main.c and locate compare_operations. It reads each source into one bounded scratch buffer and compiles into a separate caller-owned instruction array. The scratch buffer may be reused after compilation because instructions retain values and source offsets, not pointers into the text.

The command then calls umc_program_same_operations. Open src/comparison.c: that service validates both complete programs before comparing opcode and operand fields. Source offsets are excluded intentionally. The hosted command owns file I/O; the core service owns instruction identity.

## Separate instructions from results

Change left.uc to return 2 + 3 and right.uc to return 5, preserving each function body. The expected comparison is different, exit one, although both programs would return five when executed. One contains an addition and extra constant; the other does not.

Now set both bodies to return 1 / 0. The expected comparison is same, exit zero. Execution would fail, but this command does not execute. This is a useful counterexample to the claim that equal operations establish a successful runtime result.

## Exercise and recovery

Explain three different comparisons: source bytes, instruction identity and execution results. For each, name a pair of programs where it differs from another comparison. Comments can change bytes and diagnostic offsets; a simplified expression can change operations; a failing expression can have identical operations in two files without producing a result.

If a comparison is surprising, inspect each program and disassemble newly compiled copies in separate output files. Preserve the inputs. Do not modify the comparison service to ignore an opcode merely because two sample results happen to match.

Instruction identity alone cannot approve a cache hit, skip a regression, certify a binary or preserve diagnostic locations. Keep the preceding configuration-input lesson's source, tool and artifact questions separate.

[Course contents](index.md) · [Previous lesson](62-keep-template-looking-text-as-data.md) · [Next lesson](64-handle-comparison-exits-without-hiding-errors.md)
