<!--
Umicom Bits2Banking
File: labs/framework/delivery-tickets/README.md

PURPOSE:
Run and understand the Framework delivery-ticket consumer lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Delivery tickets and restarted workers

This lab shows how two attempts with the same worker name receive different acquisition identities. It calls the Framework messaging library; it does not reimplement lease rules.

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

For a fuller introduction to C syntax, use [Learning C](../../../content/courses/learning-c/index.html). You can complete the explanation below without leaving this lesson.

## Expected output

```text
First acquisition is owned at 119 and expired at 120.
Stale release rejected; replacement remains owned.
Replacement released.
```

## Files and functions

| File or function | Purpose |
| --- | --- |
| [main.c](main.c) | Calls the SDK and checks observable state |
| [CMakeLists.txt](CMakeLists.txt) | Finds the messaging SDK and registers the consumer check |
| report | Compares one returned status and explains a mismatch |
| main | Creates the store, performs the scenario, and releases memory |
| umi_delivery_lease_store_create / destroy | Own the store allocation and cleanup boundary |
| umi_delivery_lease_acquire_ticket | Publishes a fresh generation only after successful acquisition |
| umi_delivery_lease_ticket_is_owned | Observes the exact acquisition at a supplied time |
| umi_delivery_lease_release_ticket | Releases that acquisition only |

## Explore carefully

1. Read the source before running it. Locate first and replacement.
2. Run the unchanged example and compare its output.
3. In a practice copy, change the second acquisition time from 120 to 119. Rebuild. BUSY should cause the example to fail.
4. Restore the time. Change the delayed release to use replacement. The example should detect the unexpected successful release.
5. Restore the original code and rerun.

The example uses no sleeps, threads, network, credentials, payment or trade. Each work item in an asynchronous application must keep its own ticket and keep its context alive until every callback has finished. Store destruction invalidates all tickets for that store. Do not reuse tickets with a new store.

## Continue

[Follow the five-lesson module](../../../content/courses/learning-rabbitmq/lessons/09-workers-restarts-and-acquisition-identity.html). The preceding lessons explain queues, acknowledgements and idempotency. Local leases do not enforce a durable external effect; the module explains the additional boundary needed.
