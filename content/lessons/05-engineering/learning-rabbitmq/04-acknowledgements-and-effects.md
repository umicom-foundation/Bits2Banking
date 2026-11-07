<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/04-acknowledgements-and-effects.md

PURPOSE:
Separate acknowledgements from completed work

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate acknowledgements from completed work

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


## Two different confirmations

A publisher confirm tells a producer about broker handling of a publication. A consumer acknowledgement tells the broker about a delivery the consumer has handled. They concern different communication directions. Read the [official confirmation guide](https://www.rabbitmq.com/docs/confirms). Neither alone proves that every external application effect happened exactly once.

Consider a worker that writes a report and then loses its connection before acknowledging. The report exists, but the broker may deliver the request again. If the worker acknowledges first and crashes before writing, the report may never be created.

## Trace the failure window

~~~text
receive request
validate identity and permission
commit application effect and durable retry outcome
acknowledge delivery
~~~

This is an architectural sequence, not executable code. “Commit” requires a storage design that makes the effect and record consistent. A memory-only map cannot provide that guarantee across crashes.

1. Open main.c and locate umi_idempotency_store_record.
2. Observe that the lab records text; it performs no external effect.
3. Mark the point where a real worker would commit its durable effect.
4. Place a hypothetical crash immediately before and immediately after that point.
5. For each case, describe what a restarted consumer would inspect before acting.

## Application boundary

A trading order must not be resubmitted simply because a local response was lost. Query and reconcile broker identity through the established execution service. A bank transfer needs durable transaction and authorisation rules. Message delivery policy must not replace either domain's rules.

## Check your design

Write two expected outcomes: repeated delivery of an already committed request, and first delivery of an invalid request. The former should recover the recorded outcome; the latter should produce an explicit rejection without the requested effect. A transport retry must not turn a rejected command into a new authorised action.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/main.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Prepare a local RabbitMQ learning environment](03-start-a-local-broker-safely.md) · [Next: Use stable identities when requests are retried](05-stable-identity-and-retries.md)
