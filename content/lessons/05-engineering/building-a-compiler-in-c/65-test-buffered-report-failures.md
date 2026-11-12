<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/65-test-buffered-report-failures.md

PURPOSE:
Test buffered report failures

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test buffered report failures

A command can compute the right answer and still fail to deliver it. This lesson tests the Umicom C comparison command with an output stream that refuses writes. You will follow the actual hosted entry point, distinguish buffered success from delivered output, and preserve the command's three exit meanings.

## Identify the last fallible operation

The compare-operations command compiles two source inputs and compares their validated instructions. It prints a short report and returns 0 for matching operations or 1 for different operations. Invalid input or an I/O failure returns 2.

A successful printf can mean that bytes reached a C library buffer. If the command returns its semantic result before that buffer is written, a later output failure can escape its decision. Merely asking ferror does not force pending output to leave the buffer.

Read the final reporting code in tools/main.c:

~~~c
if (fflush(stdout) != 0 || ferror(stdout)) return 2;
return equal ? 0 : 1;
~~~

The explicitly retained predecessor checked ferror alone. The new flush keeps report delivery inside the command's failure boundary. It does not make comparison equivalent to execution, prove disk durability, or define general C program equivalence.

## Inject a real descriptor refusal

Open tests/test_cli_report_failure.c. It compiles the actual CLI implementation with its main function renamed, then invokes that entry with compare-operations arguments. The comparison and report logic are not copied into the test.

The test opens an existing source file for reading and duplicates that read-only descriptor onto stdout. Windows uses _fileno and _dup2; the POSIX branch uses fileno and dup2. This small host boundary is C code. No compiler or runtime product logic depends on those platform calls.

Before invoking the command, the fixture requests a 4096-byte fully buffered stream. The report is small enough to remain buffered until the command flushes it. The operating system then refuses the write because the installed descriptor is read-only. This exercises an actual stdio failure instead of substituting a fake ferror return.

The fixture closes stdout while the denied descriptor remains installed. Restoring a writable descriptor first could cause cleanup to publish buffered report bytes through the wrong destination. The buffer also remains alive until the stream is closed.

## Require both positive and negative controls

From an Umicom C checkout configured with its tools and tests enabled:

~~~powershell
cmake -S . -B build/report-check -G Ninja
cmake --build build/report-check
ctest --test-dir build/report-check -R '^umicom[.]c[.]report[.]' --output-on-failure --no-tests=error
~~~

The four registered cases cover same/control, same/deny, different/control and different/deny. Control cases must preserve the semantic result, 0 or 1. Both denied cases must return 2 and set the stream error indicator. Every case compares input bytes before and after the call.

CTest reports the fixture's own result: zero means it observed the expected CLI result. Do not confuse a passing different/control fixture with a CLI comparison returning zero; the fixture expects the CLI to return one there.

## Demonstrate that the test detects the omission

In a disposable teaching copy, keep the CLI implementation identical except for replacing the flush condition with the retained ferror-only predecessor. Build the fixture against that copy. The control cases should still pass. The denied cases should fail because the short report can stay buffered until after the semantic result is chosen.

Keep that experiment separate from the working implementation and retain its exact source identity. Do not weaken the expected result from 2 to 0 just to obtain a passing test. Restore the reviewed implementation before continuing development.

## Interpret evidence narrowly

This fixture exercises the actual CLI C entry and the host C library's descriptor failure path. It does not launch the installed executable, test Windows shell pipelines, emulate a disk becoming full, or guarantee every platform's descriptor semantics. The normal CLI subprocess tests cover command invocation separately. Run the POSIX branch on a supported POSIX host before claiming it passed there.

A full suite run adds confidence that the new test registration and input-identity record remain consistent with the other compiler/runtime tests. Source review alone cannot establish that the injected error occurs at the expected point.

## Practice

Explain why fflush belongs before the semantic return, why ferror alone is insufficient for buffered output, and why fclose must happen while the test's buffer still exists. Then identify another command that reports a computed result through stdout. Inspect its output contract and existing tests before proposing a shared solution; do not assume every command already implements this guarantee.

[Course contents](index.md) · [Previous lesson](64-handle-comparison-exits-without-hiding-errors.md) · [Next lesson](66-bind-local-names-to-slots.md)
