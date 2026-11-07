<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/14-admit-decimal-literals-without-overflow.md

PURPOSE:
Explain the lesson: Admit decimal literals without overflow.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Admit decimal literals without overflow

Reading a decimal number requires arithmetic before the interpreter executes any instruction. The lexer must keep that arithmetic within its own limits.

## Prepare the source study

Open src/lexer.c in Umicom C and test_grammar.c in the compiler-experiments lab. Use the lab README for optional PowerShell or Bash execution.

A lexer groups source characters into tokens. A decimal token is a run of digits, such as 123.

## 1. Accumulate one digit at a time

To extend 12 with digit 3, calculate 12 × 10 + 3. Repeating this process gives the numeric value.

For a bounded integer type, multiplication can overflow before a later check sees the result. Therefore the lexer checks whether the next step fits first.

## 2. Rearrange the bound

The desired rule is value × 10 + digit <= INT32_MAX. The implementation checks:

```c
value > (INT32_MAX - part) / 10
```

If that condition is true, it reports UMC_LITERAL_RANGE before multiplying.

Here part is a decimal digit from zero to nine, so subtracting it from the maximum is safe. Integer division supplies the permitted whole-number threshold.

## 3. Understand unary minus

The lexer reads a positive literal token. The parser handles a preceding minus sign as a separate operation.

Consequently, this current subset refuses literal 2147483648 even when preceded by minus. The expression -2147483647 - 1 can still produce the minimum signed value through checked execution.

State this restriction clearly in a language guide. Do not teach an unsupported spelling as if it already works.

## Exercise

Trace the final digit of 2147483647 and 2147483648. Show the threshold and explain the different outcome.

Then predict the grammar test for -2147483648. The result should be a literal-range failure, not an execution overflow.

## Troubleshooting

An accepted literal and an overflowing expression are different cases. Preserve both in tests because a lexer fix cannot replace runtime arithmetic checks.

Record the tested source revision; a future deliberate language extension may change literal admission and require updated documentation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-c/blob/main/src/lexer.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-build-an-instruction-viewer.md) · [Next lesson](15-validate-stack-shape-before-execution.md)

