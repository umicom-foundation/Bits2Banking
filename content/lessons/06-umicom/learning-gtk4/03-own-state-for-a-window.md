<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/03-own-state-for-a-window.md

PURPOSE:
  Present "Own state for the lifetime of a window" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Own state for the lifetime of a window

A window can outlive the function that created it. Its callbacks therefore need state that remains valid after that function returns. This lesson follows how the activity example creates, attaches and releases that state.

Source to open: `Umicom-Bits2Banking/labs/native/framework-activity/window.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'labs\native\framework-activity\window.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'labs/native/framework-activity/window.c'
```

## Understand the idea

A local variable ordinarily lives only until its function returns. g_new0 allocates a zero-initialised object with a longer lifetime. g_object_set_data_full associates that object with the window and supplies g_free as the function to release it. This is an ownership agreement: the window owns the allocation. It does not mean every pointer stored inside the object must be freed by g_free.

```text
window ─owns→ ActivityWindow { completed, label }
button ─clicked→ callback ─temporarily retains→ window
```

## Work through the lab

1. Find the ActivityWindow structure. Identify the count and the label pointer. Explain which holds a value and which refers to an existing GTK widget.
2. Find g_new0 and the call attaching activity to the window. Draw an arrow labelled owns from the window to the state allocation.
3. Find g_signal_connect_object. Its object argument connects the signal's lifetime to the window. Next inspect Completed: it takes a temporary reference before using state and releases it on return.
4. Write a manual check: open two practice windows, advance only the first, then close it. The remaining window should retain its own count. This is a proposed observation to perform when running the example, not a recorded result.

## Expected result

The code gives each activation its own state allocation. The label belongs to the widget hierarchy. Freeing the state allocation should not separately destroy the label pointer.

## If the result differs

If closing causes a crash, inspect who frees the state and whether callbacks can run after that. If two windows share a count unexpectedly, look for a global variable where per-window state was intended.

## Explain it yourself

Why would passing the address of a short-lived local ActivityWindow variable to a future callback be unsafe?

<details>
<summary>Worked explanation</summary>

The creating function could return before the click. The saved pointer would then refer to storage whose lifetime ended. Attaching allocated state to the window gives its lifetime an explicit owner.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-gtk4/lessons/03-own-state-for-a-window.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-connect-a-button-to-a-shared-rule.md) · [Course contents](index.md)

[Continue: Trace a button through a C callback](04-trace-a-button-through-a-callback.md)
