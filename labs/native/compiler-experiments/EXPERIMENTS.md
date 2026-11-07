<!--
Umicom Bits2Banking
File: labs/native/compiler-experiments/EXPERIMENTS.md

PURPOSE:
Provide concrete prediction and diagnosis exercises for the compiler consumer lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compiler experiment sheets

Use the setup and commands in [the lab guide](README.md). Each row is a different question. The purpose is to explain the observation, not merely to collect passing results.

## Expression order

| Expression | Expected value | Explain before running |
| --- | ---: | --- |
| 2 + 3 * 4 | 14 | Multiplication consumes 3 and 4 first. |
| (2 + 3) * 4 | 20 | Parentheses force addition first. |
| 10 - 3 - 2 | 5 | Repeated subtraction groups from the left. |
| 20 / 2 / 2 | 5 | Repeated division also groups from the left. |
| -7 / 2 | -3 | Integer division truncates toward zero. |

Place each expression inside `int main(void) { return ...; }`. Draw a stack after every emitted instruction. Write values from bottom to top.

## Three different refusals

| Source change | Stage | Expected reason |
| --- | --- | --- |
| Use literal 2147483648 | Compilation | Decimal token exceeds the admitted positive int32 range. |
| Use 2147483647 + 1 | Execution | Representable inputs produce an unrepresentable result. |
| Remove the semicolon | Compilation | Required punctuation is missing. |

The current lexer reads a positive literal before unary negation. Therefore `-2147483648` is refused as a literal, while `-2147483647 - 1` can produce the minimum result. This is a documented subset behavior, not a general statement about every C compiler.

## Fuel and shape

Read test_validation.c. A push followed by return needs two units of fuel. With one unit, the VM has calculated a value but has not reached the instruction that publishes it. The caller's result must remain unchanged.

Draw why ADD needs two prior values. Draw why RETURN rejects a stack containing two values. Finally explain why instructions after RETURN are rejected instead of ignored.

## Extension lab

Add one case to the existing tables: choose a negative multiplication whose result fits, then another whose result overflows. Predict both results using a wider mathematical range before running the checks.

Keep the implementation in Umicom C. If an observation differs from the contract, preserve the failing input and investigate the shared source rather than changing a second implementation in this lab.

