<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/12-browser-boundaries-and-trust.md

PURPOSE:
Separate browser validation from server authority

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate browser validation from server authority

## Before starting

Run or read the browser exercise. Open profile_window.cpp and identify the single shared C call. Compare it with the Wt course, where a server-side application receives events. Both examples check the same naming rule, but the location of execution changes what the result can authorize.

## Trace the result

The Qt Wasm name check runs in the browser. The form turns a QString into UTF-8 bytes, passes the exact byte count and displays the returned status. The user controls this client environment. An Accepted name label is a local explanation, not a server-issued identity or permission. The lab intentionally contains no registration request.

~~~text
Text field -> UTF-8 byte span -> local C policy -> result label
Future request -> server admission -> shared policy -> authorized storage
~~~

## Design a future request honestly

If a later product adds registration, the receiving service must validate its own request and enforce authentication and authorization for protected actions. Do not send an accepted=true flag and assume it is trustworthy. Send the necessary input under an explicit protocol and let the receiving service apply its own policy. A rejected client field should still be helpful to the user, but server refusal remains possible.

## Keep capabilities explicit

This lab needs neither credentials nor local files. Do not add account storage to the portable target merely because the desktop account library exposes it. Browser file and network capabilities have their own permissions and protocols. Keep a future adapter outside the pure naming library and describe its supported environment before using it.

## Exercise and worked answer

Imagine a request body containing name=../../other and accepted=true. Should a receiving service skip validation? No. The flag is client input. The service must independently reject the invalid name. In this lab, test the equivalent text locally and confirm the result changes to refusal; that experiment checks presentation, while the hypothetical server rule still needs its own implementation and tests.

## Review your evidence

Write three statements: the compiled target you built, the browser action you observed, and the authority you did not implement. A useful final statement is: the browser form called the shared name policy; no account creation or sign-in was exercised. Continue with the C web and Wt courses to study request boundaries in a server process.

## Read the source

[labs/framework/qt-profile/profile_window.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/profile_window.cpp). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Serve and observe the generated web application](11-serve-and-observe-the-web-build.md) · [Next: Package the same Qt lab for Android](13-package-the-android-lab.md)
