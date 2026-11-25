<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/14-check-complete-rows-in-a-saved-prefix.md

PURPOSE:
Check complete rows in a saved prefix

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check complete rows in a saved prefix

When a test run writes text as it works, a saved copy may end before the run does. The copy is a **prefix**, meaning the beginning of the output captured so far. Start with the outer run's selected total. Lesson 10 uses that total to set aside rows that belong to a smaller run. This exercise adds checks for missing, repeated and unfinished outer results.

## 1. Count the lines that have finished

The Framework fixture supplies the following bytes. The first line ends with LF, a line-feed character. The captured text stops immediately after `Passed` on the second line.

~~~text
1/3 Test #22: outer.done ....Passed 0.01 sec
2/3 Test #23: outer.unterminated ....Passed
~~~

Use 3 as the selected outer total. Underline the complete row and put a mark after the last captured byte. The expected summary has one observed result and one pass. Its `trailingBytes` field measures the unprocessed second line. If a later capture includes the rest of that line and its newline, give the checker the complete saved prefix again.

## 2. Check two kinds of numbers

In `1/3 Test #22`, progress is 1 of 3 and the registered test number, also called its **ordinal**, is 22. The next outer progress number must be 2. The next ordinal can be any different registered number. Filtered tests can finish in an order different from the order in which they were registered.

| Complete outer rows in a fresh practice prefix | Expected check |
| --- | --- |
| Progress `1/3` for test #8 and `2/3` for test #8 | Refuse the repeated registration number. |
| Progress `1/3` for test #7 and `3/3` for test #8 | Refuse the gap in completed progress. |
| A complete result reports a different total | Count it separately. Keep outer progress unchanged. |

Start with a saved summary from the first exercise. Try each refusing prefix on paper. The checker leaves that saved summary in place.

~~~text
READ complete captured lines from the start
COUNT a result with a different total separately
REQUIRE the next progress number on each matching row
REQUIRE each matching row's registered number to be unique
RECORD remaining bytes after the last completed line
PUBLISH the summary after these checks succeed
~~~

The Framework function `UmiDeveloperCtestConsoleSummarize` reports these observations. A prefix with zero complete matching rows returns `UMI_STATUS_NOT_FOUND` and leaves the previous summary intact.

A child run can happen to use the same total and valid-looking numbers. Keep evidence of which process produced the rows. A summary records observed progress from the supplied bytes. To assess a real run, keep the test command, executable identity and final suite result with that summary.

[Course contents](index.md) · [Previous lesson · Match the selector to the test executable](13-match-the-selector-to-the-test-executable.md) · [Read counted results from a running test log](09-read-counted-results-from-a-running-test-log.md) · [Keep the outer test total](10-keep-the-outer-test-total.md) · [Next lesson · Group console checks by what they submit](15-group-console-checks-by-what-they-submit.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/14-check-complete-rows-in-a-saved-prefix.html)
