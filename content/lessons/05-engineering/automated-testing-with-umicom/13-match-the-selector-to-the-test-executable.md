<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/13-match-the-selector-to-the-test-executable.md

PURPOSE:
Match the selector to the test executable

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Match the selector to the test executable

A **selector** is a word a test program reads to decide which practice case to run. CTest can register several test names that call the same executable with different selectors. This makes small cases easier to run and report separately.

## 1. Follow the registered command

Imagine a Bank CSV test called `practice.csv.header-quote`. The registration tells CTest to run a program called `csv-issue-check` and give it the selector `header-quote`. The program starts by looking for that word in its list. It builds the practice input and calls the CSV parser after it recognizes the case.

~~~text
START the executable named by the registration
LOOK UP the selector in that executable's case list
IF the case is missing, REPORT a selection failure and stop
BUILD the practice input and call the subject being tested
~~~

The **subject** is the code whose behavior the test intends to check. A selection failure tells us that the executable started and could not choose a case. The subject has yet to receive that practice input.

## 2. Compare four pieces of evidence

In the saved Umicom Bank example, four CSV issue-location selectors were present in the configured registrations. The source and freshly compiled object also contained them. An **object file** holds the translated code from one source file before the linker combines it with other code. The executable recorded for the run was from an earlier build and contained none of the four selectors.

| Evidence to check | In the saved example |
| --- | --- |
| Registered command | Names the test executable and each current selector. |
| Fixture source | Lists the selectors before it constructs a CSV sample. |
| Fresh object file | Contains the four selector names. |
| Executable used in the run | Contains none of those selectors. The selection check fails before CSV processing. |

Draw these four cards. Beside the object card, write “compiled”. Beside the executable card, write “older link output”. Then put the actual failure next to the executable card. The object file cannot tell you what happened inside a different executable.

## 3. Write the conclusion and the missing check

On paper, record that the four tests failed at selection and that the configured tests still need to run with the intended executable. Keep the original failure with the earlier executable's identity. After a successful link, check which executable the registration points to and compare its identity with the built file before rerunning the four cases.

If the new executable selects a case and a CSV check then fails, keep that new result under its own run. It now gives evidence from a later stage. The recorded selector comparison identified the earlier mismatch. The current native rerun is still pending in that record.

[Course contents](index.md) · [Previous lesson · Check the link inputs of a fixture](12-check-the-link-inputs-of-a-fixture.md) · [Next lesson · Check complete rows in a saved prefix](14-check-complete-rows-in-a-saved-prefix.md) · [Recognize stale tests after a failed build](../learning-build-systems/26-recognize-stale-tests-after-a-failed-build.md) · [Select one saved test result](07-select-one-saved-test-result.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/13-match-the-selector-to-the-test-executable.html)
