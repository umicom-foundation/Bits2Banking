<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/12-identify-a-control.md

PURPOSE:
Identify a control independently of its caption

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Identify a control independently of its caption

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


## What you will learn

You will give a control a stable identity and explain why visible text is a different property. A caption is the text a person reads, such as Confirm. An identifier is a name that software uses to refer to that specific control. Captions can be translated or edited. Coordinates change when a window is resized.

## Follow the example

1. Open main.c in the lab. Find gtk_button_new_with_label. It creates a button with the caption Confirm.
2. Find gtk_widget_set_name. It assigns lab-confirm as a GTK widget name. Existing Umicom components sometimes use names for discovery.
3. Find umi_gtk4_automation_tag_widget. It assigns lesson.review.confirm as the Framework automation identifier. New interface contracts should use these explicit IDs.

```c
gtk_widget_set_name(confirm, "lab-confirm");
UmiStatus tagged = umi_gtk4_automation_tag_widget(
    confirm, "lesson.review.confirm");
```

The first argument is the control's address. The second is a C string: characters terminated by a zero byte. The returned UmiStatus must be checked. In this lab, failure disables Reveal because a route without a valid identifier would be misleading.

The two identifiers belong to separate selector systems. A GTK name is also used by styling code. A Framework automation ID expresses an application control contract. Neither is a password or a user's identity.

## Try it

1. Start the lab and choose Inspect by name. Expect Unique control found even while Review is collapsed.
2. Change only the button caption in the source to Approve, rebuild the lab and repeat.
3. The lookup should still succeed because the explicit name did not change.
4. Restore the caption, or keep your local variation and note its purpose.

## Check your understanding

Why would a test that searches for the English caption break after translation? Why must two buttons inside the same search scope have distinct IDs? An ID does not make a disabled button clickable; it only establishes which control is being discussed.

## Where this appears in Umicom

Framework's GTK automation service accepts stable IDs. Broker workspace tests also inspect existing explicitly named controls. This lets an application reuse the shared tree rules instead of reimplementing a search based on labels or screen positions.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Next: Understand the logical widget tree](13-understand-the-logical-widget-tree.md)
