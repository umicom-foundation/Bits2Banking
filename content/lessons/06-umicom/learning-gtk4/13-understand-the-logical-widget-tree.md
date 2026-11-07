<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/13-understand-the-logical-widget-tree.md

PURPOSE:
Understand the logical widget tree

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand the logical widget tree

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


## A tree describes ownership

A tree is a set of nodes connected by parent-child relationships. The window contains a box; the box contains an expander; the expander owns a Confirm button. An expander is a section that can open or collapse.

```text
Window
  Box
    Inspect button
    Reveal button
    Review expander
      Confirm button
```

This ownership picture is useful even when a child is not currently displayed. GTK's physical child links describe the widget hierarchy used for layout. A compound widget can retain content through a public property while its current physical layout changes. Framework's logical lookup explicitly understands collapsed expander content.

## Inspect the source

1. Find gtk_expander_set_child. That call assigns the Confirm button as Review's content.
2. There is no call expanding Review during initial setup, so it begins collapsed.
3. Inspect by name calls Framework lookup. It does not walk GTK children itself.
4. The returned status is displayed in the status label. No Confirm action is emitted.

[GTK's expander child reference](https://docs.gtk.org/gtk4/method.Expander.get_child.html) documents how to obtain its retained child. The returned child is owned by the widget; retrieving it does not transfer ownership to the caller.

## Experiment

1. Inspect while Review is collapsed. Expect one match and Confirmations: 0.
2. Open Review by clicking its header and inspect again. Expect the same match and count.
3. Collapse Review and inspect a third time. The control still exists.

## Avoid a common mistake

Do not conclude that a feature is missing merely because a physical-child traversal did not find it. Conversely, finding a logical child does not prove a user can currently see or operate it. A lookup test and a visible interaction test answer different questions.

## Extension exercise

Draw the tree of a Studio panel containing a notebook with an editor and an output page. Mark which nodes exist and which page is selected. Keep that diagram separate from an assertion about whether typing into the editor works.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Identify a control independently of its caption](12-identify-a-control.md) · [Next: Read checked lookup results before using a pointer](14-read-checked-lookup-results.md)
