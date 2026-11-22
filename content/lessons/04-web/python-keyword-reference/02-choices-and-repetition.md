<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/02-choices-and-repetition.md

PURPOSE:
Use a colon and indentation to choose a path or repeat an action.

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

# Choices and repetition

[Course contents](index.md) · [Previous · Values and yes-or-no questions](01-values-and-questions.md) · [Next · Functions, results, and where names belong](03-functions-and-names.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/02-choices-and-repetition.html)

Use a colon and indentation to choose a path or repeat an action.

## Before you try a word

Start a block after a colon and indent each line of the block by the same amount. Four spaces is the usual style. The examples use short, finite loops that are easy to trace on paper.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### if

Run a block when its question is true.

```python
if 30 > 20:
    print("over")
```

Expected output

```text
over
```

### elif

Try a second question after an earlier condition failed.

```python
amount = 20
if amount > 20:
    print("over")
elif amount == 20:
    print("exact")
```

Expected output

```text
exact
```

### else

In this decision, handle the case where no earlier question matched.

```python
if 4 == 5:
    print("same")
else:
    print("different")
```

Expected output

```text
different
```

### for

Visit the values supplied by an iterable in order.

```python
for cents in [2, 4]:
    print(cents)
```

Expected output

```text
2
4
```

### while

Retest a condition before each pass through a block.

```python
left = 2
while left > 0:
    print(left)
    left -= 1
```

Expected output

```text
2
1
```

### break

Finish the nearest loop early.

```python
for cents in [2, 0, 4]:
    if cents == 0:
        break
    print(cents)
```

Expected output

```text
2
```

### continue

Finish the current pass and let the loop attempt another one.

```python
for cents in [2, 0, 4]:
    if cents == 0:
        continue
    print(cents)
```

Expected output

```text
2
4
```

### pass

Fill a required block with a statement that does nothing.

```python
if 8 > 2:
    pass
print("done")
```

Expected output

```text
done
```

## Compare the meaning in another language

C and Go both allow an explicit counter with a separate update in the loop header. A Python for loop instead follows successive values from an iterable. Python also supports `else` on a loop, with the else block skipped when the loop exits through break.

## Try it

Put 4 before the zero in the break example. Predict the output before running it. The first two lines are 2 and 4.

## Apply it to Umicom

Trace whether a synthetic Trader import skips a blank line or ends its whole report. Those are different acceptance tests.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Values and yes-or-no questions](01-values-and-questions.md) · [Next · Functions, results, and where names belong](03-functions-and-names.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/02-choices-and-repetition.html)
