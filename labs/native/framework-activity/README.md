# Framework activity example

This example shares one checked counting rule between a console and an optional GTK4 window. It consumes an installed Umicom Framework base component rather than copying Framework implementation files.

Read [Umicom Framework Development](../../../content/lessons/umicom-development/index.md) for a step-by-step explanation. The [CMake lesson](../../../content/lessons/umicom-development/03-introduction-to-cmake.md) gives configure, build, test and console commands. The [GTK4 lesson](../../../content/lessons/umicom-development/05-introduction-to-gtk4.md) enables and checks the window.

The rule accepts counts from zero to 999 and advances them by one. At 1000 it returns capacity exceeded. Higher values or a null output pointer are invalid. A failed call preserves the output. The six CTest cases cover the first and last successful counts, full capacity, invalid input, null output and an in-place update.

The program does not save data or connect to a network. Closing its window ends that count. Graphical checks require a display and are separate from the logic tests.
