# Read-only driver qualification worksheet

Use this worksheet with the original Umicom MINIX status-driver lab. Copy it into
your own evidence directory before filling it in. Its empty fields are not test
results. The code and checks are authored; compilation and execution require
separate evidence.

## 1. Identify the source and environment

| Field | Value to record |
| --- | --- |
| Bits2Banking repository revision | Not recorded |
| Local source differences | Not recorded |
| read_window.c and read_window.h identities | Not recorded |
| read_reply.c and read_reply.h identities | Not recorded |
| status_driver.c identity | Not recorded |
| Host operating system, architecture and compiler | Not recorded |
| Host CMake/Ninja versions and build directory | Not recorded |
| Framework branding source revision and local differences | Not recorded |
| Guest image digest and MINIX release | Not recorded |
| Guest headers, libraries and compiler identity | Not recorded |
| Guest service configuration and assigned device node | Not recorded |
| Guest driver binary identity | Not recorded |

A revision alone is insufficient when local files differ. Record the differences
or complete file hashes. Keep a failed build's log with its source identity; do
not overwrite it with a later successful attempt.

## 2. Qualify the host model

From the Bits2Banking repository, run each command separately and stop on errors:

~~~powershell
cmake -S labs/minix/status-driver -B build/minix-read-window -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/minix-read-window
ctest --test-dir build/minix-read-window --output-on-failure --no-tests=error -R "^minix[.]learning[.]"
~~~

The expected registration is one original range case plus nineteen read-reply
cases. Compare actual names and outcomes, not just a final count. If configuring
fails because the branding helper is absent, correct UMICOM_FRAMEWORK_SOURCE.
These host targets use C99 and do not compile the MINIX adapter.

| Check | Expected behavior | Actual result / evidence |
| --- | --- | --- |
| Ordinary and tail slices | Only available source bytes are copied | Unexecuted |
| EOF, huge position and empty input | No callback; fresh zero-byte report | Unexecuted |
| Zero requested size | No callback; not an independent proof of EOF | Unexecuted |
| Oversized request | Clamped to remaining source bytes | Unexecuted |
| Positive and negative injected errors | Exact error; no acknowledged bytes | Unexecuted |
| Retry | Caller repeats position; next outcome replaces the previous report | Unexecuted |
| Reused report at EOF | Old error and attempt flag cleared | Unexecuted |
| Invalid input | No callback; prior reply unchanged | Unexecuted |
| Chunked reads | Concatenation equals the original fixed text | Unexecuted |
| Explicit null callback context | Accepted only by a callback that supports it | Unexecuted |

The failed-copy probe changes its destination before returning an error. Explain
why this is compatible with zero acknowledged bytes. A host pass says nothing
about the authenticity, ownership or permissions of a MINIX grant.

## 3. Qualify a separate MINIX guest

Use the matching MINIX 3.3.0 source and development environment. Preserve a
powered-off guest copy or a supported snapshot. Copy the complete lab into a
separate directory and compile there with make.

Review the chosen release's service configuration and device-node procedure before
loading. Record the exact commands used and the configuration they applied. Do not
guess a free major number, grant unrelated hardware access or use a production
machine as the learning target.

| Guest check | Expected observation | Actual result / evidence |
| --- | --- | --- |
| Compile current sources | umi_status built using the guest service rules | Unexecuted |
| Minor zero read | Fixed status text followed by newline, without C terminator | Unexecuted |
| Short prefix and subsequent read | Slices match the requested positions | Unexecuted |
| End of source | Zero bytes for a positive request at source end | Unexecuted |
| Invalid minor | ENXIO through the driver callback | Unexecuted |
| Controlled invalid-grant harness | Actual safecopy error preserved | Unexecuted |
| Restart using the supported manager | Service announced and read again | Unexecuted |
| Live update | Not implemented; no acceptance claim available | Not applicable |

A normal client read cannot establish the invalid-grant harness result. Describe
the controlled harness and actual returned status separately. Record a denied
operation without treating denial itself as evidence that the driver is healthy.

## 4. Review the conclusion

State which checks passed, failed, were skipped or remain unexecuted. Include
diagnostics and a reason for every skipped check. If only source was inspected,
say so. Do not infer guest success from host tests or live update from restart.

For a failure, identify whether the first adverse observation was a compiler
diagnostic, a refused service configuration, a grant-copy error or wrong data.
Choose the next investigation from that evidence. Preserve earlier observations
when correcting source or environment so another reader can reconstruct the
reason for the conclusion.
