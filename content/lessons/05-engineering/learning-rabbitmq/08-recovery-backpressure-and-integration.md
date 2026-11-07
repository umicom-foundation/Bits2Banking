<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/08-recovery-backpressure-and-integration.md

PURPOSE:
Plan recovery and connect messaging to applications

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan recovery and connect messaging to applications

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


## Bound the work in progress

Backpressure means slowing producers or limiting in-flight work when a consumer cannot keep up. Without a bound, a responsive interface may still exhaust memory in a worker. A useful design tracks waiting work, active work, completed work and rejected work separately.

RabbitMQ connection recovery can involve re-establishing channels and subscriptions. Delivery may repeat around failures; application consumers must account for that. Use the [reliability guide](https://www.rabbitmq.com/docs/reliability) when implementing an adapter. Recovery is a state machine, not an unconditional retry loop.

## Prepare an integration checklist

1. Define a typed Framework command and an event describing completion or rejection.
2. Validate envelope size, schema, identity and permission before allocating expensive work.
3. Separate transport state from domain state. A connection error is not proof that a trade failed.
4. Bound retry attempts and delay them. Preserve enough evidence to investigate a final failure.
5. Define durable commit and duplicate-request behaviour before acknowledging successful work.
6. Make cancellation explicit. Cancelling a local wait does not automatically cancel a remote effect.

## Connect the lesson to Studio, Trader and Bank

Studio can display background build progress without owning the build engine. Trader can display reconciled execution events without inventing fills. Bank can request a report without exposing an internal ledger mutation as a generic message handler. In each case the application is a client of Framework services; a RabbitMQ adapter would carry approved messages at that boundary.

## Acceptance exercise

Write expected observations for five cases: valid work, invalid schema, duplicate delivery, connection loss after commit, and a worker paused past its lease. Mark which cases the local C lab covers and which require a real broker and durable domain integration. The answer must leave the latter unverified until those components exist and are exercised. A green local test is useful evidence for its contract, not evidence of a complete distributed system.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Handle temporary ownership and safe deadlines](07-leases-time-and-overflow.md)
