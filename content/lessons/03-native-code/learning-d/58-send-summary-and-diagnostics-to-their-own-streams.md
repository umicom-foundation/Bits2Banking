<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/58-send-summary-and-diagnostics-to-their-own-streams.md

PURPOSE:
Send the summary and diagnostics to their own streams

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Send the summary and diagnostics to their own streams

A command-line tool can send a result, an explanation, and an exit status. **Standard output**, or stdout, carries data another program may read. **Standard error**, or stderr, carries messages for the person diagnosing a problem. The **exit status** is the integer returned by `main` to the operating system.

## Prepare

Draw three columns for standard output, standard error and exit status. Use the saved report and the refusal examples below to fill one row for each case.

## Decide what each exit status means

This teaching tool returns 0 after writing its summary, 2 when the arguments are invalid, and 3 when the saved report cannot be read or accepted. If writing stdout fails and stderr is usable, it reports the write error and returns 4. A failed write can leave part of a summary in stdout. The caller checks the status before using that output. An explicit `--help` request writes usage text and returns 0.

Add this entry point and summary function to the reader you built in the earlier exercises.

~~~d
import std.array : join;
import std.conv : to;
import std.file : read;
import std.stdio : stderr, stdout;

enum reviewUsage =
    "Usage: review [--details] [--limit 1..32] --producer-exit 0..255 REPORT";

string formatSummary(Review review)
{
    // Build the whole line before writing anything to stdout.
    auto fields = summaryKinds(review);
    fields ~= "steps=" ~ to!string(review.steps.length);
    fields ~= "instructions=" ~ to!string(review.instructions);
    fields ~= "value=" ~ to!string(review.value);
    return join(fields, " ").idup;
}

string formatStepDetails(Review review, uint limit)
{
    // Apply the display limit only to the already verified sequence.
    string details;
    size_t shown = 0;
    foreach (step; review.steps)
    {
        if (shown == limit)
            break;
        details ~= "\nstep " ~ to!string(step.number) ~ " " ~ step.stepKind;
        ++shown;
    }
    return details;
}

int main(string[] args)
{
    Options options;
    try
        options = readOptions(args);
    catch (Exception problem)
    {
        stderr.writeln(problem.msg);
        stderr.writeln(reviewUsage);
        return 2;
    }

    string line = reviewUsage;
    if (!options.helpWanted)
    {
        try
        {
            // One extra byte lets the framer detect an oversized report.
            auto bytes = read(options.path, reportByteLimit + 1);
            auto records = decodeReport(frameReport(bytes));
            auto review = completeReport(records, options.producerExit);
            line = formatSummary(review);
            if (options.showDetails)
                line ~= formatStepDetails(review, options.detailLimit);
        }
        catch (Exception problem)
        {
            stderr.writeln("Report refused: ", problem.msg);
            return 3;
        }
    }

    try
    {
        stdout.writeln(line);
        stdout.flush();
    }
    catch (Exception problem)
    {
        stderr.writeln("Cannot write summary: ", problem.msg);
        return 4;
    }
    return 0;
}
~~~

The summary uses every verified step. With `--details --limit 2`, its summary stays the same and the next two lines are `step 1 statement` and `step 2 statement`. The reader checks all five records before it shows either detail line.

## Write three evidence rows

Trace these inputs on paper. The saved successful report contains three statement steps, one return step, ten instructions, and the value 42. The producer status is supplied separately.

| Input | stdout | stderr | Reader exit |
| --- | --- | --- | --- |
| Complete report and producer exit 0 | `return=1 statement=3 steps=4 instructions=10 value=42` | Empty | 0 |
| Required report path omitted | Empty | Option error and usage | 2 |
| Final result row missing, with every remaining row still framed | Empty | Report refusal | 3 |

Now trace a valid synthetic report whose last value is 0. Its summary ends in `value=0` and its reader exit is 0. In a saved test record, write down the producer exit, the reader exit, and the reported value in separate fields. They answer three different questions.

[D console entry point](https://dlang.org/spec/function.html#main) · [D standard streams and flushing](https://dlang.org/phobos/std_stdio.html) · [D bounded file read](https://dlang.org/library/std/file/read.html) · [D array join](https://dlang.org/library/std/array/join.html)

[Course contents](index.md) · [Previous lesson · Make grouped step counts reproducible](57-make-grouped-step-counts-reproducible.md) · [Next lesson · Review a saved report in a Studio D starter](59-review-a-saved-report-in-a-studio-d-starter.md) · [Related lesson · Keep startup evidence with its test attempt](../../05-engineering/automated-testing-with-umicom/11-keep-startup-evidence-with-its-test-attempt.md) · [HTML edition](../../../courses/learning-d/lessons/58-send-summary-and-diagnostics-to-their-own-streams.html)
