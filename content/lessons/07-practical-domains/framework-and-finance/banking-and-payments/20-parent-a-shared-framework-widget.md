<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/20-parent-a-shared-framework-widget.md

PURPOSE:
Parent a shared Framework widget in a desktop application

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Parent a shared Framework widget in a desktop application

Build a small desktop host around Framework banking services, then follow how an explicit filename becomes an owned workspace.

## Start here

You can read this lesson without prior banking or GTK knowledge. To run the exercise, obtain the Bits2Banking sources, install a C23 compiler, CMake, Ninja and GTK4, and install a matching Umicom Framework SDK with bank_operations_gtk4. A terminal is a window where you type commands; a build translates source files into an executable program. Follow the [Bank workspace lab setup](../../../../../labs/framework/bank-workspace/README.md) for complete PowerShell and Bash commands and expected behaviour. The lab uses practice records only.


## Objects and ownership

GTK represents windows and controls as objects. A reference keeps an object alive. A parent widget owns the child it displays. Keeping ownership explicit prevents a control from using memory after that memory has been released.

Read these two statements in Activate:

```c
GtkWidget *launcher = UmiGtk4BankOperationsLauncherCreate();
gtk_window_set_child(GTK_WINDOW(window), launcher);
```
The first creates a reusable banking launcher. The second places it in the window and establishes widget ownership. The application does not copy Framework's financial implementation.

## Follow activation

1. Find gtk_application_new in main. Its identifier distinguishes the application.
2. Find g_signal_connect. The activate event is connected to Activate.
3. Find g_application_run. This starts GTK's event processing; it is not a one-off drawing function.
4. Find the existing-window check. It presents the existing window instead of making another copy whenever the application is activated.
5. Close the host and check that its operational child also closes.

## Extend carefully

To place the launcher above another panel, make a GtkBox, append the launcher and your panel, then make the box the window's child. Do not add another child directly to a window that already has one. Use the public launcher API rather than traversing its private controls from product code.

## Exercise

Draw an ownership map: application → host window → launcher; launcher → operational window; operational window → banking service. Mark which relationships are references and which are weak observations by reading the adapter source.

## Read the source

[Open the example source](../../../../labs/framework/bank-workspace/main.c).

## Continue learning

[Course contents](../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Choose a database location before opening a workspace](19-choose-a-database-location.md) · [Next: Separate path selection from database operations](21-separate-path-selection-from-storage.md)
