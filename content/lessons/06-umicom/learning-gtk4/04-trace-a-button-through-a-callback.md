<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/04-trace-a-button-through-a-callback.md

PURPOSE:
Explain the lesson: Trace a button through a C callback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a button through a C callback

## From gesture to function

A GTK signal reports an event such as a button being activated. A callback is the function registered to receive that signal. Its parameters must match the signal's expected signature; a cast does not make an incompatible function safe.

The activity window uses a button named Record one exercise. Its clicked signal reaches Completed, which calls the same C model used by the console exercise.

## Setup recap

Use the [Framework activity lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/README.md). Install GTK4 development files, a C23 compiler, CMake, Ninja and a matching Framework SDK. Configure the lab with BTB_ACTIVITY_GTK4=ON. Follow its complete commands rather than enabling GUI options in an unrelated build directory.

## Follow four stages

1. Activate creates a GtkApplicationWindow and a vertical GtkBox.
2. The code creates the label and button and appends them to the box.
3. g_signal_connect_object connects clicked to Completed with the window as callback data.
4. Completed asks BtbActivityAdvance to update the count, then changes the label.

~~~text
button activation -> Completed -> BtbActivityAdvance
                                  |
                         status + count
                                  |
                            label text
~~~

The model does not know which mouse button was used or how the window is arranged. Those are interface concerns.

## Lab

1. Build and launch the optional window.
2. Click Record one exercise and expect the displayed count to increase.
3. Use keyboard focus and activation to repeat the action.
4. Compare the callback with the console caller.
5. Locate the error branch and explain its message.
6. Close the window and confirm the process exits when no application work remains.

A compilation pass alone does not prove the signal was delivered. Record the action and visible result.

## Troubleshooting

If the window opens but clicking does nothing, check the actual signal registration, the callback data and whether the button is sensitive. If the process becomes unresponsive, investigate work blocking the main event loop. Do not add a busy waiting loop to make a callback arrive.

## Exercise and explanation

Why can both the console and GTK window call the same model? The model's inputs and outputs are ordinary C values and a Framework status. It has no dependency on the widget tree. That separation makes the rule reusable and directly testable.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-own-state-for-a-window.md) · [Next lesson](05-window-state-and-independent-instances.md)

