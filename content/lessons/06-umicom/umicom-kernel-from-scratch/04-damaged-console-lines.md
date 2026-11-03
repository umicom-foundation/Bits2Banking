# Never execute a damaged prefix

Console input arrives as a stream. A control byte, overflow or lost input can invalidate a whole command. Removing the bad byte and executing the remaining prefix can change the meaning of an administrative request.

## Inspect the line owner

`UmicomKernelConsoleLineFeed` tracks a bounded line and a discard flag. Unsupported input marks the line damaged. A later newline returns `UMICOM_CONSOLE_LINE_REJECTED` and clears the unusable input. Backspace cannot repair bytes that were already lost. Explicit clear and cancel remain deliberate operations.

1. Read the `line-loss` case in `labs/native/kernel-bounded-input/test_input.c`.
2. It feeds a printable character, a NUL byte and a newline. Predict each event.
3. It then feeds a clean new line. Verify why rejection of the first line must not poison all future input.
4. Read the existing console tests for CRLF framing, overflow and input loss before extending the editor.

## Exercise

Add a local case with more than the line capacity followed by backspace and newline. It should reject the line, not produce a shortened command. Then consume a clean line and explain which state must survive to treat CRLF as one submission.

This input policy is useful beyond an educational shell, but it does not turn the machine-mode administration console into a user login service or a security boundary. Privilege separation and trusted pointer admission remain separate work.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/04-damaged-console-lines.html) · [Learning sequence](../../../start/learning-sequence.md)
