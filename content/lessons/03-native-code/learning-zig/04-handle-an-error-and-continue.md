<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-zig/04-handle-an-error-and-continue.md

PURPOSE:
Explain the lesson: Handle an error and continue.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Handle an error and continue

An error does not always mean the entire program must stop. Sometimes a batch contains independent requests, and one refusal should be reported while later requests continue.

## Setup recap

Read main.zig and activity.zig in labs/languages/zig-activity. Use Zig 0.15.2 and the lab README for the complete compilation command.

The example array contains four counts. Each is a separate input; this is not a sequence that automatically feeds one output into the next call.

## 1. Read catch

The call to activity.advance can produce an error. The catch block handles that case by printing a refusal and continuing the loop.

On success, execution proceeds to the line that prints current and next. On refusal, continue skips that success line.

This prevents a refused request from being presented as a valid new count.

## 2. Trace the loop

Write a two-column table for inputs 0, 41, 999 and 1000. Fill in the expected output for each.

Now add 12 after 1000 in a practice copy. The refusal should not prevent the later input from producing 13.

A program that processes a financial transaction group might require different behavior, such as stopping the whole group. Error handling must follow the feature's contract rather than a universal rule to continue.

## 3. Know where the output goes

The example uses std.debug.print. Its output goes to standard error. A terminal normally displays that stream alongside standard output, but redirection can separate them.

If a log is empty, check which stream was captured before concluding that no code ran.

## Exercise

Replace the values on paper with 1000, -1 and 0. Predict the order of all messages. Then explain why a local next variable must not be read after a refused result.

## Recovery

An error-union type mismatch usually means a possible error has not been handled or propagated. Read the diagnostic at the call site. Do not remove the error from the API simply to silence the compiler.

This example teaches control flow. It does not implement background jobs, retries or automatic network reconnection.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/zig-activity/main.zig). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-call-the-shared-c-model.md) · [Next lesson](05-build-a-mixed-language-program.md)

