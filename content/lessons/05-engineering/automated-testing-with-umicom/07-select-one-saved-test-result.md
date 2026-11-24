<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/07-select-one-saved-test-result.md

PURPOSE:
Select one saved test result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Select one saved test result

A **saved test report** records what happened during an earlier run. It can contain several test results. Reading one result helps you investigate a specific check while keeping the overall run in view.

## Start with two fictional results

Copy this sample into a new practice file called <code>sample-tests.xml</code>. XML uses named tags to mark each test. The whole report describes two checks. One passed and one recorded an assertion failure.

~~~xml
<testsuite tests="2" failures="1">
  <testcase name="notes.pass" status="run" time="0"/>
  <testcase name="notes.failure" status="fail" time="0">
    <failure message="The note count differed"/>
  </testcase>
</testsuite>
~~~

## Select a recorded name

1. Open PowerShell in the exercise folder and use the current <code>umicom</code> CLI. Run the first command. It shows the earlier passing test and reports exit code 0. The suite summary still counts two tests and one failure.
2. Run the second command. It shows the saved failure and gives exit code 1. Open the XML and find the assertion message.
3. Try the third command. It gives exit code 2 because the exact name is missing. Names are case-sensitive. Use the spelling in the report and keep quotes around a name that contains spaces.

~~~powershell
umicom test-report sample-tests.xml --test "notes.pass"
$LASTEXITCODE
umicom test-report sample-tests.xml --test "notes.failure"
$LASTEXITCODE
umicom test-report sample-tests.xml --test "Notes.Pass"
$LASTEXITCODE
~~~

Read <code>$LASTEXITCODE</code> immediately after the corresponding command. If the CLI cannot read the file, verify the filename and its directory. Use the command help to check whether your installed version supports <code>--test</code>.

~~~text
READ the complete saved report
KEEP the same suite totals
FIND the exact decoded test name
SHOW the selected earlier result
REPORT its outcome
~~~

This operation reads the report without running its tests. For a failure on an actual project, compare the saved report to the source revision, target platform and environment recorded by that earlier run. Use the suite summary to understand the other checks. An automated testing tool can use the selected result for a narrow decision and retain the whole suite evidence for review.

[Course contents](index.md) · [Previous lesson · Keep the fixture permissions small](06-keep-the-fixture-permissions-small.md) · [Related lesson · Read one test evidence row](04-read-one-evidence-row.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/07-select-one-saved-test-result.html)

[Next lesson · Read a workflow summary](08-read-a-workflow-summary.md)
