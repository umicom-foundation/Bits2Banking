<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/01-values-and-questions.md

PURPOSE:
Use the reserved words for logical values, an absent value, and questions about other values.

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

# Values and yes-or-no questions

[Course contents](index.md) · [Next · Choices and repetition](02-choices-and-repetition.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/01-values-and-questions.html)

Use the reserved words for logical values, an absent value, and questions about other values.

## Before you try a word

A Boolean is a value that represents a yes-or-no answer. A membership question asks whether a collection contains something. An identity question asks whether both names refer to the very same object.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### True

The Boolean value for yes.

```python
ready = True
print(ready)
```

Expected output

```text
True
```

### False

The Boolean value for no.

```python
pending = False
print(pending)
```

Expected output

```text
False
```

### None

The singleton often used to represent an absent result.

```python
note = None
print(note)
```

Expected output

```text
None
```

### and

Evaluate the right operand only when the left operand is truthy. The expression returns an operand.

```python
print((2 < 5) and (8 < 6))
```

Expected output

```text
False
```

### or

Evaluate the right operand only when the left operand is falsey. The expression returns an operand.

```python
print((2 > 5) or (8 > 6))
```

Expected output

```text
True
```

### not

Reverse the truth value of a question.

```python
print(not (2 == 5))
```

Expected output

```text
True
```

### is

Ask whether two values are the same object. Use it for a sentinel such as None.

```python
missing = None
print(missing is None)
```

Expected output

```text
True
```

### in

Ask whether a value belongs to a collection. The for statement also uses this spelling.

```python
print(25 in [10, 25, 40])
```

Expected output

```text
True
```

## Compare the meaning in another language

C uses `&&`, `||` and `!` for logical expressions. Python spells them `and`, `or` and `not`. Use `==` for Python value equality and `is` when you actually mean object identity.

## Try it

Try changing 25 to 30 in the last example. It shows False because the list contains 10, 25 and 40.

## Apply it to Umicom

Write a test for a synthetic Bank receipt that is either absent or present. Keep an absent amount separate from the legitimate amount zero.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Next · Choices and repetition](02-choices-and-repetition.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/01-values-and-questions.html)
