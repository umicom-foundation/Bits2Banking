<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-rabbitmq/11-callback-ownership-and-lease-renewal.md

PURPOSE:
Keep lease ownership with an asynchronous work item

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep lease ownership with an asynchronous work item

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

You will design a work context that keeps a ticket with the callback that acquired it. You will also distinguish renewal from starting another acquisition.

## Define the work context

An asynchronous operation starts now and completes later. Its callback needs enough information to identify its original work. A **context** is a structure containing that information.

~~~c
typedef struct PreviewWork {
    UmiDeliveryLeaseStore *store;
    UmiDeliveryLeaseTicket ticket;
    const char *owner;
} PreviewWork;
~~~

The structure groups a borrowed store pointer, a copied ticket and an owner string pointer. Borrowed means this structure does not decide when the store is freed. The application must ensure that the store and owner string outlive every callback using them.

For a real implementation, either use an owner string with a clearly longer lifetime or copy it into owned bounded storage. Do not keep a pointer to a local array after the function containing that array returns. That would be a dangling pointer: an address whose intended object no longer exists.

The context must also remain alive until completion or confirmed cancellation. A ticket protects acquisition identity; it cannot repair a freed context.

## Renewal is not acquisition

An unexpired ticket acquisition returns BUSY even when the owner name matches. To keep the same attempt alive, call **umi_delivery_lease_renew_ticket**.

~~~c
UmiStatus status = umi_delivery_lease_renew_ticket(
    work->store, work->ticket, work->owner, now, duration);
~~~

The arrow selects a structure field through a pointer. This fragment assumes work points to a live context and now and duration have already been obtained. It is an integration sketch, not a complete asynchronous application.

A successful renewal retains the generation. Its new deadline is now plus duration. Renewal at the previous deadline is too late. Invalid or overflowing duration leaves the previous deadline unchanged.

## Plan cancellation carefully

1. Mark the work context as cancelling in the application's own job state.
2. Ask the operation to stop using its supported cancellation mechanism.
3. Wait for the completion or cancellation acknowledgement required by that mechanism.
4. Release the exact ticket if it still identifies the stored record.
5. Free the context only when no callback can use it.

Do not assume that requesting cancellation immediately destroys every pending callback. This is a common route to dangling pointers.

## Legacy callers

The older name-only renew and release calls refuse ticket-protected records. This ensures that an older callback cannot bypass generation checking by supplying only the owner name. Existing legacy-only records keep their original behaviour.

## Practice and summary

Draw two boxes for two work contexts with the same owner string. Give them different generations. Connect an old completion callback to the first box. Explain why it must never look up a shared "current ticket" and substitute that value.

Safe integration requires both valid memory lifetime and valid acquisition identity. Neither one replaces the other.

## Read the source

[Open the example source](../../../../labs/framework/delivery-tickets/README.md).

## Continue learning

[Course contents](../../../courses/learning-rabbitmq/index.html) · [Previous: Trace a complete Framework delivery-ticket program](10-trace-the-delivery-ticket-program.md) · [Next: Connect local work ownership to durable message effects](12-local-leases-and-durable-message-effects.md)
