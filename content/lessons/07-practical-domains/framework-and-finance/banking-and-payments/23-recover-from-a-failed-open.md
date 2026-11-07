<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/23-recover-from-a-failed-open.md

PURPOSE:
Recover from a failed open without replacing user data

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Recover from a failed open without replacing user data

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## Treat failure as a state transition

Opening can fail because a folder is missing, access is denied, the file is not a suitable database, or a storage dependency is unavailable. A useful application returns to a state where the user can correct the problem. It does not need to crash or invent a different location.

## Run the recovery exercise

1. Choose a filename under a folder that does not exist. Do not create that folder yet.
2. Press Banking operations. Read the failure message.
3. Confirm that no empty operational window is left open.
4. Correct the path to an existing practice folder.
5. Press Banking operations again.
6. Close and reopen the resulting file.

The service returns a status value. UMI_STATUS_OK means its open contract completed successfully. Any other result follows the error branch. The adapter frees its copied proposed filename on that branch and retains no half-open service.

## Keep old data safe

An older per-user database is not migrated automatically. Close applications that use it, make a backup through your normal file-management workflow, and select it explicitly. If it fails to open, investigate the format and version instead of deleting it. Never use real banking records in this practice lab.

## Explain the result

Write down the selected path, expected outcome and actual message for each attempt. Do not include account credentials or private record contents in a shared defect report.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/README.md).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Keep an open workspace attached to its original database](22-keep-a-selected-workspace-stable.md) · [Next: Test native events while isolating persistent storage](24-test-events-without-touching-user-data.md)
