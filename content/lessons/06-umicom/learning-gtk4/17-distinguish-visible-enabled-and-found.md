<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/17-distinguish-visible-enabled-and-found.md

PURPOSE:
Distinguish a found control from a usable control

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish a found control from a usable control

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

For more detail after this lesson, see [Learning C](../../../courses/learning-c/index.html), [Learning CMake](../../../courses/learning-cmake/index.html) and the [lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-control-inspection/README.md).


## Three different questions

A control can exist while its section is collapsed. It can be displayed but disabled. It can also be enabled in a window that has not been presented. These are different states, and a useful test states which one it is checking.

**Visible** means the widget is intended to be shown, subject to its ancestors and selected page. **Mapped** means it is part of the displayed hierarchy. **Sensitive** means it accepts interaction, also subject to its ancestors. Checking just the local visible flag is not enough to prove a person can use a control.

## Study the lab in steps

1. Before expanding Review, Inspect finds Confirm. Discovery succeeds even though the user cannot click the hidden content.
2. Reveal selects the section. The event loop can then perform layout and display work.
3. The user clicks Confirm after it is displayed. That is a separate interaction.

## Read the Framework contract

The GTK automation driver supports WAIT_VISIBLE for user-facing journeys. It checks effective visibility and mapping. Its mutation operations also reject disabled controls. TYPE_TEXT replaces editable text through the adapter; it is not evidence of an operating-system keyboard event.

These distinctions prevent a misleading test: calling a callback directly may verify the callback's logic while missing a broken menu binding, hidden overlay or focus problem.

## Write a small test plan

1. Present the lab on a real desktop.
2. Wait for the window to be visible.
3. Inspect while collapsed and confirm no action ran.
4. Reveal, wait for the target to become visible, click it and verify the displayed count.
5. Close the window and confirm the process exits normally.

Record what was actually executed. A skipped GUI test means the scenario was not observed, not that it passed.

## Extension exercise

Add a disabled Confirm variation in a private copy of the lab. Predict whether lookup, reveal and user interaction should succeed. Keep the underlying lookup service unchanged; disabled presentation must not erase the control's identity.


## Exercise: export through a collapsed section

A file-export panel often keeps its path field and Save button inside an expander. Framework lookup can discover those controls while the expander is closed. That is useful for navigation, but it does not mean a person can press the button. A test that finds the button and emits its signal has tested a different interaction from a native click.

Use a temporary destination that does not already exist. Keep the expected document text before opening the export section so that you can compare the resulting file with the intended content, rather than accepting the mere existence of a file.

1. Find the export expander and check that its type is GtkExpander before using the expander API.
2. Call gtk_expander_set_expanded(expander, TRUE), then allow the owning GTK event loop to process layout. A bounded wait should observe the button becoming mapped; do not assume a fixed sleep proves readiness.
3. Find the path field again from the live panel. Check GTK_IS_EDITABLE before setting its text. Find the Save button and check that it is visible, mapped and effectively sensitive.
4. Activate the button through the same native activation path used by the application. Wait for the export job to finish, with a deadline and an explicit failure when it does not finish.
5. Read the destination and compare its bytes with the expected document. Close the panel, reopen it and confirm that stale operation state has not made the next export appear complete.

For a negative test, keep the section collapsed and verify that native activation is unavailable. Test a rejected destination separately and confirm that the existing file is unchanged. These cases establish different guarantees: usable control, completed operation and correct saved content.

If lookup succeeds but activation fails, inspect visibility, mapping and effective sensitivity before changing the lookup algorithm. If activation succeeds but no file appears, inspect the job result and destination permissions. Do not remove the output comparison to make the test pass.

### Check your understanding

Why should the test wait for both mapping and export completion?

**Answer:** Mapping means the control participates in the displayed interface. Export completion means the asynchronous operation has finished. Neither state implies the other, and neither by itself proves the saved bytes are correct.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Reveal a panel without running its action](16-reveal-without-running-an-action.md) · [Next: Keep callback state alive for the right lifetime](18-keep-callback-state-alive.md)
