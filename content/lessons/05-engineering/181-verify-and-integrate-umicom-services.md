# Chapter 181 — Verify the composed C23 service and plan Framework integration

**Bits to Banking · Engineering track · Umicom Foundation**  
**Language:** ISO C23 · **Lab:** `labs/native/work-dispatch` · **Prerequisite:** Chapters 177–180.

## Verification is an engineering argument

A green build proves only that the compiler and linker accepted one configuration. It does not prove correct request ordering, memory lifetime, or shutdown. A good test plan states a claim, exercises a boundary that could falsify that claim and collects evidence that another developer can reproduce.

The Update 30 lab registers nine CTest cases. Eight exercise the dispatcher contract directly, and one runs the executable demonstration. The stress case executes **80,000 deterministic state mutations** and checks invariants after each mutation. This tests more transition combinations without relying on thread schedules, sleeps or a network service.

## Native toolchain: Windows UCRT64

Use a PowerShell terminal, but **do not create PowerShell scripts**:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\work-dispatch" --output-on-failure
```

Expected registration: nine named tests (`fifo`, `capacity`, `cancel`, `stale`, `quiesce`, `invalid`, `ownership`, `stress`, `demo`). They are independently selectable with `ctest -R` and return failure status when an assertion fails, even in builds that define `NDEBUG`.

The build compiles three libraries: the prior work handoff and completion queue sources, plus the new integration adapter. Do not copy or rewrite previous modules simply to make this project compile. If the earlier directories are absent, first merge those earlier batches rather than filling the gap with a temporary replacement.

## What each test demonstrates

| Test | Falsifiable claim |
|---|---|
| `fifo` | Surviving queued work is processed in submission order; terminal receipts correlate with accepted IDs. |
| `capacity` | A full notification queue prevents both processing and cancelling another queued request without losing state. |
| `cancel` | A cancellation emits one terminal result; surviving work remains processable. |
| `stale` | A prior generation cannot affect a reused slot. |
| `quiesce` | Closing admission is separate from draining undelivered results. |
| `invalid` | Invalid pointers, sizes, budgets and exhausted IDs are rejected without output changes. |
| `ownership` | The queue deep-copies input; returned receipts remain valid after the work slot is cleared. |
| `stress` | State invariants remain true across 80,000 seeded operations and a final controlled drain. |
| `demo` | A small bank-report mock completes and drains without a socket or external provider. |

The `ownership` case compares a **known FNV-1a diagnostic digest** for a specified byte sequence; this is a regression check for byte handling, **not** a security hash assessment.

## GCC, Clang and memory analysers

The project uses ISO C23, disables compiler extensions and enables `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` on GCC/Clang. Where the installed compiler/runtime supports it, configure `-DBTB_ENABLE_SANITIZERS=ON` in a **different build directory** and run the same tests. ASan and UBSan can detect some lifetime and undefined-behaviour defects. A passing sanitizer suite still cannot prove thread safety, because no competing threads exist in this teaching model.

Review the exact compiler version using `gcc --version` or `clang --version`. Keep platform results separate: passing on Linux does not justify claiming that Windows UCRT64 or the full MkDocs publication pipeline passed.

## Framework promotion checklist

The native dispatcher is a **classroom integration example**, not a new production implementation in Umicom Framework. Before considering reuse in real Studio, Trader or TMS modules, review these questions:

1. What scheduling, task, completion, cancellation and wakeup services already exist in Umicom Framework?
2. Can an existing Framework contract carry `requestId`, `generation` and a terminal result, or must an ABI change be proposed?
3. Which controller owns admission policy, and which component owns the accepted bytes?
4. How will completed results reach GTK4's owning thread without an invalid cross-thread widget call?
5. What is the shutdown budget, and what happens when a worker cannot finish in time?
6. Which failures require retry, quarantine, or an explicit user-visible error?
7. What independent concurrency, sanitizers, platform and integration tests are required before shipping?
8. Which domain owns durable state? Never bypass the Framework Data Server to create an app-local copy.

Do not mistake architectural intent for current implementation evidence. No Framework or OS file is changed in this update, and no claim of a real worker pool or HTTP reactor integration is made.

## Capstone exercise

Draw the path of a `CASH|GBP|ACCOUNT-A` mock request through `Submit → WorkQueue → Step → CompletionQueue → Receive`. At every arrow, identify whether data is **owned**, **borrowed**, or **copied**. Then explain exactly which operation prevents a fifth undelivered notification and which predicate proves shutdown is complete. Run all nine CTest cases, record compiler, operating system and results, and retain the log as your acceptance evidence.

**Next:** [Git's working tree, index and history](182-git-working-tree-index-and-history.md), followed by the extended version-control learning track.
