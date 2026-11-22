<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/45-separate-local-static-storage-from-caller-ownership.md

PURPOSE:
Separate local static storage from caller ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate local static storage from caller ownership

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `local_storage.d` in `labs/languages/native-language-boundary` in the course checkout. Draw three storage lifetimes for automatic, local static and caller-owned state. Trace two calls and mark which values should carry over.

## A local name does not describe the whole lifetime

A function's local name can refer to fresh automatic storage or retained static storage. D adds another distinction: ordinary mutable static variables are thread-local by default. Thread-local means each thread has its own copy. This lesson uses one thread to trace the difference between a new counter on each call, a retained counter and explicitly supplied owner state. No filesystem persistence or background work is involved.


## Read the small record and update

~~~d
struct Counter { uint value; }

bool nextOwned(ref Counter state, ref uint outputValue) @safe nothrow @nogc
{
    if (state.value >= 3) return false;
    uint candidate = state.value + 1;
    state.value = candidate;
    outputValue = candidate;
    return true;
}
~~~


## Understand the declaration


| Spelling | Meaning here |
| --- | --- |
| struct Counter | A value record with one uint field. |
| uint | A 32-bit unsigned integer in D. |
| ref | Refer to an existing caller variable instead of receiving an independent value copy. |
| bool | Return true for an admitted update or false for a refusal. |
| @safe | Ask D's compiler to enforce its safe-language restrictions within this function. |
| nothrow | The function cannot propagate an ordinary D Exception; this is not a guarantee against every possible failure. |
| @nogc | The function cannot perform D garbage-collector allocation. This alone is not a claim of zero memory use or an application-wide no-allocation policy. |


## Why the output parameter uses ref

An out parameter is initialized on entry. That would not match this exercise's requirement to preserve a caller's sentinel when admission fails. ref lets the caller retain the prior value unless the function performs an assignment. The source checks the small cap before adding or writing either output. D's function attributes do not replace this business rule. A memory-safe function can still implement the wrong policy.


## Fresh automatic state

~~~d
bool nextAutomatic(ref uint outputValue) @safe nothrow @nogc
{
    Counter state;
    return nextOwned(state, outputValue);
}
~~~


## Trace two calls

Counter's uint field receives its default zero initialization. Each invocation creates a fresh automatic state. nextOwned increments that call's value to one. After the function returns, that automatic counter is no longer available. A second call starts another zero-valued counter. The caller therefore sees 1, 1. You must not return a reference to this automatic local and expect it to remain alive.


## Retained state in the current thread

~~~d
bool nextHidden(ref uint outputValue) @safe nothrow @nogc
{
    static Counter state;
    return nextOwned(state, outputValue);
}
~~~


## Trace the retained value

The local name state remains hidden outside the function, but its storage persists between calls on this thread. The first call sees zero and returns one; the second sees one and returns two. Two different callers on the same thread still reach that same retained state. A new thread normally has its own mutable static instance. Do not assume D's default is identical to a C static local, and do not bypass ownership by adding __gshared merely to make code compile. Shared mutation needs its own synchronization design.


## Explicit ownership makes independent state visible


| Call | Left owner | Right owner | Meaning |
| --- | --- | --- | --- |
| Create both | 0 | 0 | Two independent Counter values. |
| nextOwned(left, a) | 1 | 0 | Only left advances. |
| nextOwned(right, b) | 1 | 1 | Right begins its own sequence. |
| nextOwned(left, a) | 2 | 1 | Left resumes from its retained caller-owned value. |
| Advance left to cap | 3 | 1 | The small teaching limit is now reached. |
| Try left with output 99 | 3 | 1 | False; output remains 99. |


## Build and run the complete program

1. Open labs/languages/native-language-boundary and inspect local_storage.d. It contains the record, all three functions, owner checks, a unittest block and main.
2. Confirm the selected compiler with Get-Command dmd and dmd --version. Follow the setup lesson if it is not installed.
3. Use the commands below. The active example uses an ordinary require function that throws on a false condition; its operations and checks remain active even if assertions are disabled. The initial assertion-based variant is retained in a disabled version block for review.
4. The unittest checks explicit owner state. main demonstrates the automatic and retained counters once, then checks explicit owners again.
5. Run the executable a second time. Each execution starts a new process and reproduces the same output. A static variable is not a saved database value.


## Commands and expected output

~~~powershell
dmd -unittest -g -of=local_storage-d.exe local_storage.d
.\local_storage-d.exe
~~~

~~~text
Automatic calls: 1, 1
Static calls: 1, 2
Owned counters: left 3, right 1; refusal preserved 99
~~~


## Do not hide application identity in a function

Imagine two open Studio documents asking a helper for their next progress number. A hidden static counter on the UI thread can mix their sequences even if the variable name is local and its access is memory-safe. Passing a document-owned record makes the identity explicit. The same reasoning applies to Media job progress, Trader connection state and reusable SDK clients. Framework already provides shared native ownership services; a language lesson does not authorize duplicating those services in each application.


## Reflection can describe declarations, not prove lifecycle intent

Earlier lessons inspected fields and attributes at compile time. Such information can help generate checks or describe an API, but it does not decide which window, request or document should own a mutable value. A reflected type name is not a lifetime plan. Review the actual storage declaration, caller identity and synchronization contract. This example deliberately uses plain C-compatible numeric state instead of suggesting that reflection automatically fixes state sharing.


## Separate this lesson from concurrency

This program starts no threads. The C and FreeBASIC companion programs also run in one thread. Their matching single-thread outputs do not prove identical thread behavior. C's ordinary static local is shared across threads, while D's mutable static is thread-local by default. Thread-local state can still couple callers within one thread; it also cannot replace synchronization for an explicitly shared object. Keep thread lifetime and shared access as separate exercises.


## Exercises

1. Add a third retained call in main and predict output three. Set an output to 99 and try a fourth: expect false and unchanged 99.
2. Interleave updates to three explicit Counter objects. Draw one row per call and track each owner's value.
3. Explain why changing ref outputValue to out would violate the refusal-preserves-output requirement.
4. Explain why @safe and @nogc do not prove that two documents have independent counters.
5. Point to the difference between scope, storage lifetime and process persistence in each of the three functions.


## Qualification

The complete D source is an authored teaching example until run with the selected D compiler. Its C comparison is a separately built native program and cannot establish a D compiler or runtime result. The laboratory README explains the optional C CMake target and the other language commands. An installed Framework package, multithreaded integration and product UI behavior require their own checks.


## Further reading


- [D attributes and static storage](https://dlang.org/spec/attribute.html)
- [D declaration storage classes](https://dlang.org/spec/declaration.html)
- [D thread-local storage tour](https://tour.dlang.org/tour/en/multithreading/thread-local-storage)
- [D function attributes and parameter rules](https://dlang.org/spec/function.html)


[Previous: Distinguish conditional selection from argument evaluation](44-distinguish-conditional-selection-from-argument-evaluation.md)

[Next: Separate runtime dispatch from type reflection](46-separate-runtime-dispatch-from-type-reflection.md)
