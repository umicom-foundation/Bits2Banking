# Represent bytes with bits and hexadecimal

Learn why two hexadecimal digits can describe one byte, then follow the same calculation used by the Umicom Kernel console.

## Start with place values

In decimal, 42 means four tens and two ones: 4 × 10 + 2. Binary uses base two and the digits 0 and 1. Hexadecimal uses base sixteen: 0 to 9, then a to f for values 10 to 15. Base describes how much the next position is worth; it does not change the stored value.

| Decimal | Eight binary digits | Two hexadecimal digits |
| --- | --- | --- |
| 0 | 00000000 | 00 |
| 65 | 01000001 | 41 |
| 127 | 01111111 | 7f |
| 255 | 11111111 | ff |

 <svg viewbox="0 0 700 110" role="img" aria-label="Splitting a byte into two four-bit parts selects its two hexadecimal digits." style="width:100%;max-width:700px"><title>Splitting a byte into two four-bit parts selects its two hexadecimal digits.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">65 = 4 × 16 + 1</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">High part 4; low part 1</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Characters &#x27;4&#x27; and &#x27;1&#x27;</text></svg>

Splitting a byte into two four-bit parts selects its two hexadecimal digits.

## Trace a real expression

The Kernel renderer uses this character table:

```text
static const char digits[] = "0123456789abcdef";
```

`char` stores one character-sized value. Square brackets declare an array, a sequence of elements. The string provides sixteen visible characters followed by a zero terminator. `const` means this code does not change the table; `static` gives it storage that lasts for the program's lifetime.

For an unsigned byte named `byte`, these expressions select the digits:

```text
digits[byte >> 4U]
digits[byte & 15U]
```

`>>` shifts the promoted unsigned-byte value right by four positions. For 65 it produces 4. `&` is a bitwise AND: a result bit is one only where both input bits are one. Decimal 15 has the low four bits set, so the second expression keeps those four bits and produces 1. The `U` suffix marks an unsigned integer constant. This is bitwise AND, not the logical `&&` used to combine true-or-false conditions.

## Keep table access within its bounds

The input here is an eight-bit unsigned value. After either operation the index is between 0 and 15, so it selects one of the sixteen visible characters. That explanation depends on the input type. Do not copy this reasoning to an arbitrary signed integer or a larger unchecked number.

In `umicom-kernel/kernel/console_file_range.inc`, the actual input type is `UmicomU8`. Follow its declaration through the Kernel type headers. The implementation stores output characters in a local fixed-size array and passes its actual character count to the console callback. It does not depend on a terminator.

## Bytes are not automatically text or numbers

The pair 41 represents decimal 65. Displaying A is an additional ASCII interpretation. A program may instead use 65 as a length or an instruction byte. Likewise, several file bytes do not become one native C integer just because they are next to each other. Their format must specify byte order, length and alignment before a decoder combines them.

## Follow an example without installing anything

1. Write decimal 171 as 10 × 16 + 11.
2. Find the table characters at positions 10 and 11, counting the first position as zero.
3. Check the answer: hexadecimal ab.
4. Use the table to explain ff: 15 × 16 + 15 = 255.

When a Kernel console is available, follow [the binary file lesson](../06-umicom/umicom-kernel-from-scratch/14-inspect-binary-files.md) to compare these calculations with a real byte view.

## Exercises and answers

1. What are the two digits for decimal 16?
2. Why is `digits[byte]` unsafe for many byte values?
3. Does reading an executable with `hex` run it?

<details>

<summary>Answers</summary>

16 = 1 × 16 + 0, so the digits are 10. An unmasked byte could index beyond the table: index 255 is not a valid element. The hex command only reads and renders bounded file bytes; loading and executing a program is a separate Kernel operation.

</details>

## Read the source

Open [umicom-kernel/kernel/console_file_range.inc](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/console_file_range.inc) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/17-bits-and-hexadecimal.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Further study: systems programming · Lesson 5 of 6.

[Previous: Keep counts, offsets and progress separate](16-counts-offsets-and-progress.md) · [Next: Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md)


## Continue learning

[Continue: Check a function at its boundaries](18-check-a-function-at-its-boundaries.md)
