# Update 10 — Native archives, link maps and cross-compilation

This update extends the Bits2Banking native-build course with the complete path from a C23 source file to a reusable library, the linker, an installed application and target-specific object files.

## Read and use the native archive inspector

The Framework-owned `umicom-education archive --file PATH` command recognises ordinary GNU/BSD static-library `ar` containers. The implementation reads headers and selected name bytes without loading every member or executing the archive. It reports ordinary object counts separately from symbol indexes and GNU name tables.

The parser checks the signature, fixed header endings, bounded decimal sizes, archive padding and name-table references. It supports ordinary short names, GNU long-name references and BSD embedded names. Thin archives are explicitly unsupported because their data lives outside the archive. It retains a bounded display list while counting ordinary members. The standard C file-seek implementation is limited by `LONG_MAX` on some hosts. No extraction, signatures or complete member-level ELF/COFF validation is implied.

## Read and use the lessons

| Chapter | Subject | Working evidence |
| --- | --- | --- |
| 77 | Static archives and name tables | `umicom-education archive` and real `.a` file |
| 78 | External/internal symbols and linker maps | `libbtb_ledger.a`, `nm`, `btb-ledger-demo.map` |
| 79 | Sections, relocations and PIC | `objdump -h`, `objdump -r`, Kernel linker concepts |
| 80 | Host/target cross-compilation to RISC-V64 | Native and RV64 `.obj` files; `riscv64_hart.S` |
| 81 | CMake installation and package staging | Private `bin`, `lib` and `include/btb` folders |

The new video scripts provide full spoken narration and on-screen build commands. The SVG figures remain editable and render independently of JavaScript.

## Safety and ownership

- The new static library inspection code belongs to Umicom Framework. It does not duplicate it in the educational laboratories.
- The training ledger is a separate, intentionally small C23 application. It handles only fictional amounts and cannot initiate real payments.
- The RISC-V Assembly source is compiled to an object for inspection only. The actual kernel and its runtime behaviour remain owned by the Umicom Kernel repository.
- Existing book manuscripts, the Islam volume, site-build scripts, video scripts and Framework commands are not deleted or disabled.
- C and target-specific Assembly are the only new application languages in this batch. CMake is needed to configure builds, Markdown for lessons and YAML/SVG for website navigation and illustrations.

See `UPDATE_10_BUILD_TEST_AND_GIT.md` for the exact merge, build, test and commit sequence.
