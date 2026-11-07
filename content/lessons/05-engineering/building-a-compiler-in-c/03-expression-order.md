# Give expressions an unambiguous meaning

A **parser** checks how tokens fit together. A **grammar** is the set of rules defining valid combinations. The parser in `src/compiler.c` accepts one function containing one return expression. It is intentionally smaller than the grammar of the C implementation used to build the compiler itself.

## Why order needs a rule

For `2 + 3 * 4`, multiplying first gives 14. Adding first gives 20. The language must choose one meaning. Umicom C gives multiplication and division higher **precedence**, meaning they bind more tightly than addition and subtraction. Parentheses allow the author to choose a different grouping: `(2 + 3) * 4` returns 20.

| Function | Responsibility |
| --- | --- |
| unary | Numbers, leading plus/minus, parenthesised expressions |
| product | Multiplication and division |
| expression | Addition and subtraction |

`expression` asks `product` to finish each more tightly grouped part before emitting an ADD or SUBTRACT instruction. A leading minus is **unary**: it acts on one value, as in `-7`. Subtraction acts on two values, as in `9 - 7`.

## Trace emitted instructions

```text
Source: 2 + 3 * 4
PUSH 2
PUSH 3
PUSH 4
MULTIPLY
ADD
RETURN
```

`PUSH` places a number on a stack, a last-in-first-out collection. MULTIPLY takes the most recent two numbers, produces 12, and puts that result back. ADD then combines 2 and 12. The compiler stores instructions directly in the caller's bounded output array; it does not build a full syntax-tree object for this small grammar.

## Repeated operators and parentheses

**Associativity** decides how operators of the same precedence group. `8 - 3 - 2` means `(8 - 3) - 2` and gives 3. The loops in `product` and `expression` implement this left-to-right grouping without one recursive call per operator.

Parentheses and unary operators do use recursion: a function asks another invocation to process a nested part. Nesting is limited by `UMC_PARSE_DEPTH_LIMIT`. The output also has an instruction limit. These limits are part of the contract, not permission to overwrite a buffer when a program is too large.

## Exercise

Write the instruction sequence for `(2 + 3) * 4`. Then explain why `return 2 + ;` cannot be accepted.

<details>

<summary>Explanation</summary>

The sequence is PUSH 2, PUSH 3, ADD, PUSH 4, MULTIPLY, RETURN. The invalid expression is missing a value after plus. The semicolon ends a statement; it cannot stand in for a value. On failure, the compiler reports zero usable instructions, even if it wrote some partial instructions before discovering the error.

</details>

## Find the implementation

Open `umicom-c/src/compiler.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/03-expression-order.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Read one token at a time](02-reading-tokens.md)

[Next: Execute instructions with checked arithmetic](04-checked-execution.md)
