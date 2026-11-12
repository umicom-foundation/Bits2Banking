<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/48-lower-negation-to-existing-operations.md

PURPOSE:
Lower logical negation without a new opcode

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Lower logical negation without a new opcode

## Before you begin
Understand stack instructions and the comparison equality operation. Read the new unary parser beside its retained predecessor in src/compiler.c.

## Express the result with existing semantics
Logical negation returns one when its operand is zero and zero otherwise. The runtime already compares two signed integers for equality, so the compiler can express this result without changing the public opcode enumeration.

~~~text
Source: !0
PUSH 0       operand
PUSH 0       comparison constant
EQUAL        operand == 0
RETURN
~~~

1. Compile the operand recursively.
2. Emit the additional zero.
3. Emit equality.
4. Keep both inserted operations tied to the source byte offset of !.

The lowering adds two instructions beyond its operand. It also needs one extra temporary stack value during equality. Those costs matter to a bounded interpreter.

## Work through precedence
!0 + 4 becomes 1 + 4 and returns 5. !(0 + 4) negates the parenthesized sum and returns 0. The unary parser's position in the existing expression hierarchy gives those forms different meaning.

## Exercise and expected result
Draw stack states for !!-9. Start with the arithmetic unary-minus lowering already supported by the compiler, then apply each logical negation from the inside out. The final value is 1. Compare your prediction with the library regression rather than guessing from the spelling.

## Recovery
Do not add a special VM instruction only to make the source look more direct. A new opcode would affect encoding, decoding, inspection and every consumer. If existing semantics express the exact required behavior, reuse them and qualify their resource costs.

The emitted equality selects the existing comparison wire profile. An older arithmetic-only decoder still cannot accept that profile. No format-number change is needed, but consumer compatibility must still be checked.

See tests/test_logical_not.c for the four-instruction !0 case, source-offset assertions and wire round trip. Those checks establish the tested library behavior, not a full C compiler.


[Course contents](index.md) · [Previous lesson](47-recognise-prefix-negation.md) · [Next lesson](49-observe-negation-failures-and-budgets.md)
