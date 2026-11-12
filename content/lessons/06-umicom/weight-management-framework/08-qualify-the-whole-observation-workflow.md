<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/08-qualify-the-whole-observation-workflow.md

PURPOSE:
Collect evidence for each application boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Collect evidence for each application boundary

## Before you begin
Read the preceding lessons and keep the exact source and SDK identities for your practice build. Use only synthetic observations during early qualification.

## Start with the native contract
The new Framework regression groups cover decimal values, refused syntax, numeric capacity, complete entries, invalid dates/units and note length. Their registration is visible in cmake/UmicomWeightLog.cmake.

~~~powershell
ctest --test-dir build/your-framework-build --output-on-failure -R "^framework[.]weight_log[.]"
~~~

Replace the build path with a configured and built Framework tree. Listing tests is not executing them. Capture the final command status and failed/skipped cases, not just a line containing the word pass.

## Follow one fixture through each boundary
1. Use the same date and integer grams in the C client, desktop form and browser request.
2. Compare the accepted model before examining presentation.
3. Save an authorized reviewed revision, reopen it and compare exact content.
4. Introduce an invalid date, wrong unit and stale revision, then verify that each refusal preserves the accepted model.
5. On mobile, repeat the workflow after backgrounding and process recreation.

## Expected evidence
A parser pass demonstrates input admission for the tested build. A database readback adds persistence evidence. A screenshot demonstrates one visible state. None alone proves the complete product, every platform or safe deployment.

Keep build identity, test command and result together. Record missing tools and skipped tests separately. Do not turn a known missing mobile dependency into an unconditional passing test.

## Exercise
Create a release checklist with a row for each boundary: parser, shared form, storage, desktop editor, web host, mobile lifecycle and distribution. Mark a row verified only when you have executed evidence for its actual source and environment. Mark the rest unexecuted or blocked with a concrete reason.

## Recovery
When two clients disagree, first compare schema and SDK versions, then the submitted bytes and revision expectations using synthetic reproductions. Keep private personal data out of bug reports. Add a narrow regression for the discovered contract failure before broadening the feature.

This first course sequence provides a native example and real integration contracts. The finished multi-platform application, its approved layouts, authentication and deployment are further work. That distinction makes the next implementation step reviewable.


[Course contents](index.md) · [Previous lesson](07-plan-a-mobile-native-boundary.md) · [Next lesson](09-test-the-kilogram-boundary-with-synthetic-inputs.md)
