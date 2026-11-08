<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/04-events-and-shared-c-services.md

PURPOSE:
Connect web controls to the shared C service

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Connect web controls to the shared C service

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

<!-- The shared policy target and explicit event-test dependency replace the broader setup. The previous wording is retained for engineering review.
Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.
-->
Prepare compatible C23 and C++17 compilers, CMake 3.26 or later, Ninja and Wt 4 with its HTTP connector and test library. Choose either a matching Framework SDK containing the profile_name component or the explicit Framework source route in the lab README. Open labs/framework/wt-profile and follow that guide for configuration, event tests and loopback launch. Use the dedicated build/public directory and the real installed Wt resources path. Open http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C. Reading requires no account; executing the lab requires the selected development tools.

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md) -->
[Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md).

## Trace one action

The check button emits a clicked signal. The input emits an enterPressed signal. Both connect to the same validate callback. The callback converts the current text to UTF-8, invokes UmiLocalProfileNameBytes and sets the result text.

~~~text
button click --+
               +-> validate -> Framework -> status -> result
Enter key -----+
~~~

A callback is code saved for a later event. The const auto validate declaration lets the compiler infer the callback's C++ type. The capture [input, result] provides access to this session's controls.

## Step through the source

1. Locate the callback's std::string bytes variable.
2. Find bytes.data() and bytes.size(). They pass an address and exact byte count.
3. Find canonical, the fixed-capacity output array.
4. Find the UMI_STATUS_OK branch.
5. Locate the two connect calls after the callback.

The frontend does not repeat the lower-casing rule or length check. If the Framework contract changes, all consumers must use the updated contract and tests rather than maintaining divergent copies.

## Verify two event routes

Enter Alice_7 and click the button. Expect Accepted name: alice_7. Enter ../../other and press Enter. Expect a rejection message. Repeat with an empty input. The result must reflect the new input, not an earlier accepted value.

If one route works and the other does not, inspect the relevant signal connection. If both reach the callback but report unexpected results, inspect the Framework status and SDK revision. If the callback is slow because future work adds network requests, investigate the operation's scheduling and cancellation model instead of hiding the delay with a misleading success message.

## Add a view-only feature

In a practice copy, add a Clear button. It should empty the input and reset the result text. It must not create or delete a profile. Keep this presentation behaviour in the Wt adapter. Keep any reusable account or storage policy in Framework.

## Check your understanding

Why are two signals connected to one callback? To keep equivalent actions consistent. Why is canonical read only after success? Because the function publishes valid output only on success. Why is this still not registration? No durable profile is created by the callback.

## Read the source

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp) -->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Keep each session’s widgets and state separate](03-session-owned-widget-trees.md) · [Next: Validate input boundaries and display plain text](05-input-boundaries-and-plain-text-output.md)
