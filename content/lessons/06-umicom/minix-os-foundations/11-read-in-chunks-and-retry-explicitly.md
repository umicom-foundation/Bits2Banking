# Read in chunks and retry explicitly

## Keep the read position with the caller

The portable helper is stateless. Its position argument belongs to one request; the helper does not maintain a shared cursor. This lets two clients ask for different parts of the same immutable text without changing each other’s position. The MINIX adapter forwards the position supplied by the character-driver interface.

Open the chunked case in read_reply_tests.c. It uses requests of one, three and five bytes repeatedly, appending acknowledged slices to a separate buffer. The source is small and immutable. Every request count is positive, so a complete result with zero bytes means this exercise has reached the end of that source.

## Advance by what was acknowledged

The complete test checks available destination capacity before appending. It advances by reply.bytes, not by the requested count. A final short read is ordinary success. Advancing by the requested size would skip source bytes or move beyond the source; appending that size could also copy bytes that the callback never supplied.

This sketch is not a generic unbounded stream reader. The test proves its small destination limit before adding the offset. A general reader needs an explicit destination capacity, an overflow check and a policy for sources that change or grow. The helper’s source length must describe accessible storage throughout the callback.

~~~c
/* A bounded sketch for this fixed response, after checking COMPLETE. */
if (reply.bytes == 0) {
    /* All requests in this loop were positive: source end reached. */
    break;
}
memcpy(assembled + offset, probe.copied, reply.bytes);
offset += reply.bytes;
~~~

## Retry is a caller decision

The retry case injects one error and then repeats exactly the same source position and requested size with a successful callback. The helper has no remembered failure and no hidden position to repair. The second observation reports the same offset and a successful byte count; the probe records two attempts.

This is safe to study because the source is fixed text and the fake destination is controlled by the test. Do not conclude that every failed operation can be retried automatically. A callback may have changed its destination before failing, and a real service may have other side effects. An automatic retry policy would need its own ownership and idempotence argument. This lab deliberately supplies none.

## Distinguish source position from destination position

The source offset selects bytes in status_text. Each guest copy begins at offset zero in the grant supplied for the current request. The host chunked test has an additional coordinate: the offset at which it assembles successful slices in its own buffer. Mixing these three offsets can duplicate or omit data even when all individual bounds checks look plausible.

Draw three boxes labelled source, current request destination and assembled output. For the second request, show which coordinate has advanced and which starts again at zero. This small drawing often exposes a mistaken assumption before compiler or guest work begins.

## Exercise and expected reasoning

The tests are authored source until the host commands are executed. Even a host pass would establish only the portable callback contract. Guest character-driver dispatch, correct client position handling and grant permissions remain separate checks. Keep those distinctions in the evidence record introduced in the next lesson.

1. For a ten-byte source, predict positive requests of four, four and four bytes. The returned counts should be four, four and two.
2. Insert a failed second attempt in your trace. Keep the acknowledged source position unchanged until the caller chooses another request.
3. Compare the retry and chunked cases, then locate the zero case. Explain why a zero-size request cannot be used as an EOF probe.
4. Write a recovery note for an unexpected duplicate prefix: inspect the caller’s position update before changing grant permissions.

## Source and further reading

- [Original Umicom read-only driver and host commands](../../../../labs/minix/status-driver/README.md)
- [Qualification worksheet](../../../../labs/minix/status-driver/QUALIFICATION.md)
- [MINIX 3.3.0 character-driver example](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/hello.c)
- [MINIX memory grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants)

[Course contents](index.md) · [Previous lesson](10-preserve-failed-copy-outcomes.md) · [Next lesson](12-build-a-driver-evidence-record.md)
