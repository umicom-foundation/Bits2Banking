<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/10-exercise-server-events-without-http.md

PURPOSE:
Exercise production widget events without HTTP

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Exercise production widget events without HTTP

## Before starting

Build the lab with BUILD_TESTING=ON and a Wt installation exporting Wt::Test. Locate test_application.cpp and the production factory in profile_application.cpp. The fixture constructs the existing application rather than a separate demonstration form.

## Follow ownership

Exercise creates WTestEnvironment first and then the application. On return, the application and its widgets are destroyed before the environment. The input, button and result pointers are borrowed from that widget tree. They must never escape the application lifetime. The factory assigns stable object names so the fixture can find the controls without relying on layout coordinates.

## Send an event through the real connection

Setting input text alone does not activate the validation handler. The click case emits the production button signal, while the Enter case emits the input signal. Both should reach the existing lambda and the real C policy. These are in-memory signal calls; no browser sends a request.

~~~cpp
input->setText("Bob-8");
input->enterPressed().emit();
CHECK(result->text().toUTF8() == "Accepted name: bob-8");
~~~

## Run the focused checks

Run the focused command after a successful test-enabled build. Record the number of cases discovered as well as their outcomes. A zero-test result cannot establish that the fixture worked.

~~~powershell
ctest --test-dir build-source --output-on-failure -R '^btb\.wt_profile\.'
~~~

## Read a failure narrowly

A missing control points first to object naming or factory construction. A wrong result after Enter points to the signal connection or policy inputs. A crash during cleanup points to ownership. A passing fixture leaves HTTP startup, resource loading, browser JavaScript, accessibility and concurrent sessions unverified.

## Exercise and worked answer

The fresh-session case destroys one application and creates another, checking that the new input starts empty. Does that prove two concurrent browser sessions cannot interfere? No. It checks sequential re-creation. The separate browser-context exercise is still needed, and concurrency under load would need additional instrumentation and tests.

## Reference

[Wt test environment reference](https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1Test_1_1WTestEnvironment.html). Consult the version matching your installation.

## Read the source

[labs/framework/wt-profile/test_application.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/test_application.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Build one shared C policy for the web adapter](09-build-a-shared-c-policy-target.md) · [Next: Separate public assets from application source](11-separate-public-assets-from-source.md)
