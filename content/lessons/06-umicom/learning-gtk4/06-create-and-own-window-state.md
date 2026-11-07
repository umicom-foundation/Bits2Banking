<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/06-create-and-own-window-state.md

PURPOSE:
Explain the lesson: Create and own a window's state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Create and own a window's state

## Prepare
Install a C23 compiler, CMake, Ninja, GTK4 development files and a matching installed Framework SDK. From the Bits2Banking checkout, configure the existing activity example:
~~~powershell
cmake -S labs/native/framework-activity -B build/activity-window -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications" -DBTB_ACTIVITY_GTK4=ON
cmake --build build/activity-window
~~~
On Bash use the same commands with the actual SDK prefix. Stop if configure or build fails.

## Understand the data
`ActivityWindow` stores the completed count and a pointer to the label. A pointer identifies an object; it does not by itself explain who releases that object. The code attaches the allocated state to the window:
~~~c
g_object_set_data_full(G_OBJECT(window), "activity", state, g_free);
~~~
The final argument supplies the release operation for that attached data. GTK's widget hierarchy owns the label once it is added to its container. The state borrows access to the label rather than separately freeing it.

## Trace the lifetime
Draw three boxes: application, window and state. Add the label beneath the window's container. Mark allocation, attachment, use in a click, and final release. The count must remain alive throughout every callback that uses it.

**Exercise:** why would a pointer to an automatic local `ActivityWindow` inside `Activate` be unsuitable after that function returns? Expected answer: the automatic object's lifetime ends on return; later clicks would use invalid storage.

## Check and diagnose
Launch the built activity window and record a count. Close it and repeat with a fresh window. If a crash occurs during close, investigate ownership and callbacks before changing visual style. Do not free an attached state twice.

This lab's build and window checks are separate from reading the lifetime diagram. Keep actual observations distinct from the expected behaviour.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-window-state-and-independent-instances.md) · [Next lesson](07-wire-a-signal-to-a-callback.md)

