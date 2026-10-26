# Test what you promised and understand failures

Compare expected and observed behaviour without mistaking a missing run for a pass.

**Before you begin:** Read [Give reusable work a clear contract](06-functions-with-a-contract.md), or return to it for a refresher.

## Start with an expectation

A test is a repeatable check of a stated expectation. For the greeting program, the expectation includes successful completion, exactly one greeting line and no unexpected diagnostic text. For the count function, the expectation includes valid boundary results and rejection of invalid values.

Write expectations before observing a run when possible. If you change expected output merely to match whatever a broken program prints, the test stops protecting the intended behaviour. A failed check can mean the implementation is wrong, the expectation is wrong or the environment is unsuitable; investigate rather than guessing.

## There are two kinds of checks here

The lab's output checks launch each built demonstration and compare its standard output with a small expected text file. They also check its completion result and standard error. On Windows the line ending can be carriage-return plus newline; on other environments it is commonly newline. The checker normalises only that line-ending spelling.

The contract check calls BtbRemainingCount directly with a table of inputs and expected results. It includes zero, the maximum permitted total, all activities completed, values just outside the limits and extreme int values. This check tests the function independently of how the demonstration formats a message.

## Read one table row

In test_counts.c the row {5, 2, 3} means total five, completed two, expected remaining three. {5, 6, -1} means the function must reject completed six when only five activities exist. Braces group values; commas separate them.

The table is an array, an ordered collection whose entries have positions called indices. Its loop visits each row within the table's size. You do not need to write arrays yet to read a row. The linked borrowed-memory lesson later explains indices, bounds and how data is represented in memory.

## Build before testing

CTest is CMake's test runner. It runs registered checks; it does not automatically repair or compile their programs. Build the lab first. If a program cannot be found, that is a missing execution prerequisite, not a passed behavioural test.

The README gives the test command with --output-on-failure to display a failed check's details and --no-tests=error to reject an unexpectedly empty test selection. The command's final result matters as well as the displayed percentage. A warning, a skip and a failure are different observations; record them separately.

## Use the first useful diagnostic

A compiler error means the source could not be translated as requested. A linker error means the required compiled pieces could not be combined. A runtime failure happens after launching a program. A failed test comparison means the observed behaviour did not meet that check's expectation.

For a mismatch, record the case number, arguments, expected result and actual result. For a build problem, retain the first relevant compiler or linker diagnostic and the exact command. A long list of later failures may share one earlier cause. Fixing that cause still requires a fresh run before saying the failures are resolved.

## Keep claims as small as the evidence

The authored tests are intended checks, not evidence of execution by themselves. A passing run of this lab establishes only its checked behaviours in the environment used. It does not prove every future input is safe or qualify Umicom OS, Framework or Kernel.

When you change a rule intentionally, update its explanation and tests together after reviewing the consequences. When you fix a defect, keep a test that would expose the original mistake. That is a regression test: it helps detect the same behaviour returning later.

## Try it step by step

1. Choose one accepted and one rejected table row and explain each expectation.
2. List three separate observations: program completion result, stdout and stderr.
3. Predict what should happen if a built test executable is absent.
4. If using the practical route, run the README's checks and record actual results without replacing them with predictions.

## Check your understanding

A test was skipped because its required program was unavailable. Is that evidence the behaviour passed?

**Explanation:** No. The behaviour was not checked by that run. Record the missing prerequisite and skipped coverage, prepare the required program, then run the check before claiming a pass.

## Before you continue

You can distinguish build errors, behaviour mismatches, skips and executed passes.

[Course contents](index.md) · [Words explained](../../courses/c-from-the-beginning/glossary.html) · [Practical lab guide](../../courses/c-from-the-beginning/practical-guide.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Give reusable work a clear contract](06-functions-with-a-contract.md).

**Next:** [Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
