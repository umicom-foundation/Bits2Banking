<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/01-enter-return-and-name-integers.md

PURPOSE:
Meet int, main, void, return, and const in a small practice receipt.

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

# Enter the program and return a whole number

[Course contents](index.md) · [Next · Choose with if, else, true, and false](02-choose-with-if-and-literals.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/01-enter-return-and-name-integers.html)

Meet int, main, void, return, and const in a small practice receipt.

## Read the whole program

```c
int main(void)
{
    const int starting_cents = 200;
    int extra_cents = 50;
    return starting_cents + extra_cents;
}
```

- `int` introduces a checked integer result or local whole-number amount in this profile.
- `main` names the no-input entry of the standalone integer profile. The lexer assigns the exact spelling a dedicated token.
- `void` inside `main(void)` says there are no inputs.
- `const` makes the initialized `starting_cents` name read-only. A later assignment to it is rejected.
- `return` gives the program result to its caller. The profile expects a final return.

## Read its punctuation

The parentheses surround the input list. The braces surround the body. A semicolon ends a declaration and the return. A name such as `extra_cents` is an identifier chosen by the author. A literal such as `200` writes a value directly.

## Try it

Save the exact example as `entry-and-units.uc`. Use the run command for source shown by your compiler help. Expect the result 250. Change 50 to 25 and predict 225. If Windows reports that the command is missing, use the absolute path to your Umicom C executable.

In C23, your tools can accept other entry forms and types. This checked integer profile expects the form shown here. Use the unit in a small Studio project and write the expected result before running the language tool.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Native statement calculations](../../../courses/native-statement-calculations/index.html)
- [Building a compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Published Umicom C language guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Next · Choose with if, else, true, and false](02-choose-with-if-and-literals.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/01-enter-return-and-name-integers.html)
