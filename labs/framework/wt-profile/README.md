# Wt profile-name laboratory

A browser form calls Umicom Framework's C profile-name validator through a thin Wt C++ adapter. Each session owns its own input and output widgets. This is a local learning example; it neither registers users nor implements authentication.

## Prepare

Install CMake 3.26 or newer, Ninja, a C/C++ compiler, Wt 4 with its HTTP connector and an Umicom Framework SDK containing the security component. Use matching operating system, architecture, compiler and runtime libraries. A package prefix is the directory containing a package's lib/cmake directory. Find the real paths on your machine before using the examples.

## Run locally

In PowerShell, from this directory:

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/umicom/installed/applications;C:/libraries/wt'
cmake --build build --parallel 2
.\build\btb-wt-profile.exe --docroot . --http-address 127.0.0.1 --http-port 9090
~~~

For bash, choose matching Unix packages, use '-DCMAKE_PREFIX_PATH=/opt/umicom;/opt/wt', and launch ./build/btb-wt-profile with the same server options. Keep the terminal open. Visit http://127.0.0.1:9090 in a browser. Press Ctrl+C in the terminal to stop the server. The loopback address restricts this exercise to your computer; the example is not a production deployment recipe.

## Manual checks

1. Enter Alice_7 and select Check name. Expect Accepted name: alice_7.
2. Enter ../../other and press Enter. Expect a rejection instead of the previous accepted result.
3. Repeat with an empty value, a non-ASCII name and 49 letters. Each is rejected by Framework.
4. Open a separate private browser session. Enter Bob there. The first session's result must not change.
5. Use keyboard navigation to reach the input and button. Check the name label is announced by your assistive technology.
6. Stop the server. A browser connection failure now describes the stopped host, not a failed validation rule.

These are steps to execute, not recorded passes. The C validator's unit tests live in Framework tests/local_profile. Browser rendering, session separation and packaging need target-host checks as well.

## Troubleshoot

If CMake cannot find Wt::HTTP, install the Wt HTTP connector using the same toolchain as the SDK. If the server reports address in use, stop your earlier lab process or choose a free port and use that same port in the browser. Do not expose this exercise on a public network as a substitute for a reviewed deployment with TLS, access policy, request limits and operational monitoring.

[Learning Wt](../../../content/courses/learning-wt/index.html)
