# Chapter 177 — From request handoff to completion delivery

**Bits to Banking · Engineering track · Umicom Foundation**  
**Language:** ISO C23 · **Lab:** `labs/native/work-dispatch`  
**Prerequisites:** Chapters 172–176 and a working CMake/Ninja installation.

## The problem: accepted is not completed

When a customer asks a bank application to display a cash-position report, the UI sends a request. Three different facts matter: (1) the service accepted the request; (2) the service finished processing it; and (3) the original requester received the result. They do not necessarily happen together. A server can finish calculating while the UI is temporarily busy. A user can close a tab while an older report remains queued. A software service must never describe *accepted* work as *delivered* work.

Update 29 introduced a **handoff** queue. `BtbWorkSubmit` copies the request into bounded, queue-owned storage; `BtbWorkAcquire` gives the processing component a borrowed view; `BtbWorkComplete` marks the operation terminal; and `BtbWorkRelease` permits slot reuse. This is the producer-to-worker half of the journey. Update 30 adds a separate completion notification and an explicit receipt operation.

![The composed request lifecycle](../../assets/diagrams/dispatch-composition.svg)

Our running example uses text such as `CASH|GBP|ACCOUNT-A`. It is deliberately a **mock request**, not a bank instruction or an authenticated API. The work performed is a deterministic diagnostic digest of these bytes. This allows us to inspect lifetime and ordering without creating a second bank, HTTP server or Framework task engine.

## Learning objectives

By the end of this lesson, you should be able to locate the authoritative owner of every byte at each stage, distinguish completion production from completion consumption, and prove that a slot is not recycled while its completion remains undelivered.

## Trace one operation in real source

Read `labs/native/work-dispatch/dispatch.h` before looking at `dispatch.c`. The public contract contains three important types:

```c
BtbDispatch dispatcher;              /* Caller owns this whole object. */
BtbDispatchIdentity identity;        /* Caller owns the returned token. */
BtbDispatchReceipt receipt;          /* Caller receives a value copy. */
```

The key operations are intentionally small:

```c
BtbDispatchInit(&dispatcher);
BtbDispatchSubmit(&dispatcher, 1001U,
                  "CASH|GBP|ACCOUNT-A", 18U, &identity);
BtbDispatchStep(&dispatcher);
BtbDispatchReceive(&dispatcher, &receipt);
```

Check that your manual length really matches the bytes supplied. The actual demo calculates its length, rather than trusting a typed number; in production, an API should receive an explicit size from the parser that validated its input. The string above has 18 bytes (excluding `\0`). If you change its contents, update the length.

`Submit` copies bytes into the **existing** `BtbWorkQueue` (capacity eight, maximum 96 bytes per record). `Step` borrows the queued bytes, evaluates a deterministic FNV-1a diagnostic digest and pushes a terminal notice into the **existing** completion queue (capacity four). `Receive` returns a caller-owned receipt, consumes the terminal notice and then releases the work slot.

The receipt contains request ID, slot/generation token, connection ID, original length, completion status and digest. A digest can help compare demonstrations, but FNV-1a is **not** cryptographic: never treat it as a signature, audit guarantee or proof of financial correctness.

## Why the two acknowledgements matter

Consider a user closing the Bank dashboard as soon as the report finishes. The queue may say `BTB_WORK_COMPLETE`, but its completion notice has not yet been received. It would be unsafe to reuse that slot without first finishing the delivery protocol. In this lab, `BtbDispatchReceive` is the only normal release point. This is a deliberate adapter decision; it does not change the Update 29 queue API.

There are three useful counters:

| Field | Meaning |
|---|---|
| `accepted` | Number of requests successfully copied into the work queue. |
| `succeeded` and `cancelled` | Number of terminal outcomes produced. |
| `delivered` | Number of receipts consumed and their slots released. |

The invariant is `accepted = delivered + records still owned`. A second invariant is `succeeded + cancelled = delivered + pending completion notices`. `BtbDispatchInvariants` checks both and verifies identity mappings. These are stronger than merely asking whether the worker queue has no waiting entries.

## Build and observe

From the Bits2Banking repository in PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
& ".\output\learning-build\work-dispatch\btb-work-dispatch-demo.exe"
```

Expect three accepted requests and three delivered results, followed by `PASS`. Actual digest values are determined by the source bytes. No socket is opened and no payment or broker action is sent.

## Guided exercises

1. Trace request ID 1 through `Submit`, `Step` and `Receive`. At each operation, identify who owns the input and output storage.
2. In a debugger, inspect `dispatcher.notifications.count` **after** `Step` but **before** `Receive`. Why is the original work slot still occupied?
3. Alter the demo's request text, rebuild and compare its diagnostic digest. Explain why matching digests do **not** establish cryptographic identity.
4. Run `ctest --test-dir ".\output\learning-build\work-dispatch" -R "dispatch.fifo" --output-on-failure` and explain the requested result ordering.
5. **Design question:** in real Umicom Trader, where should the current request generation be kept when a chart is refreshed rapidly? Explain how a stale completion should be refused.

**Check your understanding:** A queued request has been accepted, not executed. A completed request has been executed, not necessarily delivered. A delivered receipt is an owned value; the original work slot may now be recycled.

**Next:** [Compose two existing C23 libraries](178-compose-existing-c23-libraries.md).
