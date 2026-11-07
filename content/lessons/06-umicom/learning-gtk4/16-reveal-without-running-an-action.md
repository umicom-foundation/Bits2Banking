<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/16-reveal-without-running-an-action.md

PURPOSE:
Reveal a panel without running its action

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reveal a panel without running its action

This practical module explains how a GTK interface identifies controls, navigates to them and keeps callback state alive. Each lesson includes the setup needed to follow its own example.

## Start here

A graphical application is a program that shows windows and reacts to input. A **widget** is one control, such as a button or a label. A **callback** is a C function GTK calls when an event occurs. The **event loop** waits for input and dispatches those callbacks. You can read this lesson without installing anything. The optional lab needs a C compiler, CMake, Ninja, GTK4 development files and an installed Umicom Framework SDK containing the GTK4 component and the checked named-lookup API.

In C, a pointer stores an address; it does not automatically keep an object alive. A structure groups related values. The lab's LabWindow structure belongs to one window and holds pointers to controls owned by that window. A return status reports whether an operation completed. Check that status before using its output.

### Prepare the optional lab

1. Open PowerShell on Windows. A terminal accepts commands; Set-Location changes the folder in which they run. Locate the Bits2Banking checkout and the installed Framework SDK first.
2. Put the matching UCRT64 compiler and GTK runtime on Path. Use the SDK built with that same toolchain.
3. Configure a separate build folder, then build the small lesson executable. Stop if any command reports an error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-control-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications"
cmake --build build --parallel 2
& ".\build\btb-control-inspection.exe"
```

On Linux, install your distribution's C compiler, CMake, Ninja, pkg-config and GTK4 development package, and use the path where you installed the Framework GTK4 SDK:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/native/framework-control-inspection
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"
cmake --build build --parallel 2
./build/btb-control-inspection
```

CMake reads CMakeLists.txt and finds the installed libraries. Ninja compiles only what this lab needs. This recipe does not rebuild the Framework. If CMake cannot find UmicomFramework, correct the SDK path. If ui_gtk4 or the checked lookup symbol is missing, install an SDK containing that component and API before continuing. A GTK window needs an interactive desktop session. On Windows, the GTK DLLs must remain reachable through Path.

For more detail after this lesson, see [Learning C](../../../courses/learning-c/index.html), [Learning CMake](../../../courses/learning-cmake/index.html) and the [lab guide](../../../../labs/native/framework-control-inspection/README.md).


## Separate navigation from an operation

Navigation changes which part of an interface is visible. An operation changes application state, such as saving a file or confirming an order. Keeping them separate lets a user inspect a destination before performing an action.

The lab's Reveal button calls umi_gtk4_automation_reveal_tagged_widget. The service can expand the section and select existing pages on the route to the tagged control. It does not click Confirm, enable a disabled control or present a new window.

## Follow the journey

1. Start with Review collapsed and Confirmations: 0.
2. Click Reveal review section. Expect Review to expand.
3. Read the message. It asks you to click Confirm yourself.
4. Click Confirm once. Expect the callback count to become 1.
5. Click Collapse review section, then Reveal again. Expect the count to remain 1.

## Read the code

reveal_clicked checks the reveal status, then performs a fresh checked lookup by ID. Why a second lookup? Revealing can emit notifications. Application code reacting to them might rebuild a page. A pointer captured before that work might no longer identify the current destination.

The shared service returns CANCELLED if the destination changes during the operation. Partial navigation can remain visible after cancellation; no action has been run. A caller should report the changed view and let the user choose again.

## Apply the idea

In Studio, revealing an output panel should not start a build. In Trader, revealing an order ticket should not send an order. In Media, opening an export panel should not overwrite a file. The same separation is reusable across these products.

## Check your understanding

Does successful reveal prove the button is mapped, enabled and ready for a real mouse event? No. Visibility, mapping and sensitivity are separate conditions. The next lesson explains how to examine them.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Detect duplicate names and keep searches scoped](15-find-ambiguous-controls.md) · [Next: Distinguish a found control from a usable control](17-distinguish-visible-enabled-and-found.md)
