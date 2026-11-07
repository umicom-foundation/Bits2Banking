<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/12-local-leases-and-durable-message-effects.md

PURPOSE:
Connect local work ownership to durable message effects

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect local work ownership to durable message effects

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

You will separate a local scheduling decision from a durable business result. This matters for statement preparation, order processing and training jobs where a repeated action may have consequences.

## Define the terms

**Durable** means a result survives a process stopping and restarting. A local lease store is held in memory, so it is not durable. **Idempotency** means repeating a request has the same intended effect as processing it once. A **transaction** groups changes so the storage system commits them together or rejects them together.

An acknowledgement tells a message broker that a delivery has been handled according to the consumer's protocol. It does not by itself prove that a bank ledger, file export or model checkpoint was committed.

## Examine a dangerous sequence

1. Worker A acquires a local lease.
2. A pauses for a long time.
3. Its lease expires and worker B acquires the same job.
4. B commits a result.
5. A resumes and sends its own result to an external service.

The Framework ticket API can reject A's later renewal or release. It cannot reach into A's external service call and prevent it. Checking local ownership before sending is useful, but time can advance between the check and the effect.

## Put authority at the commit boundary

For a durable application, design the storage or provider boundary to verify the operation's stable identity and any required generation inside the same authoritative operation that commits the result. Do not implement a separate "check then write" race.

This is a design requirement, not a capability supplied by the in-memory lab. Different providers offer different transaction and idempotency contracts. Inspect the chosen provider's documented guarantees before adopting it.

A statement job may write a result under a unique export identity. A training job may publish a checkpoint only if the coordinator still accepts its assignment generation. A broker order needs the broker's order-identity and reconciliation rules. Sharing a lease API does not make those domain rules interchangeable.

## Design exercise

Create a four-column table:

| Operation | Stable identity | Authoritative result store | Recovery question |
| --- | --- | --- | --- |
| Prepare a statement | Statement request ID | Statement metadata and output record | Was the result already published? |
| Generate a preview | Asset and revision ID | Preview catalogue | Is this still the current asset revision? |
| Publish a training checkpoint | Run, task and attempt IDs | Coordinator and checkpoint manifest | Is this attempt still accepted? |

These are example designs, not claims that the applications have completed those integrations.

For each row, add the action required after a timeout. A timeout means the caller did not receive a result in time; it does not prove that the remote operation failed. Query or reconcile before blindly retrying.

## Summary

Use local tickets to coordinate local work. Use a durable authority to decide whether an external result is accepted. Keep acknowledgements, cancellation, idempotency and ownership as explicit parts of the workflow, each with its own evidence.

## Read the source

[Open the example source](../../../../labs/framework/delivery-tickets/README.md).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Keep lease ownership with an asynchronous work item](11-callback-ownership-and-lease-renewal.md) · [Next: Test stale workers without sleeps or a broker](13-regression-tests-for-stale-message-workers.md)
