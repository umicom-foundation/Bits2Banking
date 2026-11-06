# Types and a small check

[Course contents](index.md) · [Next: Return an explicit error](02-return-an-explicit-error.md)

## Let the expected result be visible

Zig is a systems programming language with explicit types and built-in test declarations. This first lesson uses a test rather than version-sensitive console I/O. Install a stable Zig release from its official distribution and select the matching version of the language reference. Record `zig version`; development documentation can differ from an installed stable compiler.

Save this as `progress.zig`:

```zig
const std = @import("std");

fn remaining(target: u32, completed: u32) u32 {
    return target - completed;
}

test "three of five leaves two" {
    try std.testing.expectEqual(@as(u32, 2), remaining(5, 3));
}
```

`@import` makes another module available. `const` names a value that is not reassigned. `fn` defines a function; types follow parameter names after a colon. The type after the closing parenthesis is the return type. `@as(u32, 2)` makes the expected value's type explicit. The test compares expected and actual values.

Run `zig test progress.zig` from that folder. Expect the named test to pass. A successful result concerns this example and compiler, not the whole Umicom product. If Zig is not found, check its installation and terminal path; do not replace the command with a different language's compiler.

## Exercise and answer

Add a second test expecting remaining(5, 5) to equal zero. Then deliberately expect 1 and observe a failure. Restore the correct expectation. A check that has never been seen to fail may not be checking what you think it is.

The function currently assumes completed <= target. Passing a larger value violates that assumption and can underflow. It is not a complete validated counter. The next lesson replaces the implicit assumption with an explicit error result.

Read the real activity rule in Bits2Banking. Its guarded update provides the architectural comparison: accepted input, reported failure and unchanged output. A language exercise should make those decisions visible rather than silently fork the production Framework rule.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.c). Path: `labs/native/framework-activity/activity.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://ziglang.org/documentation/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-zig/lessons/01-types-and-a-small-check.html).

[Course contents](index.md) · [Next: Return an explicit error](02-return-an-explicit-error.md)

Sammy Hegab · Umicom Foundation · Original learning material.
