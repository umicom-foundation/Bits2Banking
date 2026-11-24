<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/08-read-a-workflow-summary.md

PURPOSE:
Read a workflow summary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a workflow summary

A test run can produce a long report with one row for each check. For a
status meeting, start with its totals. For diagnosis, open the relevant row
of the detailed report. Both views can describe the same run.

## Read a finished workflow

A Framework application can ask for a compact JSON summary from a report
it already owns. JSON is a text format that names each value. A reader can
look up a name such as `attempted` without counting the detailed rows.

~~~c
#include "umicom/testing/uat_workflow.h"

/* The caller owns the finished report and lends it for this read. */
UmiStatus ReadWorkflowTotals(const UmiUatReport *report, char *buffer,
    size_t capacity)
{
    return UmiUatReportSummaryJson(report, buffer, capacity);
}
~~~

1. In an existing Framework application, borrow a finished workflow
   report before the application releases it. Supply a separate writable
   buffer. Include room for the terminating zero byte after the JSON text.
2. Check the returned status before parsing or displaying the buffer.
   `UMI_STATUS_OK` says the text was serialized successfully. Read the
   JSON field `accepted` to tell whether the workflow passed.
3. If the buffer is too small, supply more room and try the same read again.
   A writable buffer with positive capacity is cleared on failure. A retry
   views the same report and starts no new test.

## Explain the totals

Here is one synthetic report with a cancellation. The counts belong to the
rows of the workflow. Each row represents a planned step.

~~~json
{"schema":1,"product":"Umicom Automated Testing","kind":"uat-summary","accepted":false,"cancellation_requested":true,"planned":64,"attempted":59,"passed":41,"failed":11,"skipped":7,"not_run":5,"cleanup_failed":2}
~~~

1. Add the 59 attempted and 5 unrun rows to get the 64 planned rows in
   this example. Inspect the detailed report to learn why a specific row
   was skipped or left unrun.
2. Within the attempted rows, add the 41 passes, 11 failures, and 7 skips.
   The 2 failed cleanup rows are included in the 11 failures.
3. Read `accepted`. A cancelled workflow can still produce a complete
   report with useful evidence, and cleanup can report its own failures.
4. In your copy of the example, make a separate two-row passing report.
   Set planned, attempted, and passed to 2. Set the other counts to zero,
   set accepted to true, and set cancellation requested to false. Read
   each number back before comparing it with the first example.

The aggregate includes acceptance, cancellation and counts. Keep target
names, individual steps and adapter output in the separately reviewed detail
record. The compact report cannot identify which row failed. Use the detailed
workflow report for that question, or select a saved JUnit row using the
previous lesson if your evidence was exported in that format.

[Course contents](index.md) · [Previous lesson · Select one saved test result](07-select-one-saved-test-result.md) · [Related lesson · Read one test evidence row](04-read-one-evidence-row.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/08-read-a-workflow-summary.html)

[Next lesson · Read counted results from a running test log](09-read-counted-results-from-a-running-test-log.md)
