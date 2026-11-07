<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/14-read-checked-lookup-results.md

PURPOSE:
Read checked lookup results before using a pointer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read checked lookup results before using a pointer

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


## Why a status is useful

A null pointer means there is no usable object address. It cannot explain why discovery failed. The checked Framework operation returns a status and writes the found control through an output parameter. An output parameter is an address through which a function can return an additional value.

```c
void *control = NULL;
UmiStatus status = umi_gtk4_automation_find_named_widget_checked(
    state->root, "lab-confirm", &control);
```

Here control is a variable capable of storing an object address. The expression &control passes the address of that variable. The function can therefore update it. void means the public adapter does not expose a GTK-specific pointer type.

## Interpret each result

- OK: one control was found after a complete supported search.
- NOT_FOUND: the supported search finished with no match.
- ALREADY_EXISTS: more than one control has the requested name; selecting either would be ambiguous.
- INVALID_ARGUMENT: a required argument was missing or unsuitable.
- CAPACITY_EXCEEDED: a traversal bound was reached, so a unique answer was not established.

On failure, the checked API clears the output. Never cast or dereference it before checking the status. A bounds failure must not be converted into a successful partial result.

## Follow the lab

1. Read status_text. A switch statement selects explanatory text for each status value.
2. Read inspect_clicked. It searches only the lab's root container.
3. Observe that the callback prints the section state and count; it does not call Confirm.
4. Inspect the compatibility API in Framework's automation.h. It still returns null on failure for existing callers, while new diagnostic code can use the richer checked API.

## Exercise

On paper, write the expected status for a misspelled name, two identical names and a null output-parameter address. Answers: NOT_FOUND, ALREADY_EXISTS and INVALID_ARGUMENT. Explain why retrying a misspelled name forever cannot repair it.

## Troubleshooting

If your installed SDK lacks this symbol, the lesson and installed library are from different revisions. Updating only a header cannot provide an implementation at link time. Install a consistent SDK before trying to run the lab.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Understand the logical widget tree](13-understand-the-logical-widget-tree.md) · [Next: Detect duplicate names and keep searches scoped](15-find-ambiguous-controls.md)
