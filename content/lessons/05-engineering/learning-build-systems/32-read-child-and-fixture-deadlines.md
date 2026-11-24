<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/32-read-child-and-fixture-deadlines.md

PURPOSE:
Read child and fixture deadlines

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read child and fixture deadlines

One build test can launch many smaller commands. The test runner can keep time both for each command and for the whole group. In this lesson you will decide which clock applies to three saved Umicom C observations and then draw a small timeline.

## 1. Name the two clocks

A **child process** is a command started by another program. The Umicom C interpreter console fixture starts several commands to test the same tool in different ways. In the fixture script, `execute_process(... TIMEOUT 10)` gives an individual invocation ten seconds. The **fixture** is the full test script with its setup, child commands and assertions. The CTest `TIMEOUT` property gives that registered test its overall limit.

| Clock | What contributes to it | What its refusal tells you |
| --- | --- | --- |
| Child deadline | Elapsed time for one invocation | That invocation did not finish before its limit |
| Whole-fixture deadline | The full script, including child launches, setup and checks | The registered test reached its overall bound |

Consider a paper fixture with eight child commands that take seven seconds each and ten further seconds of setup and checking. Each child fits its own ten-second limit. Together the work takes 66 seconds, so the group cannot finish under a 60-second overall limit. If one child alone needs 11 seconds, it can still fail its own bound even when the whole fixture has plenty of time.

## 2. Read the saved Windows observations

These are observations of the named console fixture, rather than timings for every Umicom C test.

| Observation | What the saved evidence says |
| --- | --- |
| Earlier registered run | The fixture was registered with a 60-second whole-test limit. CTest marked it `Timeout`. |
| Direct control | The same identified script and executable finished successfully in 66.01 seconds when the outer CTest deadline was absent. Its script still supervised each child. |
| Later selected registered run | A Windows-only 120-second whole-test limit was registered for that test. Its result row reported a pass in 54.34 seconds. All 47 selected tests passed. |

The 66.01-second direct control was longer than the earlier 60-second allowance. The later registered pass used the 120-second Windows bound. The saved result times describe individual runs, which can experience different process startup and scheduling delays. The later result gives no measurement of what caused each delay. The ordinary registration still gives 60 seconds on other platforms, and the existing ten-second child bounds remain in the script.

## 3. Decide what to preserve after a timeout

Copy the following fields onto paper for a build test in Umicom Studio IDE.

~~~text
REGISTERED TEST NAME:
WHOLE-FIXTURE LIMIT:
CHILD INVOCATION LIMIT:
LAST OBSERVED CASE OR RESULT:
SCRIPT AND EXECUTABLE IDENTITIES:
LATER CONTROL OR RERUN:
~~~

Use the earlier registered observation to fill in the first part. Enter the 66.01-second control and 54.34-second selected result as separate rows. A direct control tells you whether the script and its checks can finish in that setting. The registered run supplies the result that includes the test runner’s own limit. Keep both with their source, executable and environment so a colleague can review the sequence.

Instruction fuel is a third number if the tool runs a virtual machine. It counts operations inside the interpreter. A host timeout describes elapsed seconds in the surrounding command or test. Changing one of the time limits leaves the interpreter’s fuel assertions in place.

[Course contents](index.md) · [Previous lesson · Measure the process temporary volume](31-measure-the-process-temporary-volume.md) · [Related lesson · Read a Ninja progress record](28-read-a-ninja-progress-record.md) · [Related lesson · Separate instruction fuel from wall-clock time](../building-a-compiler-in-c/59-separate-instruction-fuel-from-wall-clock-time.md) · [Related lesson · Read the instruction budget at a pause](../building-a-compiler-in-c/116-read-the-instruction-budget-at-a-pause.md) · [HTML edition](../../../courses/learning-build-systems/lessons/32-read-child-and-fixture-deadlines.html)
