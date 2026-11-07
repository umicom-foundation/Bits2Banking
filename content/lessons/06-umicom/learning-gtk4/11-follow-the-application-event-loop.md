<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/11-follow-the-application-event-loop.md

PURPOSE:
Explain the lesson: Follow the application event loop.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow the application event loop

## Prepare
Open the GTK4 activity lab's `window.c`. For a practical run, follow its README to install the native tools, locate the Framework SDK and enable the optional GTK4 target.

An **event loop** waits for events and dispatches them to handlers. A program that creates widgets and immediately exits cannot provide an interactive window.

## Read main in order
1. `gtk_application_new` creates the application object.
2. The activate signal is connected to `Activate`.
3. `g_application_run` runs the application.
4. After it returns, the application reference is released.
5. The result is returned to the operating system.

Inside `Activate`, the window is assembled and presented. Later button events invoke `Completed`. These callbacks run at different times; local variables from a completed function cannot be assumed to remain available.

## Draw the time line
~~~text
main -> run
          -> Activate -> return
          -> click -> Completed -> return
          -> close / application finishes
        run returns -> release -> exit
~~~
This is a conceptual trace; actual event ordering depends on the window system.

**Exercise:** where would a long, blocking file conversion inside `Completed` delay user interaction? Expected answer: while that handler occupies the event-loop thread. Moving work to a worker also requires a safe result-delivery and lifetime design.

## Troubleshoot
A frozen-looking screen may have an unwired action, a disabled control, a modal input owner or a blocked event loop. Collect evidence before choosing a cause. Avoid adding repeated event-loop calls as an unexplained repair; reentrant callbacks can make ownership harder.

Keep reusable asynchronous jobs and workbench behaviour in Framework when moving from this teaching window to a real Umicom application.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/window.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](10-separate-logic-and-window-checks.md)

