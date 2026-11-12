# Build a driver evidence record

## Make the claim smaller than the evidence

An evidence record tells another reader exactly what was inspected or executed. For this lab there are at least four separate activities: source review, host compilation and tests, MINIX guest compilation, and guest service exercises. A passing activity in one column does not fill the others. Start with QUALIFICATION.md in the lab directory and leave unexecuted rows explicit.

Record the repository revision, any local source differences and the identities of read_window.c, read_reply.c and status_driver.c. For a guest run, also identify the guest image, release, headers, libraries and service configuration. A binary copied from a previous build is not evidence that the current sources compile.

## Qualify the host boundary

Run each command separately and stop on an error. The intended registration is one existing range test and nineteen named read-reply cases. A count of twenty is an expectation from the authored CMake source, not a result reported for your machine. If CTest finds no matching tests, inspect BUILD_TESTING and the selected directory before recording a pass.

If the branding helper cannot be found, correct the Framework path. If the compiler rejects a declaration, retain the first diagnostic and check the C99 mode. The two host executables contain no MINIX headers and perform no device access. These commands do not compile status_driver.c.

~~~powershell
cmake -S labs/minix/status-driver -B build/minix-read-window -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/minix-read-window
ctest --test-dir build/minix-read-window --output-on-failure -R "^minix[.]learning[.]"
~~~

## Identify the guest separately

Use the pinned MINIX 3.3.0 environment described earlier in the course. Its Makefile builds status_driver.c, read_window.c and read_reply.c with the guest service rules and libraries. Copy the complete lab into a separate working directory rather than overwriting the operating-system source tree. Preserve the guest snapshot before installation or service exercises.

In the guest lab directory, make is the compilation step. Installation, device-node assignment and service launch depend on the reviewed configuration of that guest. This course does not guess a free major number or provide a broad access policy. Follow the matching source and service documentation, then record the exact commands actually used.

## Review outcomes without erasing failures

Keep failed attempts and their diagnostics alongside a later successful run. A corrected environment and a corrected source are different explanations. When a check is skipped, give its reason and leave the corresponding capability unqualified. Never rename a skipped guest check as a host pass.

For the capstone, include one short-read trace, one copy-error trace and the distinction between source and destination offsets. Explain which invariants came from source inspection and which were observed at runtime. The lab provides a small read-only service; it does not establish hardware support, a complete operating system or a state-transfer protocol.

| Observation | Supported conclusion |
| --- | --- |
| Host tests pass | Portable range and callback cases passed for the recorded host build |
| Guest compilation succeeds | Recorded guest toolchain accepted these source files |
| A client reads the expected text | One recorded guest read path worked |
| Controlled grant refusal preserves the error | That tested guest refusal path propagated its observed status |
| Restart succeeds | Recorded restart behavior worked; live update remains unimplemented |

## Source and further reading

- [Original Umicom read-only driver and host commands](../../../../labs/minix/status-driver/README.md)
- [Qualification worksheet](../../../../labs/minix/status-driver/QUALIFICATION.md)
- [MINIX 3.3.0 character-driver example](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/hello.c)
- [MINIX memory grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants)

[Course contents](index.md) · [Previous lesson](11-read-in-chunks-and-retry-explicitly.md)
