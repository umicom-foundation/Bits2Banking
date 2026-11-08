<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/01-browser-server-and-session.md

PURPOSE:
Browser, server and session

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Browser, server and session

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

<!-- The shared policy target and explicit event-test dependency replace the broader setup. The previous wording is retained for engineering review.
Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.
-->
Prepare compatible C23 and C++17 compilers, CMake 3.26 or later, Ninja and Wt 4 with its HTTP connector and test library. Choose either a matching Framework SDK containing the profile_name component or the explicit Framework source route in the lab README. Open labs/framework/wt-profile and follow that guide for configuration, event tests and loopback launch. Use the dedicated build/public directory and the real installed Wt resources path. Open http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C. Reading requires no account; executing the lab requires the selected development tools.

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md) -->
[Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md).

## Three different things

A browser displays pages and sends user actions. A server is a program that listens for requests and responds. A session groups one user's ongoing interaction so that the server can keep the right state for that interaction.

~~~text
browser tab -> local HTTP connection -> Wt application session
                                           |
                                           v
                                Framework C validation
~~~

HTTP is a protocol: an agreed format for exchanging requests and responses. A port is a numbered endpoint used by a process that listens for network traffic. The lab uses port 9090. The address 127.0.0.1 is loopback, which refers to the same computer.

## Follow startup

1. Open main.cpp.
2. Find Wt::WRun. It starts the Wt server and uses the supplied application factory.
3. Follow CreateProfileApplication into profile_application.cpp.
4. Find the creation of WApplication. This owns the session's interface.
5. Follow calls through application->root(). They add controls to that session's root container.

The browser does not execute the Framework C function directly. An event reaches the server, which calls the function and updates the result shown to that session.

## First experiment

Build and launch using the lab README. Keep the server terminal open. Open the local URL in a browser. Enter Alice_7 and choose Check name. Expect a lower-case accepted name. Stop the server and try another interaction. Observe how the browser behaves when its server is unavailable.

Do not infer that a page still visible in a browser proves the server is alive. A previously rendered interface can remain visible after the process stops.

## Recover from a connection failure

Check that the server process is running, the chosen port is free and the URL uses the same port. A compiler error cannot be fixed by refreshing a browser. A connection-refused error does not necessarily mean the C validation logic is wrong.

## Check your understanding

Where does the C function run? In the server process. Why use a session? To associate controls and state with the correct interaction. Does a session prove who a person is? No. Authentication is an additional feature with its own rules.

## Read the source

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/main.cpp) -->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/main.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Next: Build and launch the Wt server](02-build-and-launch-the-server.md)
