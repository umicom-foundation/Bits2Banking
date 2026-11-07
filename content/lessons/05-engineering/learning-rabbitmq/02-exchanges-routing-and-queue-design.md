<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/02-exchanges-routing-and-queue-design.md

PURPOSE:
Design routes and queue boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Design routes and queue boundaries

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


## Give each route a purpose

In RabbitMQ, producers normally publish to an exchange. Bindings connect exchanges to queues using routing rules. A routing key is text used by those rules. The default exchange is a special case that can route by queue name. Consult the [queue guide](https://www.rabbitmq.com/docs/queues) before configuring a broker.

For a first design, separate report requests from report completion events. A request asks for an action; an event reports something that already happened. Neither is an instruction to execute an arbitrary shell command.

## Design on paper first

1. Write a command name: report.prepare.
2. Define required fields and maximum lengths. Include a stable request identity and schema version.
3. Choose which application role may publish it and which worker may consume it.
4. Draw one processing queue and one error-review destination. Record what should happen to an unsupported schema.
5. Decide whether two worker instances compete for requests or each needs its own copy. These are different arrangements.

A useful design table is:

| Concern | Decision to record |
| --- | --- |
| Ordering | Per report, account, or globally? |
| Retention | How long can an unprocessed request remain useful? |
| Capacity | What happens if production exceeds consumption? |
| Privacy | Which fields must be excluded from logs? |

## Apply it to Umicom

A Bank report worker may receive a report identifier, then obtain authorised account data through a Framework service. Do not place passwords or a complete account export into an unprotected message simply because the queue is convenient. Studio could use the same pattern for a build request, but the worker must enforce workspace and executable policy.

## Review

Explain why a successful routing decision is not an authorisation decision. The expected answer distinguishes destination selection from permission to act on the destination's data. Keep this design alongside the future adapter contract; the local lab cannot verify broker bindings.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/README.md).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Understand messages, queues and consumers](01-messages-producers-and-consumers.md) · [Next: Prepare a local RabbitMQ learning environment](03-start-a-local-broker-safely.md)
