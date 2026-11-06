# An exact record format

[Course contents](index.md) · [Next: Validate before changing state](02-validate-before-changing-state.md)

## Build the smallest useful part

Read Introduction to Blockchain and C arrays, functions and pointers first. We will design an offline teaching ledger, not a currency or public network. The first component converts a number into exact bytes. A deterministic encoding produces the same bytes every time for the same value.

Our fictional record contains a four-byte sequence number followed by a four-byte amount in whole practice units. Both are unsigned and little-endian: the least significant byte comes first. This is our teaching format, not Bitcoin's transaction format.

```c
#include <stdint.h>

static void write_u32_le(unsigned char out[4], uint32_t value)
{
    out[0] = (unsigned char)(value & 255u);
    out[1] = (unsigned char)((value >> 8) & 255u);
    out[2] = (unsigned char)((value >> 16) & 255u);
    out[3] = (unsigned char)((value >> 24) & 255u);
}
```

The caller must provide at least four writable bytes. The shift operator moves the desired byte down to the low eight bits; the mask keeps only those bits. This function writes a field, not a whole transaction validator.

## Trace a record

1. Allocate an eight-byte array named record in a practice main function.
2. Call write_u32_le(record, 1u) for the sequence.
3. Call write_u32_le(record + 4, 1000u) for the amount. Adding four advances four bytes in this array.
4. Print each byte in hexadecimal using a loop over all eight positions.

Expected bytes: 01 00 00 00 e8 03 00 00. Hexadecimal e8 represents 232; 3 * 256 + 232 = 1000. Defining the field order makes a decoder possible later.

## Exercise

Encode sequence 2 and amount 256 on paper. Explain why writing a C struct directly to disk is not a substitute for this function.

## Explained answer

02 00 00 00 00 01 00 00. A struct's padding and native byte order can differ between toolchains. Explicit serialization is a boundary contract. When this becomes a shared product capability, implement the contract in Framework and keep the teaching program separate from production clients.

## Continue learning

[Course contents](index.md) · [Next: Validate before changing state](02-validate-before-changing-state.md)

[Browser edition](../../../courses/building-blockchain-from-scratch/lessons/01-an-exact-record-format.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
