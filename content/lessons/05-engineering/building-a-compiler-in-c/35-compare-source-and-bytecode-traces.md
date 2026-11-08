<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/35-compare-source-and-bytecode-traces.md

PURPOSE:
Compare source and bytecode traces

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare source and bytecode traces

## Setup recap

Build the compiler as in lesson 31. Choose a new output filename for the encoded program; compilation refuses existing outputs. The example below uses trace-study.umcb and does not replace it on a later run.

```powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" compile ".\examples\inspection.uc" "trace-study.umcb"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" trace ".\examples\inspection.uc"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" trace-bytecode "trace-study.umcb"
```

## Trace a format without changing it

Bytecode stores opcodes, operands and source offsets. The new trace is an observation produced while those instructions execute; it is not another field in the encoded file. Wire format 1 and its existing opcode values remain unchanged. A bytecode decoder validates the complete file before the executor can produce a row.

When the source file is unchanged, its compiled instructions and the decoded artifact should produce identical trace rows. The CLI regression compares the complete source and bytecode output, not only the final value. It also hashes the inputs before and after tracing to check that this observation did not modify them.

## Identify the source before reusing a report

If you insert a comment before an expression, its arithmetic can stay the same while its source offsets change. The operation-comparison API deliberately ignores offsets, but a displayed trace must still identify the source it describes. An old artifact may carry valid offsets for an older file.

Record the source revision or a content digest alongside the artifact and trace. A matching arithmetic result does not identify a compiler version, build configuration or source file. None of these commands proves that a native guest image was rebuilt.

## Exercise

Insert a blank line before the return statement, recompile to a different output name and compare the old and new traces. Predict unchanged operations and values, with shifted source offsets. Keep both files so the distinction remains visible.

For recovery, inspect the command path and input path before changing runtime code. A malformed UMCB header should fail decoding with no step rows. An accepted artifact that later divides by zero should instead produce a runtime fault row.

## Read the source

[umicom-c/tests/check_cli_trace.cmake](https://github.com/umicom-foundation/umicom-c/blob/main/tests/check_cli_trace.cmake). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Count the rejected fuel step](34-count-the-rejected-fuel-step.md) · [Next: Present a fresh Framework trace](36-present-a-fresh-framework-trace.md)
