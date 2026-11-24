<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/09-read-counted-results-from-a-running-test-log.md

PURPOSE:
Read counted results from a running test log

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read counted results from a running test log

A test report may still be growing while you read it. CTest prints a
line when it starts a test and a separate line when it records an
outcome. Start by finding the latest complete outcome line.

## Identify the information in a line

In `2/4 Test #7: exercise.paused ....***Timeout 3.00 sec`, CTest
has recorded outcome 2 of 4. The configured test number is 7. These
numbers answer different questions. In the same way, a skipped or timed
out row can increase the observed count without adding a pass.

This small C23 exercise borrows the Framework reader used by the
developer tools. Save it as `count-test-rows.c` in a tutorial
project linked with the Framework developer productivity library.

~~~c
#include "umicom/developer_productivity/diagnostic_parsers/ctest.h"
#include <inttypes.h>
#include <stdio.h>

int main(void)
{
    const char *const lines[] = {
        " 1/4 Test #5: exercise.read .... Passed 0.03 sec",
        " 2/4 Test #7: exercise.paused ....***Timeout 3.00 sec",
        "Start 11: exercise.waiting"
    };
    for (size_t index = 0U; index < sizeof lines / sizeof lines[0]; ++index) {
        UmiDeveloperCtestResultRow row;
        const UmiStatus status = UmiDeveloperCtestResultParse(lines[index], &row);
        if (status == UMI_STATUS_NOT_FOUND) {
            puts("No completed result in this line.");
            continue;
        }
        if (status != UMI_STATUS_OK) return 1;

        /* The counted result and the registered test number serve different needs. */
        const char *label = row.kind == UMI_DEVELOPER_CTEST_PASSED
            ? "passed" : "timed out";
        printf("%" PRIu64 "/%" PRIu64 " #%" PRIu64 " %s\n",
            row.observedResults, row.plannedTests, row.testNumber, label);
    }
    return 0;
}
~~~

With a current GCC on your PowerShell path, point the compiler at the
Framework source checkout containing the reader. Run these commands from
the folder where you saved the example.

~~~powershell
$Framework = Read-Host 'Enter the path to the Umicom Framework checkout'
gcc -std=c23 -I "$Framework/include" count-test-rows.c "$Framework/src/developer_productivity/diagnostic_parsers/ctest.c" -o count-test-rows.exe
if ($LASTEXITCODE -eq 0) { & .\count-test-rows.exe }
~~~

The example supplies three fixed lines with two possible result kinds.
An application that accepts other outcomes can check the full
`UmiDeveloperCtestResultKind` enumeration.

~~~text
1/4 #5 passed
2/4 #7 timed out
No completed result in this line.
~~~

## Use the partial result

1. Count the observed outcomes and write down how many passed. In this
   example, two outcomes are visible and one passed.
2. Keep the latest start line separately. It shows that test number 11
   started, with its result still absent from this capture.
3. Read the final summary and the command exit status after the run
   finishes. For a real project, compare the report with the configured
   target and build before using it as qualification evidence.

The SDK reader expects one complete, bounded line at a time. If a capture
ends in the middle of a line, keep the bytes until the rest arrives.
The parser leaves its output unchanged when a line is unsupported.
An Umicom Studio IDE test panel can update its progress label while the
final test report is still being produced.

[Course contents](index.md) · [Previous lesson · Read a workflow summary](08-read-a-workflow-summary.md) · [Related lesson · Select one saved test result](07-select-one-saved-test-result.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/09-read-counted-results-from-a-running-test-log.html)

[Next lesson · Keep the outer test total](10-keep-the-outer-test-total.md)
