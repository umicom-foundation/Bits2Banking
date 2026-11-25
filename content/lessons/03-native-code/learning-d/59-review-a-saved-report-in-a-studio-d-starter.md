<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/59-review-a-saved-report-in-a-studio-d-starter.md

PURPOSE:
Review a saved report in a Studio D starter

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Review a saved report in a Studio D starter

Bring the earlier parts together in one learner-owned `src/main.d`. Keep your paper predictions beside the saved report. The predictions give you something precise to compare with an observed result when the D toolchain is available.

Copy the D blocks from lessons 52 through 58 in order. Keep one import for each symbol. Then add the saved fixture and test block below to the same file.

## Prepare independent inputs

Copy the five saved JSON Lines records from lesson 54 into `Example Run.jsonl` as ASCII with a final newline. Above the test block, type `enum goodReport =` followed by an opening backtick. Paste the first record immediately after the backtick. Put a closing backtick and semicolon on the line after the final record. Use the seven cases to predict what the reader should accept.

| Case | Change from the saved report | Expected review |
| --- | --- | --- |
| Saved success | Use the original report and producer exit 0 | Complete, value 42 |
| Synthetic zero | Change the final value to 0 and keep producer exit 0 | Complete, value 0 |
| Quoted schema | Change the first numeric schema to a string | Refused |
| Missing result | Remove the final row and keep the preceding newline | Refused |
| Extra result | Repeat the final row | Refused |
| Over the byte limit | Supply 4,097 bytes | Refused |
| Producer error | Use the original report with producer exit 1 | Refused |

~~~d
import std.array : replaceFirst;

unittest
{
    struct ReportCase
    {
        string name;
        string input;
        int producerExit;
        bool accepted = false;
        long value;
    }

    // Change one input at a time so each refusal has a clear cause.
    auto rows = frameReport(cast(const(void)[]) goodReport);
    assert(rows.length == 5);
    string missing = join(rows[0 .. $ - 1], "\n").idup ~ "\n";
    char[reportByteLimit + 1] oversized;
    oversized[] = 'x';
    oversized[$ - 1] = '\n';
    // A final LF isolates the first-stage byte-cap refusal from the end check.
    bool byteLimitRejected;
    try
        frameReport(cast(const(void)[]) oversized[]);
    catch (Exception problem)
        byteLimitRejected = problem.msg == "Expected a bounded report ending in a line feed.";
    assert(byteLimitRejected);

    auto cases = [
        ReportCase("saved", goodReport, 0, true, 42),
        ReportCase("zero", replaceFirst(goodReport, `"value":42`, `"value":0`), 0, true, 0),
        ReportCase("quoted schema", replaceFirst(goodReport, `"schema":1`, `"schema":"1"`), 0, false, 0),
        ReportCase("missing result", missing, 0, false, 0),
        ReportCase("extra result", goodReport ~ rows[$ - 1] ~ "\n", 0, false, 0),
        ReportCase("oversized", oversized[].idup, 0, false, 0),
        ReportCase("producer error", goodReport, 1, false, 0),
    ];

    foreach (testCase; cases)
    {
        bool accepted;
        Review review;
        try
        {
            auto lines = frameReport(cast(const(void)[]) testCase.input);
            review = completeReport(decodeReport(lines), testCase.producerExit);
            accepted = true;
        }
        catch (Exception problem)
        {
            // A refused candidate leaves the acceptance flag false.
        }
        assert(accepted == testCase.accepted, testCase.name);
        if (accepted)
        {
            assert(review.value == testCase.value, testCase.name);
            string expected = "return=1 statement=3 steps=4 instructions=10 value="
                ~ to!string(testCase.value);
            assert(formatSummary(review) == expected, testCase.name);
            assert(formatStepDetails(review, 2) == "\nstep 1 statement\nstep 2 statement",
                testCase.name);
        }
    }
}
~~~

## Check the starter, then check the reader

In a fresh Studio **D Console Application** starter with CMake, Ninja, and a supported LDC installation, run these PowerShell commands one at a time. Stop if a command fails.

~~~powershell
Get-Command cmake, ninja, ldc2 -ErrorAction Stop
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug --parallel 2
ctest --preset windows-ucrt64-debug -R '^console\.result$' --output-on-failure --no-tests=error
~~~

The stock check starts its program without arguments and expects `Result: 42`. If your existing starter built its result executable with `-unittest`, the D runtime's default `test-or-main` mode can finish after running the tests and skip `main`. If CTest reports missing application output, check that explanation by building the stock source into a separate executable with an explicit runtime mode.

~~~powershell
ldc2 -g -O0 -unittest -of=starter-control.exe .\src\main.d
.\starter-control.exe --DRT-testmode=run-main
~~~

Look for `Result: 42` and record the direct command separately from the CTest outcome. This check helps locate the missing output because `run-main` lets a passing unit test be followed by the application's entry point. [D runtime test modes](https://dlang.org/phobos/core_runtime.html#runModuleUnitTests)

In a separate learner folder, place the assembled reader and its unit test in `src/main.d`. First build and run the test executable. `test-only` runs the assertions without opening the saved report file because the test cases have their own input strings. Check the exit value immediately and stop on a failure.

~~~powershell
ldc2 -g -O0 -unittest -of=report-tests.exe .\src\main.d
.\report-tests.exe --DRT-testmode=test-only
$LASTEXITCODE
~~~

Then build the reader without the unit test switch. Use it to capture the application's streams and exit separately.

~~~powershell
ldc2 -g -O0 -of=review.exe .\src\main.d
.\review.exe --producer-exit 0 'Example Run.jsonl' 1>stdout.txt 2>stderr.txt
$reviewExit = $LASTEXITCODE
Get-Content -LiteralPath .\stdout.txt
Get-Content -LiteralPath .\stderr.txt
$reviewExit
Get-FileHash -LiteralPath '.\Example Run.jsonl' -Algorithm SHA256
ldc2 --version
~~~

Expect the exact summary from lesson 58 and exit 0. Record the LDC version, the input file's SHA-256, both streams and the observed reader exit. The saved Umicom C producer evidence establishes the sample data. A learner's successful D check would establish a separate observation for the reader and its tested inputs.

[D unit tests](https://dlang.org/spec/unittest.html) · [D console entry point](https://dlang.org/spec/function.html#main) · [D first replacement](https://dlang.org/library/std/array/replace_first.html)

[Course contents](index.md) · [Previous lesson · Send the summary and diagnostics to their own streams](58-send-summary-and-diagnostics-to-their-own-streams.md) · [Related lesson · Describe a contract and run D unit tests](02-contracts-and-unit-tests.md) · [Related lesson · Measure the process temporary volume](../../05-engineering/learning-build-systems/31-measure-the-process-temporary-volume.md) · [Related lesson · Read child and fixture deadlines](../../05-engineering/learning-build-systems/32-read-child-and-fixture-deadlines.md) · [HTML edition](../../../courses/learning-d/lessons/59-review-a-saved-report-in-a-studio-d-starter.html)
