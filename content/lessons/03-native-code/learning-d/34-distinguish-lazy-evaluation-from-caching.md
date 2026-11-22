<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/34-distinguish-lazy-evaluation-from-caching.md

PURPOSE:
Distinguish lazy evaluation from caching

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish lazy evaluation from caching

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `lazy_evaluation.d` in `labs/languages/native-language-boundary` in the course checkout. Prepare three rows for the eager, deferred and cached examples. Record how many times you expect each to call the counted function.

## Start with an observable operation

A normal function call generally obtains the values of its ordinary arguments before the function body uses its parameters. D can also declare a lazy parameter. That parameter represents deferred work: the caller’s expression can be evaluated when the function reads the parameter. The important question is how many reads occur. Lazy does not automatically mean “run once and remember the answer.” It also does not mean “run on a background thread.” We will count evaluations using a tiny function that increments an integer and returns its new value.


## Read the counter function

The function nextValue takes a ref int. ref means the parameter refers to the caller’s integer storage rather than an independent value. The prefix ++ increments the integer. Returning calls gives the new number to the caller. Starting at zero, successive calls return one, two and three. This deliberate side effect makes repeated evaluation visible. It is a teaching device: unnecessary hidden side effects make real deferred computations harder to reason about.

~~~d
int nextValue(ref int calls)
{
    ++calls;
    return calls;
}
~~~


## Define three consumers of deferred work

Each consumer declares lazy int candidate. The argument expression is not evaluated merely to enter the function. ignoreCandidate never reads candidate, so the expression is never evaluated. readTwice stores candidate into two local constants in separate statements, causing two evaluations. snapshotOnce reads it into one local constant and then uses that stored value twice. const makes that local value read-only; it does not cause the expression to run again. The separate statements in readTwice make the observation sequence clear without relying on the evaluation order of two operands in one addition.

~~~d
int ignoreCandidate(lazy int candidate)
{
    return 40;
}
int readTwice(lazy int candidate)
{
    const int first = candidate;
    const int second = candidate;
    return first + second;
}
int snapshotOnce(lazy int candidate)
{
    const int value = candidate;
    return value + value;
}
~~~



## Work through the calls by hand

Begin with calls equal to zero. ignoreCandidate(nextValue(calls)) returns 40 without using its argument, so calls stays zero. Next, readTwice receives the same expression. The first access increments calls to one and produces one. The second access increments it to two and produces two. The sum is three. Reset calls to zero before the last experiment. snapshotOnce evaluates nextValue once, stores one, then returns one plus one. Its result is two and the counter is one.

| Consumer | Evaluations | Returned value | Final counter |
| --- | --- | --- | --- |
| ignoreCandidate | 0 | 40 | 0 |
| readTwice | 2 | 3 | 2 |
| snapshotOnce after reset | 1 | 2 | 1 |

## Separate deferral, caching and concurrency

Deferral means postponing work until it is needed. Caching means retaining a computed result for later reuse. Concurrency means overlapping activities, for example through multiple tasks or threads. The lazy keyword alone promises neither caching nor concurrency. A deferred expression that reads the current time may produce a different value on each use. One that opens a file may do that work repeatedly. If a computation must run once, decide explicitly where its result is stored and how long that storage lives. Our snapshotOnce function stores one integer for the duration of its call; it is not a global cache.


## Build and run with unit tests

Use the open-source D compiler installed in the earlier setup lesson. The commands below use DMD syntax; use that compiler’s documented equivalents if you selected LDC or GDC. -unittest includes the unittest block, while -checkaction=context helps explain failed assertions. Leave release-mode assertion removal off during these exercises. A compiler warning about an intentionally unused lazy parameter should be understood from ignoreCandidate’s purpose, rather than suppressed globally. The source is a normal D program, not a BetterC example: it imports std.stdio for output.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
New-Item -ItemType Directory -Force build/learning-languages | Out-Null
dmd -unittest -checkaction=context -of=build/learning-languages/lazy-evaluation.exe labs/languages/native-language-boundary/lazy_evaluation.d
& ".\build\learning-languages\lazy-evaluation.exe"
$LASTEXITCODE
~~~


## Read the expected observations

The unittest block and main both check the arithmetic and the number of evaluations. A successful run prints the three lines below and returns normally. If the compiler is unavailable, keep the example labelled uncompiled; reading expected output is not execution. If an assertion fails, compare the counter reset and the number of accesses to candidate before changing the expected values. Adding a debug print that reads candidate is itself another evaluation and can change the experiment.

~~~text
ignored: result=40 evaluations=0
repeated: result=3 evaluations=2
snapshot: result=2 evaluations=1
~~~

1. Add a third separate read inside readTwice, rename the function for that exercise, and predict both the result and final counter.
2. Replace nextValue(calls) with the constant expression 7. Explain why equal results no longer reveal how many evaluations occurred.
3. Move the read in snapshotOnce below a conditional return. Predict a path with zero evaluations and a path with one.
4. Describe why measuring elapsed time alone is a weaker test of evaluation count than this explicit counter.


## Apply the lesson without changing Framework’s language boundary

Deferred work can be useful for optional diagnostics or calculations whose result is needed only on one branch. It is dangerous to assume that deferral automatically reduces memory or makes a computation thread-safe. In a native C API, similar choices are usually explicit: pass a computed value, or pass a callback function and a separate context with documented lifetime and call-count rules. A D lazy parameter is a D language contract, not a portable C parameter type. Do not place it directly into an extern(C) interface. Keep Framework services in C and write a thin, reviewed D adapter when a D application needs them.


## Further reading

- [D language specification: lazy parameters](https://dlang.org/spec/function.html#lazy-parameters)

[Previous: Admit enumerated states before exhaustive dispatch](33-admit-enumerated-states-before-dispatch.md)

[Next: Separate invariants from input validation](35-separate-invariants-from-input-validation.md)
