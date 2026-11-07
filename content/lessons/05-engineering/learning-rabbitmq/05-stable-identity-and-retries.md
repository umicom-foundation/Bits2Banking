<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/05-stable-identity-and-retries.md

PURPOSE:
Use stable identities when requests are retried

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Use stable identities when requests are retried

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


## What idempotency means

An operation is idempotent when repeating it has the same intended effect as doing it once. A retry registry helps recognise the same request, but the registry is only one part of an idempotent application. An identity must remain stable across retry attempts and must belong to the correct account, operation and payload policy.

The Framework registry stores a request key, an outcome code and result text. In this local contract, keys contain at most 159 bytes and result text at most 511 bytes; each internal array also reserves one terminating zero byte. Oversized input is rejected, not silently shortened.

## Read the calls

1. umi_idempotency_store_create allocates a bounded number of entries. The caller owns the returned handle.
2. umi_idempotency_store_record remembers one key and result. The lab expects a repeated key to return UMI_STATUS_ALREADY_EXISTS.
3. umi_idempotency_store_lookup copies the complete stored result into the caller's buffer and returns the stored outcome separately.
4. umi_idempotency_store_destroy releases the store. Its contents do not survive this call or process exit.

## Experiment in a practice copy

Change only the second key from export-7 to export-8. The existing duplicate assertion should fail: it is now a distinct request. Restore the key and change only the proposed second result. The first stored result should still be returned. Never change an assertion merely to make an unexpected result appear successful.

## Design question

What if someone submits the same key with different payment details? This basic registry does not compare structured payloads. A durable domain service must bind identity to its authorised request data and reject mismatches. Record that requirement before exposing a network endpoint. A unique-looking random string alone does not provide permission, durability or atomicity.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/main.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Separate acknowledgements from completed work](04-acknowledgements-and-effects.md) · [Next: Copy complete message results without truncation](06-buffer-boundaries-in-message-results.md)
