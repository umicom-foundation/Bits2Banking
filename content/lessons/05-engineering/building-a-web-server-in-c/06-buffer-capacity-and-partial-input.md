# Buffer capacity and partial input

[Course contents](index.md) · [Previous: Requests are bytes, not packets](05-requests-are-bytes-not-packets.md) · [Next: Run and explain a Framework service](07-run-and-explain-a-framework-service.md)

## Capacity and length mean different things

Capacity is the amount of memory available. Length is the number of bytes currently used. Before appending input, prove that the remaining space is sufficient. This original helper is a buffer exercise, not an HTTP parser.

```c
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static bool append_bytes(unsigned char *buffer, size_t capacity,
                         size_t *used, const unsigned char *input,
                         size_t count)
{
    if (buffer == NULL || used == NULL || *used > capacity ||
        count > capacity - *used || (count != 0 && input == NULL))
        return false;
    if (count != 0) memcpy(buffer + *used, input, count);
    *used += count;
    return true;
}
```

The caller must provide real storage of at least capacity bytes. Input must not overlap the destination range for this memcpy-based contract. The function stores binary data and does not add a string terminator. A later text parser must not call string functions beyond used bytes.

## Trace the boundary

1. Let capacity be 8 and used be 3.
2. Append five bytes. There are exactly five spare bytes, so used becomes 8.
3. Try appending one more byte. The function returns false and used stays 8.
4. Try a zero-byte append. It succeeds without copying, even with a null input pointer.

Checking count > capacity - used after validating used avoids overflow in used + count. Bounds checks are not decorative; their order affects whether the check itself is safe.

## Exercise

Why should this function not simply resize forever when a peer keeps sending data? Why is returning false better than silently discarding the extra byte?

## Explained answer

Unbounded growth allows a peer to consume memory without limit. Silently discarding bytes changes the message and may confuse framing. A connection layer should turn the limit into an explicit error and close or otherwise handle the request according to its documented protocol. The application's handler must never receive a silently truncated request as if it were complete.

## Continue learning

[Course contents](index.md) · [Previous: Requests are bytes, not packets](05-requests-are-bytes-not-packets.md) · [Next: Run and explain a Framework service](07-run-and-explain-a-framework-service.md)

[Browser edition](../../../courses/building-a-web-server-in-c/lessons/06-buffer-capacity-and-partial-input.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/examples/web/local_service.c). This public revision matches the source inspected for this lesson.

[Primary reference](https://www.rfc-editor.org/rfc/rfc9112.html).
