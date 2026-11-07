<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/15-validate-stack-shape-before-execution.md

PURPOSE:
Explain the lesson: Validate stack shape before execution.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate stack shape before execution

Before executing a program, Umicom C checks whether its instructions can use the stack correctly. This is structural validation: it concerns instruction arrangement before numeric results are calculated.

## Setup recap

Open umc_validate in src/vm.c. For executable exercises, use the compiler-experiments lab and its test_validation.c file.

A stack stores values in order. A depth of three means three values are currently available.

## 1. Track depth without computing values

PUSH adds one value, so depth increases. ADD needs two values and replaces them with one, so depth decreases by one. NEGATE needs one value but leaves depth unchanged.

These rules can be checked using only instruction kinds. There is no need to know whether the values are 2 and 3 or 200 and 300.

## 2. Check RETURN precisely

RETURN requires exactly one stack value and must be the final instruction. Otherwise the program is rejected.

Allowing unexamined instructions after RETURN would make the accepted representation ambiguous. Full validation keeps the entire declared program accountable.

The validator also rejects unknown opcodes and nonzero operand fields on instructions that do not use an operand.

## 3. Separate shape from arithmetic

PUSH 8, PUSH 0, DIVIDE, RETURN has a valid stack shape. Execution must still refuse division by zero.

Validation therefore does not mean every accepted program will calculate a result. It establishes the structural preconditions needed to attempt execution safely.

## Exercise

Draw depths for these sequences:

```text
PUSH, PUSH, ADD, RETURN
ADD, RETURN
PUSH, PUSH, RETURN
PUSH, RETURN, PUSH
```

Only the first has the required shape. Explain the first failing rule for each other sequence.

## Recovery and limits

Run the validation group through the lab commands when ready. A refusal must preserve the caller's result fields, which the tests initialise to recognisable values.

The VM has no jump or host-call instruction in this subset. More complex bytecode would require additional reasoning about control-flow paths and capabilities; the current linear check is not a general validator for arbitrary languages.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-c/blob/main/src/vm.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-admit-decimal-literals-without-overflow.md) · [Next lesson](16-budget-execution-and-publish-results.md)

