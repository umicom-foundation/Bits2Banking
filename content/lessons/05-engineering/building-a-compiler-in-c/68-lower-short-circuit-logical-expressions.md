<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/68-lower-short-circuit-logical-expressions.md

PURPOSE:
Lower short-circuit logical expressions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Lower short-circuit logical expressions

## Goal

Compile a logical expression whose right operand must sometimes be skipped. You should already understand arithmetic precedence, local names and stack bytecode from the previous lessons. Work in the Umicom C checkout with its configured native C toolchain.

## Start with a guard

~~~c
int main(void) {
    int divisor = 0;
    return divisor != 0 && 42 / divisor > 1;
}
~~~

The left comparison returns zero. Logical AND therefore returns zero without dividing. Change divisor to seven: both operands are needed and the result becomes one. Reverse the two operands while divisor is zero: execution now fails. A guard works because of evaluation order, not because the runtime ignores all arithmetic errors.

## Separate precedence from evaluation

Equality is parsed before logical AND, and logical AND before logical OR. Thus a || b && c groups as a || (b && c). Grouping determines the expression tree. Short-circuit rules then determine which parts execute. Parentheses change grouping but never make the right operand execute first.

The lexer recognizes adjacent && and || as single tokens. Single & and | are outside this language. Spaces or comments between their two characters do not form a logical token. Token recognition must remain bounded by the supplied source length.

## Emit two paths

Read logical_and and expression in src/compiler.c. After emitting the left value, the compiler emits JUMP_IF_ZERO with a target to patch later. That instruction consumes the condition. For AND, the zero arm pushes zero. The other arm evaluates the right expression and normalizes its truth value by comparing it with zero. JUMP skips the arm that was not selected.

For OR, the nonzero arm pushes one; the zero arm evaluates and normalizes the right expression. Both arms arrive at the join with exactly one integer. Patch targets as instruction indices after the target position is known. A capacity failure must leave compilation failed rather than publish a partly patched program.

## Observe real output

Run each command from the repository root after following the existing build setup:

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe check .\examples\short_circuit.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace .\examples\short_circuit.uc --max-steps 8
ctest --test-dir .\build\windows-ucrt64-debug -R "umicom[.]c[.]logical[.]short_circuit_source" --output-on-failure --no-tests=error
~~~

Expect 16 admitted instructions, eight executed instructions and result zero for the supplied example. The test group also checks evaluated division faults, skipped overflow, chained operators, precedence and malformed tokens. These are expected outcomes to verify on the selected build.

## Exercise and recovery

Write three programs: zero && unsafe-division, nonzero || unsafe-division, and zero || unsafe-division. Predict which one fails before running it. Then explain why all three can pass structural inspection. If compilation fails at an operator, verify that the two characters are adjacent. If an old installed tool rejects the syntax, select the binary from the intended build directory rather than editing the test expectation.

The feature does not add if statements, loops, bitwise operations or a full C frontend. Source spelling is a compiler capability; forward branch execution is a separate runtime capability.

[Course contents](index.md) · [Previous lesson](67-prove-local-initialization-before-execution.md) · [Next lesson](69-validate-joins-on-all-forward-paths.md)
