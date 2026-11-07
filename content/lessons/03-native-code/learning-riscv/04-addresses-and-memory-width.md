<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/04-addresses-and-memory-width.md

PURPOSE:
Explain the lesson: Read bytes and words at memory addresses.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read bytes and words at memory addresses

## Setup recap
Use paper and an editor. No emulator is needed for the trace. An address identifies a location in memory. A byte contains eight bits; a word's width depends on the operation being discussed.

## A memory picture
~~~text
address   byte in hexadecimal
0x1000    0x34
0x1001    0x12
0x1002    0x00
0x1003    0x00
~~~
For a little-endian interpretation of these four bytes, the least significant byte comes first. A 32-bit load gives 0x00001234. The same bytes viewed one at a time remain four separate values.

## Distinguish three questions
What address is used? How many bytes are accessed? How is the loaded bit pattern extended into a register? A signed load and an unsigned load can produce different register values from the same high-bit-set byte.

## Practical trace
1. Draw four adjacent boxes and label their addresses.
2. Place the bytes shown above into the boxes.
3. Write the result of reading only the byte at 0x1000.
4. Write the little-endian four-byte value.
5. Replace the first byte with 0xFF. Explain what changes before deciding whether it is signed.

Expected original byte value is 0x34; expected original four-byte value is 0x1234.

## Read a real boundary
Open Umicom Kernel's diagnostic entry Assembly. Identify which values are moved in registers before a service request. Do not assume every register value is a pointer: the service contract determines whether it means an address, length, selector or ordinary number.

## Link to safer C
A pointer plus a length is a common way to describe a byte range. The length must describe valid storage. Seeing an address in a register does not prove the program owns that memory or may access it.

## Troubleshooting
When a value looks reversed, inspect the individual bytes and the intended width before blaming arithmetic. When an access traps, inspect the target platform's alignment and memory-access rules; do not assume every board handles a misaligned access identically.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/diagnostic/entry.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](03-binary-and-instruction-traces.md) · [Next lesson](05-branches-and-counted-loops.md)

