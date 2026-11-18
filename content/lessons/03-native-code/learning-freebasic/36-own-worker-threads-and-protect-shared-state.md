<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/36-own-worker-threads-and-protect-shared-state.md

PURPOSE:
Own worker threads and protect shared state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Own worker threads and protect shared state

[Course contents](index.md)

## Why a second worker changes the problem

Until now most examples have followed one sequence of instructions. A thread is another sequence running inside the same process. Threads can share the process's memory, which makes communication convenient and also creates new responsibilities. This lesson uses two finite workers that increment one counter. The purpose is to learn ownership and synchronization, not to make counting faster. A one-thread loop is likely simpler and cheaper for this tiny workload.

1. Read the earlier pointer-lifetime and procedure lessons before passing an address to a worker.
2. Use a supported FreeBASIC Windows or Linux installation in its normal fb dialect; this exercise is not a DOS or QuickBASIC example.
3. Open the complete thread_counter.bas file. Keep the original and experiment in a separate practice copy.


## Concurrency and parallelism are different

Concurrency means that multiple activities can be in progress during the same period. Parallelism means that work actually executes simultaneously on different processing resources. A single-core system can interleave two threads without executing them at exactly the same instant. Do not infer ordering from the order in which workers are started. A scheduler decides when each runnable worker receives execution time.


## An increment contains several conceptual steps

Think of completed += 1 as reading the old value, calculating the next value and writing it back. Without a synchronization rule, two workers can interfere with one another's accesses. The following sketch is a teaching model of a lost update, not a guarantee of what an actual data race will produce. Unsynchronized access is a defect even if one run happens to print the expected number.

~~~text
Worker A reads 10
Worker B reads 10
Worker A calculates 11 and writes it
Worker B calculates 11 and writes it
Two intended increments produced only one visible increase.
~~~


## Use a mutex to define the critical section

A mutex is a mutual-exclusion lock. All participants use the same lock around accesses that must not overlap. In this example the critical section contains the counter update. Work outside it can proceed independently. Merely creating a mutex does not protect anything: every competing access must follow the protocol.

~~~basic
MutexLock(state->gate)
state->completed += 1
MutexUnlock(state->gate)
~~~


## Separate the record from its runtime handles

CounterState contains a mutex handle and a ULong counter. A handle is a value used to refer to a runtime resource; it is not the resource's portable serialized form. The main code owns the record and controls cleanup. Worker procedures borrow its address. They do not allocate or destroy the record or mutex.

~~~basic
Type CounterState
    gate As Any Ptr
    completed As ULong
End Type
~~~


## Understand the worker parameter

CountWorker receives ByVal raw As Any Ptr. ByVal copies the pointer value, not the pointed-to record. CPtr expresses the expected CounterState pointer type. That conversion is justified here because the caller passes @state, the address of a live CounterState. The cast would not make an arbitrary or expired address safe. The record must remain alive until both workers finish.

~~~basic
Sub CountWorker(ByVal raw As Any Ptr)
    Dim state As CounterState Ptr = CPtr(CounterState Ptr, raw)
    For stepIndex As ULong = 1 To Iterations
        MutexLock(state->gate)
        state->completed += 1
        MutexUnlock(state->gate)
    Next
End Sub
~~~


## Create resources in a deliberate order

Initialize the count and create the mutex before starting any worker. Check the returned mutex handle before using it. Then request each worker with ThreadCreate and retain every successful handle. A worker can begin promptly, so all of the context it needs must already be ready.


| Order | Owned item | Required state |
| --- | --- | --- |
| 1 | Counter record | completed is initialized |
| 2 | Mutex | A nonzero handle is available |
| 3 | First worker | Context and lock remain live |
| 4 | Second worker | The same lifetime and locking rules apply |
| 5 | Completion | Every successful worker is joined |
| 6 | Cleanup | Destroy the mutex after all workers finish |


## Inspect partial-start failure

The first worker may start successfully while the second creation fails. Failure does not erase ownership of the first handle or stop that worker. The example joins all earlier successful workers before destroying the mutex and returning an error. Because each worker has a fixed finite loop, the owner knows what must complete. General long-running jobs need their own cancellation and completion protocol; a pointer becoming inaccessible is not a cancellation signal.


## Join before destroying borrowed context

ThreadWait waits for the specified worker to finish and releases its handle. It is not a request to forcibly stop the worker. Call it for each successfully created worker. In the successful path, both waits happen before the final snapshot and mutex destruction. The example never waits while holding the mutex, because a worker might need that same mutex to finish.


## Picture a lifetime rather than a race

The main owner's lifetime encloses both worker lifetimes. The order of the two workers' individual increments can vary without changing the final contract. A valid design permits scheduling variation while preserving ownership and the protected result.

~~~text
main:   initialize ---- start A ---- start B ---- wait A ---- wait B ---- destroy lock
worker A:                 [ finite protected updates ]
worker B:                              [ finite protected updates ]
record and mutex: [---------------- live for every worker access ----------------]
~~~


## Read the complete resource vocabulary

Some names are language keywords and others are runtime procedures. Learning that distinction helps you find the correct reference and understand which operations depend on platform support.


| Name | Role in this exercise |
| --- | --- |
| Type / End Type | Declare the record's field layout |
| Any Ptr / CPtr / @ | Represent, type and obtain a borrowed address |
| Sub / ByVal | Declare the worker's pointer-parameter procedure |
| For / Next | Bound each worker to 10,000 updates |
| MutexCreate / MutexDestroy | Acquire and release the synchronization resource |
| MutexLock / MutexUnlock | Enter and leave the shared-data protocol |
| ThreadCreate / ThreadWait | Start a worker and wait for its completion |
| If / Then / End If | Handle failed admission and incorrect final results |
| End 0 / End 1 | Report successful or failed program completion |


## Compile the example with runtime checks

Use the prepared compiler and run commands separately. The multithreaded runtime option is explicit, and -exx retains learning-time checks. Stop if compilation fails; a previously built executable is not evidence that the current source compiled.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -mt -w all -exx thread_counter.bas -x thread_counter_basic.exe
& .\thread_counter_basic.exe
$LASTEXITCODE
~~~


## Interpret the result honestly

A successful run reports 20,000 completed increments, confirms that both workers were joined, and exits with zero. BASIC numeric Print formatting can include spaces. The explicit comparison checks the number rather than the visual spacing. In the current mirror work this source is authored and reviewed but has not been compiled or executed with FreeBASIC; website link and packaging checks do not establish its runtime behavior.


## Avoid using delay as synchronization

A sleep or a long calculation does not prove that another worker finished. Faster hardware, different scheduling or an earlier failure can invalidate a guessed delay. Joining states the required event directly. Likewise, a volatile-style declaration does not replace a mutex or an atomic update protocol. Correctness must not depend on the machine being slow enough to hide a race.


## Watch the size of a critical section

Keep the protected operation small and avoid unrelated I/O while holding the lock. A slow operation inside the lock prevents other participants from making progress. For this exercise, acquiring the lock for each increment is deliberately easy to reason about; it is not a high-performance counter design. A real batch processor might accumulate private worker results and combine them after joining, reducing shared-state contention.


## Transfer the lesson to Umicom applications

Model downloads, image preparation and build jobs can run in background workers, but their progress objects and callbacks still need clear owners. A window closing must not leave a worker dereferencing its destroyed controls. Reusable job and synchronization behavior belongs in Framework; a BASIC experiment should call a reviewed native boundary when integrating with a product. This example does not add a second application thread scheduler or permit GUI calls from arbitrary workers.


## Practice without introducing uncontrolled races

1. Change Iterations to 3 and predict six final increments. The order of individual updates remains unspecified.
2. Trace the second-worker failure path on paper: identify the first handle, its join, the mutex destruction and the final error.
3. Explain why moving MutexDestroy before ThreadWait violates the worker's borrowed-resource lifetime.
4. Design a private-counter alternative: give each worker its own record, join both, then add the results in the owner. Explain why this removes the shared increment.
5. Do not demonstrate a race by removing protection in production code. Keep invalid variants as written reasoning exercises unless using a dedicated reviewed diagnostic environment.


## Official API references


- [FreeBASIC ThreadCreate](https://www.freebasic.net/wiki/KeyPgThreadCreate)
- [FreeBASIC ThreadWait](https://www.freebasic.net/wiki/KeyPgThreadWait)
- [FreeBASIC MutexCreate](https://www.freebasic.net/wiki/KeyPgMutexCreate)


[Previous: Measure records before sharing their bytes](35-measure-records-before-sharing-their-bytes.md)

[Next: Select a union value with an explicit tag](37-select-a-union-value-with-an-explicit-tag.md)
