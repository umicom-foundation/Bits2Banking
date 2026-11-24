<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/102-require-a-complete-debugger-command.md

PURPOSE:
Require a complete debugger command

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Require a complete debugger command

A debugger reads commands that tell a program when to step, continue or stop. The command stream may come from a terminal, a file or another program. Read the complete command line before choosing an action. A line that looks valid at its start may contain an extra byte later.

## Understand the bytes in a line

| Bytes or event | What it means in this exercise |
| --- | --- |
| `0D 0A` | Carriage return and line feed, a common Windows line ending. |
| `0A` | Line feed. |
| `1A` | A control byte associated with Ctrl+Z. A translated Windows C input stream can treat it as end-of-file. |
| `00` | A zero byte. It may terminate a C string, so a command reader needs to recognize and reject it before parsing. |
| End of the stream | There are no more bytes. A complete last command may end here without a newline. |

Windows binary input mode supplies the original redirected bytes. The checked Umicom C debugger can then reject malformed commands and still recognize a legitimate CRLF line ending. The terminal can continue to use its normal interactive input mode. The interpreter's source-file input is separate from the debugger's command input. [Microsoft C runtime translation modes](https://learn.microsoft.com/en-us/cpp/c-runtime-library/translation-mode-constants?view=msvc-170)

## Define when a command is admitted

The command reader can collect up to 63 command bytes in this profile. CRLF completes the physical line and the carriage return does not use one of those bytes. A disallowed control byte or excess command text makes the entire line invalid. The reader advances to the next line before asking again. Only a validated command goes to the source or instruction debugger.

~~~text
READ the whole command through its line ending or actual end of stream
IF it contains a forbidden byte OR is longer than the command limit
    REFUSE the command without moving the program
OTHERWISE
    INTERPRET the complete command
~~~

Read the three expected behaviors together. A valid `continue` ending at actual end-of-stream can complete the small test program. A longer line beginning with `continue` and containing a forbidden byte leaves the program paused. A valid line of 63 command bytes followed by CRLF is admitted, and the neighboring 64-byte line is refused.

## Observe the existing tests

1. Open `tests/check_debugger.cmake` in the Umicom C checkout. Find the controlled long, end-of-file and bytecode cases. The fixtures create their own known byte sequences.
2. Open a terminal beside a configured Umicom C build with testing enabled. Build the `umicom-c` target before invoking its debugger CLI tests.
3. Replace `build` below if your configured build has a different name. Expect three selected, passing tests. Read the printed test name before recording a pass.

~~~powershell
cmake --build build --target umicom-c
ctest --test-dir build -R "^umicom[.]c[.]debugger[.](long|eof|bytecode)$" --output-on-failure --no-tests=error
~~~

Use the automated fixtures for control-byte checks so you know exactly which bytes reached the parser. When a boundary result seems surprising, look at the input bytes and the program step separately. A text editor or test script can translate line endings before the debugger reads them. The fixture checks the CRLF bytes to keep that translation visible.

[Course contents](index.md) · [Previous: Read adjacent assertion messages](101-read-adjacent-assertion-messages.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/102-require-a-complete-debugger-command.html)

[Next: Translate whitespace that both languages admit](103-translate-whitespace-that-both-languages-admit.md)
