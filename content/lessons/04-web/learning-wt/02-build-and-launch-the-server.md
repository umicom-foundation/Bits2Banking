<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/02-build-and-launch-the-server.md

PURPOSE:
Build and launch the Wt server

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build and launch the Wt server

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.

[Open the complete lab guide](../../../../labs/framework/wt-profile/README.md).

## What must be available

The compiler translates C++ source. CMake prepares build instructions. Ninja executes those instructions. Wt supplies the web widgets and HTTP connector. Umicom Framework supplies the C validation service. A browser is the client used to interact with the running server.

## Read the build file

1. Find LANGUAGES C CXX. The consumer uses C++ at the Wt boundary and links a C service.
2. Find find_package(UmicomFramework ... security).
3. Find find_package(Wt ... Wt HTTP).
4. Find add_executable. It lists the two source files compiled into this server.
5. Find target_link_libraries. Wt::Wt supplies the core library and Wt::HTTP supplies the connector used here.

Package targets carry dependency information. They should come from a Wt installation built for the same compiler and architecture as the application. A 64-bit executable cannot directly link a 32-bit library.

## Configure, build, run

Use the commands in the README with your actual package installation roots. Do not copy an example path if that directory does not exist on your machine. Configure first; build only after configuration succeeds. Then launch the executable with the documented address, port and document-root options.

A document root is a directory from which a web server may serve files. The lab command uses the lab directory for a local exercise. A production deployment should expose only intended public resources; it should not point at a home directory, repository root with secrets or arbitrary drive.

~~~text
source files + package metadata -> build instructions
build instructions + compiler -> server executable
server executable + launch options -> listening process
~~~

## Verify the launch

Open the URL printed in the guide. Check a valid name and an invalid name. Record the server's startup output and any browser error. A successful build establishes that the selected source can compile and link in that environment; it does not establish that the web workflow has been exercised.

## Troubleshooting

If the Wt package is not found, inspect the installation prefix. If the HTTP target is missing, install a Wt build that includes that connector. If a shared library cannot load, repair the runtime library search path. If port 9090 is already in use, stop the process that you own or select another unused port and use that same port in the browser URL.

## Read the source

[Open the example source](../../../../labs/framework/wt-profile/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Browser, server and session](01-browser-server-and-session.md) · [Next: Keep each session’s widgets and state separate](03-session-owned-widget-trees.md)
