<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/18-keep-callback-state-alive.md

PURPOSE:
Keep callback state alive for the right lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep callback state alive for the right lifetime

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


## What a dangling pointer means

A dangling pointer still contains an address after the object at that address has ceased to be valid. Reading or writing through it can produce a crash or corrupt memory. Keeping the number in a C variable does not preserve the object.

The lab creates LabWindow with g_new0. This allocates zero-initialised storage for the structure. It attaches the structure to the window using g_object_set_data_full and gives g_free as the cleanup function. The window is therefore responsible for releasing the state.

## Trace ownership

```text
Window owns LabWindow state
Window contains the root box
Root box contains controls
Callbacks borrow state and control pointers during one call
```

1. Find g_object_set_data_full in activate.
2. Find window_state. It retrieves the attached structure; it does not allocate a second one.
3. Find each g_signal_connect_object call. The window is the callback's associated object.
4. Read confirm_clicked. It uses the state during the callback and returns.

Object-bound signal connections keep the associated object alive during the callback and disconnect when it is destroyed. This behaviour is documented in [GLib's signal connection reference](https://docs.gtk.org/gobject/func.signal_connect_object.html). It is not permission to destroy GTK objects from an arbitrary worker thread.

## Apply the rule to lookup

The widget returned by Framework lookup is borrowed. Do not store it in a background job or retain it across an event-loop iteration. Reacquire it when you need it, using a live root on the GTK owning thread. Even taking an object reference does not prove that the control still belongs to the current view.

## Exercise

Explain the difference between these claims: the object still exists; it is still the currently selected editor; it is visible; it can be edited. A reference addresses only lifetime. Identity, selection and permissions need their own checks.

## Recovery

When diagnosing a lifetime crash, record who owns the object, which callback releases or replaces it and which later operation uses it. Avoid hiding the fault with an arbitrary delay.


## Focus changes can call back into your code

Disabling a panel while an entry inside it owns keyboard focus can leave the focus transition happening during another state change. Releasing focus first makes the transition explicit, but changing focus can itself emit notifications. A notification callback may request another load or close the panel before your original function resumes. This is called reentrancy: one operation is entered again before its earlier call has returned.

Treat focus release as a callback boundary. Framework adapters should use the existing shared focus-handoff helper rather than each application implementing another traversal of GTK internals. The low-level GTK operation is gtk_root_set_focus(root, NULL), which unsets focus; it must only be used after establishing that the focused widget belongs to the panel being retired or disabled.

1. Keep the root object alive for the duration of the operation, using the ownership contract already established by the component.
2. Publish the busy or retired flag before changing focus. A nested callback must see the new state and reject an incompatible second operation.
3. Check whether the focused widget is the panel itself or one of its descendants. Preserve focus in unrelated controls, such as another editor.
4. Release the owned focus through the shared helper. Then recheck whether a callback retired, replaced or detached the panel.
5. Disable controls or queue work only if the panel is still valid for that action. On cancellation, return resources to their owner and release temporary references.

An object reference prevents finalisation while held. It does not prove that the widget still belongs to the same window or that the user still wants the pending operation. Check lifetime and current state separately.

A useful regression fixture connects to the window focus notification and attempts to reload or retire the panel when focus is cleared. Check that the nested load is rejected, that no abandoned job is queued and that retiring twice is safe. Also test an unrooted panel and a window whose focus is outside the retiring subtree.

### Check your understanding

Why is setting busy after releasing focus too late?

**Answer:** The focus notification runs before the original call resumes. Its callback can observe the old idle state and start a second operation. Set the guard first, then recheck state after the notification.

### Retained windows and available windows

Keeping a strong reference to a GtkWindow does not mean it can still receive input. Window destruction can hide and unrealize the native window while a retained object and its children still exist. A focus traversal must check mapping after the callback and stop if the viewport was unmapped, even if another callback immediately presents it again. Test both acceptance and rejection after closure, then separately test a fresh command after the reopened view has been allocated.

## Read the source

[Open the example source](../../../../labs/native/framework-control-inspection/main.c).

## Continue learning

[Course contents](../../../courses/learning-gtk4/index.html) · [Previous: Distinguish a found control from a usable control](17-distinguish-visible-enabled-and-found.md) · [Next: Test control discovery at its boundaries](19-test-control-lookup-boundaries.md)
