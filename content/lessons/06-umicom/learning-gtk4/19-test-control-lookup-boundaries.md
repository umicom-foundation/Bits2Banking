<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/19-test-control-lookup-boundaries.md

PURPOSE:
Test control discovery at its boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test control discovery at its boundaries

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


## A regression test protects a behaviour

A regression is a previously working behaviour that stops working after a change. A useful regression test checks the contract that was broken, including failure paths. It should not merely repeat the implementation's exact internal steps.

Framework's named-lookup tests construct small widget trees and ask observable questions. A unique control must be returned. A missing name must clear the output. Duplicate names must be rejected. A collapsed section must remain collapsed after read-only inspection.

## Understand the boundary cases

- unique: one explicit name inside the requested root.
- missing: no matching name and a null result.
- duplicate: two matches, so no arbitrary selection.
- collapsed and expanded: discovery preserves the section state.
- isolated: another root cannot contribute a match.
- invalid: unusable inputs report INVALID_ARGUMENT.
- depth: a tree beyond the supported depth yields CAPACITY_EXCEEDED.
- tag-separation: a matching automation ID is not a matching GTK name.

The tests also count actions. Inspection must leave that count at zero. This catches a search that accidentally activates the found widget.

## Follow a test manually

1. Open Framework's tests/gui_control_checks/test_named_lookup_status_gtk4.c.
2. Locate the selected case name.
3. Read the setup, operation and assertions as three separate parts.
4. State the expected output before reading the assertion.
5. Check the cleanup path: both owned roots must be released.

## Qualification commands

After the Framework tests have been configured and built by the project maintainer, run the focused group from the configured build directory:

```powershell
ctest --test-dir "C:/umicom/Umicom-Applications/build/windows-ucrt64-all-debug" -R "^framework[.]gui_control_checks[.]named_lookup[.]" --output-on-failure --no-tests=error
```

This command selects tests; it does not compile missing executables. A no-tests result can mean the build configuration does not include the group. Exit code 77 in the fixture represents unavailable GTK display coverage. Keep that separate from an executed pass.

## Exercise

Design a test for a late duplicate: put the first matching widget near the start and the second near the end. Explain why returning immediately on the first match would fail the intended uniqueness contract.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Keep callback state alive for the right lifetime](18-keep-callback-state-alive.md) · [Next: Diagnose a button journey from click to result](20-diagnose-a-button-journey.md)
