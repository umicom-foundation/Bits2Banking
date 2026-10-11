# Major Update 09 — Native binary inspection and C23 build engineering

## New native capability

Umicom Framework supplies a read-only header inspection service in `include/umicom/education/binary_inspect.h` and `src/education/binary_inspect.c`. The standalone C23 utility accepts:

```text
umicom-education binary --file PATH
```

The command can inspect a Windows PE executable, an ordinary COFF object file, or an ELF object or executable. It reports the binary container, machine type, address width, section count and entry-point field. PE entry points are labelled *RVA* rather than absolute virtual addresses.

The service is deliberately bounded and does not load the programme, execute its instructions, disassemble code, parse symbol tables or accept a network request. It samples the first 64 KiB and checks the declared file size and section-table ranges. Known but unsupported formats return a non-success status. A malformed file never partially modifies an existing report. On some hosts, the standard C file-seeking interface limits readable file sizes to `LONG_MAX`; very large images are not promised to work. Files with non-ASCII Windows paths require separate host qualification.

This module does not replace the existing Framework web server, GUI, process runner or compiler tooling. It adds one small reusable educational capability to the Framework.

## New learning material

| Page | Practical focus |
| --- | --- |
| Lesson 72 | See preprocessing, Assembly emission, object compilation and linking as separate steps. |
| Lesson 73 | Build a real static C23 library shared by an application and CTest. |
| Lesson 74 | Examine the ELF/PE/COFF headers of actual compiler-produced files. |
| Lesson 75 | Compare x86-64 Windows, x86-64 System V and RISC-V64 calling conventions. |
| Lesson 76 | Follow the freestanding C23 and Assembly hand-off in Umicom Kernel. |
| Episode 20 | Demonstrate the native compile-and-link pipeline. |
| Episode 21 | Inspect executable files and follow a kernel's first instructions. |

The `course-catalogue-library` laboratory contains C23 library, client and test sources, a CMake build, and a deliberately unlinked demonstration that is never included in normal build targets.

## Original content and policy

The ten *Islam: Blueprint for Life* navigation entries remain in their original sequence. No historical manuscript, publishing script, operating-system source file or application source file has been deleted or renamed. The roadmap is extended, not replaced by a new plan. The update uses C23 for new implementation code, existing Framework and Kernel Assembly for low-level instruction examples, and the declarative formats necessary for building and publishing the website.

## Review boundary

All full-file replacements should be reviewed in Beyond Compare before merging. In particular, verify that the local Framework CLI and CMake files match Update 08 before selecting the replacement. If local development has moved ahead, preserve those changes and merge the additional code manually.

## Acceptance

A successful Linux build proves the portable C23 implementation and tests on that host. **It does not prove the Windows UCRT64 PE/COFF integration.** Windows acceptance additionally requires a native `umicom-education.exe` build, CTest results and inspection of one real `.exe` and `.o`/`.obj` file.

The full website still requires MkDocs and Material from the existing Python virtual environment. The native binary-inspection feature itself has no Python dependency. Do not publish site changes until `mkdocs build --strict` succeeds and the original book navigation is verified.
