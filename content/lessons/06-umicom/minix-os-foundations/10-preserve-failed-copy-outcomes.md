# Preserve failed copy outcomes

## An error is an outcome to preserve

Continue with the same read-only driver. The range may be valid while the copy callback fails. The portable helper must preserve that distinction. It returns UMI_LEARNING_READ_COPY_FAILED and records the exact nonzero callback status. It acknowledges zero bytes because the callback did not report complete success.

Zero acknowledged bytes does not mean that the destination stayed unchanged. A general callback can copy some bytes and then fail. The helper cannot roll back an external operation or infer a trustworthy partial count from an integer error. This distinction matters in file I/O, device drivers and network adapters as well as this small example.

## Compare the three results

Read the header before adding another result category. The callback contract currently reports complete success with zero and failure with any other integer. It has no partial-success protocol. Supporting partial success would require an explicit new contract and corresponding caller changes, not an invented interpretation of a positive status.

The guest adapter maps invalid arguments to EINVAL and returns a failed copy’s actual status. A completed reply becomes the read byte count. Its response is a small fixed string, so that count fits in ssize_t. A later variable-sized service must prove its own conversion bound rather than copying this cast without review.

| Result | Reply storage | Copy callback |
| --- | --- | --- |
| INVALID | Unchanged; do not interpret as a new observation | Never called |
| COMPLETE | New offset and acknowledged byte count; zero copy status | Zero or one call |
| COPY_FAILED | New offset; zero acknowledged bytes; exact error | One call |

## Study an intentionally imperfect copy

In read_reply_tests.c, capture_copy copies the bounded slice into its small probe buffer and then returns the chosen status. This design makes a useful failure visible: destination bytes can differ even though the helper reports failure. The positive-failure and negative-failure cases both require the original status, one callback attempt and zero acknowledged bytes.

Those two artificial signs test preservation in the portable helper. They do not claim that a particular MINIX release uses both error conventions. The driver uses the status supplied by its real grant-copy function. Keep that source identity in the guest record.

~~~c
if (result == UMI_LEARNING_READ_COPY_FAILED) {
    /* Record reply.copy_status; do not advance by the requested count. */
    return reply.copy_status;
}
~~~

## Prevent stale reports from looking successful

The reuse-eof case first creates a failed reply, then requests the end of the source using the same reply object. The second valid operation must clear the earlier error and copy-attempt flag. It must not call the callback again. This checks that reporting is per request rather than accumulated accidental state.

Invalid arguments have a different contract: they leave the caller’s storage alone. A caller that ignores INVALID may display an old success or an old failure. Branching on the function result is therefore part of correctness, even if your UI or log already has a report object ready to reuse.

## Exercise and recovery

The expected answer is a failed result, the admitted source offset, zero acknowledged bytes, the exact callback error and copy_attempted equal to one. Permissions require review in the selected guest. Do not add unrelated hardware access to resolve a memory-transfer problem. Host fault injection demonstrates report semantics; it does not demonstrate that the kernel rejected a real grant.

1. Trace positive-failure and identify the copied bytes that remain in the probe.
2. Explain why returning the requested count after that error would mislead the reader.
3. Change only your worksheet’s requested size and predict the failure reply fields; do not change error signs to make a test pass.
4. When qualifying the guest, record the actual error and service configuration before investigating a grant failure.

## Source and further reading

- [Original Umicom read-only driver and host commands](../../../../labs/minix/status-driver/README.md)
- [Qualification worksheet](../../../../labs/minix/status-driver/QUALIFICATION.md)
- [MINIX 3.3.0 character-driver example](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/hello.c)
- [MINIX memory grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants)

[Course contents](index.md) · [Previous lesson](09-separate-read-planning-from-copying.md) · [Next lesson](11-read-in-chunks-and-retry-explicitly.md)
