<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/10-trace-the-delivery-ticket-program.md

PURPOSE:
Trace a complete Framework delivery-ticket program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Trace a complete Framework delivery-ticket program

A message is a request to perform work. This module uses a small C program and the Framework messaging service to explain how a worker keeps temporary ownership, how callbacks can become stale, and how to preserve the current work when an old callback arrives.

## Prepare this lab

A terminal accepts typed commands. A source file contains a program's instructions. A compiler translates those instructions into a program. CMake describes the build; Ninja carries out the build steps; CTest runs registered checks. An SDK is a set of headers and libraries used by another program.

Reading needs no account or broker. To run the exercise, install a C23 compiler, CMake 3.26 or later, Ninja and a compatible Umicom Framework SDK with its messaging component. Use the same compiler family and architecture as that SDK. The SDK must contain the delivery-ticket API described here.

1. Locate the Bits2Banking repository and its **labs/framework/delivery-tickets** folder.
2. Open PowerShell on Windows or Bash on Linux.
3. Run the commands for your platform one at a time, stopping at an error. Replace the checkout and SDK paths if you installed them elsewhere.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\delivery-tickets"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-delivery-tickets.exe"
~~~

~~~bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/delivery-tickets
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-delivery-tickets
~~~

A missing UmicomFramework package means CMake cannot find the SDK. Check the installation prefix. An unknown ticket type or missing ticket symbol usually means the SDK is older than the example, or headers and libraries come from different installations. Select one matching SDK; do not copy individual libraries at random. The exercise uses local, deterministic clock values and performs no broker connection or financial transaction.

For a fuller introduction to C syntax, use [Learning C](../../../courses/learning-c/index.html). You can complete the explanation below without leaving this lesson.

## What you will learn

You will read the example from entry to exit, identify which object owns memory, and understand why every failure path releases that memory.

## Start at main

**main** is the program's entry function. It returns an integer to the operating system. Zero means success in this example; one means a required step failed.

~~~c
UmiDeliveryLeaseStore *store = NULL;
int result = 1;
~~~

The asterisk declares a pointer: a value referring to an object in memory. NULL means no store has been obtained yet. The result begins as failure, so an early exit cannot accidentally report success.

**umi_delivery_lease_store_create(1U, &store)** asks Framework to allocate one slot. The ampersand supplies the address of the local pointer, allowing Framework to write the allocated store's address into it. Framework owns the internal representation; the caller is responsible for eventually calling the destroy function.

## Understand the small report function

The lab's **report** helper compares an actual status with an expected status. It returns one for a match. Otherwise it writes a diagnostic to standard error and returns zero. Standard error is a program output channel commonly used for problems.

The helper does not implement lease logic. The acquisition, deadline and generation rules remain in Framework. This is how a thin application uses a reusable service while retaining its own presentation.

## Step through the operations

1. Create a store.
2. Acquire the first ticket.
3. Check ownership just before and at the deadline.
4. Acquire a replacement at the deadline.
5. Try the old release and require rejection.
6. Confirm that the replacement remains owned.
7. Release the replacement.
8. Destroy the store.

The **goto finished** statements jump to one cleanup label in the same function. They do not restart the program. This small C pattern lets multiple error branches share one cleanup operation. The store is destroyed exactly once after successful creation.

## Expected result

~~~text
First acquisition is owned at 119 and expired at 120.
Stale release rejected; replacement remains owned.
Replacement released.
~~~

The fixed times are inputs, not delays. No sleep is required. This makes the exercise reproducible and lets you examine a deadline boundary without depending on how quickly your computer runs.

## Experiment

In a practice copy, change replacement acquisition from time 120 to time 119. Rebuild the lab. The acquisition should return BUSY, and the program should exit unsuccessfully because the example expected success. Change it back and rebuild.

Then change the delayed release to use replacement. The call would successfully release the current record; the example correctly reports a mismatch because it expected rejection. This demonstrates why passing the right ticket matters.

## Recovery and summary

If compilation fails, read the first diagnostic and confirm the SDK version before changing the example. If the status differs at runtime, record the operation and expected status. The example teaches object lifetime, status checking and generation identity through actual Framework calls.

## Read the source

[Open the example source](../../../../labs/framework/delivery-tickets/main.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Recognise a restarted worker with a delivery ticket](09-workers-restarts-and-acquisition-identity.md) · [Next: Keep lease ownership with an asynchronous work item](11-callback-ownership-and-lease-renewal.md)
