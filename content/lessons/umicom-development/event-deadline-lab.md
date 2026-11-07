# Lab: keep an event deadline observable

A graphical program handles work through an event loop. A click, a worker's completion or a timer can place work on a queue. A test often needs to wait until a particular operation finishes. The important question is whether that operation finished, not whether every unrelated event has disappeared.

## Setup recap: Prepare to follow the example

For the reading exercise you need a browser or text editor. No build is required. To compile the real regression later, prepare a compatible C23, CMake, Ninja and GTK4 environment and a Framework checkout. Use the [terminal setup lab](../learning-c/terminal-lab.md), then [the SDK consumer lab](sdk-practical-lab.md) for a smaller first project. Each command in a build workflow has a separate result: configuration prepares build rules, compilation creates executables, and testing executes checks.

The source study uses [the bank CSV test](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/bank_feed/test_csv_native.c), [the shared bounded dispatcher](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/support/main_context.h) and [the test registration](https://github.com/umicom-foundation/umicom-framework/blob/main/cmake/UmicomBankFeed.cmake). Inspect the revision you have; an older checkout may retain the earlier wait loop as active code.

## 2. Draw the control flow

```text
Start an import
      |
      v
Is this import still busy? --- no ---> inspect its result
      |
     yes
      v
Has the deadline expired? --- yes --> report a timeout
      |
      no
      v
Dispatch a bounded slice of events
      |
      +---------------------------> check busy again
```

Busy is state owned by the bank-feed service. A deadline is a time after which the wait must stop. The test uses a monotonic clock: time measured for elapsed intervals, independent of a user changing the wall clock.

## 3. Find the trap in an inner loop

Consider this small pseudocode example:

```text
while operation is busy and current time is before deadline:
    while an event was dispatched:
        dispatch another event
```

The outer condition looks bounded. But if an idle callback remains ready, the inner loop may always find another event. Execution never returns to the outer condition. The elapsed time can exceed the deadline even though each individual event dispatch is nonblocking.

An idle callback is work a main context can dispatch when ready; it can remain registered by returning a continue result. Nonblocking means an iteration does not wait for new work. It does not mean a repeated series of successful iterations is finite.

## 4. Read the shared correction

`UmiTestDispatchSlice` accepts a context, an absolute monotonic deadline and a maximum iteration count. It checks both limits before each iteration and returns to its caller. In the bank CSV fixture, 64 iterations form a slice, followed by another observation of completion and elapsed time. A short sleep avoids a tight polling loop when no useful event is ready.

The helper belongs in shared test support so fixtures use one reviewed rule. It cannot interrupt a callback that itself blocks forever. The outer CTest timeout still covers that separate class of failure. Removing timeout checks or ignoring warnings would not establish successful behaviour.

## 5. Design a regression that reaches the defect

The `event-deadline` case starts a real CSV import and requires it to be busy before entering the wait. It registers an unrelated callback at default priority which remains ready, then calls the same wait used by the normal import case. After completion, it removes that callback and verifies it actually ran. It also checks imported output and export availability.

Why check busy first? If a preparation step already completed the import, the wait loop could be skipped, allowing a broken wait implementation to pass the new test. Why remove the callback before checking success? The test must not leave a callback pointing at stack data after that data's lifetime ends.

## 6. Run only the relevant checks when ready

After configuring and building the test target `umicom-bank-feed-csv-native-test` in your chosen Framework or Applications build directory, run:

```text
ctest --test-dir <your-build-directory> -R "^framework\.bank_feed\.csv\.native\.(import|event-deadline)$" --output-on-failure --no-tests=error
```

Replace the angle-bracket placeholder before running. Expect two executed passes when the corrected fixture and environment work. A display-unavailable skip is not an executed pass. A timeout with no output needs more evidence; the presence of this loop defect alone does not prove that it caused every observed timeout.

## Exercise and answer

Draw a callback that repeatedly returns continue. Trace the old inner loop for three iterations and show where it checks elapsed time: it does not. Trace the bounded helper and show where it returns after its iteration limit. Finally imagine a callback that never returns. The helper cannot reach its next check; the process-level test timeout is needed.

[Framework course contents](index.md) · [SDK consumer lab](sdk-practical-lab.md)
