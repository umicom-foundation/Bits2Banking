<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/05-input-boundaries-and-plain-text-output.md

PURPOSE:
Validate input boundaries and display plain text

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Validate input boundaries and display plain text

Wt is a C++ library for building web applications with server-side widgets. A browser displays the interface while a server process handles application events. This course builds a small local web application that calls the same Umicom Framework C name-validation service as the desktop lab.

## Before starting

<!-- The shared policy target and explicit event-test dependency replace the broader setup. The previous wording is retained for engineering review.
Install a C++ compiler, CMake, Ninja, Wt 4 with its HTTP connector, and a matching Umicom Framework SDK containing UmiLocalProfileNameBytes. Open a terminal in the Bits2Banking labs/framework/wt-profile directory. Follow its README for PowerShell or Bash configuration, build and launch commands. The server binds to 127.0.0.1 on port 9090 for this exercise; open http://127.0.0.1:9090/ in a browser on the same computer. Stop the server with Ctrl+C. Reading requires no account. Running requires these development tools.
-->
Prepare compatible C23 and C++17 compilers, CMake 3.26 or later, Ninja and Wt 4 with its HTTP connector and test library. Choose either a matching Framework SDK containing the profile_name component or the explicit Framework source route in the lab README. Open labs/framework/wt-profile and follow that guide for configuration, event tests and loopback launch. Use the dedicated build/public directory and the real installed Wt resources path. Open http://127.0.0.1:9090/ on the same computer and stop the server with Ctrl+C. Reading requires no account; executing the lab requires the selected development tools.

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md) -->
[Open the complete lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/README.md).

## The browser is not the authority

A browser control can guide input, but a client can send unexpected data. The server must apply the real contract. In this lab, Framework accepts 3 to 48 ASCII characters, beginning with a letter, and permits letters, digits, hyphen and underscore. It publishes lower-case output.

The length passed to the C function is a byte count. UTF-8 can use more than one byte for a character. A future international naming policy would need explicit rules; it should not emerge accidentally from inconsistent frontend checks.

## Inspect the data boundary

1. Read input->text().toUTF8(). It creates an owned std::string.
2. Read bytes.data() and bytes.size(). The C function receives exactly that span.
3. Find the output array capacity constant.
4. Check that failure displays a fixed explanation rather than uninitialised output.
5. Find setTextFormat(Wt::TextFormat::Plain).

Plain-text rendering treats the result as text. It does not ask Wt to interpret user-controlled content as markup. Validation and output encoding address different problems; a broad future text field still needs correct output handling even if it passes validation.

## Boundary exercise

| Input | Expected result |
| --- | --- |
| Alice_7 | Accepted as alice_7 |
| Ab | Rejected: too short |
| 48 ASCII letters | Accepted |
| 49 ASCII letters | Rejected |
| 7Alice | Rejected: first character |
| ../Alice | Rejected: punctuation |
| A name with a space | Rejected |

Try these cases through the running page. Add an accented character and record the rejection under this contract. Do not paste passwords or personal account details into the exercise.

## Think beyond the example

A profile name validator does not make a filesystem path safe, authorise a user, prevent request flooding or secure a database query. Each operation needs its own boundary. For example, writing a file still requires a rooted path policy, and an account update still requires authentication and authorisation.

## Check your understanding

What protects against reading beyond this input? The exact readable byte span and the service's bounded implementation. What protects the result widget from treating text as markup? Its explicit plain-text mode. These are complementary controls, not interchangeable ones.

## Read the source

<!-- Published documentation resolves source links through the repository browser. Retained route: [Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp) -->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/profile_application.cpp).

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Connect web controls to the shared C service](04-events-and-shared-c-services.md) · [Next: Test a local web workflow and record outcomes](06-test-a-local-web-workflow.md)
