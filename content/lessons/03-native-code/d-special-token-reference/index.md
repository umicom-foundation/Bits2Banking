<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-special-token-reference/index.md

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

# D Special Tokens for Beginners

Read the extra pieces the D compiler recognises when it scans your source. Use them to interpret a build or find a line in a diagnostic.

This course covers all six D special tokens and the #line special token sequence in the published lexical specification. It also illustrates the six related special keywords defined by the expressions specification. The ordinary reserved words have their own concept map in Learning D.

A keyword is a word that the language grammar reserves for a specific job. A value name such as `cents` is a name you choose. Syntax describes where the pieces can go. Meaning describes what happens when the program runs.

Begin by reading the example aloud. To run it, save the full code to a plain text file named practice.d and open a terminal in the folder that contains it.

## Follow the lessons

1. [Read the date and time of a build](01-read-build-time.md) Use three D special tokens to learn which information is chosen when the compiler reads a program.
1. [Record which compiler read a program](02-record-compiler-identity.md) Separate a compiler's vendor name and encoded version from the version of your teaching example.
1. [Stop reading source at an explicit marker](03-stop-reading-at-a-marker.md) Compare an end-of-source marker with the return statement in a tiny D program.
1. [Map a diagnostic back to source](04-map-a-diagnostic-back-to-source.md) Label the next generated source line and use the reported location to find the teaching example.

## Find a token or keyword

- [`__DATE__`](../../../courses/d-special-token-reference/lessons/01-read-build-time.html#kw-__DATE__)
- [`__EOF__`](../../../courses/d-special-token-reference/lessons/03-stop-reading-at-a-marker.html#kw-__EOF__)
- [`__FILE__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__FILE__)
- [`__FILE_FULL_PATH__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__FILE_FULL_PATH__)
- [`__FUNCTION__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__FUNCTION__)
- [`__LINE__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__LINE__)
- [`__MODULE__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__MODULE__)
- [`__PRETTY_FUNCTION__`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-__PRETTY_FUNCTION__)
- [`__TIME__`](../../../courses/d-special-token-reference/lessons/01-read-build-time.html#kw-__TIME__)
- [`__TIMESTAMP__`](../../../courses/d-special-token-reference/lessons/01-read-build-time.html#kw-__TIMESTAMP__)
- [`__VENDOR__`](../../../courses/d-special-token-reference/lessons/02-record-compiler-identity.html#kw-__VENDOR__)
- [`__VERSION__`](../../../courses/d-special-token-reference/lessons/02-record-compiler-identity.html#kw-__VERSION__)
- [`#line`](../../../courses/d-special-token-reference/lessons/04-map-a-diagnostic-back-to-source.html#kw-hash-line)

## Apply the course

Practise with a fictional source name before applying these ideas to Umicom Studio compiler diagnostics. Treat the compiler message and source mapping as evidence of where to look, then open the actual source and compare.

- [Start with Introduction to Programming](../../../courses/introduction-to-programming/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [Build a Compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Follow the connected learning paths](../../../start/connected-learning.md)
- [Explore the full D keyword inventory](../../../courses/d-keyword-reference/index.html)
- [C23 Keywords for Beginners](../../../courses/c23-keyword-reference/index.html)
- [Go Keywords for Beginners](../../../courses/go-keyword-reference/index.html)
- [Python Keywords for Beginners](../../../courses/python-keyword-reference/index.html)

## Language references

- [D language specification, Special Tokens](https://dlang.org/spec/lex.html#specialtokens)
- [D language specification, Lexical grammar and Special Token Sequences](https://dlang.org/spec/lex.html)
- [D language specification, Expressions and Special Keywords](https://dlang.org/spec/expression.html)
