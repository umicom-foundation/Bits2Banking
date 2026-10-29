# Close background work safely

Continue from [Understand which program a test runs](09-understand-test-commands.md). This lesson uses Framework background tasks to explain ownership, cancellation and shutdown.

```text
Submit → close admission → callbacks return → join workers → release owners
Keep callback payload alive ----------------------------^
```

## What is background work?

A program normally follows a sequence of instructions. A thread is one sequence that the operating system can schedule alongside others. A background worker is a thread used for work that should not hold up the visible interface. Studio can keep accepting input while a worker reads project files. Media can prepare a file while its window stays responsive.

A task is a unit of work described by a function and the data that function needs. A queue holds tasks until a worker can take them. Framework's UmiTaskQueue owns workers and schedules accepted tasks. Applications use this shared service instead of implementing their own operating-system thread management.

Closing a window does not automatically stop a worker. The worker may still be reading data owned by that window. If the window releases the data too soon, the worker can access memory that no longer belongs to it. This is a lifetime error. We must decide who owns each object and when its last use ends.

## Separate the task from its payload

A pointer stores the location of an object. Ownership means responsibility for keeping that object alive and eventually releasing it. A borrowed pointer lets another part of the program use an object without taking that responsibility. A reference count is one way an object records several owning references.

umi_task_create returns one task reference to its caller. A successful umi_task_queue_submit gives the queue another reference. Releasing the caller's reference therefore need not destroy an accepted task. The queue keeps its own reference until it no longer uses the task.

The callback payload is different. This is the application data passed as user_data, such as a search request or a collection being inspected. Retaining the task does not retain arbitrary objects reached through that pointer. The payload owner must keep those objects alive until every callback use has ended. Treat task ownership and payload ownership as two separate lines in your design.

## Cancellation is a request

Cooperative cancellation asks work to stop at a safe point. The callback checks its cancellation context, finishes any required local cleanup, and returns a cancelled result. Cancellation does not interrupt an arbitrary instruction, automatically undo a file write, or prove the worker has already returned.

The installed consumer deliberately waits until its first callback has entered, then queues another task behind it. One worker and a small queue make this relationship explicit. Requesting cancellation can now exercise two different behaviours: the active callback observes the request, and the pending callback never starts.

This arrangement uses atomic counters. An atomic access is an operation whose concurrency rules let threads exchange a value without an ordinary unsynchronised read/write race. Atomics here report entry and progress. They do not make every object reached through a pointer safe or replace the queue's ownership rules.

## Close admission, then join

Closing admission means refusing new tasks. Draining means allowing already accepted work to finish. Cancelling pending work means removing tasks that have not started. These policies are distinct; choose the one that matches the application's operation.

A join waits for a native worker to finish, including its thread-exit cleanup. Empty task counters do not necessarily prove that native cleanup has ended. Framework therefore exposes a STOPPED phase that means its workers have been joined. The controller can then release the stopped queue.

The command-line consumer may wait in a blocking join. A graphical application's event thread must keep handling input and drawing, so it should not silently perform that blocking wait. Framework also provides a nonblocking join route on supported platforms: a controller checks again later when the result is BUSY. Unsupported capability is reported explicitly.

## Read the real consumer

Open the Framework shutdown client's lifecycle_cases.c alongside platform/task_queue.h. ConsumerWork holds the callback payload. The controller allocates it before creating tasks and frees it after joining and releasing the queue. The queue pointer inside that payload is borrowed; it remains valid while the callback uses it.

The caller-release case first submits a task successfully, then releases only the caller's task reference. It clears its local task pointer to avoid using that released reference later. The payload stays allocated. After shutdown, the case checks that the queue completed the accepted task before the payload is released.

The rejected-reusable case closes admission before submission. It expects INVALID_STATE, checks that the task remains CREATED, and runs the caller's task directly. This would be wrong after successful submission: the queue would already own scheduling. A failed submission must not silently consume work that was never accepted.

## A stopped queue can contain failed work

The callback-error case returns INTERNAL_ERROR from its task. Successful queue shutdown means the workers finished; it does not change that task result into success. The consumer checks the task state, the returned error and the queue's failed-work count independently.

The worker-self case checks another boundary. A callback cannot wait for its own queue to become idle: the callback itself is part of the running work. It also cannot join its own worker. The public API refuses those operations with INVALID_STATE rather than entering a wait that cannot complete.

A timeout is also evidence of a problem, not a successful cancellation. Keep the first diagnostic and the source identity that produced it. Do not free borrowed data merely because a deadline passed. The fixture has a finite callback escape path and retains heap owners if native cleanup itself fails before the failed test process exits.

## Follow the example step by step

First, read the public task, queue and threading headers. Find which functions create an owning reference, borrow a pointer, request a stop, join workers and release storage. Write a short ownership table before changing code.

Next, read the independent client CMakeLists.txt. Its original mode selects the focused queue laboratory package. Its full-SDK mode selects the installed Framework package, checks its origin and declared environment, then links Umicom::platform. Neither route should include a private queue structure from the source tree.

Use the linked installed-shutdown guide when you are ready to configure and run the client with a matching SDK. Run each command separately and preserve its log. The six named lifecycle checks use portable blocking shutdown; the original polling example can report a skip when nonblocking join is unavailable. Record that skip separately from passed checks.

Finally, trace one case on paper before running it. List the caller reference, queue reference, payload and worker. Cross out each ownership obligation only when the corresponding operation actually succeeds. A source-reading exercise helps explain a contract; a compiler, test or GUI result requires execution evidence.

## One ownership operation in C

This fragment comes from the installed consumer, after a checked successful submission. Follow the complete linked program for its setup and cleanup.

```c
/* After a successful submission, the queue holds its own task reference. */
umi_task_destroy(task);
task = NULL;
/* Keep the separate callback payload alive until worker shutdown completes. */
```

## Check your understanding

<details><summary>Does requesting cancellation let the window free the task's payload?</summary>

No. The request must be observed and the callback must stop using the payload. This consumer conservatively waits for joined workers before releasing the payload.

</details>

<details><summary>Why can a task still run after the caller destroys its task reference?</summary>

A successful submission gave the queue its own reference. Releasing one reference is different from unconditionally freeing the task. The payload still needs its separate owner.

</details>

<details><summary>What does successful shutdown say about a callback that returned an error?</summary>

It says the workers have finished. The task's error and failed count remain observable; they must not be reported as successful work.

</details>

<details><summary>Why does the cancellation case wait for the first callback to enter?</summary>

Without that observation, both tasks might still be pending. The test could then exercise only removal from the queue and miss running-task cancellation.

</details>

## Read the Umicom source

- [Queue's public contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/platform/task_queue.h)
- [Task references and callback lifetime](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/platform/task.h)
- [Thread join and release](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/platform/threading.h)
- [Installed consumer scenarios](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/queue_shutdown/client/lifecycle_cases.c)
- [Installed shutdown guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/guides/check-sdk-shutdown.html)

[Previous: test commands](09-understand-test-commands.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.

Next: [Register shared application services](11-register-shared-services.md).
