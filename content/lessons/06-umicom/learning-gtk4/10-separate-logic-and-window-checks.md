<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/learning-gtk4/10-separate-logic-and-window-checks.md

PURPOSE:
Explain the lesson: Separate model checks from window checks.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate model checks from window checks

## Prepare the tools
Install CMake, Ninja, a C23 compiler and a matching Framework SDK. Configure the activity lab using its README, with GTK4 enabled if graphical checks are available. CTest runs the registered model checks:
~~~powershell
ctest --test-dir build/activity-window --output-on-failure --no-tests=error
~~~
This is a command to execute after a successful build, not evidence that a run has already passed.

## Read the cases
The test program selects a case from its command-line argument. The registered cases cover first success, last success, full capacity, invalid input, a null output and an in-place update.

Notice the sentinel `result = 77U`. Failure checks require it to remain 77. That verifies an observable contract beyond merely returning an error.

## Add the UI dimension
A model test never clicks the real button. Write a separate window checklist:
1. Launch and locate Record one exercise.
2. Activate with the pointer.
3. Activate with keyboard navigation.
4. Observe the displayed count.
5. Resize and close the window.

**Exercise:** a model test passes but the button is unwired. Which check detects it? Expected answer: the window workflow, because the model function itself remains correct.

## Record accurately
Keep source revision, build configuration, test name and observed result. Mark graphical checks skipped if no display is available. A skipped check is not a pass.

## Recovery
If CTest reports no tests, inspect the build directory and `BUILD_TESTING` configuration. If a test fails, reproduce its named case and inspect its assertion. If the process crashes before a test runs, preserve that distinction. The purpose of these layers is to locate failures, not to inflate a passing-test total.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-activity/test_activity.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-present-status-without-changing-the-model.md) · [Next lesson](11-follow-the-application-event-loop.md)

