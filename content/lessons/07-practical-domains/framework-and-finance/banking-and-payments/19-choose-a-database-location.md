<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/19-choose-a-database-location.md

PURPOSE:
Choose a database location before opening a workspace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Choose a database location before opening a workspace

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## What you are building

A workspace groups the information used for a task. In this lab it includes a banking simulation database: a file of structured records that survives after the program closes. An absolute filename includes its starting location, such as a drive on Windows or the root directory on Linux. A relative filename depends on where the program was started.

## Follow the workflow

1. Open the lab source and find Activate. It constructs the host window and inserts the shared launcher.
2. Start the compiled lab and leave the filename blank.
3. Press Banking operations. Read the message asking for a location.
4. Create a practice folder using your normal file manager. Choose a new filename in it.
5. Before pressing Banking operations, inspect the folder. Merely choosing should not create a database.
6. Press Banking operations. The operational window should open for that selected file.

The important separation is intention → selection → execution. Selection records a proposed choice. Execution performs the operation. This makes a cancelled chooser harmless and makes the storage location visible.

## Check your understanding

Why should a program not silently fall back to a different folder when the chosen one is unavailable? The user may then believe their work was saved in one place while the application writes elsewhere. Show the error and let the user correct the choice.

## Troubleshooting

If no window opens, read the launcher's message. Check that the parent folder exists and is writable. A database open failure is not permission to discard or overwrite the file. Use a new practice filename if you are unsure what an existing file contains.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/main.c).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Next: Parent a shared Framework widget in a desktop application](20-parent-a-shared-framework-widget.md)
