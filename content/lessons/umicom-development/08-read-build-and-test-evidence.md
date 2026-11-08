# Read build and test evidence

## A result needs an identity

A useful result tells you what ran, which source produced it, which tools and configuration were used, and what happened. A green result from an older executable does not establish that today's source works. A failure from an older source tree does not prove that a newly authored fix failed.

| Observation | What it means | What it does not mean |
| --- | --- | --- |
| Configure succeeded | The build description was generated. | Every source file compiled. |
| Build succeeded | The requested outputs were produced. | Every runtime workflow works. |
| Test passed | That test's executed checks passed. | Unexecuted or skipped checks passed too. |
| Test skipped | The check did not provide a pass for that case. | The feature is qualified on this host. |
| Test not run | The test could not be executed as requested. | A test assertion passed or failed. |

## Capture a small, useful record

1. Use a log folder outside the public source repositories for local execution records. Give each run a distinct name so a later attempt does not replace the earlier evidence.
2. Record the source revision and any local changes, the preset, tool versions, and the exact command. Do not put credentials or private account information into logs.
3. Run configuration before building when needed. Check each command's outcome before starting the next stage.
4. Read the first concrete diagnostic and the nearby context. The final message 'build failed' identifies the outcome, not necessarily its cause.
5. Keep the original failure and the later rerun. Record a proposed fix as awaiting validation until the rerun identifies the actual fixed source and environment.

Tee-Object displays command output and writes a copy to a file in PowerShell. It does not make a failed native command stop every following line automatically. CTest's --output-log writes test output to the selected file. A log file existing is not proof that the command completed successfully.

## Capture reports through the native command

A transcript helps a person investigate a failure. A JUnit XML file gives another program named test results and durations. Neither file proves which source was tested by itself; keep the source and tool record described above beside them.

1. Choose an existing private directory for a new attempt, such as `C:\work\evidence\attempt-01`. The example project must already have a configured and built `build\debug` tree.
2. Run `umicom test --help` and confirm it lists `--output-log` and `--output-junit`. An older executable may need to be updated before using these options.
3. Preview this request. Confirm the source, build directory and three separate output paths.

~~~powershell
umicom test --source C:\work\sample --build build\debug --output-log C:\work\evidence\attempt-01\ctest.log --output-junit C:\work\evidence\attempt-01\results.xml --log C:\work\evidence\attempt-01\stream.log --dry-run
~~~

The expected preview contains a CTest command with --test-dir, --output-on-failure, --no-tests=error, and the two CTest output paths. No tests run and no output file is created by this preview.

4. When the preview is correct, run the same line without --dry-run. Stop if the command fails and inspect the first useful diagnostic.
5. Compare the transcript and XML result. Record failures, skips and missing results separately. For a rerun, select a new attempt directory.

--log uses Framework's raw stream capture and refuses to overwrite a file. CTest owns --output-log and --output-junit, so those paths can be overwritten by CTest. The shared Framework validator rejects equal paths because independent writers would corrupt each other's evidence. CTest's JUnit output requires version 3.21 or later; see [the official output contract](https://cmake.org/cmake/help/latest/manual/ctest.1.html#cmdoption-ctest-output-junit).

<details><summary>Practice: spot an evidence collision</summary><p>A request uses <code>--log results.xml --output-junit ./results.xml</code>. Both paths resolve against the same source directory. What should happen before any test starts?</p><p><strong>Answer:</strong> The invocation should fail validation before reserving a log or launching CTest. Give the raw transcript and structured report separate names, then retry. Accepting both spellings as different files would allow two writers to damage the same evidence.</p></details>

## Trace a real text-boundary failure

Read [the Framework receipt importer](https://github.com/umicom-foundation/umicom-framework/blob/main/src/testing/reuse.c) and [its file-boundary cases](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/test_reuse/check_receipt_file.cmake). Text can use LF or CRLF to mark the end of a line. LF is a line-feed byte; CRLF is a carriage-return byte followed by a line-feed byte. A parser that accepts only LF can reject a valid file written with CRLF.

~~~text
LF text:       record bytes  [LF]
CRLF text:     record bytes  [CR][LF]
Damaged text:  record bytes  [CR]  more record bytes
~~~

The repair accepts complete CRLF pairs while retaining validation of the record contents. A carriage return appearing alone is still rejected. Duplicate identities, truncated records and embedded zero bytes remain invalid. Accepting a common line ending does not justify accepting arbitrary damaged evidence.

The important regression cases sit at the file boundary as well as the in-memory parser boundary. That exercises the producer's output and the consumer's input together. A unit test containing only a hand-written LF string would not expose the same producer/consumer mismatch.

## Decide what to run again

After a local repair, run the regression checks that demonstrate the original failure and important nearby boundaries. Also account for other consumers affected by the change. A parser fix needs valid-input cases and invalid-input cases; accepting everything would make one failure disappear by weakening the contract.

Keep skipped coverage visible with a reason and a suitable host or capability requirement. If a native window check needs a graphical session, record that requirement. Do not relabel the skip as a pass, or disable the check just to improve a percentage.

<details>
<summary>Check your understanding</summary>
<p>A test suite reports 99% passed but one installed-consumer test failed. Can the installed SDK be marked complete?</p>
<p><strong>Answer:</strong> No. The overall percentage does not replace that consumer's acceptance condition. Inspect its configuration, compile, link or runtime failure, repair the cause, and rerun against the identified installation.</p>
</details>

For practice, take a non-sensitive local test log and write four lines: source identity, command, observed result, and next investigation. If any identity is unknown, write 'unknown' rather than guessing. Keep that working record private; public guides should teach the workflow without publishing personal machine or account details.

[Previous lesson](07-build-only-what-changed.md) · [Next lesson](09-understand-test-commands.md) · [Course contents](index.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.

## Continue this module

Build, test and investigate a change · Lesson 2 of 5.

[Previous: Build only what changed](07-build-only-what-changed.md) · [Next: Understand which program a test runs](09-understand-test-commands.md)


## Record versions without claiming a build

Run `umicom doctor --versions-only` to collect discovered tool paths and version results. This invokes tool version and compiler-target commands but skips generated compile, link and run probes. Its report says `NOT RUN` for those probes. Save the inventory with the source revision and selected preset, then qualify the project separately.

A successful inventory does not prove that the CMake cache uses that compiler, that GTK dependencies match it or that any source compiles. Compare the recorded paths with the configure log. If discovery reports a missing required tool, correct the environment before proceeding. Use the existing PowerShell transcript when you also need a record of the commands typed around the native CLI.
