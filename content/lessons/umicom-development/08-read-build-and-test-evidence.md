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
