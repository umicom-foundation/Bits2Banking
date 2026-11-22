<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/07-understand-contextual-keywords.md

PURPOSE:
Learn when match, case, the underscore and type have a special role in Python 3.14.

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

# Words that depend on context

[Course contents](index.md) · [Previous · Wait for a result with async and await](06-wait-for-work.md) · [Next · Read tokens, expressions, and blocks](08-read-tokens-and-blocks.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/07-understand-contextual-keywords.html)

Learn when match, case, the underscore and type have a special role in Python 3.14.

## Before you try a word

A soft keyword has a grammatical meaning in particular places. The same spelling can otherwise be used as a name. A pattern describes the shape or value a match statement should recognise.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Soft keyword examples

### match

Begin a pattern-matching statement when followed by a subject and case clauses.

```python
state = "open"
match state:
    case "open":
        print("show receipt")
```

Expected output

```text
show receipt
```

### case

Introduce a candidate pattern to test in a match statement.

```python
match 2:
    case 1:
        print("one")
    case 2:
        print("two")
```

Expected output

```text
two
```

### _

Match any subject without capturing it when used as a wildcard pattern.

```python
match "unknown":
    case "open":
        print("open")
    case _:
        print("other")
```

Expected output

```text
other
```

### type

Start a type-alias statement. This example is valid with Python 3.12 or later.

```python
type Cents = int
print(Cents.__name__)
```

Expected output

```text
Cents
```

## Compare the meaning in another language

Use `match = 9` to see the same spelling serve as an ordinary variable. C uses `switch` and `case` for integral selections. Python pattern matching also handles shapes and named parts of data.

## Try it

In the wildcard example, change the subject to "open". The output switches from other to open.

## Apply it to Umicom

Plan a short classification lesson for synthetic import statuses in Bank. Tell the reader what the screen should show for a known state and for an unexpected state.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Wait for a result with async and await](06-wait-for-work.md) · [Next · Read tokens, expressions, and blocks](08-read-tokens-and-blocks.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/07-understand-contextual-keywords.html)
