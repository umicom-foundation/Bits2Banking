<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/08-compose-widgets-in-a-container.md

PURPOSE:
Explain the lesson: Compose widgets in a GTK container.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compose widgets in a GTK container

## Set up
Open `window.c` in the Framework activity lab. Reading requires only an editor. To run it, install GTK4 development files and a compatible Framework SDK, configure with `BTB_ACTIVITY_GTK4=ON`, and build as described in the lab README.

A **container** arranges child widgets. In this example a vertical `GtkBox` holds a label and a button. A margin is space outside a widget; spacing is the gap the box places between children.

## Follow construction
1. Locate `gtk_box_new(GTK_ORIENTATION_VERTICAL, 12)`.
2. Find the four margin calls. Each uses 20 in this example.
3. Find the label and button construction.
4. Follow the two `gtk_box_append` calls.
5. Find `gtk_window_set_child`, which installs the box as the window's content.

The construction order helps explain the initial vertical arrangement. The count model does not know about margins, orientation or window size.

## Explore safely
In a disposable exercise copy, change only the box orientation. Predict where the controls will appear, build and observe. Restore it, then change spacing. Keep one variable different at a time so the result has an understandable cause.

**Exercise:** draw the hierarchy using indentation:
~~~text
window
  box
    label
    button
~~~
Mark which object receives each append/set-child call.

## Check real usability
Resize the window and increase text size. Verify that the full button label and result can be reached. An attractive screenshot at one width is insufficient evidence for a resizable workflow.

## Diagnose
A missing widget can result from failing to add it to the hierarchy, putting it in the wrong parent or replacing the window child. Trace ownership and placement before adding more fixed sizes. Shared Framework workbench components should be reused for product work; this small GTK lab explains the underlying container concept.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-wire-a-signal-to-a-callback.md) · [Next lesson](09-present-status-without-changing-the-model.md)

