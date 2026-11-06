# Widgets and the event loop

[Course contents](index.md) · [Next: Connect a button to a shared rule](02-connect-a-button-to-a-shared-rule.md)

## Before opening a window

First learn C functions, pointers and the basics of compiling a program. A widget is an interface element such as a button or label. GTK4 arranges widgets inside containers. An event loop waits for input and asks registered functions to respond. The program does not repeatedly ask a button whether it was clicked.

Use the existing Framework activity project for this course. Read its `README.md` and `CMakeLists.txt` before building. They describe the installed SDK and GTK dependency; copying `window.c` alone is not enough because it calls the shared activity rule.

## Read the real window

Open `labs/native/framework-activity/window.c`. Find `Activate`, then follow these operations in order:

```text
GtkApplication -> application window -> vertical box
                                      |-- label
                                      |-- button
```

`gtk_application_window_new` associates a window with the application. `gtk_box_new` creates a container. Its orientation controls the direction children are arranged. Spacing is the gap between children; margins are space outside the container's content. These are different decisions.

`gtk_window_set_child` attaches the main content. Appending a label and button to the box makes them part of that content. `gtk_window_present` asks for the window to be shown. The application continues through its event loop until it exits.

## Observe before changing

Build and run the example using its README when your environment is ready. Expect a label showing zero completed exercises and a button labelled Record one exercise. Resize the window. Observe which space grows and which text remains readable. A source inspection alone cannot establish that the native window opens or accepts input on your machine.

## Exercise and answer

In a practice copy, change the box spacing from 12 to 20 and rebuild the example. The space between the label and button should increase; the number of completed exercises should not change. If changing appearance changes the counting rule, presentation and behaviour have become unnecessarily coupled.

Find the allocation of `ActivityWindow` and its `g_object_set_data_full` call. The state has an owner and a cleanup function. You do not need to memorise every GLib function yet; identify what survives after `Activate` returns and who releases it. The next lesson follows the button event through that retained state.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/window.c). Path: `labs/native/framework-activity/window.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://docs.gtk.org/gtk4/getting_started.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-gtk4/lessons/01-widgets-and-the-event-loop.html).

[Course contents](index.md) · [Next: Connect a button to a shared rule](02-connect-a-button-to-a-shared-rule.md)

Sammy Hegab · Umicom Foundation · Original learning material.
