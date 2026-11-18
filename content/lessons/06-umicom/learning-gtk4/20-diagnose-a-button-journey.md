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

For more detail after this lesson, see [Learning C](../../../courses/learning-c/index.html), [Learning CMake](../../../courses/learning-cmake/index.html) and the [lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-control-inspection/README.md).


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


## Separate an accepted request from a completed result

A catalogue load may return success because it has accepted a job. At that moment the worker may not have inspected any files. Checking for an empty catalogue immediately after that return can confuse “not loaded yet” with “loaded and empty”. The same distinction applies to exports, search and project discovery.

Observe the component state and result through its supported API. A bounded test pumps the owning event loop until the pending count reaches zero or a deadline expires. Only then should it inspect the final status, record count and visible notice. Keep missing-folder, existing-empty-folder and valid-content cases separate.

1. Prepare one fixture for each outcome and record the expected final status before starting the operation.
2. Check the immediate return value. If the request was rejected, verify that no job was queued and that the previous view remains intact.
3. For an accepted request, observe busy state and wait for completion with a deadline. Report a timeout as a failure; do not convert it into an empty result.
4. Check the final status and visible notice. An unavailable lesson should identify the missing local content and a recovery action, while preserving the previously selected reading material.
5. Repeat after closing or replacing the panel to verify that stale completion callbacks cannot update the new view.

A persistent project button needs a second kind of transition test. Create the Explorer while no project is open and confirm that Project board is disabled. Open a project and confirm that the same button becomes enabled. Close the project, then open a different one and verify that the button follows the new project. Recreating the entire Explorer for each case would miss a stale sensitivity state.

When the button is disabled, a forced signal is a useful service-boundary test: the handler must still reject the unavailable operation. Keep that check separate from the native input test. Correct appearance and correct command policy are both required.

### Check your understanding

What does a successful “start load” return prove?

**Answer:** It proves only the documented acceptance contract. Completion, valid content, a refreshed view and preservation of the previous selection require their own observations.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Test control discovery at its boundaries](19-test-control-lookup-boundaries.md)

[Next lesson](21-choose-an-interactive-development-tool.md)

## A connected button can still refuse its command

An **admission check** decides whether an operation may start. For example, Studio requires a matching open project and explicit permission to execute its build scripts. A build script is a file containing instructions for the build tool; those instructions can run programs. Selecting a project folder is therefore different from agreeing to run its scripts.

Consider this diagnostic sequence:

```text
button.clicked  command=run.start status=0
command.dispatch command=run.start status=0
command.return command=run.start status=7
```

The first two lines show that the button reached its command handler. In Umicom's status enumeration, 0 means success and 7 means permission denied. The last line says this particular command refused execution. It does not say a compiler ran and failed. A status enumeration is a set of named integer values; use the name from the actual API rather than assuming every library assigns the same meaning to 7.

1. Confirm the open folder is the intended project. Opening or reopening a project resets its execution trust.
2. Open **Build → Project Settings → Build**. Scroll the page to find the trust checkbox if the window is short.
3. Review the project's files and build scripts before selecting trust. Choose **Apply Settings** to apply that decision; Cancel and an unchecked box leave tools disabled.
4. Request **Build and Run** again. Applying settings does not automatically retry the previous request.
5. Distinguish a new job in Output from a retained command warning in Problems. A refused request has no compiler transcript.

When designing this flow, keep the explanation visible long enough to read, state what the user can do next and preserve an existing settings draft. Do not silently grant permission just because the user clicked Run. A useful regression starts with an unsaved edit, refuses the command, then checks that the saved source bytes, unsaved draft, trust and job count are all unchanged.

## Keyboard focus is different from being on screen

**Focus** identifies the control that receives keyboard input. A **viewport** is the visible rectangle through which a larger page is shown. A control can have focus while lying outside that rectangle. GTK also needs time to assign final positions and sizes, a step called **layout allocation**. Requesting focus before allocation does not prove that the control has scrolled into view.

Imagine a viewport 200 pixels high. A checkbox starts at vertical position 300 and is 25 pixels high. Its bottom is at 325, so a scroll of at least 125 pixels is needed to show its bottom. Margins count too: measure relative to the viewport, not to a different container whose origin leaves out the margin.

For a native test, check the checkbox's full bounds after layout, with a deadline. Check that its top is not above the viewport and that its bottom is not below it. Then close the form before deferred work runs and repeat after moving focus to another control. The old request must not change the new focus or use a destroyed form. Umicom's shared build-settings review uses bounded frame work and weak window references for this reason. A weak reference can observe an object without extending its lifetime; it must be checked before use.

**Exercise:** a viewport is 240 pixels high, and a control's top is 290 with a height of 30. How far must the viewport move to reveal the bottom? What else must be checked before applying that scroll?

**Answer:** at least 80 pixels because 290 + 30 − 240 = 80. Check that the form still exists, the control still belongs to it, that this control is still the intended focus, and that the requested scroll stays within the adjustment's permitted range.


## Check what receives a mouse click

A **hit test** asks which widget occupies a position and may receive pointer input there. An **overlay** places a widget above another widget. Drawing nothing does not necessarily make an overlay stop receiving clicks. A collapsed GTK revealer may hide its child while its own rectangle remains eligible for input.

Imagine a clear sheet over a button: you can see the button, but your finger touches the sheet. A successful call to `g_signal_emit_by_name(button, "clicked")` proves the callback can run. It does not prove a mouse can reach the button.

1. Present a small test window with a button and tool drawer above it. Use temporary test data.
2. Let GTK finish assigning widget sizes and positions. Set a deadline so a missing frame cannot wait forever.
3. Find the button rectangle relative to the window using `gtk_widget_compute_bounds`.
4. Ask `gtk_widget_pick` which widget receives the centre of that rectangle. A button child label is valid; an unrelated hidden drawer is not.
5. Open the drawer and check its Close control. Collapse it and check the original button. Repeat for left, right, top and bottom drawers.
6. Check that the editor draft and saved layout revision did not change. Revealing a temporary drawer should not change a document or save layout data.

This fragment assumes a presented `GtkWindow *window` and visible descendant `GtkWidget *button`. It is not a complete program:

```c
graphene_rect_t rectangle;
if (!gtk_widget_compute_bounds(button, GTK_WIDGET(window), &rectangle))
    return false;
GtkWidget *picked = gtk_widget_pick(GTK_WIDGET(window),
    rectangle.origin.x + rectangle.size.width / 2.0,
    rectangle.origin.y + rectangle.size.height / 2.0,
    GTK_PICK_DEFAULT);
bool reachable = picked != NULL &&
    (picked == button || gtk_widget_is_ancestor(picked, button));
```

The coordinate origin is the reference point from which positions are measured. Both calls use the window as that reference. Mixing window coordinates with panel coordinates can report the wrong target.

Framework connects the existing drawer reveal state to input eligibility:

```c
(void)g_object_bind_property(drawer, "reveal-child",
    drawer, "can-target", G_BINDING_SYNC_CREATE);
```

A **property binding** keeps properties in step. Both properties here belong to the drawer. Initial synchronization excludes a collapsed drawer; revealing it restores input. The binding follows object lifetime without a separate callback holding a borrowed workspace-controller pointer. This input repair does not establish that unrelated focus, rendering or build behaviour is correct.

**Exercise:** a callback test passes and the button looks enabled, but picking returns an unrelated collapsed drawer. Should you add another callback, force execution trust, or correct drawer input policy?

**Answer:** correct the drawer input policy and retest both states. Another callback or a trust change cannot remove an intercepting overlay.
