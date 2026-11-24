<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/04-read-one-evidence-row.md

PURPOSE:
Read one test evidence row

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read one test evidence row

A test result describes what one observed run reported. A summary counts the rows reported by a particular file. Compare the summary and the detailed rows before treating the total as pass evidence.

## Compare a complete record and a refusal

Suppose a saved report describes two tests. One passes and one fails.

~~~xml
<testsuite tests="2" failures="1" disabled="0" skipped="0">
  <testcase name="positive" status="run" />
  <testcase name="negative" status="run"><failure /></testcase>
</testsuite>
~~~

Each row carries its own evidence. The word `run` describes an attempted run in this report dialect. The `failure` element supplies the failed outcome. A skipped case remains separate from passed and failed cases.

A saved report can also claim an error in its summary without carrying one of the error records that the selected parser understands. Preserve that file for review. A refusal means the parser cannot establish a valid set of outcomes from it.

~~~text
COUNT the admitted rows
COUNT failures and skips in those rows
COMPARE the known summary fields to the recorded rows
IF the report claims unsupported results THEN report incomplete evidence
OTHERWISE publish the qualified counts
~~~

## Keep source, runner and scope with the count

1. Record the selected test name and product build revision.
2. Record the host or model that actually ran the test.
3. Keep a path to the produced result data and the original status.
4. Retain skipped and unexecuted work in separate rows. A command that was never launched cannot supply a passing outcome.

Umicom’s passive CTest report reader is suitable for checking the saved data format. A fixture that parses ordinary sample text can run without a GUI, device or external process under test. Use a later target-specific run to learn what the actual application did.

[Course contents](index.md) · [Previous lesson · Check a workflow and its cleanup](03-check-a-workflow-and-cleanup.md) · [Next lesson · Qualify each platform separately](05-qualify-each-platform-separately.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/04-read-one-evidence-row.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)
