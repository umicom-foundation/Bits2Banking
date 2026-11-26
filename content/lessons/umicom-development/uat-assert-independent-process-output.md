<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/uat-assert-independent-process-output.md

PURPOSE:
Verify a command's data output, diagnostics and exit separately through one UAT fixture.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Assert data output and diagnostics separately

[Previous lesson](uat-compare-typed-query-results.md) · [Next lesson](deployment-models-and-real-providers.md)

![Umicom](../../assets/branding/umicom-wordmark.svg)

[![Umicom icon](../../assets/branding/umicom-icon.svg)](../../assets/branding/umicom.ico)

A process can write data to standard output, send diagnostics to standard error and return an exit code when it finishes. For an import or conversion test, keep these observations separate. A clean data stream does not establish that an expected warning appeared.

## Run four native process checks

Use the Framework source checkout and the same CMake toolchain as the previous lesson. This exercise builds the process fixture without requiring SQLite. CTest supplies the path to the built fixture, which starts its own controlled child. You do not need an external account, device or command from a report.

```powershell
$framework = "C:/umicom/Umicom-Applications/framework"
$build = Join-Path $framework "build/uat-process-workshop"
$env:PATH = "C:/msys64/ucrt64/bin;$env:PATH"
cmake -S "$framework/tests/uat" -B $build -G Ninja
cmake --build $build --target umicom-uat-process-fixture-tests
ctest --test-dir $build -R '^framework[.]uat[.]process_fixture[.]dual-(exact|mismatch|code|raw-stress)$' --output-on-failure --no-tests=error
```

Expect four passes. The test named `dual-mismatch` verifies that the inner assertion rejects the wrong diagnostic bytes. The test named `dual-code` checks a disagreement with the expected exit. The raw stress case reads both channels from one child and checks the large captured streams.

## Express three expectations for one probe

Use `UmiUatProcessProbe` for the trusted program, working directory, counted arguments and expected standard-output bytes. Pair it with `UmiUatProcessExpectedOutcome` for each probe, in the same table order. The outcome supplies the expected exit code and the complete standard-error span.

| Channel | What the expectation covers |
|---------|-----------------------------|
| Standard output | The exact data bytes, including deliberate separators and line endings |
| Standard error | The exact diagnostic bytes, or an empty span when none are expected |
| Process exit | The ordinary exit code expected for this input, from 0 through 125 |

An exit code other than zero can be the expected outcome of a command that refuses invalid input. A failure to launch, a timeout, cancellation or incomplete process cleanup still fails the assertion. Give the fixture an explicit target, session and allowed operation, and leave the workflow plan's inline command fields empty. The trusted fixture owns the program and argument vector.

## Keep useful evidence without printing captured data

The report can name the channel that differed. This allows you to investigate a test in an appropriate private location without moving the captured bytes into a shared report. An empty expectation means the channel should produce zero bytes.

If a mismatch disappears when you merge the two streams, rerun the original test and inspect the separately expected lengths. Check the source of those expectations before changing the fixture. Keep the failed operation and cleanup results separate. [Read the process fixture contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/testing/uat_process_fixture.h) · [Open the native regression source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/uat/test_process_fixture.c)
