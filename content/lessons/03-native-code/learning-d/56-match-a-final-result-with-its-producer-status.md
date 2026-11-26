<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/56-match-a-final-result-with-its-producer-status.md

PURPOSE:
Match a final result with its producer status

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Match a final result with its producer status

The file contains typed records. To accept a completed report, check their order, the final result, and the producer's recorded exit status. An exit status belongs to the process that wrote the report. The value in the last record belongs to the program that process interpreted.

## Prepare

Use the stored sample from the preceding report exercise or copy the sequence and result into a small table. Give the producer exit status its own cell so you can change it without changing a record.

## Check the whole sequence

This reader accepts 1 to 31 step records followed by one result, for up to 32 records in all. A valid step has the next sequence number, also called its ordinal, starting at 1. It has `ok` set to true. The reader checks that the final count equals the sum of the step counts. The limit of 1,000,000 instructions is a rule for this exercise.

~~~d
struct Review
{
    ReportRecord[] steps;
    long value;
    long instructions;
}

Review completeReport(ReportRecord[] records, int producerExit)
{
    // The recorded process status and the stored result both matter.
    if (producerExit != 0)
        throw new Exception("Producer exit must be zero");
    if (records.length < 2 || records.length > 32)
        throw new Exception("Expected 2 to 32 records");

    const result = records[$ - 1];
    if (result.event != "result")
        throw new Exception("The final record must be a result");

    // Keep the final result outside the step checks.
    auto steps = records[0 .. $ - 1];
    enum maxInstructions = 1_000_000L;
    long total = 0;
    foreach (offset, step; steps)
    {
        if (step.event != "step" || !step.ok
            || step.number != cast(long) offset + 1)
            throw new Exception("Expected the next successful step");

        // Compare against the remaining allowance before adding.
        if (step.instructions < 0 || step.instructions > maxInstructions - total)
            throw new Exception("Step instructions exceed the report bound");
        total += step.instructions;
    }
    if (result.instructions != total)
        throw new Exception("Result instruction count differs from the steps");

    // Give the accepted review its own array of step records.
    return Review(steps.dup, result.value, total);
}
~~~

In a D slice, `$` means the array length. `records[0 .. $ - 1]` starts at position 0 and stops before the last record. With five records, it contains positions 0 through 3. [D array slices and properties](https://dlang.org/spec/arrays.html) · [D statements](https://dlang.org/spec/statement.html)

## Predict acceptance

The saved Umicom C example has step counts 2, 2, 4 and 2. The sum is 10. With a final result of value 42 and count 10, and a recorded producer exit of 0, the expected review has four steps.

| Practice change | Expected decision |
| --- | --- |
| Remove the final result or append a step after it | Refuse because the last record is a step |
| Add a second result to the end | Refuse when the first result appears among the steps |
| Set the third step's `ok` to false | Refuse the failed step |
| Change the final count to 9 | Refuse the count mismatch |
| Record producer exit 1 | Refuse the completed review |
| Use a separate synthetic success with returned value 0 and exit 0 | Accept if the sequence and counts agree |

[Course contents](index.md) · [Previous lesson · Keep the previous preview when a new record fails](55-keep-the-previous-preview-when-a-record-fails.md) · [Next lesson · Make grouped step counts reproducible](57-make-grouped-step-counts-reproducible.md) · [Related lesson · Watch one integer slot](../../05-engineering/building-a-compiler-in-c/114-watch-one-integer-slot.md) · [Related lesson · Read the instruction budget at a pause](../../05-engineering/building-a-compiler-in-c/116-read-the-instruction-budget-at-a-pause.md) · [HTML edition](../../../courses/learning-d/lessons/56-match-a-final-result-with-its-producer-status.html)
