<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/15-find-ambiguous-controls.md

PURPOSE:
Detect duplicate names and keep searches scoped

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Detect duplicate names and keep searches scoped

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


## One name must select one control

An ambiguous request has more than one valid interpretation. If two controls share the same name, silently choosing the first can operate the wrong one. This becomes especially dangerous when several account windows or project windows are open.

The lab contains a second label called lab-other. Selecting Give a second control the same GTK name changes that label's name to lab-confirm. It does not replace the real Confirm button.

## Reproduce the ambiguity

1. Start the lab and inspect. Expect Unique control found.
2. Enable the duplicate-name checkbox.
3. Inspect again. Expect More than one matching control.
4. Disable the checkbox and inspect. Expect a unique result again.
5. Notice that the number of confirmations remains unchanged throughout.

A checkbox emits toggled when its state changes. duplicate_toggled reads that state with gtk_check_button_get_active and changes the label name. It then asks you to inspect again; it does not hide the error by choosing a winner.

## Understand the search scope

state->root is the box belonging to this window. Searching from it excludes unrelated top-level windows. A scope is a deliberate boundary for a lookup. Making it too broad introduces ambiguity; making it too narrow can miss the intended control.

Framework's regression cases include duplicate, isolated and tag-separation. They check ambiguity, exclusion of another root and independence between GTK names and Framework IDs. These checks provide more evidence than finding a button once.

## Design exercise

Imagine a Bank app with two transfer forms. Give each form its own root and identify its submit button inside that root. Explain why a process-wide search for a button caption Submit is unreliable.

## Recovery

When a duplicate is reported, inspect construction of the affected controls and their intended scope. Rename only identifiers that are meant to be distinct. Do not fix the symptom by accepting the first match, changing a test to ignore the error or deleting one feature.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Read checked lookup results before using a pointer](14-read-checked-lookup-results.md) · [Next: Reveal a panel without running its action](16-reveal-without-running-an-action.md)
