<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/96-read-versioned-interpreter-reports.md

PURPOSE:
Teach how a tool reads checked C interpreter events and distinguishes an error from a return value.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Read versioned interpreter reports

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](95-pause-before-a-reached-line.md)

A person can read the interpreter's normal trace. An editor or test runner needs a predictable format so it can find the same fields on every run. JSON Lines gives it one structured object per line.

## Read a successful run

1. Save the following C program as **charge.c** with its first source line on line 1.
2. Use an Umicom C executable that lists **--jsonl** in its help. If PowerShell cannot find **umicom-c**, use the full path to the executable you built.
3. Run the PowerShell commands below. Expect a **step** for the declaration, a **step** for the return, and a **result** with the value **42**.

~~~c
int main(void) {
    int amount = 40;
    return amount + 2;
}
~~~

~~~powershell
$events = @(umicom-c interpret charge.c --jsonl | ConvertFrom-Json)
$runExit = $LASTEXITCODE
$events | Format-Table event, stepKind, firstLine, ok, value
$runExit
~~~

Each record contains **schema** with the value **1**. The schema is the agreed layout of a record. A consumer can check the version before reading fields such as **firstLine** or **value**. In this run **firstLine** is **2** for the declaration and **3** for the return. An exit code of **0** means the tool finished successfully. The program's return value is **42**, stored separately in the final event.

## See what a failed run keeps

Change **return amount + 2;** to **return amount / 0;** and save the file. Run the same PowerShell block. The declaration still produces a successful step. The return step has **ok** set to **False**, and the interpreter prints a separate diagnostic about division by zero. Expect exit code **1** and no **result** event.

Restore the addition and run it again. An editor could use **firstLine** to highlight a step and display diagnostics beside the source. Explain why it should check both the exit code and the final **result** event before displaying a returned value. Keep prompts and diagnostics separate from the JSON objects when collecting the report. [Umicom C interpreter guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/source-interpreter.md)

[Next lesson, check a constant before running C](97-check-a-constant-before-running.md)
