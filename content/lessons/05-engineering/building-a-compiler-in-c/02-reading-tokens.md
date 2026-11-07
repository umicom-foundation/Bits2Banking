# Read one token at a time

A **lexer** reads characters and recognises tokens. It does not yet decide how arithmetic should be grouped. In Umicom C, `umc_lex_next` reads one token and moves a position forward through a borrowed span of source bytes.

## Understand a span

A byte is a small storage unit. For the ASCII text used in this example, each visible character occupies one byte. A span supplies both the address of the first byte and the number of bytes available. The lexer must use that number; it cannot assume there is another readable byte after the end.

```text
return 12 + 3;
```

| Text | Meaning |
| --- | --- |
| return | Keyword beginning a return statement |
| 12 | Integer value twelve |
| + | Addition operator |
| 3 | Integer value three |
| ; | Statement terminator |

Spaces separate words, but do not become arithmetic instructions. A **keyword** is a word with a meaning fixed by the language. This prototype recognises `int`, `main`, `void` and `return`; it rejects other names rather than pretending that variables are implemented.

## Follow number recognition

The lexer begins with one digit. To append another decimal digit, multiply the value by ten and add the digit. Reading `12` starts at 1 and computes `1 * 10 + 2`. Before doing that arithmetic, the implementation checks whether it would exceed the largest supported integer. A check performed only after signed overflow would be too late.

Read `value > (INT32_MAX - part) / 10` in `src/lexer.c`. `part` is the next digit. The comparison asks whether there is enough room for both multiplication and addition. An oversized literal produces `UMC_LITERAL_RANGE`.

## Comments also need boundaries

`//` starts a comment ending at a line break. `/*` starts a comment ending at `*/`. To inspect two adjacent characters, the lexer first checks that at least two bytes remain. A final slash in a file must not cause a read beyond the span. An unfinished block comment reports an error at its start.

Comments can change source positions without changing arithmetic. That is why instruction identity and diagnostic locations are separate in the comparison service. General C preprocessing, string literals and macro rules are not part of this prototype.

## Exercise and review

Compare `return 12;` and `return12;`. Then inspect the loop which consumes an identifier in the lexer.

<details>

<summary>Explanation</summary>

The first spelling contains the keyword and an integer. The second is one identifier named return12. Because that identifier is unsupported, the lexer reports an error. Splitting every recognised prefix into a keyword would accept unintended syntax.

</details>

Also try tracing `/* note */ 12` on paper: the comment is consumed, then the integer begins after it. The source offset must still refer to the original file, including the comment.

## Find the implementation

Open `umicom-c/src/lexer.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/02-reading-tokens.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: From source text to a result](01-source-and-execution.md)

[Next: Give expressions an unambiguous meaning](03-expression-order.md)
