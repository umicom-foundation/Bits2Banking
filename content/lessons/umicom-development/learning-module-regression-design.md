<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-regression-design.md

PURPOSE:
Test a learning module through observable outcomes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test a learning module through observable outcomes

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## Decide what must remain true

A regression test detects a behaviour that changes unexpectedly after an edit. For authoring, important outcomes include refusing an existing output, preserving the old manifest, detecting missing resources and accepting a complete reviewed revision. Checking only that a function was called does not prove these outcomes.

| Situation | Required observation |
|---|---|
| One lesson changes | Old manifest verification fails |
| Candidate is prepared | Revision increases and new bytes verify |
| Candidate already exists | Existing candidate bytes remain unchanged |
| Resource is missing | No candidate is published |
| Output uses a parent-directory path | Operation refuses it |
| Revision reaches its maximum | It never wraps to an older value |

## Read the test structure

1. Open `tests/learning_pack/authoring_fixture.h`. A fixture is a known starting set of data used by a test. This one writes resources into an isolated test directory.
2. Read `test_authoring_cli.c`. It calls the actual command adapter, including argument handling.
3. Find the comparison of original manifest bytes at the end. That comparison protects a promise made to users.
4. Read `test_authoring.c` for binary, empty and changed resources. Binary means arbitrary bytes, which may contain zero values; `strlen` cannot measure such data.

## Qualification commands

After configuring the owning build, build the authoring test targets and run their registered CTest cases. From an Applications checkout:

~~~powershell
cmake --build --preset windows-ucrt64-all-debug --target umicom-learning-pack-authoring-test umicom-learning-pack-authoring-cli-test
ctest --preset windows-ucrt64-all-debug -R "^framework[.]learning_pack[.]authoring[.]" --output-on-failure --no-tests=error
~~~

Expected result is that every selected case passes. This expectation is not evidence of an executed run. Save the actual output, source revision and compiler identity when you run it. If no tests are found, stop and check the configure preset and `BUILD_TESTING` setting.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/learning_pack/test_authoring_cli.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Copy an example into a learner-chosen file](learning-module-copy-example-safely.md) · [Next: Review content, accessibility and publication separately](learning-module-publication-and-limits.md)
