<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/02-build-a-small-qt-consumer.md

PURPOSE:
Build a small Qt consumer of the Framework SDK

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build a small Qt consumer of the Framework SDK

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](../../../../labs/framework/qt-profile/README.md).

## The three build stages

Configuration reads CMakeLists.txt and finds dependencies. Generation writes instructions for a build tool. Building compiles source files and links the resulting machine code. A dependency is code this program uses but does not define itself.

~~~text
profile_window.cpp -> compiler -> object code --+
Framework security library --------------------+-> linker -> executable
Qt Widgets libraries --------------------------+
~~~

## Read the build description

1. Find project(... LANGUAGES C CXX). CXX is CMake's name for C++.
2. Find CMAKE_CXX_STANDARD 17. It requests the language level used by this adapter.
3. Find find_package(UmicomFramework ... COMPONENTS security). The installed package must expose the security service.
4. Find find_package(Qt6 ... COMPONENTS Widgets). Widgets is the Qt component that provides the visible controls.
5. Find add_library(btb-qt-profile-view STATIC ...). This compiles the reusable view once for the application and its test.
6. Find target_link_libraries. Imported targets such as Qt6::Widgets carry include directories and link dependencies. They are more reliable than guessing filenames for individual libraries.

## Configure and build

Follow the exact commands in the lab README, substituting your actual SDK and Qt directories. A prefix is an installation root that CMake searches for package metadata. It is not the directory containing this lesson. After configuration succeeds, build the btb-qt-profile target. Start the executable from the same configured toolchain environment.

Expected configuration output includes completion of configuration and generation. Expected build output ends without a failed command. These expectations are checks for your run, not a claim that every kit has already been qualified.

## Make one small change

Change the window title in your practice copy, build again and inspect the build output. An incremental builder should compile the changed source and relink affected targets. Unchanged source files need not all be recompiled. Deleting the build directory discards that useful state.

## Recover from a package error

If CMake cannot find Qt6Config.cmake, verify the selected kit and prefix. If it cannot find UmicomFrameworkConfig.cmake, verify that the SDK was installed. An undefined reference to UmiLocalProfileNameBytes can mean the installed library predates the header; reinstall a matching SDK rather than inventing a second implementation in the Qt application.

[Learning CMake](../../../courses/learning-cmake/index.html) explains these stages in greater depth.

## Read the source

[Open the example source](../../../../labs/framework/qt-profile/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: A window, a program and an event loop](01-window-program-and-event-loop.md) · [Next: Controls, layouts and ownership](03-controls-layouts-and-ownership.md)
