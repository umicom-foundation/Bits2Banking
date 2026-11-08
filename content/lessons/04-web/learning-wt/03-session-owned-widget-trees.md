<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/03-session-owned-widget-trees.md

PURPOSE:
Keep each session’s widgets and state separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep each session’s widgets and state separate

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

<!-- The shared policy target and explicit event-test dependency replace the broader setup. The previous wording is retained for engineering review.
Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.
-->
Prepare compatible C23 and C++17 compilers, CMake 3.26 or later, Ninja and Wt 4 with its HTTP connector and test library. Choose either a matching Framework SDK containing the profile_name component or the explicit Framework source route in the lab README. Open labs/framework/wt-profile and follow that guide for configuration, event tests and loopback launch. Use the dedicated build/public directory and the real installed Wt resources path. Open http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C. Reading requires no account; executing the lab requires the selected development tools.

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md) -->
[Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md).

## Ownership in a web interface

The application factory returns a std::unique_ptr to WApplication. A unique pointer owns one object and releases it when its ownership ends. Wt's root container owns the controls added to it. The local raw pointers input, check and result refer to those owned controls; they are used to connect behaviour.

~~~text
session A application -> A input, A button, A result
session B application -> B input, B button, B result
shared code            -> stateless C name validator
~~~

Sharing code is useful. Sharing one user's editable input object with every other session would be a defect.

## Inspect the example

1. Find std::make_unique<Wt::WApplication>.
2. Find root()->addNew for each control.
3. Check that input and result are local variables inside the factory.
4. Search the file for global mutable input or result objects. The example does not need them.
5. Follow the callback capture. It retains pointers to controls in this session's tree.

The C validator accepts input bytes and produces an output name. It does not need a global current-user variable. This makes it easier to call from independent interfaces.

## Two-session experiment

Start the lab server. Open the page in a normal browser window and in a private browser window. Enter Alice_7 in the first and Bob_8 in the second. Check both. The first should still show alice_7 and the second bob_8. Refresh one and observe how the application starts a fresh interaction under the current session behaviour.

Different browser contexts are useful here because ordinary tabs can share cookies and authentication state. This exercise is an observation of the lab, not a general guarantee about all session configurations.

## A dangerous shortcut

Moving a mutable result string to a process-wide variable may seem convenient for a demonstration. It can cause one user's request to overwrite another user's result. Protecting that variable with a mutex would prevent some simultaneous access problems, but it would not fix the incorrect ownership model.

## Exercise

Draw the object tree for two active sessions. Mark which objects are owned by a session and which code can be reused. Explain why the validation function can be shared while the result widget cannot.

## Read the source

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp) -->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Build and launch the Wt server](02-build-and-launch-the-server.md) · [Next: Connect web controls to the shared C service](04-events-and-shared-c-services.md)
