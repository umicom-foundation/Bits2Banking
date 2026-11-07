<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/06-test-a-local-web-workflow.md

PURPOSE:
Test a local web workflow and record outcomes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test a local web workflow and record outcomes

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.

[Open the complete lab guide](../../../../labs/framework/wt-profile/README.md).

## Define an observable test

A useful test names its starting state, action and expected result. 'The server starts' is one test. 'Pressing Enter validates the entered name' is another. They should not be treated as equivalent.

## Manual test sequence

1. Start the lab on loopback using the README command.
2. Open the page in a new browser context. Expect the initial instruction and empty input.
3. Type Alice_7 and click Check name. Expect Accepted name: alice_7.
4. Replace it with ../../other and press Enter. Expect the fixed rejection explanation.
5. Clear the input and submit again. Expect rejection rather than the previous accepted name.
6. Try the 48- and 49-byte boundaries from the preceding lesson.
7. Use Tab and Shift+Tab to reach the input and button. Submit without a mouse.
8. Open a second browser context and check that its result does not replace the first context's result.
9. Stop the server and record the observed connection-loss behaviour.

Keep each actual result beside its expected result. Mark a step not run when you have not executed it. A planned test case is not a pass.

## Separate layers of coverage

The Framework C service has boundary tests for its contract. A Wt service call can reuse that tested policy, but its event wiring and session ownership still need coverage. A browser-level test observes the complete journey. A load test would examine many sessions and resource limits. An accessibility review examines another set of requirements.

This lab currently provides the application source and a manual web checklist. It does not claim an automated browser suite or production deployment qualification.

## Investigate a failure

If the page renders but a click does nothing, check the server log and signal connection. If two sessions affect each other, inspect state ownership. If only one browser behaves differently, record the browser version and interaction before changing shared C logic.

## Exercise

Write a small table containing three cases: valid input by click, invalid input by Enter and two-session isolation. Include actual results only after running them. This is the beginning of a repeatable qualification record, not a substitute for implementing the missing checks.

## Read the source

[Open the example source](../../../../labs/framework/wt-profile/README.md).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Validate input boundaries and display plain text](05-input-boundaries-and-plain-text-output.md) · [Next: Plan registration and login beyond a name checker](07-from-name-check-to-registration.md)
