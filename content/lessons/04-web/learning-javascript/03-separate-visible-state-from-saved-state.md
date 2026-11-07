<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-javascript/03-separate-visible-state-from-saved-state.md

PURPOSE:
  Present "Separate visible state from saved state" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate visible state from saved state

The task-board example updates a list in memory and attempts to save it in the browser. These are two separate operations. We will trace what happens when the storage operation fails.

Source to open: `Umicom-Bits2Banking/content/labs/task-board/board.js`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\task-board\board.js'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/task-board/board.js'
```

## Understand the idea

tasks is an array: an ordered collection held by the running page. localStorage keeps strings for a browser origin between visits when storage is available. JSON.stringify converts the array to a string; it does not guarantee that setItem will succeed. The try/catch block lets the program continue after a storage exception.

```text
submit → tasks.push → storage attempt → renderTasks
                              ↓ failure
                        console warning; memory still changed
```

## Work through the lab

1. Find the submit handler and number its operations: prevent the default submission, trim text, reject empty text, push a task, try to save, clear the input, render.
2. Draw the array and saved JSON separately. Start with an empty list and trace adding Read GTK. Both contain the task after a successful write.
3. Now imagine setItem throws. Follow the catch block, then continue to renderTasks. Identify the warning's destination: the developer console, not a visible status label.
4. Write a UI requirement for this case: show Unsaved changes near the list and offer a retry. Describe the state needed before changing code.

## Expected result

The current code can display a new task even when saving failed. A subsequent reload may therefore show older stored tasks. textContent displays task strings as text rather than interpreting HTML.

## If the result differs

If tasks vanish after reload, first inspect the browser origin and storage result. A page opened from another origin does not share the same storage. Do not mistake a visible row for proof of a completed write.

## Explain it yourself

Should a retry add another copy of the task to the array?

<details>
<summary>Worked explanation</summary>

No. The task is already in memory. A storage retry should attempt to persist the current state without repeating the original add operation. Otherwise one failed write can become duplicate visible work.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-javascript/lessons/03-separate-visible-state-from-saved-state.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-local-storage-and-untrusted-data.md) · [Course contents](index.md)

[Continue: Wait for a native module before enabling actions](04-await-a-native-module.md)
