<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/39-trace-an-event-to-a-framework-rule.md

PURPOSE:
  Present "Trace an event to a shared Framework rule" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace an event to a shared Framework rule

A button becomes useful when its event reaches a rule and the result reaches the screen. This lab makes that path visible using the existing activity window. It is a small teaching example of the separation used by Umicom applications.

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

An event is a notification that something happened. A callback is a function registered to receive that notification. GTK owns the event delivery; the activity rule decides whether the count may advance. The rule is in activity.c, outside the window code. This lab is a practice adapter, not a replacement implementation of the production Framework progress service.

```text
button click → Completed → BtbActivityAdvance → status + count
                    ↓                              ↓
              window-owned state ← label text refresh
```

## Work through the lab

1. Find the button created with the label Record one exercise. Follow g_signal_connect_object to the Completed callback. Write down the event name clicked.
2. Find the state attached to the window under activity. Draw two fields: completed for the number and label for the widget displaying it.
3. Follow Completed into BtbActivityAdvance. Read both files side by side. Mark the rule's possible statuses and the text the callback chooses for success and failure.
4. Design three UI checks: one click advances once; repeated clicks update the same label; closing the window disconnects its associated callback. For each check, record an action and an observable result.

## Expected result

The initial label describes zero completed exercises. A successful first callback produces Completed exercises: 1. The source keeps the window alive during callback work and releases that temporary reference afterwards.

## If the result differs

If a control appears idle, distinguish a missed event from a rejected rule. Check the connection, then the callback, then the returned status. A test calling the rule directly cannot prove that a mouse click reaches it.

## Explain it yourself

Where should a second application obtain the same production progress policy?

<details>
<summary>Worked explanation</summary>

From a shared Framework service with a documented contract. Its client should translate input events and present the result. Reimplementing the policy in each callback allows the applications to disagree.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../courses/umicom-development/lessons/39-trace-an-event-to-a-framework-rule.html)

[Terminal and editor setup guide](../learning-c/terminal-to-visual-studio.md)

[Previous lesson](38-incremental-functions-and-failure-contracts.md) · [Course contents](index.md)

[Next lesson: Plan one C model for several interfaces](40-one-model-several-interfaces.md)
