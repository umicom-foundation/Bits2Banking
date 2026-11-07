# Return an explicit error

[Course contents](index.md) · [Previous: Types and a small check](01-types-and-a-small-check.md)

## Describe both outcomes

Continue after the first Zig test. An error union represents either a successful value or an error. It makes a failure path part of the function's type. Save this complete example as `checked-progress.zig`:

```zig
const std = @import("std");

fn remaining(target: u32, completed: u32) error{BeyondTarget}!u32 {
    if (completed > target) return error.BeyondTarget;
    return target - completed;
}

test "valid count" {
    try std.testing.expectEqual(@as(u32, 2), try remaining(5, 3));
}

test "reject a count beyond target" {
    try std.testing.expectError(error.BeyondTarget, remaining(5, 6));
}
```

Run `zig test checked-progress.zig`. Expect both checks to pass. `error{BeyondTarget}` names the allowed error set. `!u32` adds the successful result type. In the first test, the inner `try` obtains the value or propagates an error. The outer `try` propagates a failed comparison. In the second test, passing the entire result to `expectError` checks the rejection itself.

## Follow the branch

```text
completed <= target -> subtraction is valid -> return remaining count
completed > target  -> return BeyondTarget -> no subtraction
```

The guard is before subtraction. Checking after an unsafe calculation would be too late. The same order matters in C bounds checks and memory-size calculations.

## Exercise and answer

Add checks for target=0/completed=0 and target=0/completed=1. The first returns zero; the second returns BeyondTarget. Explain why both are needed: zero is a valid boundary, not an automatic error.

Compare this result with Framework's status-based interfaces. Different language syntax can express similar contracts, but a native ABI cannot be guessed from a Zig error union. Future integration requires an explicit C-compatible adapter and ownership rules. This lesson adds no such binding; it teaches how to make a local calculation's failure visible and testable.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.c). Path: `labs/native/framework-activity/activity.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://ziglang.org/documentation/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-zig/lessons/02-return-an-explicit-error.html).

[Course contents](index.md) · [Previous: Types and a small check](01-types-and-a-small-check.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next: Call the shared C model](03-call-the-shared-c-model.md)
