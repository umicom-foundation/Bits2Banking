<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/09-workers-restarts-and-acquisition-identity.md

PURPOSE:
Recognise a restarted worker with a delivery ticket

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Recognise a restarted worker with a delivery ticket

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

You will distinguish the name of a worker from one particular attempt to do a job. This distinction prevents a delayed callback from changing the ownership of a newer attempt.

## Begin with a small job

Imagine a preview worker preparing an image for a media application. A message says which preview to prepare. The **message identifier** is a number identifying that job. The **owner name** is a readable label such as "preview-worker". A **lease** allows that worker to own the message until a deadline.

A callback is a function called later when something happens, such as a file read finishing. It can arrive after the original attempt has expired. The worker name alone cannot tell whether a callback belongs to the current attempt.

Follow this timeline:

| Clock value | Event | Local owner |
| --- | --- | --- |
| 100 | First attempt acquires message 42 for 20 units | Ticket generation 1 |
| 119 | First attempt checks ownership | Still generation 1 |
| 120 | First attempt expires; another attempt acquires message 42 | Generation 2 |
| 121 | Old callback tries to release generation 1 | Rejected; generation 2 remains |

The **generation** is an integer that changes on each successful ticket acquisition. The same message number and worker name can appear twice, while their generations differ.

## Read the public value

~~~c
UmiDeliveryLeaseTicket first = {0U, 0U};
~~~

The type contains two fields: message_id and generation. Braces initialise both to zero. The suffix U denotes an unsigned integer constant. Zero is not a valid acquired ticket. The acquire function fills the value only when it succeeds.

The value is copied into the work item. It does not own the store's memory and is not a pointer into an internal record. A copied old value stays old, which is precisely what lets Framework reject it.

## Work through the example

1. Find the declaration of **first** and **replacement** in main.c.
2. Find the first acquisition at time 100.
3. Find the acquisition at time 120. Both use "preview-worker".
4. Find the delayed release. It passes **first**, not **replacement**.
5. Read the expected result: **UMI_STATUS_PERMISSION_DENIED**.
6. Observe that the example then checks the replacement's ownership.

Expected output includes "Stale release rejected; replacement remains owned." If it reports another status, stop and check that the matching Framework SDK was installed.

## Practice and answer

Why would keeping one global variable named latest_ticket be unsafe? An old callback might read the new value and release the new attempt. Keep each callback's own acquisition value in its work context instead.

A ticket is not an authentication token. Any code in the process can see its integers. Its purpose is to detect accidental stale operations within a coordinated caller, not to establish trust in an unknown machine.

## Summary

Message identity tells you which job. Owner identity tells you which worker name. Acquisition identity tells you which attempt. The third piece is essential when names are reused.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/delivery-tickets/main.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Next: Trace a complete Framework delivery-ticket program](10-trace-the-delivery-ticket-program.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](08-recovery-backpressure-and-integration.md)
