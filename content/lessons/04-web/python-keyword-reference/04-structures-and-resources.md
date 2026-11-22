<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/04-structures-and-resources.md

PURPOSE:
Use names from other modules and ask the language to manage a short-lived resource.

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

# Classes, imports, and resources

[Course contents](index.md) · [Previous · Functions, results, and where names belong](03-functions-and-names.md) · [Next · Recognise and handle an error](05-find-and-handle-errors.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/04-structures-and-resources.html)

Use names from other modules and ask the language to manage a short-lived resource.

## Before you try a word

A module is a collection of Python definitions. A class gives related data and operations their own type. A context manager defines actions when entering and leaving a block, often to release a resource.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### class

Define a class. The example stores a value on the class itself.

```python
class Receipt:
    unit = "cents"

print(Receipt.unit)
```

Expected output

```text
cents
```

### import

Make a module available under a name in this file.

```python
import math
print(math.isqrt(81))
```

Expected output

```text
9
```

### from

Select a named item from a module in an import statement.

```python
from math import isqrt
print(isqrt(49))
```

Expected output

```text
7
```

### as

Give an imported object or another supported binding a local name.

```python
import math as arithmetic
print(arithmetic.isqrt(16))
```

Expected output

```text
4
```

### with

Enter and leave a managed context. Here the stream closes when leaving the indented block.

```python
from io import StringIO

with StringIO("receipt") as source:
    print(source.read())
print(source.closed)
```

Expected output

```text
receipt
True
```

## Compare the meaning in another language

C has preprocessor includes and explicit resource release. Python source can import modules and use a context manager. The shared design question is who owns the resource and when ownership ends.

## Try it

Change the in-memory stream text to club. The first output line is club and the second line still says True.

## Apply it to Umicom

Write down who closes a file or frees a buffer when adding a native Framework document importer.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Functions, results, and where names belong](03-functions-and-names.md) · [Next · Recognise and handle an error](05-find-and-handle-errors.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/04-structures-and-resources.html)
