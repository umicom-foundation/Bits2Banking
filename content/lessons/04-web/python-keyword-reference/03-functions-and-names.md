<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/03-functions-and-names.md

PURPOSE:
Define procedures, return results and see which part of a program owns a name.

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

# Functions, results, and where names belong

[Course contents](index.md) · [Previous · Choices and repetition](02-choices-and-repetition.md) · [Next · Classes, imports, and resources](04-structures-and-resources.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/03-functions-and-names.html)

Define procedures, return results and see which part of a program owns a name.

## Before you try a word

A function groups steps under one name. Scope is the region where a name can be used. Have a caller supply an input and receive a result before experimenting with shared state.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### def

Create a named function.

```python
def show_count():
    print(3)

show_count()
```

Expected output

```text
3
```

### return

Stop the current function call and send a value to its caller.

```python
def double(count):
    return count + count

print(double(3))
```

Expected output

```text
6
```

### lambda

Make a small function from one expression.

```python
amounts = [[7, "a"], [3, "b"]]
print(sorted(amounts, key=lambda row: row[0])[0][1])
```

Expected output

```text
b
```

### global

Tell an inner block that assignment should bind a module-level name.

```python
count = 2

def reset():
    global count
    count = 0

reset()
print(count)
```

Expected output

```text
0
```

### nonlocal

Assign to a name that already exists in an enclosing function.

```python
def outer():
    count = 2
    def reset():
        nonlocal count
        count = 0
    reset()
    return count

print(outer())
```

Expected output

```text
0
```

### del

Delete a binding or remove an element from a collection. Other references may still keep the object alive.

```python
rows = [2, 4]
del rows[0]
print(rows)
```

Expected output

```text
[4]
```

### yield

Produce one value and pause a generator function until the caller asks for another value.

```python
def labels():
    yield "first"
    yield "second"

print(list(labels()))
```

Expected output

```text
['first', 'second']
```

## Compare the meaning in another language

C, Go and Python share `return`. Python uses `def` to define a named function. Go uses `func`, and C writes the result type at the start of the declaration. A generator supplies values over successive requests.

## Try it

Pass 8 to double. The result is 16. Decide whether the function needs to know which screen will display it.

## Apply it to Umicom

Define one reproducible calculation before displaying it in Umicom Studio IDE or calling it through Framework. A tiny function with explicit inputs is easy to qualify.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Choices and repetition](02-choices-and-repetition.md) · [Next · Classes, imports, and resources](04-structures-and-resources.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/03-functions-and-names.html)
