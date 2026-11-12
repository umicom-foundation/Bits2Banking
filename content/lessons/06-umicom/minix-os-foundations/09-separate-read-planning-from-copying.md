# Separate read planning from copying

## A read has two different responsibilities

The status driver has a fixed response, but reading it still crosses two boundaries. First, decide which bytes belong to the request. Then ask the operating system to copy those bytes into storage described by the request. A successful range calculation does not prove that the second step is permitted. This lesson separates those responsibilities while keeping the original range helper.

Open read_window.c, read_reply.h and read_reply.c in labs/minix/status-driver. These are original C teaching sources. The portable helper knows lengths, positions and callback results. It does not know MINIX endpoints, device minors or grant identifiers. status_driver.c supplies those release-specific details in a small adapter. C99 is intentional for the pinned MINIX 3.3.0 example; it does not change the C23 policy of Umicom Framework.

## Work out the slice before touching a pointer

Use the string ABCDEFGHIJ, which has ten data bytes. A request at position seven for six bytes can return only HIJ. The helper first proves that the position is below the length. Only then does it subtract the position from the length and choose the smaller of the remaining and requested sizes. This avoids forming position plus requested, which could overflow.

The returned offset describes a position in the source text. It is not an offset into the client grant. The adapter continues to copy to grant offset zero for each read request. Keep these coordinate systems separate when drawing the request on paper.

~~~c
/* This fragment assumes a valid copy callback and separate reply storage. */
UmiLearningReadReply reply;
UmiLearningReadResult result = umi_learning_read_reply(
    "ABCDEFGHIJ", 10, 7, 6, copy, context, &reply);
/* On complete copy: reply.offset == 7 and reply.bytes == 3. */
~~~

## Read the ownership contract

The source text and callback context are borrowed for the duration of one call. The helper stores neither pointer. The caller must provide accessible source storage of the stated length, a callback and separate reply storage. A null source is accepted only for an empty source. A null callback is refused even when the request would return no bytes; keeping one admission rule makes callers easier to review.

For valid input, the helper publishes a fresh reply on every outcome. Invalid input leaves the old reply unchanged. This is why callers must branch on the returned result before interpreting a report. When no bytes are needed, the callback is not called. A zero byte result can mean an empty request as well as end of source, so do not infer EOF from a request whose requested count was zero.

## Follow the existing MINIX adapter

The adapter accepts minor zero and constructs a short-lived context containing the endpoint and grant from that request. Its callback invokes the same sys_safecopyto interface used by the earlier implementation. The original inline implementation remains in a disabled block for source comparison. Neither implementation retains a grant after the read returns.

Read the MINIX memory grants guide alongside the release-specific source. Grants describe controlled access to another process’s memory; a normal C pointer is not an interchangeable capability. The portable callback is a seam for testing outcomes, not an emulation of those access checks.

## Exercise and review

Expected calculations are (0,6), (7,3), (10,0) and (10,0). If your answer exceeds ten source bytes, revisit the subtraction before changing the driver. A failed host build should be diagnosed using its first compiler error and the declared C99 target; changing guest permissions cannot repair a C declaration error.

1. Calculate the offset and count for positions zero, seven, ten and UINT64_MAX with a requested count of six.
2. Locate the prefix, tail, eof and huge-position cases in read_reply_tests.c. Compare each expected result with your calculation.
3. Find every path that reaches the copy callback. Explain why there can be no pointer arithmetic on a null, empty source.
4. Record source review separately from a compiled host result or a guest run.

## Source and further reading

- [Original Umicom read-only driver and host commands](../../../../labs/minix/status-driver/README.md)
- [Qualification worksheet](../../../../labs/minix/status-driver/QUALIFICATION.md)
- [MINIX 3.3.0 character-driver example](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/hello.c)
- [MINIX memory grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants)

[Course contents](index.md) · [Previous lesson](08-compare-recovery-with-umicom-kernel.md) · [Next lesson](10-preserve-failed-copy-outcomes.md)
