<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/07-troubleshoot-with-evidence.md

PURPOSE:
Troubleshoot a desktop adapter with evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Troubleshoot a desktop adapter with evidence

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](../../../../labs/framework/qt-profile/README.md).

## Classify the failure first

Different stages need different evidence. A package lookup failure occurs before compilation. A compiler error refers to source code. A linker error refers to missing or incompatible compiled definitions. A runtime error happens after the executable starts. A usability defect may occur even when all those stages succeed.

| Observation | First check |
| --- | --- |
| Qt package not found | Installed kit and CMake prefix |
| Framework function undeclared | SDK header revision |
| Undefined reference | Matching SDK library and link target |
| DLL or plugin missing | Runtime search path and deployment |
| Click has no visible effect | Event connection and status handling |
| Text clipped | Layout, font size and window dimensions |

## Keep a useful record

1. Write the source revision or exact files used.
2. Record compiler, Qt and SDK versions.
3. Copy the full failing command and its exit status.
4. Save the first diagnostic and the nearby context.
5. For UI failures, write the exact input and action sequence.
6. Record the expected result and the actual result separately.

For example: 'Type Alice_7, press Enter, expected Accepted name: alice_7, result label unchanged' is actionable. 'Qt is broken' is not a reproducible observation.

## Compare like with like

A new header with an old library is not a valid comparison of source changes. A test launched from one build directory may use a different executable from the desktop shortcut. Inspect the actual executable path and dependency environment before repeatedly editing the callback.

If a test passes offscreen but a real window fails, retain both observations. Investigate host input, focus, modal windows, event filters and toolkit versions. Do not report the offscreen test as proof that the user's native workflow works.

## A repair checklist

Make the smallest change that addresses a supported cause. Add or strengthen a regression check for the observed failure. Re-run the relevant checks when execution is available. Preserve the evidence of both the failure and the repaired result.

For a changed SDK service, qualify the C contract and each affected adapter. For a changed label or layout, inspect the window at different sizes. Neither a large test count nor a successful compile substitutes for testing the affected behaviour.

## Exercise

Write a defect report for a deliberately removed click connection in a practice copy. Another learner should be able to reproduce the failure using only your report.

## Read the source

[Open the example source](../../../../labs/framework/qt-profile/README.md).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Test the real widget event path](06-widget-event-tests.md) · [Next: Extend the view while keeping Framework authoritative](08-extend-the-view-without-duplicating-policy.md)
