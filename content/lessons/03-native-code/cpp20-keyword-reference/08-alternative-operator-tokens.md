<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/08-alternative-operator-tokens.md

PURPOSE:
Match all eleven reserved alternative operator spellings to their symbol forms and distinguish logical from bitwise operations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Read word forms of operators

[Course contents](index.md) · [Previous lesson — Read modules, coroutines and reserved words](07-module-and-coroutine-spellings.md) · [Continue with Learning C++](../../../courses/learning-cpp/index.html)

## What you will learn

Match all eleven reserved alternative operator spellings to their symbol forms and distinguish logical from bitwise operations.

## Read the words in context

An **operator** combines values or changes how an expression is read. A **token** is one entry the compiler recognises, such as a name, literal or operator. C++20 has these built-in word forms of some operators. The paired tokens are equivalent in ordinary evaluation, with a difference in source spelling that matters when preprocessing stringizes a token.

## Reserved alternative operator tokens

| Spelling | Symbol | Meaning | Read this example |
| --- | --- | --- | --- |
| `and` | `&&` | Logical AND. The right operand is only evaluated if the left operand is true in this built-in operation. | `bool ready = posted and approved;` |
| `and_eq` | `&=` | Applies bitwise AND and stores the result back in the left operand. | `flags and_eq 3u;` |
| `bitand` | `&` | Bitwise AND in this example. Other grammar positions use the same token for references or addresses. | `unsigned mask = flags bitand 3u;` |
| `bitor` | `\|` | Bitwise inclusive OR. One or both corresponding bits may be set. | `unsigned mask = first bitor second;` |
| `compl` | `~` | Bitwise complement. It flips the bits of the promoted integer operand. | `unsigned inverted = compl flags;` |
| `not` | `!` | Logical NOT. It reverses a truth value. | `bool empty = not has_rows;` |
| `not_eq` | `!=` | Tests whether the values differ. | `bool changed = old_total not_eq new_total;` |
| `or` | `\|\|` | Logical OR. The right operand is only evaluated if the left operand is false in this built-in operation. | `bool keep = saved or reviewed;` |
| `or_eq` | `\|=` | Applies bitwise OR and stores the result back in the left operand. | `flags or_eq 4u;` |
| `xor` | `^` | Bitwise exclusive OR. A bit is set when exactly one corresponding input bit is set. | `unsigned diff = first xor second;` |
| `xor_eq` | `^=` | Applies bitwise XOR and stores the result back in the left operand. | `flags xor_eq 1u;` |

## Punctuation forms

C++20 also defines six alternative punctuation tokens. They are not word-like spellings in the keyword inventory.

| Alternative | Primary spelling | Read it as |
| --- | --- | --- |
| `<%` | `{` | Opening brace |
| `%>` | `}` | Closing brace |
| `<:` | `[` | Opening bracket |
| `:>` | `]` | Closing bracket |
| `%:` | `#` | Number sign |
| `%:%:` | `##` | Preprocessor token pasting |

The declarations `int samples<:2:> = <%4, 7%>;` and `int samples[2] = {4, 7};` define equivalent arrays when read separately. Use the ordinary punctuation in new exercises unless practising these alternatives. Another language can choose the same word with different rules, as the cross-language examples show.

## Try it and check

Start flags at 2. Apply the or_eq example, then the xor_eq example. What is the value after each line?

**Check:** After storing the inclusive OR with 4, flags is 6. After exclusive OR with 1, flags is 7. Write the values as small groups of binary digits if two bits seem to represent one position.

## Apply it to an Umicom project

Create a two-state flag exercise in Umicom Studio for a synthetic Bank import screen. Plot the original bits and result in separate columns so another learner can trace each operation.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/08-alternative-operator-tokens.html)

[Course contents](index.md) · [Previous lesson — Read modules, coroutines and reserved words](07-module-and-coroutine-spellings.md) · [Continue with Learning C++](../../../courses/learning-cpp/index.html)
