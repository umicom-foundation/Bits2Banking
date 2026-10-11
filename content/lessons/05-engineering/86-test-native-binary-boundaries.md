# 86. Test binary-file readers before trusting their results

A useful binary inspection tool should report the truth about a file it understands and reject a file it cannot safely interpret. Incorrect or truncated input must not cause an out-of-bounds memory read, an infinite loop or a partially updated report.

This lesson uses the Umicom Framework ELF symbol inspector as a practical example of **defensive parsing** in C23.

## 1. Start with a clear contract

The Framework has two public interfaces:

```c
UmiStatus UmiEducationElfInspectBytes(
    const void *bytes,
    size_t length,
    UmiEducationElfReport *out);

UmiStatus UmiEducationElfInspectFile(
    const char *path,
    UmiEducationElfReport *out);
```

The byte interface works on a caller-supplied span. The file interface opens a file, reads at most 32 MiB and delegates to the same parser. Both preserve `*out` on a failure. The parser supports ELF32 and ELF64 in either byte order and rejects non-ELF formats with an explicit status.

The first interface is especially useful in tests because a test can construct the bytes directly, without relying on whichever compiler version happens to be installed on a particular machine.

## 2. Reject overflowing offsets before using pointers

A naïve check is:

```c
/* Unsafe as a general bounds check: offset + length can overflow. */
if (offset + count <= total) {
    /* ... */
}
```

An unsigned addition may wrap around to a smaller value, making the comparison incorrectly succeed. A safer check is:

```c
static int Fits(uint64_t offset, uint64_t count, uint64_t total)
{
    return offset <= total && count <= total - offset;
}
```

The first condition protects the subtraction. The second compares a length against the remaining capacity. The same idea applies to arrays, strings, network packets, database records and financial messages.

## 3. Count tables only after validating them

An ELF symbol table is described using a file offset, total size and entry size. The parser must check all three. A zero entry size would cause division by zero. An entry size smaller than the specified structure cannot hold the fields the parser needs. A table whose length is not a multiple of its entry size is malformed.

Once validated, the record count can be computed safely. A **separate work limit** protects against files designed to demand excessive iteration. The Framework's ELF reader has a 262,144-record budget across accepted symbol and relocation entries. This is a safeguard, not a claim that every legitimate ELF file will fit.

Names need a second check. The `st_name` field is only an offset into a string table. The parser verifies that the offset is inside that table **and** that a terminating zero byte appears before its end.

## 4. Run the supplied tests

On Windows:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake --build ".\build\umicom-education" --parallel 2

ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_symbols|symbols\.cli)$" `
  --output-on-failure
```

The parser test creates synthetic little-endian ELF64 and big-endian ELF32 symbol tables, checks expected names and relocations, tries truncated and malformed data, and runs 12,000 deterministic byte mutations. It also writes a fixture whose filename contains spaces so the CLI test can inspect it on Windows.

On a supported Clang/LLVM configuration, enable AddressSanitizer and UndefinedBehaviorSanitizer when building an **independent** test build directory. Sanitizers help discover some memory errors but do not prove that every parser path is correct.

## 5. Why the report is published at the end

Suppose the parser has read five valid symbols and encounters an invalid name in the sixth. If it wrote directly into the caller's output object, the caller could mistake the partial data for a complete report.

Instead, the Framework builds a local temporary report, validates the file and only then assigns the completed result to `*out`. On failure, the caller retains the previous result unchanged. This is called **failure atomicity**.

It is the same design principle we use when editing a Notes document or posting a fictional account transfer: prepare and validate the proposed change before making it visible.

## 6. The limits of the current inspector

This tool reports counts and a bounded selection of names. It does not apply relocations, resolve external dependencies, validate cryptographic signatures, disassemble code or evaluate whether an executable is trustworthy. It reads up to 32 MiB of ELF metadata into memory. It is a local learning and inspection command, not a production security scanner.

Windows COFF and PE require different parsing rules. Use `umicom-education binary --file` for their basic headers and native `objdump`/`nm` tooling for symbols. Do not infer an ELF section layout from a Windows object.

### Exercises

1. Find the `ElfFits` helper and explain why its order of checks matters.
2. In the test fixture, change the symbol's string-table offset to an invalid value. Confirm the parser returns an error and does not update the report.
3. Create an ELF file with a truncated section table. What error does the parser return?
4. Inspect a real Linux object and compare its relocation count with `readelf -r`.
5. Explain why fuzz tests complement — but do not replace — documented format checks.

Continue with [Umicom Kernel: freestanding C23 and Assembly](../06-umicom/76-freestanding-c-and-umicom-kernel.md), or revisit the [practical source laboratories](../../labs/index.md).
