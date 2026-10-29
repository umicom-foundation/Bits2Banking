# Introduction to Umicom Framework

## Why a framework exists

Consider two applications: one records exercises and another displays bank statements. Both need to report errors, open files, manage memory and present information. Writing a different version of every shared operation in every application makes corrections difficult to keep consistent.

A library is reusable compiled code with a declared interface. A framework brings reusable libraries, conventions and services together so applications can share a foundation. Umicom Framework uses C23 for its primary implementation. An application supplies its own purpose and composes the services it needs.

A framework does not automatically provide a completed product. A Bank application still needs usable banking workflows, and a Studio application still needs an editor that opens, saves and builds real projects.

## Separate the responsibilities

~~~text
Console window                 GTK4 window
       \                         /
        \                       /
         Activity rule: validate and advance
                       |
               Umicom::base status contract
                       |
                Operating-system services
~~~

Our teaching example has one rule for advancing an exercise count. The console and graphical versions call the same function. The rule does not print text, open a window or read a file. This makes it easier to test independently.

The example uses Framework's UmiStatus enumeration. An enumeration gives readable names to a defined set of values. UMI_STATUS_OK means the operation succeeded. UMI_STATUS_INVALID_ARGUMENT means an input was outside the function's contract. UMI_STATUS_CAPACITY_EXCEEDED means that a supported limit prevented the operation.

## Know the files you are reading

Open [activity.h](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.h). A header describes the interface callers can use. Read its comment before reading its implementation. The contract says that an unsuccessful operation leaves the output unchanged and does not retain the caller's address.

Open [activity.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/activity.c). It implements that contract: it validates the pointer and count, checks the maximum, and only then stores the new value. The order matters. If it wrote a result first and discovered an error later, callers could receive both an error and a partially changed value.

Open [console.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/console.c). It translates the result into a message. umi_status_text is a real Framework function, supplied by the SDK; this lab does not copy its implementation.

## Understand an SDK

SDK means software development kit. For this example it includes public headers, compiled libraries and a CMake package description. Headers let the compiler check a call. Libraries provide its implementation. The package description tells CMake which include directories and dependent libraries belong to a component.

A source folder containing status.h is not enough to satisfy a linker looking for umi_status_text. An installed SDK brings the corresponding declarations and compiled implementations together.

Use the [standalone Framework build and installation steps](../../umicom/windows-development.md). Keep the SDK built from the revision you intend to test. Mixing a new header with an old library can cause compile, link or runtime failures.

## Find the next layer

The CMake name Umicom::base denotes an imported component target. The double colon is part of CMake's target naming convention; it is not a C operator in this context. Link the target rather than copying Framework source files into the application.

For a larger product, look for an existing Framework service before implementing another persistence, ownership or error-reporting mechanism. Put product-specific rules in the product. Add reusable services to Framework with an explicit contract and regression checks.

**Question:** Does a successful console example prove that the GTK window works?

**Answer:** No. It checks the console route and linked logic. The graphical route also depends on GTK, a display environment and its own interactions. Keep those results separate.

Next, read [Introduction to CMake](03-introduction-to-cmake.md).

[Course contents](index.md)
