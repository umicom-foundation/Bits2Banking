<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/07-wire-a-signal-to-a-callback.md

PURPOSE:
Explain the lesson: Wire a GTK signal to a C callback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Wire a GTK signal to a C callback

## Prepare
Use the Framework activity lab with its GTK4 option enabled. Its README and CMake lesson describe the SDK prefix, compiler and GTK dependencies. Begin with a successful build of the unchanged lab.

A **signal** is a notification emitted by an object. A **callback** is a function supplied to receive that notification. A visible button alone does not establish that useful application work is connected.

## Locate the connection
Find:
~~~c
g_signal_connect_object(button, "clicked", G_CALLBACK(Completed), window, 0);
~~~
The connection identifies the emitting button, the clicked signal, the receiving C function and the window supplied as callback data. In `Completed`, the button parameter is deliberately unused; the window identifies the state to update.

The object-aware connection manages the callback association with the supplied object's lifetime. GTK documents its behaviour in [signal_connect_object](https://docs.gtk.org/gobject/func.signal_connect_object.html); it is not permission to manipulate widgets from arbitrary worker threads.

## Trace a press
1. The button emits clicked.
2. `Completed` obtains the window's activity state.
3. The shared C rule attempts an increment.
4. The callback formats the result.
5. The label receives the new text.

**Exercise:** place a paper marker at each step for the first press. Expected count: 1. Then identify which steps still happen when the model reports full capacity.

## Troubleshooting
For a control that appears inert, check whether the signal reaches its handler before editing business logic. A temporarily added diagnostic should name the event and status, not expose file contents or credentials. Record whether the widget is enabled and whether another window or modal operation owns input.

Do not replace a functioning C rule with a second implementation inside the callback. The callback's role is coordination and presentation.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-create-and-own-window-state.md) · [Next lesson](08-compose-widgets-in-a-container.md)

