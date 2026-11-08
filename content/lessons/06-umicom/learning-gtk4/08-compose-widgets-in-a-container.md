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

## Respect the minimum size of split panes

A **split pane** contains two regions and a draggable separator. Its minimum size is a promise: enough space for the controls that must remain usable. The natural size is the preferred size when more room is available. Neither number is the current allocation, which GTK supplies when laying out the window.

In a separate exercise copy of the activation callback, replace the box composition with the code below. Here `window` is the GTK window you already created; call this after GTK starts and before presenting the window. These labels stand in for two editing regions, so this exercise does not need a media player or a video file.

~~~c
GtkWidget *pane = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
GtkWidget *preview = gtk_label_new("Preview area");
GtkWidget *timeline = gtk_label_new("Timeline controls");
gtk_paned_set_start_child(GTK_PANED(pane), preview);
gtk_paned_set_end_child(GTK_PANED(pane), timeline);
gtk_paned_set_shrink_start_child(GTK_PANED(pane), FALSE);
gtk_paned_set_shrink_end_child(GTK_PANED(pane), FALSE);
gtk_window_set_child(GTK_WINDOW(window), pane);

int minimum = 0;
gtk_widget_measure(pane, GTK_ORIENTATION_VERTICAL, -1,
                   &minimum, NULL, NULL, NULL);
int width = 0;
gtk_widget_measure(pane, GTK_ORIENTATION_HORIZONTAL, minimum,
                   &width, NULL, NULL, NULL);
~~~

`FALSE` for both shrink properties asks GTK to preserve each visible child's minimum. It still permits the divider to move within the available space. The `-1` measurement constraint means no fixed size is supplied for the other axis. The second call asks for the width when the pane has exactly its minimum height.

1. Build and open the exercise using the existing lab instructions. Resize toward the smallest allowed window and check both labels remain reachable.
2. Replace the timeline label with a box containing a button, a wrapped label and an expander. Repeat measurement with the expander closed and open.
3. Hide one region explicitly, measure again, then show it. Hidden regions and regions permitted to shrink are different layout choices.
4. Repeat with larger text and several widths. Record the actual GTK version and whether any warning occurred; do not infer success from a compile alone.

A warning about measuring a child one pixel below its minimum points to the size contract, not necessarily to a missing font or an incorrect screenshot. Follow the parent containers and separator requirements before adding an arbitrary fixed height. Increasing the default window size may conceal the boundary without correcting it. Keep warnings visible, preserve model state across layout changes, and test the boundary as well as a comfortable full-size window.

The shared video workspace has native `minimum-empty`, `minimum-populated`, `minimum-expanded` and `minimum-visibility` checks for these transitions. Their presence in source is not evidence that they passed on your desktop.

[GTK split-pane reference](https://docs.gtk.org/gtk4/class.Paned.html) explains the independent resize and shrink choices.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-wire-a-signal-to-a-callback.md) · [Next lesson](09-present-status-without-changing-the-model.md)

