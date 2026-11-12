<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/47-recognise-prefix-negation.md

PURPOSE:
Recognise prefix negation without changing not-equal

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Recognise prefix negation without changing not-equal

## Before you begin
Read the earlier comparison-token lessons. Open umicom-c/src/lexer.c, src/internal.h and tests/test_logical_not.c. You need basic byte offsets and the difference between a token and an instruction.

## Admit the longest operator first
The characters != already form the not-equal operator. Adding a standalone ! must preserve that two-character choice. Otherwise a previously valid comparison can become a negation followed by an invalid assignment symbol.

~~~c
int main(void) { return 1 != !0; }
~~~

1. Locate the first exclamation mark. Its following equals sign makes it one not-equal token.
2. Locate the second exclamation mark. It has no adjacent equals sign and begins a unary expression.
3. List tokens before considering arithmetic or runtime behavior.
4. Confirm that the lexer never reads a second byte beyond the supplied source span.

## Expected result
The right operand !0 is 1, so the complete expression returns 0. The first and second exclamation marks have different roles. A whitespace-separated ! = sequence is not the two-character != operator.

## Exercise
Predict the token sequence for !0, !!0, 1 != 0, 1 ! 0 and !/* note */0. The lexer can recognize ! in the fourth example, but the parser must still reject its invalid infix position. Lexical recognition alone does not make a program grammatical.

## Preservation and recovery
The old guard that rejected unsupported single-character operators remains in a disabled source block for review. The new path preserves bare-assignment refusal while admitting the specific prefix token. This makes the language extension auditable without treating a removed restriction as permission for arbitrary new syntax.

If comparison tests fail after a lexer edit, inspect the exact token boundaries first. Do not repair the runtime to compensate for an operator that was split incorrectly. Run the comparison-source tests as well as the negation regressions.

The language remains a bounded C-like expression subset. Recognizing ! does not add assignments, variables, control flow, logical-and or logical-or.


[Course contents](index.md) · [Previous lesson](46-qualify-comparisons-in-a-kernel-guest.md) · [Next lesson](48-lower-negation-to-existing-operations.md)
