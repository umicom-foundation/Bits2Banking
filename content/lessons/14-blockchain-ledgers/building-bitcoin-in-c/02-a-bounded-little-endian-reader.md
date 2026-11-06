# A bounded little-endian reader

[Course contents](index.md) · [Previous: Scope, bytes and compatibility](01-scope-bytes-and-compatibility.md) · [Next: Assembly after a C reference](03-assembly-after-a-c-reference.md)

## Validate the span before reading

A parser receives a pointer and a byte count. The pointer alone does not tell how much memory is valid. This original helper reads four little-endian bytes only when the caller's buffer length permits it.

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool read_u32_le(const unsigned char *data, size_t length,
                        size_t offset, uint32_t *result)
{
    if (data == NULL || result == NULL || offset > length ||
        length - offset < 4)
        return false;
    const uint32_t value = (uint32_t)data[offset] |
        ((uint32_t)data[offset + 1] << 8) |
        ((uint32_t)data[offset + 2] << 16) |
        ((uint32_t)data[offset + 3] << 24);
    *result = value;
    return true;
}
```

The check uses length - offset after proving offset is not greater than length. Checking offset + 4 instead could itself overflow for a sufficiently large offset. Each byte is converted to uint32_t before shifting, avoiding a signed intermediate for the high byte. The output is assigned only on success.

## Trace the operations

1. Use the bytes 78 56 34 12 in hexadecimal.
2. Shift 56 by eight bits, 34 by sixteen and 12 by twenty-four.
3. Combine the nonoverlapping bits with OR, written | in C.
4. The result is hexadecimal 12345678.
5. Repeat with length three and an initial result of 99. The call should return false and leave 99 unchanged.

An 80-byte header reader can call this helper at documented scalar offsets. Hash fields should be copied as byte arrays rather than squeezed into machine integers. More complex transaction lengths require their own rules and limits.

## Exercise

What happens for offset greater than length? What happens for an empty buffer with a non-null pointer? Does success validate a block's proof of work?

## Explained answer

Both short-span cases return false before reading memory. Success only means four bytes were decoded within bounds. It says nothing about the field's allowed value or the whole block. Structural parsing, semantic validation and consensus are separate responsibilities.

## Continue learning

[Course contents](index.md) · [Previous: Scope, bytes and compatibility](01-scope-bytes-and-compatibility.md) · [Next: Assembly after a C reference](03-assembly-after-a-c-reference.md)

[Browser edition](../../../courses/building-bitcoin-in-c/lessons/02-a-bounded-little-endian-reader.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.

[Primary reference](https://developer.bitcoin.org/reference/block_chain.html).
