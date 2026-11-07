<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/learning-linux-development/03-follow-an-exit-status-to-the-terminal.md

PURPOSE:
  Present "Follow an exit status to the terminal" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow an exit status to the terminal

A command can print a useful sentence and still fail. This lesson separates a program's displayed output from its exit status, then shows how a terminal can report the status of the command that just finished.

Source to open: `Umicom-Bits2Banking/labs/native/framework-activity/console.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'labs\native\framework-activity\console.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'labs/native/framework-activity/console.c'
```

## Understand the idea

A command-line program has several ways to communicate. Standard output normally carries ordinary results; standard error carries diagnostics. An exit status is a small result value that the surrounding shell can inspect. Conventionally zero indicates success and a nonzero value indicates a failure or other condition documented by the command. The terminal does not turn a printed word such as success into proof that a build worked. When a later command runs, the shell's most-recent-status value may change.

```text
native program exits -> shell records its status -> record it immediately
                                                   |
                                        then run another command
```

## Work through the lab

1. Open console.c and find its calls into the activity rule. Identify the successful and failing returns from main. Copy the actual messages into two columns labelled result and diagnostic; do not invent an output string.
2. In the existing lab setup guide, locate the command that runs the console executable. In your own notes, place printf 'status=%s\n' "$?" immediately after that command in Bash. In PowerShell, place $LASTEXITCODE immediately after the native executable call.
3. Explain what happens if you run another native program before recording the status. Draw the command-to-status sequence below. Keep the status next to the program and source revision it describes.
4. Prepare a small observation table with command, exit status, standard output and standard error. Use it when you later run the authorised lab. A source reading can predict the outcome, but only execution supplies the observation.

## Expected result

A useful record includes the exit status as well as text output. You should be able to tell a predicted return path from an observed process result and explain why a later successful command does not erase an earlier failure in the evidence.

## If the result differs

If the recorded status seems unrelated, check which command ran immediately before it. With pipelines, inspect the shell's pipeline rules; the last stage may be a logger rather than the program of interest. Do not conclude that an empty log means success.

## Explain it yourself

A compiler reports an error, then a log-writing command succeeds. Which result determines whether compilation succeeded?

<details>
<summary>Worked explanation</summary>

The compiler's result determines compilation success. The logger's result only tells you whether logging succeeded. Record both where needed, and do not continue to tests against an incomplete build as though compilation had passed.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-linux-development/lessons/03-follow-an-exit-status-to-the-terminal.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-processes-output-and-exit-status.md) · [Course contents](index.md)

