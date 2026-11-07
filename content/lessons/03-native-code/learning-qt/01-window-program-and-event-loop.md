<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/01-window-program-and-event-loop.md

PURPOSE:
A window, a program and an event loop

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# A window, a program and an event loop

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](../../../../labs/framework/qt-profile/README.md).

## What you will learn

A running program is a process. Its main function is where this example starts. A window is an object managed by that process; it is not the entire program. An event is a notification, such as a key press, mouse click or request to close a window.

~~~text
operating system -> event queue -> Qt -> connected function -> visible result
~~~

## Follow the startup

1. Open main.cpp in a text editor.
2. Find QApplication application(argc, argv). argc counts command-line arguments; argv points to their text. QApplication prepares the GUI event machinery.
3. Find QWidget window. This is the top-level window, stored as a local variable.
4. Follow PopulateProfileWindow(&window). The ampersand obtains the address of the window so another function can populate that same object.
5. Find window.show(). Construction alone does not display the window.
6. Find application.exec(). This runs the event loop until the application is asked to finish. It is normal for this call not to return while the window remains open.

Qt requires a QApplication for a Widgets application. See the [QApplication reference](https://doc.qt.io/qt-6/qapplication.html).

## Try it

Build and launch using the setup guide. Expect one window with a name input, a Check name button and a result line. Move the window and resize it. Close it and observe that the terminal becomes available again. Record what actually happens on your machine.

In a separate copy of the lab, temporarily comment out window.show(), rebuild, and compare. Restore it afterwards. This experiment separates creating an object from displaying it; it does not test whether Framework validation works.

## If the window never appears

Run from a terminal so startup diagnostics remain visible. A missing Qt platform plugin or DLL is a runtime packaging problem; a compiler diagnostic is a build problem. Read the first error before changing code. If the window appears but clicks have no effect, continue to the signal lesson rather than repeatedly reinstalling the compiler.

## Check your understanding

Why does code after application.exec() normally wait? Because the event loop remains active while the application handles events. Why use &window? So the function receives the existing object's address, rather than an unrelated window.

## Read the source

[Open the example source](../../../../labs/framework/qt-profile/main.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Next: Build a small Qt consumer of the Framework SDK](02-build-a-small-qt-consumer.md)
