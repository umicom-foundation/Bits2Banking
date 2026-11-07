<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/05-processes-and-scheduling.md

PURPOSE:
Understand processes and taking turns on a processor

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand processes and taking turns on a processor

An operating system coordinates programs, memory, devices and access to resources. This course introduces each idea using a small Umicom example. It assumes no previous operating-system or C experience. Definitions and setup are repeated where a lesson can be read independently.

## Prepare this lesson

You need a text editor to read the examples. A terminal is a window in which a typed command asks a program to do something. PowerShell is the Windows terminal language used below; Bash is the Linux alternative. A path names a file or folder. Replace C:\umicom with your checkout location if it differs.

For the optional C lab, install a C23 compiler, CMake and Ninja, and a matching Umicom Framework SDK that includes the platform component. On Windows, open PowerShell and enter:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\boot-report"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
~~~

Read the lab README before configuring it. Run commands separately and stop on a nonzero exit status. Reading a report does not boot an operating system. QEMU exercises use the separate Kernel guide linked in the relevant lesson; no physical disk is attached. You can complete the prediction and source-reading exercises without executing programs.

## Running more than one task

A process combines a program with its execution state and owned resources. A scheduler chooses which eligible task receives processor time. On one processor, tasks take turns. Saving enough state allows a task to continue later as though its work had merely paused.

A time slice is a bounded turn. Preemption interrupts a running task at a controlled boundary. Cooperative yielding is a task voluntarily returning control. These mechanisms require different machine support and must not be treated as interchangeable names.

## Read the current native contract

The Kernel scheduler has a bounded task table. Its header documents stable storage, task states, saved trap frames and explicit reaping. Reaping releases a terminal task's retained resources; a task reaching an exit state does not mean its bookkeeping has already disappeared.

1. Find UmicomUserScheduler and its task array.
2. Read the state enumeration. Distinguish ready, running, paused and terminal states.
3. Find RunOne's contract and the meaning of idle.
4. Find the cancel and reap functions. Record which states each accepts.
5. Inspect the generation field in a handle. A reused table position must not make an old handle refer to a new task.

## Work through a paper trace

List tasks A and B as ready. Give A one turn, pause it, then give B one turn. Mark the next eligible task. Now block A while it waits for a resource. The next selection must respect eligibility rather than blindly running every occupied slot.

The header's active flag serializes the current service; it is not an atomic lock for multiple physical processors. Extending to several cores needs an explicit concurrency design and tests. A small host scheduler check cannot establish hardware timer correctness.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/user_scheduler.h).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Understand memory, addresses and ownership](04-memory-and-ownership.md) · [Next: Understand interrupts and device events](06-interrupts-and-device-events.md)
