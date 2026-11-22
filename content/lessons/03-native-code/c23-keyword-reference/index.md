<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/c23-keyword-reference/index.md

PURPOSE:
Introduce C23 reserved words through a complete grouped inventory and short examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# C23 Keywords for Beginners

Learn how C uses reserved words to name values, repeat steps, group data and describe storage.

This reference covers all 54 primary keyword spellings and the five older alternate spellings listed in the C23 lexical grammar. Optional and reserved forms are identified alongside the basic language.

A keyword is a word that the language grammar reserves for a specific job. A value name such as `cents` is a name you choose. Syntax describes where the pieces can go. Meaning describes what happens when the program runs.

Paper and pencil are enough to start. To run a program, save it as a plain text file with the .c ending. The compiler translates the text, then the second command starts the saved executable in PowerShell.

## Follow the lessons

1. [Name values and choose their types](01-name-values-and-types.md) Read a first C declaration, then choose between whole numbers, truth values, characters and measurements.
1. [Choose an action and repeat it](02-choose-and-repeat.md) Make one decision, then repeat safe actions over a short list of pretend entries.
1. [Group data and return results](03-group-data-and-results.md) Read short functions, group related facts and distinguish a missing object from a real one.
1. [Control lifetime and access](04-control-lifetime-and-access.md) Tell apart where a name can be seen, how long data survives and which code can use it.
1. [Check types and representations](05-check-types-and-representations.md) Inspect memory requirements and types, then make a build reject a broken assumption.
1. [Read optional and older forms](06-read-optional-and-older-forms.md) Identify an optional feature, a reserved spelling or a compatibility spelling before you try to use it.

## Find a word

- [`_Alignas`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Alignas)
- [`_Alignof`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Alignof)
- [`_Atomic`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-_Atomic)
- [`_BitInt`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-_BitInt)
- [`_Bool`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Bool)
- [`_Complex`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Complex)
- [`_Decimal128`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Decimal128)
- [`_Decimal32`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Decimal32)
- [`_Decimal64`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Decimal64)
- [`_Generic`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-_Generic)
- [`_Imaginary`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Imaginary)
- [`_Noreturn`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Noreturn)
- [`_Static_assert`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Static_assert)
- [`_Thread_local`](../../../courses/c23-keyword-reference/lessons/06-read-optional-and-older-forms.html#kw-_Thread_local)
- [`alignas`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-alignas)
- [`alignof`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-alignof)
- [`auto`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-auto)
- [`bool`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-bool)
- [`break`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-break)
- [`case`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-case)
- [`char`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-char)
- [`const`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-const)
- [`constexpr`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-constexpr)
- [`continue`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-continue)
- [`default`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-default)
- [`do`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-do)
- [`double`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-double)
- [`else`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-else)
- [`enum`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-enum)
- [`extern`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-extern)
- [`false`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-false)
- [`float`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-float)
- [`for`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-for)
- [`goto`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-goto)
- [`if`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-if)
- [`inline`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-inline)
- [`int`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-int)
- [`long`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-long)
- [`nullptr`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-nullptr)
- [`register`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-register)
- [`restrict`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-restrict)
- [`return`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-return)
- [`short`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-short)
- [`signed`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-signed)
- [`sizeof`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-sizeof)
- [`static`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-static)
- [`static_assert`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-static_assert)
- [`struct`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-struct)
- [`switch`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-switch)
- [`thread_local`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-thread_local)
- [`true`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-true)
- [`typedef`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-typedef)
- [`typeof`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-typeof)
- [`typeof_unqual`](../../../courses/c23-keyword-reference/lessons/05-check-types-and-representations.html#kw-typeof_unqual)
- [`union`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-union)
- [`unsigned`](../../../courses/c23-keyword-reference/lessons/01-name-values-and-types.html#kw-unsigned)
- [`void`](../../../courses/c23-keyword-reference/lessons/03-group-data-and-results.html#kw-void)
- [`volatile`](../../../courses/c23-keyword-reference/lessons/04-control-lifetime-and-access.html#kw-volatile)
- [`while`](../../../courses/c23-keyword-reference/lessons/02-choose-and-repeat.html#kw-while)

## Apply the course

Use the same ways of naming values and checking assumptions when you study native statement code or build a compiler in C. Start with fictional amounts. Keep a note of which test checks each rule.

- [Start with Introduction to Programming](../../../courses/introduction-to-programming/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [Build a Compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Follow the connected learning paths](../../../start/connected-learning.md)
- [Explore D special tokens](../../../courses/d-special-token-reference/index.html)
- [Explore D keywords](../../../courses/d-keyword-reference/index.html)
- [Go Keywords for Beginners](../../../courses/go-keyword-reference/index.html)
- [Python Keywords for Beginners](../../../courses/python-keyword-reference/index.html)

## Language references

- [WG14 public draft N3220, section 6.4.1 and Annex A](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)
- [D lexical specification for comparison](https://dlang.org/spec/lex.html#specialtokens)
