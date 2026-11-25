<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/15-group-console-checks-by-what-they-submit.md

PURPOSE:
Group console checks by what they submit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Group console checks by what they submit

A **test fixture** prepares an input, runs a program, and compares what happened with what you expected. The Umicom C script console accepts individual lines or a whole block. A single file lets us see why each mode deserves its own test result.

## 1. Predict two results from one file

Save the following three lines in a plain text file named `boxes.ucs`. A **physical line** is a row of text ending at a line break or at the end of the file. A **block** is all the text submitted as one unit.

~~~c
int boxes = 4;
boxes += 3;
return boxes;
~~~

`int` makes a place for a whole number, `+= 3` adds three to the saved number, and `return boxes` gives back the result. Start from an empty session each time. Predict the output on paper, or run these commands with the hosted Umicom C tool from the folder holding the file. Run one command at a time.

~~~text
umicom-c script boxes.ucs
umicom-c script --block boxes.ucs
~~~

| Command mode | Expected ordinary output, in order | Expected error output | Expected exit code |
| --- | --- | --- | --- |
| Lines, one at a time | `ok`, `ok`, `7`, each on its own line | Empty | `0` |
| One block | `7` on one line | Empty | `0` |

The line case checks each acknowledgement. The block case checks the single result of the submission. In both cases the fixture can compare the output bytes, including the final line break. The **exit code** is the number the tool gives the shell when it finishes. Here `0` means the command succeeded.

## 2. Keep the assertions when splitting a fixture

Make two test cards on paper. Give each card its own attempt and working folder so it cannot pick up a file left by the other. Write the command, expected ordinary output, expected error output, and exit code on each card.

~~~text
FOR each card in a fresh work folder
    RUN the command with that card's input
    CHECK the exit code and both outputs against that card
    RECORD the result with that card's test name
~~~

Copy the line card's expected output onto the block card. Predict the test results before you check the table. The line card passes. The block command can still exit with `0`, but its fixture fails the output comparison. Restore the one-line expectation and both cards agree with the table. The same idea applies to a refused input. Keep its expected error text and nonzero exit code when you move its check to another fixture.

## 3. Read the Umicom C evidence

The earlier `umicom.c.script.console` registration grouped 15 line checks and 9 block checks under one 60-second CTest deadline. Two runs reported a timeout for that registration, at 61.30 and 65.27 seconds. A timeout shows where the runner stopped waiting. In the saved output, look for completed checks. Record an unknown outcome for any check with no result.

The split gives `umicom.c.script.console` the line checks and `umicom.c.script.console-block` the block checks. They share the fixture script and use separate folders for the files they create. Each has a 60-second CTest deadline. The input, output and exit assertions travel with their groups. Direct fixture runs completed the line group in 59.811 seconds and the block group in 35.592 seconds, both with exit code `0`. The line group was close to its limit. Use those figures as observations from those runs and record the two registered CTest results separately. [CTest `TIMEOUT` property](https://cmake.org/cmake/help/latest/prop_test/TIMEOUT.html)

A later Release run selected the two registered CTest cases. Both passed. The line case took 31.12 seconds, the block case took 15.49 seconds, and CTest reported 46.64 seconds of total elapsed time. Keep the measured time and the result with each test name and configuration.

If you already have an Umicom C build configured with both registrations, open PowerShell or a Unix shell. Replace `path-to-build` with its build folder and keep the quotes. List the two names first, then run them and keep both result rows. If a name is missing, check that you selected a build generated with the split registrations. If a test stops early, check its own printed failure and deadline. [CTest test selection](https://cmake.org/cmake/help/latest/manual/ctest.1.html#run-tests)

~~~text
ctest --test-dir "path-to-build" -N -R '^umicom[.]c[.]script[.]console(-block)?$'
ctest --test-dir "path-to-build" -R '^umicom[.]c[.]script[.]console(-block)?$' --output-on-failure --no-tests=error
~~~

[Course contents](index.md) · [Previous lesson · Check complete rows in a saved prefix](14-check-complete-rows-in-a-saved-prefix.md) · [Read child and fixture deadlines](../learning-build-systems/32-read-child-and-fixture-deadlines.md) · [Keep the last accepted script value](../building-a-compiler-in-c/121-keep-the-last-accepted-script-value.md) · [Next lesson · Check a shorter Windows build path](16-check-a-shorter-windows-build-path.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/15-group-console-checks-by-what-they-submit.html)
