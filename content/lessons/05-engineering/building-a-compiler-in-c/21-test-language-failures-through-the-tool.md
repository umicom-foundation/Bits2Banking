<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/21-test-language-failures-through-the-tool.md

PURPOSE:
Test language failures through the tool

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test language failures through the tool

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## A failure can be expected

A positive test supplies valid input and expects success. A negative test supplies a specific invalid input and expects rejection. A negative test must not pass merely because an executable is missing.

The starter has four CTest cases. The result case requires `Result: 42`. The syntax case checks malformed source. The division case executes division by zero. The fuel case allows too few interpreter steps. Its CMake driver checks the exit result and requires a diagnostic for rejected cases.

1. Configure and build using `preview`.
2. Run:

```powershell
ctest --preset preview --output-on-failure --no-tests=error
```

3. Read `tests/check_preview.cmake`. Find the command for each case. Arguments are separate list entries, preserving paths containing spaces.
4. Read the timeout. It bounds waiting if a tool hangs; it does not prove all programs terminate.
5. Change the valid result to 41 and rerun the result case. Expect a mismatch. Restore 42 afterwards.

Windows output often uses carriage-return plus newline. Other systems commonly use newline alone. The driver normalizes this line ending before matching. It must not remove arbitrary characters and hide a different result.

## Diagnose a failing check

Run the exact command printed by the test. Confirm the intended executable and source. A launch failure, parser rejection and runtime arithmetic rejection are different problems. Identify which occurred before changing an assertion.

## Extend coverage

Add a parenthesized expression with an independently calculated answer. Then add an overflow case expecting a runtime diagnostic. Store expected values in the test rather than calculating them with the same compiler again.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/developer_project/test_umicom_c_preview.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Check only affected preview inputs](20-check-only-affected-preview-inputs.md) · [Next: Separate editor support from language semantics](22-separate-editor-support-from-language-semantics.md)

[Written course contents](index.md)
