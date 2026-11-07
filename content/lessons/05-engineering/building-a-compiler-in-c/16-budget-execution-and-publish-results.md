<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/16-budget-execution-and-publish-results.md

PURPOSE:
Explain the lesson: Budget execution and publish results.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Budget execution and publish results

An execution budget limits how many instructions the VM may perform. Umicom C calls that allowance fuel.

## Prepare the experiment

Use the compiler-experiments README to configure the lab. Open test_validation.c and umc_execute in the existing Umicom C source.

A budget is a limit chosen by the caller. It is separate from the count of instructions supplied by the program.

## 1. Count the final instruction

Consider PUSH 7 followed by RETURN. With two fuel units, both instructions run and the result becomes 7.

With one fuel unit, PUSH can run but RETURN cannot. The VM reports UMC_FUEL_EXHAUSTED and leaves the caller's result unchanged.

Computing an intermediate value is different from publishing a successful result.

## 2. Inspect the boundary check

The execution loop compares the program counter with fuel before processing each instruction. At fuel zero, it refuses before executing the first instruction.

Structural validation happens first and has its own bound through UMC_PROGRAM_LIMIT. Fuel does not describe all work performed by the entire API call.

This distinction matters when estimating resource use: a short execution budget does not eliminate input validation.

## 3. Preserve the caller's observation

The test initialises result.value and instructions_executed to recognisable sentinel values. After failure, it checks both remain unchanged.

A sentinel here is simply a chosen value used to detect accidental modification. It is not a special CPU feature.

## Exercise

Make a table for fuel 0, 1, 2 and 3 on the two-instruction program. Predict failure for 0 and 1, then success for 2 and 3.

Explain why a larger allowance does not cause extra instructions to execute after RETURN.

## Next investigation

The current language has no loops. If jumps are introduced later, counting instructions becomes more important because source length alone no longer bounds executed work.

Keep a future extension's control-flow validation and runtime budget separate. Reuse the existing VM contracts in consumers instead of implementing another budget around a different interpreter.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-experiments/test_validation.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](15-validate-stack-shape-before-execution.md)

