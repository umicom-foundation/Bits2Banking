<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/08-share-framework-services-across-frontends.md

PURPOSE:
Share Framework services across web and desktop

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Share Framework services across web and desktop

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

<!-- The shared policy target and explicit event-test dependency replace the broader setup. The previous wording is retained for engineering review.
Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.
-->
Prepare compatible C23 and C++17 compilers, CMake 3.26 or later, Ninja and Wt 4 with its HTTP connector and test library. Choose either a matching Framework SDK containing the profile_name component or the explicit Framework source route in the lab README. Open labs/framework/wt-profile and follow that guide for configuration, event tests and loopback launch. Use the dedicated build/public directory and the real installed Wt resources path. Open http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C. Reading requires no account; executing the lab requires the selected development tools.

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md) -->
[Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md).

## One contract, different interfaces

<!-- The portable policy target supports the expanded frontend courses without moving authority into a view. The previous wording is retained for engineering review.
The Qt and Wt labs collect the same name and call UmiLocalProfileNameBytes. Qt displays a desktop window. Wt serves a browser interface. Neither adapter owns the validation rule. This is a small example of a thin client: presentation code delegates reusable behaviour to a shared engine.
-->
The Qt and Wt labs collect the same name and call UmiLocalProfileNameBytes from Umicom::profile_name. Qt can compile the form for desktop, browser or mobile targets; this Wt lab runs its policy in a server application. Neither adapter owns the naming rule. Shared source still needs separate builds and observations for each target, and the location of execution changes what a result can authorize.

## Compare the implementations

1. Open profile_application.cpp in this lab.
2. Open profile_window.cpp in labs/framework/qt-profile.
3. Find the Framework call in each file.
4. Compare how each toolkit obtains UTF-8 bytes.
5. Compare ownership: a Qt window tree and a Wt session tree.
6. Compare event connections: click and Enter in both interfaces.
7. Compare status handling and plain-text result presentation.

~~~text
shared: input contract, canonical output, error status
specific: controls, event binding, layout, application lifetime
~~~

A shared service should expose enough information for each frontend to explain a failure. It should not embed the geometry of a desktop dialog or depend on a particular browser session.

## Extend toward a larger application

Start with one complete user journey. For example, validate a project name, choose a destination, create files through an existing rooted service and show a result. Each step should have a real implementation and a tested failure path. Do not advertise a finished project creator when only the name checker is wired.

For long-running work, define an operation identity, progress, cancellation and a safe completion handoff. The user may close a view while the service is still running. A callback must not access a destroyed widget just because the underlying job completed successfully.

## Review questions

Which code changes if the permitted name length changes? The authoritative Framework contract and its tests, with consumers rebuilt against it. Which code changes if a web button moves? The web presentation. Which code changes if a database is introduced? The relevant service/backend boundary, not a hidden database call inside every frontend button.

## Continue learning

Use [Learning Qt](../../../courses/learning-qt/index.html) for the desktop event lab, [Learning CMake](../../../courses/learning-cmake/index.html) for package and target concepts, and the Umicom development course for offline learning-module integration. Keep the implementations small enough that you can trace a user action from input to service to visible outcome.

## Continue the server workflow

The next eight lessons follow the shared target into automated events, public resources, independent browser contexts, failure diagnosis, bounded work and deployment evidence. Start with [Build one shared C policy](09-build-a-shared-c-policy-target.md).

## Read the source

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp) -->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Plan registration and login beyond a name checker](07-from-name-check-to-registration.md) · [Next: Build one shared C policy for the web adapter](09-build-a-shared-c-policy-target.md)
