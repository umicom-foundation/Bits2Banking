<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/06-buffer-boundaries-in-message-results.md

PURPOSE:
Copy complete message results without truncation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Copy complete message results without truncation

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


## Capacity is part of a function contract

A C character array has a fixed amount of storage. A C string ends with a zero byte. The eight letters in complete therefore require nine bytes when represented as a C string. The lab deliberately offers a two-byte output array so the lookup must refuse the copy.

~~~c
char result[2] = {'Q', 'Q'};
UmiStatus outcome = UMI_STATUS_BUSY;
~~~

The Q bytes are sentinels: known values that make accidental modification visible. They are not a string here because neither byte is zero. Do not print this array with a string conversion before a successful full copy.

## Follow the test

1. Read the record call that stores complete.
2. Read the lookup call that passes sizeof result. sizeof reports the whole array's byte size at this declaration site.
3. Check that the return value is CAPACITY_EXCEEDED.
4. Check both Q bytes and the original BUSY outcome remain unchanged.
5. Check the registry count is still one.

A function that returns a truncated identity or partial result as successful can cause a later component to act on incorrect information. The public Framework contract now requires enough capacity for the entire result plus its terminator.

## Try a valid buffer

In a separate practice case, use a nine-byte output array, call lookup, and inspect both the status and stored outcome before displaying the text. Add an assertion for the final zero byte. Keep the original too-small test: it verifies failure behaviour that the success case cannot establish.

## Review

Explain why changing the output variable before checking capacity would violate this contract even if no memory address was out of bounds. Memory safety and state consistency are related but separate obligations.


## Read the source

[Open the example source](../../../../labs/framework/message-retry/test_retry.c).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Use stable identities when requests are retried](05-stable-identity-and-retries.md) · [Next: Handle temporary ownership and safe deadlines](07-leases-time-and-overflow.md)
