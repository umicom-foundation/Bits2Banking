<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/95-pause-before-a-reached-line.md

PURPOSE:
Teach how to stop a checked source interpreter before a reached statement.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Pause before a reached source line

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](94-supply-a-signed-browser-input.md)

The temporary **until** command pauses before a reached statement that starts on the requested line. A line can be present in the file and still be skipped by a branch.

## Practice with two runs

1. Save the program below as **pause.c**, with the first line at line 1. Use a build of Umicom C that supports **until**.
2. Run **umicom-c interpret pause.c --step**. Type **until 6** at the prompt. Expect the initial value and condition steps, then a prompt at line 6 before the addition executes.
3. Type **next** twice. Look for **Result: 42**. Rerun, type **until 4**, and observe the same result plus a diagnostic that line 4 was never reached. The false condition skips the body.
4. Start again, pause with **until 6**, then type **quit**. The earlier step rows stay visible. This run has no returned value.

~~~c
int main(void) {
    int total = 8;
    if (0) {
        total += 99;
    }
    total += 34;
    return total;
}
~~~

## Explain the checks

The target changes where the console prompts. Try the same run with **--max-steps 1**. The instruction limit still stops the program before line 6. A command such as **until 6junk** leaves the prompt in place.

Trace rows and the returned value go to standard output. Prompts and information about an unreached line go to the diagnostic stream. Predict what happens if you split the line 6 statement across two lines. The pause matches the line where the statement begins.

## Separate program text from commands

In PowerShell, send the same program text through the input stream. Expect the trace and **Result: 42** after the stream closes.

~~~powershell
Get-Content -LiteralPath pause.c -Raw | umicom-c interpret --stdin
~~~

**--stdin** and **--step** compete for the same input stream. The CLI refuses the combination before reading the program. Draw separate arrows for program text, interactive commands and trace output. Explain which arrows the file-based and piped runs need.

If the tool cannot find the command, check which Umicom C executable is on your path and check that you used **--step**. [Umicom C interpreter guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/source-interpreter.md)

[Next lesson, read versioned interpreter reports](96-read-versioned-interpreter-reports.md)
