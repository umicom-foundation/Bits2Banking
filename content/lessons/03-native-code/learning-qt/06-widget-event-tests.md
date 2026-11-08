<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/06-widget-event-tests.md

PURPOSE:
Test the real widget event path

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test the real widget event path

Qt is a library for building applications. A widget is a visible control, such as a text box or button. This course builds a small desktop interface that calls a C function in Umicom Framework. The interface uses C++ because Qt Widgets exposes a C++ API; the reusable validation policy stays in Framework C.

## Before starting

Use a development copy of Umicom Bits2Banking and an installed Umicom Framework SDK containing the profile_name component and UmiLocalProfileNameBytes. Install a matching Qt 6 development kit, C++ compiler, CMake and Ninja. A kit groups tools and libraries compiled to work together. Do not combine libraries from different compiler families. Open a terminal in labs/framework/qt-profile. The lab README contains complete PowerShell and Bash commands and explains how to choose installation prefixes. The exercises check names only; they do not create an account or contact a broker.

[Open the lab setup guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/README.md).

## What this test observes

A unit test checks a small contract. This example's widget test also constructs the real view, sends events and inspects its visible text. It therefore catches some missing connections that a direct call to the C validator would miss.

The test is a normal executable with main. A nonzero return value reports failure. Qt Test provides helpers for simulated key and mouse input; see the [QTest reference](https://doc.qt.io/qt-6/qtest.html).

## Read the test in order

1. Find QApplication and the window construction. They match the application's startup needs.
2. Find PopulateProfileWindow. The test uses the production view, not a second imitation.
3. Find findChild calls. They locate controls by stable object names.
4. Find QTest::keyClicks and QTest::mouseClick. These exercise the click connection.
5. Find QTest::keyClick with Qt::Key_Return. This checks the keyboard route.
6. Read the 48- and 49-character cases, the non-ASCII case and the empty-input case.

~~~text
missing control -> test exits 1
wrong accepted result -> test exits 2
Enter fails to reject invalid input -> test exits 3
~~~

The remaining codes identify later boundary checks. Return codes make failure observable even when no test window is displayed.

## Run and interpret

Configure with BUILD_TESTING=ON and build btb-qt-profile-test using the lab README. Then run ctest --test-dir build/qt-profile --output-on-failure from the lab directory. A successful run should report the btb.qt_profile.events test passing.

CTest supplies -platform offscreen to this test. Offscreen execution is useful for event-path checks, but it does not prove that the installed application's windows receive real operating-system input, scale correctly or work with a screen reader. Keep those as separate manual qualification steps.

## Introduce and repair a defect

In a disposable practice copy, disconnect the Enter connection and run the test again. The keyboard case should fail. Restore the connection and repeat. This shows why a test should observe a behaviour that can actually be broken.

Do not weaken the expected result to make a failing run green. Inspect the first failing case, the tested binary and its linked SDK version before deciding whether the implementation or the test is wrong.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/test_window.cpp).

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Pass text safely from Qt to a C function](05-text-bytes-and-c-boundaries.md) · [Next: Troubleshoot a desktop adapter with evidence](07-troubleshoot-with-evidence.md)

<!-- The original out-of-docs lab routes are retained for review: (../../../../labs/framework/qt-profile/README.md) (../../../../labs/framework/qt-profile/test_window.cpp). Published manuscripts use repository source links because the site does not copy the labs directory. -->

<!-- The earlier setup required an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. The profile_name component now supplies the same policy without account-storage dependencies; the previous requirement is retained here for review. -->
