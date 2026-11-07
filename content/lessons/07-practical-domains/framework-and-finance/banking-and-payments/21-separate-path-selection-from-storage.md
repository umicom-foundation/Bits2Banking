<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/21-separate-path-selection-from-storage.md

PURPOSE:
Separate path selection from database operations

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate path selection from database operations

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## A filename is not an open database

A text entry contains characters. A storage service is an object that has actually opened and checked a database. Confusing these two states can make a program say it is ready before any file was opened.

The shared picker fills an entry. UmiGtk4BankOperationsLauncherSetPath can also fill that field from an explicit project choice. Neither function opens storage. The Banking operations command copies the entry text and passes it to the canonical banking service.

## Trace the boundary

1. Search the Framework adapter for UmiPathPickerGtk4Create. There is an existing-file mode and a new-filename mode.
2. Find UmiGtk4BankOperationsLauncherSetPath. It checks the widget, UTF-8 text and absolute path before changing the field.
3. Find OpenWorkspace. It reads and copies the chosen path.
4. Follow UmiBankOperationsOpenSqlite into src/bank_operations/runtime.c. The service applies its own path and repository rules.
5. Return to OpenWorkspace and identify the failure branch. It reports an error without constructing a partially usable banking window.

## Why check twice?

The GUI checks input for a useful interaction. The service checks its own contract because another caller may bypass the GUI. These are different responsibilities. Neither boundary should depend on the other being the only caller.

## Exercise

Try a relative path in the field. Then use a full absolute path. Observe the difference without introducing fallback locations. Record whether the selected text is preserved after an error.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/README.md).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Parent a shared Framework widget in a desktop application](20-parent-a-shared-framework-widget.md) · [Next: Keep an open workspace attached to its original database](22-keep-a-selected-workspace-stable.md)
