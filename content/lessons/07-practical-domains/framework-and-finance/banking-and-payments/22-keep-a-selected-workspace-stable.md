<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/22-keep-a-selected-workspace-stable.md

PURPOSE:
Keep an open workspace attached to its original database

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep an open workspace attached to its original database

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## Two kinds of state

The launcher stores the proposed next filename. The operational window stores the filename it successfully opened. These are separate values. Editing the proposal must not silently redirect an already-open service.

## Explore the lifecycle

1. Open practice-a.sqlite.
2. Leave that operational window open and change the launcher field to practice-b.sqlite.
3. Press Banking operations again. The same window should be presented, still attached to practice-a.sqlite.
4. Close the operational window. This releases the banking service.
5. Press Banking operations again. Now the selected practice-b.sqlite path is used.

The adapter copies the path with g_strdup. The operational window owns that copy and releases it during destruction. It does not keep a borrowed pointer into the entry's mutable text.

## Borrowed pointers and dangling pointers

A borrowed pointer lets code inspect someone else's data without owning it. gtk_editable_get_text supplies such a pointer. Editing or destroying the entry can invalidate the text. A dangling pointer still holds an address after the associated storage is no longer valid. Copying text before retaining it prevents this particular lifetime bug. It does not make arbitrary pointer use safe.

## Exercise

In the adapter, locate the path copy, assignment to ui->path and g_free in UiFree. Explain why all three are required. A copy without a release leaks memory; a release without exclusive ownership can free another object's storage.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/main.c).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Separate path selection from database operations](21-separate-path-selection-from-storage.md) · [Next: Recover from a failed open without replacing user data](23-recover-from-a-failed-open.md)
