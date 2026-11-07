# Store a program as portable bytes

A C structure describes data while a program runs. Its in-memory layout can depend on the compiler and target. **Serialization** converts that data to a defined sequence of bytes so that a different build can read it. Umicom C uses the UMCB bytecode format for that purpose.

## A file starts with a header

The first eight bytes contain four identifying characters, a version byte, a reserved-flags byte and a two-byte instruction count. Identifying characters help reject the wrong file type; they do not prove that a file is trustworthy.

| Bytes in hexadecimal | Meaning |
| --- | --- |
| 55 4D 43 42 | UMCB identification |
| 01 | Format version 1 |
| 00 | No flags |
| 04 00 | Four records, little-endian |

**Hexadecimal** is a compact base-sixteen way of writing numbers. For example, 4D represents decimal 77, the ASCII value for M. **Little-endian** means the least significant byte is stored first. A count of four is 04 00; 00 04 would mean 1024.

## Each instruction occupies nine bytes

1. One byte identifies the operation.
2. Four bytes store the signed 32-bit operand in the specified representation.
3. Four bytes store a source offset for diagnostics.

Thus four records occupy 36 bytes; with the eight-byte header, the file is 44 bytes long. Source offsets say where an instruction came from. They are positions in source, not addresses the runtime is allowed to access.

Read `put_u32` and `get_u32` in `src/bytecode.c`. They assemble bytes explicitly instead of casting a byte pointer to a C structure. This avoids depending on structure padding, pointer width and input alignment.

## Decode before executing

The decoder checks the exact file length, version, flags and record count, then validates the decoded instructions. Extra trailing bytes are rejected. A truncated file is rejected. The output count is zero on failure; partially written output must not be executed.

`tests/test_wire_contract.c` contains fixed bytes whose meaning was specified independently of the encoder. That matters because a matching mistake in both encoder and decoder could pass a simple round-trip test. It also reads input at an intentionally unaligned address.

## Exercise

How large is a two-instruction UMCB file? Would copying the same file onto an ARM64 computer make it a bootable ARM64 program?

<details>

<summary>Explanation</summary>

It is 8 + 2 × 9 = 26 bytes. It remains bytecode. A compatible interpreter must already run on that computer. The firmware cannot boot this arithmetic file as an operating system. The interpreter itself needs a native build for the processor and system interface.

</details>

## Find the implementation

Open `umicom-c/src/bytecode.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/05-portable-bytecode.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Execute instructions with checked arithmetic](04-checked-execution.md)

[Next: Explain failures and test the boundaries](06-errors-and-tests.md)
