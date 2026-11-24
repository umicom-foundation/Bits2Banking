<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/10-keep-the-outer-test-total.md

PURPOSE:
Keep the outer test total

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the outer test total

Imagine a test run that checks three small practice files. One of its tests runs two smaller tests and prints their output. The larger run is the **outer run**. The smaller run is a **nested run**. Both can write lines that look like completed results.

## Write down the outer total first

An **outer total** is the number of tests selected for the outer run. Write it down from the run plan or a matching test listing before you count results. If the test selection uses a filter, use the total for that same selection. Our practice run selects three outer tests.

Read this invented capture one line at a time. The two `nested` names belong to the smaller run. All the test names and timings are fictional.

~~~text
 1/3 Test #5: practice.read .... Passed 0.03 sec
 1/2 Test #1: nested.open .... Passed 0.01 sec
 2/2 Test #2: nested.close .... Passed 0.01 sec
 2/3 Test #9: practice.save ....***Skipped 0.02 sec
 Start 17: practice.waiting
~~~

A quick count of the four outcome lines makes a three-test run look larger than it is. Compare the numbers after the slash. The two `/2` lines report the smaller run’s total. The `/3` lines are the two recorded outcomes for the outer run in this example.

## Read the progress and the test number separately

In `2/3 Test #9`, 2 is the position of this outcome in the reported progress and 3 is the reported total for that run. The registered test number is 9. A filtered run can have only three selected tests while one of those tests keeps the number 9 from the larger registered set. The parser calls these fields `observedResults`, `plannedTests` and `testNumber`.

The outer run has two observed outcomes. One passed and one was skipped. The start line for test number 17 records a start. Its outcome is still unseen in this capture. Keep the start, the outcome counts and the final suite result as separate facts.

~~~text
SET expected outer total TO 3 from the run plan
FOR each complete captured line
    READ the result row if there is one
    IF the row reports a different total, set it aside
    IF the row belongs to the outer run, count its outcome once
KEEP starts and partial lines separate
WAIT for the final report and exit status before claiming completion
~~~

Try using 2 as the expected total on paper. You would count the two child outcomes. That is why the expected value comes from the outer plan. A nested run can also have the same total as the outer one. For a real capture, use the runner’s known output source or separate the two streams. Keep rows of uncertain origin separate until you can identify them.

## Apply the rule with the existing C23 reader

This example uses the public Framework reader from lesson 9. Its input is the same five fixed lines. The reader supplies the denominator and the outcome. The example compares the denominator with the explicit exercise total before counting the known outer outcomes. The fixture has one line per outcome.

~~~c
#include "umicom/developer_productivity/diagnostic_parsers/ctest.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    const uint64_t expected_outer = UINT64_C(3);
    const char *const lines[] = {
        " 1/3 Test #5: practice.read .... Passed 0.03 sec",
        " 1/2 Test #1: nested.open .... Passed 0.01 sec",
        " 2/2 Test #2: nested.close .... Passed 0.01 sec",
        " 2/3 Test #9: practice.save ....***Skipped 0.02 sec",
        " Start 17: practice.waiting"
    };
    uint64_t observed = 0U;
    uint64_t passed = 0U;
    uint64_t skipped = 0U;
    uint64_t other_totals = 0U;

    /* Visit every fixed input line once, including the separate start line. */
    for (size_t index = 0U; index < sizeof lines / sizeof lines[0]; ++index) {
        UmiDeveloperCtestResultRow row;
        const UmiStatus status = UmiDeveloperCtestResultParse(lines[index], &row);
        if (status == UMI_STATUS_NOT_FOUND) continue;
        if (status != UMI_STATUS_OK) return 1;

        /* The known outer selection fixes the denominator for this fixture. */
        if (row.plannedTests != expected_outer) {
            ++other_totals;
            continue;
        }
        ++observed;
        if (row.kind == UMI_DEVELOPER_CTEST_PASSED) ++passed;
        if (row.kind == UMI_DEVELOPER_CTEST_SKIPPED) ++skipped;
    }

    printf("Outer outcomes: %" PRIu64 "/%" PRIu64 "\n", observed, expected_outer);
    printf("Passed: %" PRIu64 "; skipped: %" PRIu64 "\n", passed, skipped);
    printf("Rows with another total: %" PRIu64 "\n", other_totals);
    return 0;
}
~~~

If you already have the previous lesson’s C23 project, paste this into a separate practice source file and follow the same compile steps with that filename. This program reads fixed text and prints the expected summary below. It starts no test suite. You can trace the counters by hand as well.

~~~text
Outer outcomes: 2/3
Passed: 1; skipped: 1
Rows with another total: 2
~~~

A Studio test view can display a partial count while the run continues. Keep the selected outer total, recorded outcomes and most recent start visible. Check the final report and the command exit status when the run completes, then decide whether the test evidence supports the intended result.

[CTest command reference](https://cmake.org/cmake/help/latest/manual/ctest.1.html)

[Course contents](index.md) · [Previous lesson · Read counted results from a running test log](09-read-counted-results-from-a-running-test-log.md) · [Related lesson · Read a workflow summary](08-read-a-workflow-summary.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/10-keep-the-outer-test-total.html)
