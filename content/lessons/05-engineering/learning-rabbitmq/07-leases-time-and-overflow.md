<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/07-leases-time-and-overflow.md

PURPOSE:
Handle temporary ownership and safe deadlines

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Handle temporary ownership and safe deadlines

Learn how applications exchange work, recognise repeated requests and recover from failure. Begin with messages and queues, then inspect a small C client of Umicom Framework. The course separates local contracts from the additional work needed for a real broker integration.

## Start here

A terminal is a window where you type commands. A source file contains instructions written by a programmer. A compiler translates those instructions into a program. CMake describes how files belong together; Ninja performs the build; CTest runs the checks registered by CMake. Reading this course requires no account or installation. The practical C lab uses the installed Umicom Framework messaging library and does not contact a message broker.

On Windows, use PowerShell with an MSYS2 UCRT64 C23 compiler, CMake and Ninja installed. Open the Bits2Banking checkout and locate labs/framework/message-retry. In the commands below, replace the checkout and SDK locations if yours differ. The SDK must include the messaging component and use a compatible compiler and architecture.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\message-retry"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-message-retry.exe"
~~~

On Linux, open Bash with a C23 compiler, CMake, Ninja and a compatible Framework SDK installed:

~~~bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/message-retry
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-message-retry
~~~

Run one command at a time and stop at the first error. If CMake cannot find UmicomFramework, check the SDK prefix; do not copy arbitrary libraries into the project. A missing messaging target indicates an incomplete or incompatible SDK. Expected example output is “Retry result: report prepared” followed by “Lease owned at 119; expired at 120.” These are local observations, not a broker delivery receipt.

Read each lesson's explanation before changing the example. No payment, trade, network connection or external file export is performed by this lab. Keep experiments in a practice copy. [Learning C](../../../courses/learning-c/index.html) provides a deeper introduction to syntax.


## A lease has an expiry

A lease is temporary permission to work on an item. Framework's local lease store associates a message identifier with an owner name and deadline. It expects serial access and a shared monotonic clock domain. Monotonic time is useful for elapsed duration because it does not follow wall-clock corrections.

The lab uses invented integer timestamps, not a real clock. Acquiring at 10 for duration 20 produces deadline 30. Ownership is valid at 29 and expired at 30. This exclusive boundary prevents two callers from disagreeing about the exact deadline.

## Check addition before doing it

An unsigned 64-bit integer has a largest value, UINT64_MAX. A wrapped deadline could appear to be in the past. The safe precondition is:

~~~c
duration != 0 && duration <= UINT64_MAX - now
~~~

Only after this condition holds may the implementation calculate now + duration.

1. Find the valid acquire call in test_retry.c.
2. Find the renewal using UINT64_MAX as its duration.
3. Verify the test expects INVALID_ARGUMENT.
4. Read the following ownership checks. They show that rejection preserves the earlier deadline.

## Ownership is not fencing

A paused worker might resume after its lease expires. Removing its entry cannot physically stop it from writing to another service. A distributed design needs an authoritative storage check, such as a monotonic fencing token enforced where the effect commits. This in-memory API does not provide that protocol or survive restart.

## Exercise

Add a table to your notes for times 28, 29, 30 and 31. Predict ownership before running a practice check. Then explain why a second machine's unrelated monotonic counter cannot be passed into the same deadline calculation without a shared protocol.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/test_retry.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Copy complete message results without truncation](06-buffer-boundaries-in-message-results.md) · [Next: Plan recovery and connect messaging to applications](08-recovery-backpressure-and-integration.md)
