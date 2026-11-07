<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/01-messages-producers-and-consumers.md

PURPOSE:
Understand messages, queues and consumers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand messages, queues and consumers

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


## What a message represents

A message carries information from one part of a system to another. A producer sends it. A consumer receives it and decides what to do. A queue holds messages until consumers can receive them. A broker is a separate service that manages communication. These are roles: one program can act as both producer and consumer.

Imagine a request to prepare an account report. The user interface collects a report period; a worker prepares the document; the interface displays progress. The request is not the document itself. Define an envelope before writing transport code:

| Field | Example | Meaning |
| --- | --- | --- |
| request_id | report-42 | Stable identity for one requested action |
| kind | report.prepare | Operation the consumer understands |
| schema_version | 1 | Version of the field contract |
| period | 2026-01 | Domain input to validate |

## Trace a local example

1. Open main.c and find the string export-7. It is a request key, not a broker address.
2. Find the call that records report prepared. It remembers an outcome in process memory.
3. Find the second record call. The same key returns ALREADY_EXISTS rather than overwriting the first outcome.
4. Draw a diagram with an interface, a queue and a worker. Put the registry inside the worker's application boundary.

The lab demonstrates retry records and temporary ownership. It has no RabbitMQ connection and sends no messages. Adding a queue requires a transport adapter, protocol handling and a durable application design.

## Check your understanding

Explain why a queue can help an interface stay responsive while a worker is busy. Then explain why “message delivered” alone cannot prove a report was created. Expected reasoning: transport and application processing are separate steps. An empty queue may mean successful consumption, premature acknowledgement or a discarded message; application evidence distinguishes them.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/main.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Next: Design routes and queue boundaries](02-exchanges-routing-and-queue-design.md)
