<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/08-read-tokens-and-blocks.md

PURPOSE:
Distinguish the parts of a Python statement using a tiny receipt calculation.

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

# Read tokens, expressions, and blocks

[Course contents](index.md) · [Previous · Words that depend on context](07-understand-contextual-keywords.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/08-read-tokens-and-blocks.html)

Distinguish the parts of a Python statement using a tiny receipt calculation.

## Notice the pieces

A token is a small piece that the language scanner recognises. For example, `if` is a keyword, `total_cents` is an identifier, `>=` is an operator, `250` is an integer literal and `:` is punctuation. A literal writes a value directly. An operator performs an action or comparison.

```python
total_cents = 100 + 150
if total_cents >= 250:
    print("ready")
else:
    print("collect more")
```

## What this program does

The first line adds two amounts. The names `total_cents` and `print` are identifiers. The first expression stores 250. The second line asks whether the amount is at least 250. It is, so the first indented block displays ready.

## Use common forms

- `"receipt"` is a string literal. `[100, 150]` is a list expression, and `amounts[0]` gets its first value.
- `# training data` begins a comment outside a string. The text after it explains the program.
- `a = 3` binds a name. `a == 3` asks a question. Reading the two spellings carefully prevents mistakes.
- `9 // 2` gives 4 using floor division on these integers. For −9 and 2 it gives −5, while C integer division truncates toward zero.
- `print` and `int` are built-in identifiers. They can be rebound, which is usually confusing in a first program.

## Try it

Change 150 to 140 and trace the result. The sum is 240. The program then displays collect more.

When a syntax error points to the next line, inspect the line above it for a missing colon or closing parenthesis. Return to the paper trace before changing the logic.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Words that depend on context](07-understand-contextual-keywords.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/08-read-tokens-and-blocks.html)
