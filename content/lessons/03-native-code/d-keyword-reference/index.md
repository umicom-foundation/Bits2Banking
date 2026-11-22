<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/index.md

PURPOSE:
Introduce D reserved words through a complete grouped inventory and short examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# D Keywords for Beginners

Find each keyword in the D reference table and read a small example that explains its role.

This course covers the 111 spellings in the D lexical reference’s keyword table as published in November 2026. It includes the reserved macro spelling and the ten entries marked as historical. The separate special-token course covers the six replacement tokens and the #line form.

A keyword is a word that the language grammar reserves for a specific job. A value name such as `cents` is a name you choose. Syntax describes where the pieces can go. Meaning describes what happens when the program runs.

Begin by reading the example aloud. To run it, save the full code to a plain text file named practice.d and open a terminal in the folder that contains it.

## Follow the lessons

1. [Name values and choose D types](01-name-values-and-choose-types.md) Give a value a name and choose words that fit numbers, truth flags and text units.
1. [Choose, repeat and stop in D](02-choose-repeat-and-stop.md) Trace a decision and a loop over a short practice statement before reading the whole program.
1. [Pass values and describe function promises](03-pass-values-and-promises.md) Trace a call, then see what parameter words tell the person reading it.
1. [Group and protect related data](04-group-and-protect-data.md) Distinguish a structure, a union, a class and an interface using familiar parts of a statement.
1. [Organise source and name a boundary](05-organise-source-and-boundaries.md) Separate helpers from interfaces and recognise words that depend on a build or target.
1. [Ask the compiler about a type](06-ask-the-compiler-about-types.md) Use a short template, a compile-time assertion and keywords that report what the compiler sees.
1. [Handle a failure and plan shared work](07-handle-failures-and-shared-work.md) Read a deliberate classroom error, then see why shared state needs explicit coordination.
1. [Recognise reserved and historical D words](08-recognise-reserved-and-historical-words.md) Read an older source listing and choose a current teaching form for new code.

## Find a word

- [`__FILE__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__FILE__)
- [`__FILE_FULL_PATH__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__FILE_FULL_PATH__)
- [`__FUNCTION__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__FUNCTION__)
- [`__gshared`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-__gshared)
- [`__LINE__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__LINE__)
- [`__MODULE__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__MODULE__)
- [`__parameters`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__parameters)
- [`__PRETTY_FUNCTION__`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__PRETTY_FUNCTION__)
- [`__rvalue`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__rvalue)
- [`__traits`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__traits)
- [`__vector`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-__vector)
- [`abstract`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-abstract)
- [`alias`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-alias)
- [`align`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-align)
- [`asm`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-asm)
- [`assert`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-assert)
- [`auto`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-auto)
- [`body`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-body)
- [`bool`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-bool)
- [`break`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-break)
- [`byte`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-byte)
- [`case`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-case)
- [`cast`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-cast)
- [`catch`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-catch)
- [`cdouble`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-cdouble)
- [`cent`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-cent)
- [`cfloat`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-cfloat)
- [`char`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-char)
- [`class`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-class)
- [`const`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-const)
- [`continue`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-continue)
- [`creal`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-creal)
- [`dchar`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-dchar)
- [`debug`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-debug)
- [`default`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-default)
- [`delegate`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-delegate)
- [`delete`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-delete)
- [`deprecated`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-deprecated)
- [`do`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-do)
- [`double`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-double)
- [`else`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-else)
- [`enum`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-enum)
- [`export`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-export)
- [`extern`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-extern)
- [`false`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-false)
- [`final`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-final)
- [`finally`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-finally)
- [`float`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-float)
- [`for`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-for)
- [`foreach`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-foreach)
- [`foreach_reverse`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-foreach_reverse)
- [`function`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-function)
- [`goto`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-goto)
- [`idouble`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-idouble)
- [`if`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-if)
- [`ifloat`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-ifloat)
- [`immutable`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-immutable)
- [`import`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-import)
- [`in`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-in)
- [`inout`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-inout)
- [`int`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-int)
- [`interface`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-interface)
- [`invariant`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-invariant)
- [`ireal`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-ireal)
- [`is`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-is)
- [`lazy`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-lazy)
- [`long`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-long)
- [`macro`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-macro)
- [`mixin`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-mixin)
- [`module`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-module)
- [`new`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-new)
- [`nothrow`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-nothrow)
- [`null`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-null)
- [`out`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-out)
- [`override`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-override)
- [`package`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-package)
- [`pragma`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-pragma)
- [`private`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-private)
- [`protected`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-protected)
- [`public`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-public)
- [`pure`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-pure)
- [`real`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-real)
- [`ref`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-ref)
- [`return`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-return)
- [`scope`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-scope)
- [`shared`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-shared)
- [`short`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-short)
- [`static`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-static)
- [`struct`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-struct)
- [`super`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-super)
- [`switch`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-switch)
- [`synchronized`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-synchronized)
- [`template`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-template)
- [`this`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-this)
- [`throw`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-throw)
- [`true`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-true)
- [`try`](../../../courses/d-keyword-reference/lessons/07-handle-failures-and-shared-work.html#kw-try)
- [`typeid`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-typeid)
- [`typeof`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-typeof)
- [`ubyte`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-ubyte)
- [`ucent`](../../../courses/d-keyword-reference/lessons/08-recognise-reserved-and-historical-words.html#kw-ucent)
- [`uint`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-uint)
- [`ulong`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-ulong)
- [`union`](../../../courses/d-keyword-reference/lessons/04-group-and-protect-data.html#kw-union)
- [`unittest`](../../../courses/d-keyword-reference/lessons/06-ask-the-compiler-about-types.html#kw-unittest)
- [`ushort`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-ushort)
- [`version`](../../../courses/d-keyword-reference/lessons/05-organise-source-and-boundaries.html#kw-version)
- [`void`](../../../courses/d-keyword-reference/lessons/03-pass-values-and-promises.html#kw-void)
- [`wchar`](../../../courses/d-keyword-reference/lessons/01-name-values-and-choose-types.html#kw-wchar)
- [`while`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-while)
- [`with`](../../../courses/d-keyword-reference/lessons/02-choose-repeat-and-stop.html#kw-with)

## Apply the course

Start with an integer amount and a posted flag. Keep discarded entries visible when writing practice checks. Continue with the existing Learning D course, a compiler project or a studio exercise that records the full source location and diagnostic.

- [Start with Introduction to Programming](../../../courses/introduction-to-programming/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [Build a Compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Follow the connected learning paths](../../../start/connected-learning.md)
- [C23 Keywords for Beginners](../../../courses/c23-keyword-reference/index.html)
- [Go Keywords for Beginners](../../../courses/go-keyword-reference/index.html)
- [Python Keywords for Beginners](../../../courses/python-keyword-reference/index.html)
- [D Special Tokens for Beginners](../../../courses/d-special-token-reference/index.html)

## Language references

- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
- [D language specification, Expressions](https://dlang.org/spec/expression.html)
- [D language specification, Functions](https://dlang.org/spec/function.html)
