# Keep a service's process and streams under one owner

A service is a program that performs work for another part of the system. The minimal OS starts packaged, one-shot services: each should finish one task, then exit. A supervisor is the program that starts them, observes their result and deals with a deadline.

Before this lesson, review [applications, an OS and a kernel](../00-getting-started/07-applications-os-and-kernel.md). Reading the source requires introductory C functions, return values and error handling. This is a source-reading exercise; do not run the guest startup program on your normal computer.

## A parent and a child

A process is a running program with execution state and resources. On Linux, a process can create another process using `fork`. The existing process is called the parent and the new one its child. The child can use `execve` to replace its program with the intended service. Those are function names, not commands to paste into a terminal.

A PID is a process identifier: a number used to refer to a process. A number is not a permanent identity. After a process ends and its status is collected, the operating system may reuse that number. The supervisor therefore needs to know that the child it is about to signal is still its child.

A signal asks a process to respond to an event. The supervisor uses a private process group to stop ordinary descendants when a one-shot task finishes or times out. This is not a sandbox for hostile programs that deliberately escape the group.

## Keep the result until cleanup

Waiting means asking the operating system for a child's state. Reaping means collecting the final status so the operating system can release the corresponding process record. The supervisor observes completion without immediately reaping, stops the owned group, and then collects the child's final status.

Linux can also be configured to reap children automatically. `SIGCHLD` names the child-state signal. Ignoring that signal explicitly, or selecting `SA_NOCLDWAIT`, can remove the record the supervisor needs. The active supervisor rejects those caller settings before launch. It does not silently change the caller's signal policy.

If waiting fails, the supervisor no longer treats a numeric PID as sufficient evidence of ownership. It reports a launch failure and does not signal that possibly unrelated number. A caller must remain the exclusive waiter and must not change signal policy during the operation.

## Three familiar streams and one private channel

A file descriptor is a small integer by which a process refers to an open stream or file. Conventionally, 0 is standard input, 1 is standard output and 2 is standard error. They can be closed; a new open operation may reuse one of those numbers.

The supervisor has a separate pipe, a communication channel, for reporting setup or execution errors. It keeps both pipe descriptors above 2 so that redirecting service input and output cannot overwrite that channel. It also duplicates the caller's writable log descriptor. Closing the private copy does not close the caller's descriptor.

The close-on-exec flag requests that a descriptor be closed when a new program replaces the child. That is useful for the private error channel. It is not wanted on the service's standard input. When opening the empty input device returns descriptor 0, duplicating 0 onto itself does not clear that flag. The supervisor explicitly clears it.

## Trace a difficult starting state

1. Draw three boxes labelled 0, 1 and 2. Mark them closed.
2. Give the supervisor a valid, writable log file at descriptor 5.
3. Draw private copies for the log and error pipe, all above 2.
4. Redirect 1 and 2 to the log and open empty input at 0.
5. Replace the child with the service. Keep 0, 1 and 2 open; close the private error channel on successful execution.
6. If execution fails, use the error channel to report the reason instead.

The actual descriptor numbers above 2 vary. Their ownership and separation are what matter.

## Read and check the source

Read `boot/foundation/supervisor.c` in Umicom OS. Find `OwnWritableLog`, `OpenLaunchPipe`, the `SIGCHLD` policy check and the `waitFailed` cleanup condition. Then read `tests/foundation/test_supervisor_admission.c`. Its closed-stream cases run inside a separate probe process so they do not close the test runner's own output.

The tests are intended to check rejection of automatic reaping, read-only or closed logs, closed standard streams, preserved execution errors and the caller's retained log. Their source is not evidence of execution; host and guest qualification remain separate activities.

**Question:** Why is a remembered PID alone not enough to justify signalling a process after losing wait ownership?

**Explanation:** The original child's record may already have been collected and the number reused. The supervisor needs an ownership guarantee, not merely the same integer.

[Return to the learning map](../../start/systems-learning.md) · [OS course](../../courses/umicom-os-from-scratch/index.html)
