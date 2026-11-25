<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/index.md

PURPOSE:
Define a passing result, preview a small native test plan and keep evidence for each target.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Automated Testing with Umicom Framework

Define a passing result, preview a small native test plan and keep evidence for each target.

## Lessons

- [Write the expected result](01-write-the-expected-result.md)
- [Choose target operations before dispatch](02-choose-target-operations.md)
- [Check a workflow and its cleanup](03-check-a-workflow-and-cleanup.md)
- [Read one test evidence row](04-read-one-evidence-row.md)
- [Qualify each platform separately](05-qualify-each-platform-separately.md)
- [Keep the fixture permissions small](06-keep-the-fixture-permissions-small.md)
- [Select one saved test result](07-select-one-saved-test-result.md)
- [Read a workflow summary](08-read-a-workflow-summary.md)
- [Read counted results from a running test log](09-read-counted-results-from-a-running-test-log.md)
- [Keep the outer test total](10-keep-the-outer-test-total.md)
- [Keep startup evidence with its test attempt](11-keep-startup-evidence-with-its-test-attempt.md)
- [Check the link inputs of a fixture](12-check-the-link-inputs-of-a-fixture.md)
- [Match the selector to the test executable](13-match-the-selector-to-the-test-executable.md)
- [Check complete rows in a saved prefix](14-check-complete-rows-in-a-saved-prefix.md)
- [Group console checks by what they submit](15-group-console-checks-by-what-they-submit.md)
- [Check a shorter Windows build path](16-check-a-shorter-windows-build-path.md)
- [Check available build and temporary space](17-check-available-build-and-temporary-space.md)
- [Separate a skip from a test that could not start](18-separate-a-skip-from-a-test-that-could-not-start.md)

## Try the optional native lab

The readings start with simple examples. For the optional native lab, use a C23 compiler and a Framework SDK with `UmiUatCheckTargetAdmission`.

1. Save main.c and CMakeLists.txt together in a new practice folder.
2. Set UMICOM_SDK_PREFIX to the absolute directory of the installed Framework SDK. Configure a new build directory and build the umicom-testing-preview target.
3. Run the resulting program. Expect Amount rule passed. Preview: ready, unavailable, denied. Adapter calls: 0.
4. If the target header or symbol is missing, check which SDK was configured. Use a new build directory when switching SDKs.

~~~powershell
cmake -S . -B build -G Ninja -DUMICOM_SDK_PREFIX="C:/path/to/installed-sdk"
cmake --build build --target umicom-testing-preview
.\build\umicom-testing-preview.exe
~~~

[C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt) · [HTML course](../../../courses/automated-testing-with-umicom/index.html)
