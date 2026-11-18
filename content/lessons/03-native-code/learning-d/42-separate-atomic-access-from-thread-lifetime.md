<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/42-separate-atomic-access-from-thread-lifetime.md

PURPOSE:
Separate atomic access from thread lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate atomic access from thread lifetime

[Course contents](index.md)

## Two contracts, two different questions

A background worker raises at least two questions. How do simultaneous accesses to shared data remain correct? And when may the owner release the resources that the worker uses? Atomic operations can help with the first question; waiting for completion addresses the second. This lesson uses two native D threads and one small shared counter to keep the distinction visible. It does not implement a thread pool, model server or application job system.

1. Review D functions, modules, shared state and scope guards from the preceding lessons.
2. Open the complete thread_counter.d example in the native-language-boundary laboratory.
3. Use an ordinary supported D runtime for this exercise. It is not a BetterC program or a Kernel program.


## A process and its threads

A process is a running program with an address space and operating-system resources. A thread is a sequence of execution within that process. Two threads can refer to the same memory even when they execute on different processors. The scheduler may interleave their work in many orders. Designing for just one observed order is fragile; a correct contract must tolerate allowed scheduling variation.


## What shared expresses

The example declares private shared uint completed at module scope. shared identifies data intended to be accessible across threads. It does not turn an ordinary multi-step update into an atomic operation, establish ownership of a worker, or make an arbitrary object graph safe. private limits name visibility to the module; it is not a lock. uint is a 32-bit unsigned integer, and this exercise's 20,000 increments stay well below its maximum.

~~~d
private enum uint iterations = 10_000;
private shared uint completed;
~~~


## Read-modify-write must be one admitted operation

An increment conceptually reads an old value and writes a new one. Independent competing reads and writes can interfere. The worker uses core.atomic's atomicOp with the += operation, so the update follows an atomic read-modify-write contract. The same module uses atomicStore to reset before workers start and atomicLoad to read after they finish. It does not mix ordinary accesses with the atomic protocol.

~~~d
private void countWorker() nothrow @nogc
{
    foreach (uint stepIndex; 0U .. iterations)
        atomicOp!"+="(completed, 1U);
}
~~~


## Read the punctuation slowly

The exclamation mark supplies a template argument in D. Here the string += selects the operation at compile time; it is not a command received from an untrusted user. Parentheses supply runtime arguments: the shared counter and the unsigned increment. The half-open foreach range begins at zero and excludes iterations, so it visits exactly 10,000 values. The worker's nothrow and @nogc attributes constrain that function's calls; they do not make the entire program allocation-free.


## Atomicity is narrower than a transaction

A correct atomic counter does not make several related fields change together. Suppose a job has completedBytes and totalBytes. Reading each separately can observe values from different moments. A coherent multi-field snapshot needs another design, such as one lock around the record or publication of an immutable snapshot. Do not extend this one-counter exercise into a claim that all progress objects need only atomic fields.


## Keep the default memory-order policy while learning

The calls use core.atomic's default sequentially consistent ordering. Memory ordering describes constraints on how participating accesses become observable. Relaxed or acquire/release policies require a separate proof of which event publishes which data. The exercise has no reason to weaken its ordering for a claimed speed improvement. Even the strongest ordering does not keep a freed object alive or wait for an unfinished worker.


## Constructing a Thread is not completing it

A Thread object associates a worker function with runtime thread state. Calling start begins execution. Calling join waits for completion and can report an unhandled worker exception. The example passes a function pointer to a finite worker without captured stack state. A more complex worker that captures data must still establish how long every captured object remains valid.

~~~d
auto first = new Thread(&countWorker);
first.start();
scope(exit) first.join();
~~~


## Register cleanup after successful acquisition

runPair registers a scope(exit) join only after the corresponding start succeeds. If allocation or startup of the second worker fails, the first guard still waits for the first worker during stack unwinding. If both start, the second guard runs before the first because scope guards unwind in reverse registration order. Neither guard holds a lock needed by the worker. This is explicit ownership logic, not an assumption that the garbage collector will perform a join.


## Do not read the answer before cleanup completes

The owner helper returns void. Its scope guards finish before main reads completed. Returning an expression that reads completed from inside that helper would evaluate the expression before scope-exit cleanup, which could publish an intermediate value. This subtle distinction is why the result is loaded in the caller after runPair returns.

~~~d
runPair();                 // both join guards complete before this returns
const observed = atomicLoad(completed);
if (observed != 2U * iterations) {
    return 1;
}
~~~


## Trace the successful timeline

Each worker contributes 10,000 updates. Their interleaving is unspecified, but the final count after both joins must be 20,000. The application does not print a line from each worker; this keeps output ordering separate from the data experiment.

~~~text
owner:  store 0 -> start A -> start B -> leave helper -> join B -> join A -> load final value
A:                   [ 10,000 atomic additions ]
B:                              [ 10,000 atomic additions ]
result is checked only after both workers have completed
~~~


## Understand the helper's deliberate limits

The example uses a single module counter and calls runPair serially. It is not reentrant: two callers invoking runPair concurrently would reset and reuse the same logical result even though individual accesses remain atomic. This illustrates a race in higher-level meaning that atomic storage alone cannot prevent. A reusable job API needs per-job ownership or a separately specified admission rule. The finite loop also avoids pretending that join is a cancellation mechanism.


## Garbage collection and completion are separate

Garbage collection manages eligible memory according to the runtime's reachability rules. It does not decide that a business job should stop, flush an application result, cancel a download, join a worker at the correct time, or safely close a window's callbacks. Native applications still need explicit lifecycle boundaries. Likewise @nogc on the worker does not remove Thread allocation or runtime requirements from the surrounding program.


## Compile and run with checks enabled

Use a supported DMD installation and keep unit checks enabled. Run one command at a time. A failed compilation means the current source was not qualified, even if an older executable still exists. The current mirror does not contain a validated D compiler, so this example remains authored and unexecuted here.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context -of=thread_counter_d.exe thread_counter.d
& .\thread_counter_d.exe
$LASTEXITCODE
~~~


## Read the expected result and unit check

A successful main run prints Completed increments: 20000 and confirms that both workers joined before the final result was observed. It exits zero. With -unittest, the module's unit block also runs a separate worker pair before main, checks its count and finishes its joins. runPair resets the counter before each serial run. An explicit runtime comparison remains in main so that the result is still checked independently of assertions.

~~~text
Completed increments: 20000
Both workers joined before observing the final result.
~~~


## Connect to C and Framework carefully

The ideas transfer to C23 atomic and thread ownership designs, but D's shared qualifier and runtime Thread object are not portable C ABI values. Do not pass a D object or delegate to a C service without a reviewed representation and lifetime contract. Umicom applications should reuse Framework's native job and process services rather than each creating an unrelated scheduler. D reflection can generate metadata about fields, but it cannot infer an application's correct cancellation, synchronization or ownership protocol.


## Troubleshoot the right layer

1. If the compiler rejects shared access, inspect every read and write; do not cast away shared just to silence the diagnostic.
2. If Thread startup fails, record the compiler/runtime/platform and the reported error. The cleanup path must still wait for previously started workers.
3. If a final result changes after adding more shared fields, review the whole state transition rather than assuming that more atomic variables create a transaction.
4. If a program hangs in join, inspect the worker's termination condition and any locks. A delay does not prove progress.
5. If memory grows across repeated jobs, track live workers, retained references, buffers and OS resources separately; a garbage collector is not evidence that all resources were released.


## Exercises and reasoning checkpoints

Reduce iterations to three and predict six. Explain why output remains deterministic even though worker order does not. Next describe why two concurrent runPair callers would violate the logical contract despite atomic additions. Finally design two independent worker result records whose values are combined only after both joins. That alternative removes the shared increment, but still requires explicit completion and lifetime rules.


## Official language and runtime references


- [D core.atomic](https://dlang.org/phobos/core_atomic.html)
- [D Thread runtime class](https://dlang.org/library/core/thread/osthread/thread.html)
- [D statements and scope guards](https://dlang.org/spec/statement.html)


[Previous: Inspect layout without serializing padding](41-inspect-layout-without-serializing-padding.md)

[Next: Separate union reflection from active-value state](43-separate-union-reflection-from-active-value-state.md)
