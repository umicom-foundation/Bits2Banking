<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/18-separate-a-skip-from-a-test-that-could-not-start.md

PURPOSE:
Separate a skip from a test that could not start

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Separate a skip from a test that could not start

Three learners turn up for a practical exercise. One finishes, one cannot use an optional piece of equipment, and one cannot start because their worksheet is missing. A test report can record these situations separately. Look for the result and the reason before counting what was checked.

## 1. Run a three-case practice project

Use a developer terminal with CMake and Ninja available. In an empty practice folder, save this file as `CMakeLists.txt`. A **fixture** is the small program or command that performs a test. Here the first two fixtures use built-in CMake commands. The third points to a file you have deliberately left absent.

~~~cmake
cmake_minimum_required(VERSION 3.24)
project(PracticeCoverage LANGUAGES NONE)
enable_testing()

add_test(NAME practice.pass COMMAND "${CMAKE_COMMAND}" -E echo "checked")
add_test(NAME practice.optional COMMAND "${CMAKE_COMMAND}" -E false)
# In this teaching fixture alone, exit 1 models an unavailable capability.
set_tests_properties(practice.optional PROPERTIES SKIP_RETURN_CODE 1)

add_test(NAME practice.missing COMMAND "${CMAKE_CURRENT_BINARY_DIR}/absent-check")
~~~

~~~powershell
cmake -S . -B build -G Ninja
ctest --test-dir build --output-on-failure
$LASTEXITCODE
~~~

The checked run reported one `Passed`, one `Skipped` and one `Not Run`. It also printed that the third executable could not be found. Expect a nonzero exit code from this exercise. The optional fixture ran and returned the configured signal. The missing fixture never started.

## 2. Read the evidence before choosing what to do

| Result | What to check next |
| --- | --- |
| Passed | Record which test version ran and which condition it verified. |
| Skipped | Record the unavailable capability. Arrange a later run where that capability is available if the coverage matters. |
| Not Run with a missing executable | Check the configured target and the last build's link step. Confirm the expected program exists before repeating the test. |

To list the registered cases, run `ctest --test-dir build -N`. A listed case describes the plan. Use the result lines from the real run to record execution. Keep the full output with your notes so another person can find the reason for the third result.

~~~c
static int FixtureOutcome(int optionalCapability, int checkPassed)
{
    /* This fixture reserves one distinct code for a missing capability. */
    if (!optionalCapability)
        return 77;
    return checkPassed ? 0 : 1;
}
~~~

Read the C function as a model for your own fixture. The caller supplies what it observed. A real CTest registration for this function's fixture can reserve 77 as its skip code. Keep the check failure code separate so a failed check remains visible. Platform checks in Umicom can use this pattern for optional test capabilities.

~~~text
IF the fixture could not start, record the launch reason
OTHERWISE IF its optional capability is unavailable, record the skip reason
OTHERWISE record the check's actual outcome
~~~

For practice, change `practice.optional` to use the same echo command as `practice.pass`, then configure and run again. The optional row should now pass. The missing row should still report that its program could not start. [CTest skip return codes and limits](https://cmake.org/cmake/help/latest/prop_test/SKIP_RETURN_CODE.html)

[Course contents](index.md) · [Previous lesson · Check available build and temporary space](17-check-available-build-and-temporary-space.md) · [Check the selected executable](13-match-the-selector-to-the-test-executable.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/18-separate-a-skip-from-a-test-that-could-not-start.html)
