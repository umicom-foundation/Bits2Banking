<!--
Umicom Bits2Banking
File: content/lessons/04-web/python-keyword-reference/06-wait-for-work.md

PURPOSE:
Read a small asynchronous program and distinguish waiting from starting a new thread.

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

# Wait for a result with async and await

[Course contents](index.md) · [Previous · Recognise and handle an error](05-find-and-handle-errors.md) · [Next · Words that depend on context](07-understand-contextual-keywords.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/06-wait-for-work.html)

Read a small asynchronous program and distinguish waiting from starting a new thread.

## Before you try a word

A coroutine can pause and later resume. An event loop coordinates such tasks. Awaiting a coroutine can give other ready work a turn when the awaited operation pauses. Creating a coroutine alone does not start another thread.

Each fragment is self-contained. Copy one highlighted fragment to a fresh file named `receipt.py`, open a terminal in that folder and run `python receipt.py`. This reference uses Python 3.14. Start by predicting the result on paper if you have no interpreter.

## Reserved word examples

### async

Use async def to define a coroutine function. Running the coroutine through asyncio starts this example.

```python
import asyncio

async def receipt():
    return 9

print(asyncio.run(receipt()))
```

Expected output

```text
9
```

### await

Wait for the result of an awaitable from inside an asynchronous function.

```python
import asyncio

async def receipt():
    return 9

async def main():
    amount = await receipt()
    print(amount)

asyncio.run(main())
```

Expected output

```text
9
```

## Compare the meaning in another language

Python async and await are reserved words. Go has a separate `go` statement that starts a goroutine, and C23 has library and platform APIs for threads. A program can also wait for a result without using multiple CPU cores.

## Try it

Change the receipt result to 21. The await example should show 21 when main receives the result.

## Apply it to Umicom

Think through how a synthetic Framework task would report completion to a Studio or LLM interface. The example runs entirely on the local machine.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [Learning Python](../../../courses/learning-python/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python 3.14 lexical reference](https://docs.python.org/3.14/reference/lexical_analysis.html#keywords)
- [Python 3.14 simple statements](https://docs.python.org/3.14/reference/simple_stmts.html)
- [Python 3.14 compound statements](https://docs.python.org/3.14/reference/compound_stmts.html)

[Course contents](index.md) · [Previous · Recognise and handle an error](05-find-and-handle-errors.md) · [Next · Words that depend on context](07-understand-contextual-keywords.md) · [Browser edition](../../../courses/python-keyword-reference/lessons/06-wait-for-work.html)
