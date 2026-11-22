<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/05-find-and-handle-errors.md

PURPOSE:
Observe a failed action and write the next step explicitly.

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

# Recognise and handle an error

[Course contents](index.md) · [Previous · Classes, imports, and resources](04-structures-and-resources.md) · [Next · Wait for a result with async and await](06-wait-for-work.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/05-find-and-handle-errors.html)

Observe a failed action and write the next step explicitly.

## Before you try a word

An exception records an unusual event during execution. When code handles an exception, it chooses what to do after the failed operation. An assertion records an expected internal condition for checking.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### assert

Check an internal expectation during a normal run. Optimised Python can omit this statement, so use an explicit check for user input.

```python
assert 2 + 3 == 5
print("checked")
```

Expected output

```text
checked
```

### try

Mark the statements that may produce an exception you want to handle or clean up after.

```python
try:
    print(int("12"))
except ValueError:
    print("invalid")
```

Expected output

```text
12
```

### except

Run a matching handler when the try block raises a selected exception type.

```python
try:
    print(int("bad"))
except ValueError:
    print("invalid")
```

Expected output

```text
invalid
```

### finally

Run cleanup when leaving a try statement, including after an exception path.

```python
try:
    print("work")
finally:
    print("cleanup")
```

Expected output

```text
work
cleanup
```

### raise

Create an exception path explicitly. A caller or enclosing handler can observe it.

```python
try:
    raise ValueError("negative receipt")
except ValueError as problem:
    print(problem)
```

Expected output

```text
negative receipt
```

## Compare the meaning in another language

A native C function often returns a status code to tell the caller whether work succeeded. Python can raise or catch exceptions. Both designs need a test that checks the failure path and the resulting state.

## Try it

Change "bad" to "17" in the except example. Its output becomes 17 and the handler does not run.

## Apply it to Umicom

Plan a Umicom Automated Testing exercise where a malformed receipt has a clear error message and the next report still works.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Classes, imports, and resources](04-structures-and-resources.md) · [Next · Wait for a result with async and await](06-wait-for-work.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/05-find-and-handle-errors.html)
