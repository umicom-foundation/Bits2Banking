<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/03-start-a-local-broker-safely.md

PURPOSE:
Prepare a local RabbitMQ learning environment

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Prepare a local RabbitMQ learning environment

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


## Choose an installation method

A server is a program that waits for requests. RabbitMQ is a server, so it needs its own installation and configuration. Use the [official download guide](https://www.rabbitmq.com/docs/download) for the current supported platform packages. Record the version you install. Windows installations also require a compatible Erlang runtime; follow the documented version pairing instead of guessing.

The C lab at the top of this lesson can run without a broker. This separate exercise prepares a broker for later adapter work.

## Step by step

1. Read the official instructions for your operating system. Choose a local learning installation and a directory you can administer.
2. Install the documented prerequisites, then the broker. Keep the installation output and record where the tools are installed.
3. Open the broker's command-line environment. Run the following read-only observations:

~~~text
rabbitmq-diagnostics status
rabbitmqctl list_queues name messages_ready messages_unacknowledged
~~~

4. Read the status output. A stopped service, wrong tool path or permission error must be resolved before application testing.
5. If you enable the management interface using the official instructions, open it on the local host. Do not expose a learning broker to the internet.
6. Create a dedicated learning virtual host and an account limited to that host using the documented administration interface. A virtual host separates broker resources and permissions; it is not a virtual machine.

## Understand the observations

A ready count describes waiting deliveries; an unacknowledged count describes deliveries awaiting a consumer response. The exact values depend on activity. Record actual observations rather than assuming zero means success.

## Recovery and next step

If a command is unavailable, locate the installation's command-line tools. If authentication fails, inspect the local administrative configuration; do not paste credentials into source files. Stop the learning service when no longer needed. This lesson does not install or claim a Framework RabbitMQ adapter. The next lessons establish the contracts such an adapter and its consumer must preserve.


## Read the source

[Open the example source](https://www.rabbitmq.com/docs/download).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Design routes and queue boundaries](02-exchanges-routing-and-queue-design.md) · [Next: Separate acknowledgements from completed work](04-acknowledgements-and-effects.md)
