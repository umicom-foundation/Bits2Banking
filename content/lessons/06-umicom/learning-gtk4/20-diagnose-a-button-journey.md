<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/20-diagnose-a-button-journey.md

PURPOSE:
Diagnose a button journey from click to result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Diagnose a button journey from click to result

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


## Follow one operation end to end

A window that opens successfully is only the beginning of a workflow. To diagnose an apparently inactive button, trace the path from input to an observable result. Do not assume the cause from appearance alone.

```text
Input -> visible enabled control -> signal/action binding
      -> callback -> Framework service -> model result -> view update
```

Each arrow is a possible failure point. A menu may refer to the wrong action name. A callback may return early. A service may report an error that the view never displays. A worker may block the event loop. The same symptom can therefore have several causes.

## Use the lab as a small reference

1. Click Confirm after revealing Review.
2. The clicked signal reaches confirm_clicked.
3. The callback obtains window-owned state.
4. It checks the counter's maximum before incrementing.
5. It updates the status label with the new value.

This is a small demonstration, not an implementation of a banking or trading operation. Real application commands should call the appropriate Framework domain service and present its outcome.

## Record useful evidence

Write down the application and source revision, exact menu or control, current selection, expected result and observed result. Record a lookup status if discovery fails. Keep a screenshot of the visible state and any application diagnostic message. Do not put passwords, authentication codes or document contents into general diagnostic logs.

## Separate different tests

A source review can confirm that a signal name and callback are connected in code. A model test can validate the service rule. A GUI test can show that a visible control reaches it. A real keyboard or pointer journey can expose focus and event-routing problems. None of these alone proves every application feature works.

## Final exercise

For Studio Open File, list the checkpoints: menu activation, file chooser display, user selection, file-read result, document model creation, editor-tab selection and editable text. For each checkpoint, name one observable success and one failure message. This turns a vague frozen-screen report into a reproducible workflow.

## Continue

Use the same method for Trader account refresh or Media import. Retain the application-specific operation while sharing Framework discovery, lifecycle and diagnostic services.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Test control discovery at its boundaries](19-test-control-lookup-boundaries.md)
