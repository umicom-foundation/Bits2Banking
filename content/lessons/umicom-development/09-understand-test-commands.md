# Understand which program a test runs

Continue from [Read build and test evidence](08-read-build-and-test-evidence.md). This source-reading lesson uses the actual Framework automatic-test services.

## Why a test name is not a program

An executable is a file that the operating system can run. A test is a named check. One executable may contain many checks, and a test tool can choose a particular check by passing arguments. In Umicom, CTest stores the relationship between a test name, an executable and those arguments.

Suppose a test called fixture.alpha ran yesterday and passed. Today its declaration still points to the old executable, but its actual command now runs another program. Checking the old executable's contents cannot tell us whether the new program is unchanged. A remembered pass is useful only when we first identify the program that will actually run.

## Read the two records

A registry is a list of declared relationships. The automatic qualification registry has two columns: the test name and its expected executable path. A catalogue is the list discovered from CTest. Its command field is an array: an ordered list whose first item is the executable and whose remaining items are arguments.

These records answer different questions. The registry says what the developer declared. Discovery says what CTest currently plans to execute. A declaration alone does not prove that the two agree.

~~~text
Declared owner       Actual CTest command
      |                       |
      +---- compare identity--+
                  |
           mismatch or unknown
                  |
       keep tests selected for execution

Matching identity -> check remaining inputs and outcomes
                  -> eligible historical pass or execute
~~~

## Follow the real Framework implementation

Open the Framework command catalogue header, then its implementation and regression test using the source links below. The public header describes the contract: accepted inputs, ownership, limits and possible failures. The implementation reuses the strict CTest JSON reader, rather than searching raw text for a filename.

JSON is a structured text format. Quotation marks delimit text, square brackets delimit an array, and braces delimit an object containing named fields. A valid JSON document is not automatically valid CTest data: a command must be an array of strings, identities must not be duplicated, and the version must be supported.

The parser checks the complete document before returning an owned catalogue. Owned means this object has its own allocated storage. The caller can release the original JSON buffer after parsing. When finished, the caller must destroy the catalogue to release its memory.

- [Command catalogue contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/test_platform/ctest_commands.h)
- [Catalogue implementation](https://github.com/umicom-foundation/umicom-framework/blob/main/src/test_platform/ctest_commands.inc)
- [Native regression cases](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/test_reuse/test_command_catalogue.c)
- [Automatic qualification driver](https://github.com/umicom-foundation/umicom-framework/blob/main/cmake/UmicomAutomaticTestsRun.cmake)
- [File ownership regression](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/test_reuse/check_command_owners.cmake)

## Understand the C lookup

The lookup function receives the catalogue, an exact test name and a place to store a pointer to its executable string. A pointer records the location of data in memory. The returned string is borrowed: it belongs to the catalogue, so the caller must not free or modify it and must not use it after destroying the catalogue.

A status value tells the caller whether lookup succeeded. UMI_STATUS_OK means an executable string was found. UMI_STATUS_NOT_FOUND means the identity was missing or had no available command. Neither value says that a test passed. The program has not been executed.

On lookup failure, the output pointer remains unchanged. This makes failure predictable, but the caller must still check the status before using the pointer. An earlier successful value must not be mistaken for the result of a later failed lookup.

This excerpt assumes a successfully parsed catalogue and the standard I/O header. The complete regression source shows construction and destruction.

~~~c
const char *program = NULL;
UmiStatus status = UmiCtestCommandCatalogueFind(catalogue, "alpha", &program);
if (status == UMI_STATUS_OK) {
    /* program is borrowed from catalogue and is not executed here. */
    printf("%s\n", program);
}
~~~

## Compare paths carefully

The driver requires absolute executable paths. An absolute path identifies a location from a filesystem root. A relative path depends on a working directory, which may differ between the build driver and a test. Matching two relative spellings would not establish that both tools refer to the same file.

On Windows the verifier accepts slash and backslash spelling for separators. It does not change all letters to lower case: a Windows directory can enable case-sensitive names. It also does not assume that different aliases identify the same file. A conservative full run is preferable to accepting an unproven cached result.

Matching the executable is only the first gate. The driver must also account for runtime libraries, configuration, environment and previous outcomes. Tests that read a network service, mutable file, device, clock or undeclared plugin need an appropriate contract; matching the program does not make those inputs disappear.

## Why sorted lookup helps

A large project can contain tens of thousands of tests. Searching the entire JSON document again for every registration repeats work. Framework creates one owned catalogue, sorts entries by their names and uses binary search for lookup.

Binary search compares a name with the middle entry of a sorted range. If it comes before that entry, only the earlier half remains relevant; otherwise the later half remains. Repeating this step rapidly narrows the range. The input still needs complete validation, and sorting still costs work. Faster lookup does not justify skipping validation.

## Trace a mismatch without weakening the check

First read the test's add_test declaration and its umicom_test_closed_inputs registration together. Identify the executable in each. Next inspect discovery.json.owners.log in the private automatic-run folder. It records whether the declared bindings were verified or refused.

If a test now runs a wrapper, inspect what the wrapper does. It may introduce another program, environment or input file. Correct the declaration only when the complete input contract is understood; otherwise keep ordinary test execution. Do not edit saved receipts to turn the old result into a current pass.

The real-driver regression changes a private fixture's owner from one executable to another, then requires all its tests to remain selected. The fixture also checks for the specific ownership diagnostic, so an unrelated full-run fallback cannot silently stand in for the intended check.

## Practise the reasoning

1. In the native regression source, find alpha and its escaped Unicode path. Work out what text the JSON reader returns.
2. Find the duplicate-name case. Explain why selecting the first matching entry would be ambiguous.
3. Read the missing-command case. Explain why an empty command cannot qualify a remembered pass.
4. Sketch a test that uses a wrapper. List the extra inputs needed before considering reuse.

<details>
<summary>Check your understanding</summary>
<p>The registered executable is unchanged, but discovery now runs another executable. Can yesterday's pass be reused?</p>
<p><strong>Answer:</strong> No. The previous evidence identifies a different program. Keep the test selected, inspect the declaration and verify actual execution inputs.</p>
</details>

This is a source-reading lesson. Reading a regression does not execute it, and matching a command is not a compiler, runtime or application pass.

[Previous lesson](08-read-build-and-test-evidence.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.

Next: [Close background work safely](10-close-background-work.md).
