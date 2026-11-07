<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv-assembly/15-inspect-unresolved-call-symbols.md

PURPOSE:
Explain the lesson: Inspect an unresolved call symbol.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect an unresolved call symbol

An assembler can translate a function call before it knows the final address of the target function. It records information for the linker to finish later.

## Prepare

Use the RISC-V sequences README to assemble call.S and sum.S separately. Stop if either command fails. The resulting .o files are objects, not runnable applications.

Run the documented llvm-objdump -dr command.

## Find the reference

call.S contains call BtbSum64. The target's implementation is in sum.S, so call.o cannot independently choose its final linked location.

A relocation tells the linker where a reference needs adjustment. Its exact encoding and displayed form depend on toolchain options and permitted relaxation.

## Follow the stages

1. Source names the target symbol.
2. Assembly creates instructions and relocation information.
3. Linking combines compatible objects and resolves the symbol.
4. Loading places the executable into an execution environment.

An error at one stage should be investigated at that stage.

## Exercise

On a local copy of the documented Linux build command, omit sum.S. Predict an unresolved-reference link failure. Restore it before expecting a runnable harness.

Do not solve a missing symbol by inventing an empty function with the same name. That can hide the build error while removing required behavior.

## Connect to Umicom

When a Framework library reports an undefined reference, inspect which source file defines the symbol and whether that object is included in the linked target. A declaration in a header is not an implementation.

This lesson's commands are qualification instructions. Record the actual diagnostic from your toolchain rather than assuming its wording or relocation names will exactly match another version.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/riscv-sequences/call.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-combine-shifts-with-or.md) · [Next lesson](16-check-assembly-with-a-c-oracle.md)

