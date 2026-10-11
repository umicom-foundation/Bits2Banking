# Major Update 11 — ELF Symbols, Relocations and Kernel Linking

Bits2Banking adds a native C23 symbol-inspection service to Umicom Framework, extending the earlier binary-header and static-archive inspection work. The educational course progresses into symbol visibility, relocation records, linker scripts, cross-compilation and defensive binary parsing.

## Native Umicom Education command

```text
umicom-education symbols --file ELF_OBJECT_OR_IMAGE
```

The native command reads ELF32 or ELF64 metadata without executing the file. It reports architecture, endian order, defined and undefined symbol counts, local/global/weak binding, function/object counts, and REL/RELA relocation totals. It displays at most 16 symbol names while counting all accepted records. The parser rejects malformed name offsets, unchecked table lengths, unsupported formats and inputs above 32 MiB.

**Supported:** read-only ELF section, symbol and relocation metadata.  
**Not implemented:** COFF/PE symbol tables, relocation application, code disassembly, kernel loading, malware screening, or signature verification.

The Windows compiler may generate COFF objects. For a Windows test that does not require an ELF cross-compiler, run the new CTest fixture and inspect the generated synthetic ELF object:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_symbols|symbols\.cli)$" `
  --output-on-failure

& ".\build\umicom-education\bin\umicom-education.exe" `
  symbols --file `
  ".\build\umicom-education\education-elf-test\fixture with spaces\umicom example.o"
```

The regression creates a deliberately small ELF64 object with two named symbols and one relocation. A Linux or RISC-V64 object will show its own actual counts.

## Practical course material

| Learning material | Outcome |
| --- | --- |
| Lesson 82 | Identify defined and undefined ELF symbols |
| Lesson 83 | Understand relocations and the linker's resolution process |
| Lesson 84 | Read sections and study a real kernel linker decision |
| Lesson 85 | Separate host, target and calling conventions |
| Lesson 86 | Test input-size, range and failure-atomicity contracts |
| Linker-relocations laboratory | Build a C23 static library with ABI-selected Assembly and CTest |
| Video 24 | Compile C and Assembly, inspect symbols and repair a linker failure |
| Video 25 | Inspect ELF metadata and trace Umicom Kernel memory preparation |

The lessons link directly to the original [Umicom Kernel source](https://github.com/umicom-foundation/umicom-kernel) and [Umicom Framework](https://github.com/umicom-foundation/umicom-framework). They do not duplicate production source into the educational repository.

## Architecture ownership and preservation

- Umicom Framework owns reusable binary inspection contracts and the education CLI; both the old `binary` and `archive` commands remain available.
- Bits2Banking owns lessons, illustrations, source labs and video narration.
- Umicom Kernel owns RISC-V bootstrap, linker scripts, memory mechanisms and actual QEMU tests.
- Existing book manuscripts, the Islam volume navigation, publishing workflows and Umicom OS sources are unchanged by this update.

New implementation code is C23 with x86-64 or RISC-V64 Assembly in the learning laboratory. CMake/YAML/Markdown/SVG remain necessary formats for build and publication.

## What to verify on Windows

After merging, run all 14 Framework Education tests, then both `linker-relocations` laboratory tests. Inspect the new ELF fixture through the CLI. Run the complete MkDocs strict build and open the learning website with the native C web server. The documentation site must continue to show all ten chapters of *Islam: Blueprint for Life*.

Development validation on Linux is not a substitute for these Windows checks or live GitHub Pages acceptance.
