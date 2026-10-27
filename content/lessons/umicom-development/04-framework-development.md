# Umicom Framework Development

## Choose a small observable result

Our result is an exercise counter that can be used from a terminal or a window. It accepts counts from zero through 999, producing the next count. At 1000 it reports that capacity has been reached. Values above 1000 are invalid. Failed calls leave the caller's result unchanged.

Write this rule before writing the function. It provides examples to reason about: zero becomes one; 999 becomes 1000; 1000 is refused. The maximum is a teaching policy, not a statement about the largest integer the computer can store.

## Follow the contract into the implementation

Read [activity.h](../../../labs/native/framework-activity/activity.h) and [activity.c](../../../labs/native/framework-activity/activity.c).

The function returns UmiStatus and writes a count through an output pointer. These are two separate results: the status tells whether the operation succeeded; the output contains the count only after success. Callers must inspect the status before treating the output as a new answer.

The implementation checks next == 0 before dereferencing the pointer. A null pointer identifies no writable object. It checks current > 1000U before addition. This prevents invalid values, including the maximum unsigned integer, from wrapping into a misleading small result.

It handles current == 1000U as capacity exceeded. Only after all checks does it assign current + 1U to *next. The asterisk means “the object at this address.” The function does not allocate memory or keep the address after returning.

## Observe both success and refusal

Build the lab using [the CMake lesson](03-introduction-to-cmake.md). Open [test_activity.c](../../../labs/native/framework-activity/test_activity.c). Each named case checks an externally meaningful contract.

The full and invalid cases initialise the output to 77 before calling the function. They then check that the output is still 77. This sentinel makes an unwanted write visible. Checking only the returned error would miss a function that damaged the output before failing.

The in-place case passes the address of the same variable whose value was supplied. It confirms the behaviour used by the console and GTK examples. The input is passed by value, so the function receives a copy of that unsigned count.

## Trace one failure on paper

Take current = 1000 and result = 77.

1. next is a valid address, so the pointer check passes.
2. current is not above 1000, so it is within the accepted representation.
3. current equals the capacity, so the function returns CAPACITY_EXCEEDED.
4. Execution never reaches the assignment. result remains 77.

Now repeat with current = 999. The checks permit the assignment and result becomes 1000. This walkthrough explains why a boundary test is more useful than testing only typical values such as five.

## Make an intentional feature change

As an exercise in a disposable copy, change the teaching limit from 1000 to 20. Before editing, list every affected contract: the header comment, validation conditions, boundary tests and user-facing explanation. Keep the original lab for comparison.

A limit should eventually have one named definition when several callers need it. Do not scatter unexplained numeric values across independent implementations. The lesson keeps its small original function visible so you can identify the duplication yourself.

If you add persistence later, decide who owns the file, when writing occurs, how errors are reported and how existing data is preserved. Do not silently save from a display callback. A view should not gain permission to change storage merely because it displays a count.

## Keep shared code in the right place

The activity rule belongs to this teaching application. Framework supplies the shared status contract. In a real product, reusable file, lifecycle and platform mechanisms belong in Framework. Two product windows should call the same service instead of maintaining similar copies with different error handling.

**Question:** A test reports the expected failure status but the output changed. Is the implementation correct?

**Answer:** No. The unchanged-output promise is part of the interface. Repair the implementation and retain a regression that checks both the status and the stored value.

Continue with [Introduction to GTK4](05-introduction-to-gtk4.md).

[Course contents](index.md)
