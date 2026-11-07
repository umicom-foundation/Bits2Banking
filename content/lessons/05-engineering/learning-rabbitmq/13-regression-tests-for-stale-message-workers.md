<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/13-regression-tests-for-stale-message-workers.md

PURPOSE:
Test stale workers without sleeps or a broker

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test stale workers without sleeps or a broker

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

You will turn a failure scenario into deterministic checks and understand what those checks can and cannot establish.

## Start with a claim

A useful regression test states a behaviour that should remain true. Here the claim is: "An old ticket cannot release a replacement acquisition, even when the message identifier and owner name match."

A regression test keeps that claim executable after later changes. A passing result only covers the tested implementation, environment and cases.

## Choose controlled inputs

Use clock values 100, 119, 120 and 121. The lease lasts 20 units from 100. Its deadline is exclusive, so 119 is owned and 120 is expired. Passing time as an input removes the need for sleeping, thread timing or a running broker.

Keep the original and replacement tickets as separate values. Check not only the rejected old operation but also that the new lease remains owned. Otherwise a function might return an error after already damaging the current state.

## Build a case table

| Case | Operation to reject | State to preserve |
| --- | --- | --- |
| Same owner after expiry | Release using old generation | Replacement remains owned |
| Release then reacquire | Renew using earlier ticket | New deadline remains |
| Slot reused for another message | Release old message | Other message remains |
| Full store | Acquire another message | Output ticket is unchanged |
| Overflowing renewal | Add duration beyond integer range | Previous deadline remains |
| Legacy call on protected record | Release using only owner name | Ticketed record remains |

Framework's **tests/test_delivery_lease_ticket.c** implements these categories and additional identity checks. The lab's CTest registration runs its complete example as one smaller consumer check.

## Read a CTest registration

~~~cmake
add_test(NAME learning.messaging.delivery-tickets
         COMMAND btb-delivery-tickets)
~~~

NAME gives the check a stable name. COMMAND names the built executable to run. CTest does not build the executable first; run the build command before ctest.

The program returns a nonzero exit code on a wrong result. An additional expected-output expression identifies the successful stale-release scenario. Output text alone is not a substitute for checking state inside the program.

## Exercise

In a practice copy, make the delayed release use the replacement ticket. Run the build and CTest commands. The example should fail. Restore the original call and rerun. This deliberate change checks whether the regression can detect the specific mistake.

## What remains outside the test

This lab does not test multiple processes, real broker reconnection, payment execution or hostile network participants. It also does not prove that every callback's memory lifetime is correct. Those require separate integration and ownership tests.

## Summary

Control the inputs, assert the refusal, and inspect the state that must survive. Record failures precisely and rerun the relevant checks after a fix.

## Read the source

[Open the example source](../../../../labs/framework/delivery-tickets/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Connect local work ownership to durable message effects](12-local-leases-and-durable-message-effects.md)
