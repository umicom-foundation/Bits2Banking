<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/38-record-layered-trace-evidence.md

PURPOSE:
Record layered trace evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Record layered trace evidence

## Setup recap

Keep the artifacts and notes from the preceding trace lessons. Use a private folder outside product source for execution logs. You need the exact source checkout, selected build directory and command path for each layer; do not combine results from different binaries under one success label.

## Write down the question each check answers

Runtime unit cases ask whether stack state, fault preservation, capacities and fuel follow the API contract. CLI cases additionally check argument handling, source and bytecode equivalence and unchanged input files. Framework cases check presentation state and sized storage. The Kernel guest adds native linking, user-mode execution and process-frame restoration.

These are different claims. Passing the hosted runtime cases does not show that the optional SDK adapter linked, that the guest booted or that a Studio interaction worked. A source review can identify a plausible implementation but does not produce any of those runtime results.

```powershell
ctest --preset windows-ucrt64-debug -R "^umicom[.]c[.](trace[.]|cli-trace$)" --output-on-failure --no-tests=error
```

## Make a useful observation record

For a failure, begin with the narrowest responsible layer. No rows after malformed input usually points to compilation or decoding. A rejected arithmetic row points to runtime checks. An old result shown after a rejected preview points to presentation state. A missing guest selector may indicate an old image. These are hypotheses to confirm, not automatic diagnoses.

1. Record source commit and any working changes, plus the compiler and target.
2. Record the exact command, executable or image path, and exit status.
3. Keep expected and actual observations separate. Include the first differing row on failure.
4. Record skipped and unselected coverage separately from passes.
5. After a source or header change, rebuild and repeat the affected checks before reusing evidence.

## Final exercise

Write a short report for a hypothetical run where all runtime cases passed but the Kernel image was not built. State exactly what is supported: the tested host runtime contract for that source and environment. Leave guest execution, optional Framework integration and GUI behaviour unverified.

Your finished project is a source-backed execution observer for the small arithmetic language. Variables, branches, stepping controls, breakpoints, native register inspection and full C23 semantics require separate designs and coverage. Extending this course does not claim those features already exist.

## Read the source

[umicom-c/tests/test_trace.c](https://github.com/umicom-foundation/umicom-c/blob/main/tests/test_trace.c). Read the matching checkout when qualifying your own build.

## Continue learning

[Course contents](index.md) · [Previous: Qualify a freestanding trace](37-qualify-a-freestanding-trace.md) · [Next lesson](39-recognise-comparison-tokens.md)
