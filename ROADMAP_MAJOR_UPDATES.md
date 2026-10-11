# Bits to Banking — Major Development Roadmap

## Purpose

Build one navigable educational platform that teaches computing, programming, practical software engineering, systems development, the Umicom ecosystem, banking and financial applications. Preserve authored manuscripts, the Islam: Blueprint for Life volume, previous books, illustrations, video scripts and Git history. New reusable runtime behaviour belongs in Umicom Framework; Bits2Banking owns the educational content and product composition.

A completed major update must provide learner-facing material, a reproducible practical exercise, automated verification where possible, and corresponding video-script references. The project may publish multiple books from shared authoritative Markdown lessons.

| Update | Subject | Major deliverables | Acceptance criteria |
|---|---|---|---|
| 01 | Native learning-site foundation **(this batch)** | New Framework-owned `umicom-education` C23 tool, native site preview, original-book and brand preparation, verification, MkDocs build adapter, first native lab, roadmap | GCC and Clang compiles; CTest; loopback HTTP GET/HEAD; large file; forbidden traversal/symlink; preserves original book material |
| 02 | Native book pipeline **(first increment delivered)** | C23 `book list` and safe Markdown assembly now available; next: format adapters, output manifests, checksums and parity tests | Native book CTest checks safe names, ordered chapters, BOM handling and refused overwrites. PDF/DOCX generation is not yet implemented. |
| 03 | Single publication pipeline **(native inventory and unified Pages integration delivered; publication qualification ongoing)** | Fix Windows native renderer argument transfer, strengthen renderer tests, add read-only `book check`; single GitHub Pages deployment owner now composes BookForge and MkDocs; existing generators retained; new Framework SHA-256 publication manifest | Existing site paths and Volume 1 remain; renderer fixture exercises Windows argument safety; one-site workflow and native inventory are implemented; GitHub-hosted deployment requires live workflow acceptance |
| 04 | Computer architecture course **(cache-memory laboratory introduced)** | Motherboard, CPU, RAM, storage, buses, cache, binary, gates, fetch/decode/execute, RISC-V/x86-64 comparisons | Practical binary/CPU labs, diagrams, exercises and answer guides |
| 05 | Assembly and low-level C | x86-64 Windows/System V ABI, RISC-V ABI, ELF/PE, symbols, instructions, registers, stack, debugging/disassembly, and an optional Assembly CRLF-scanning laboratory | GCC/Clang sample and conditional native Assembly code compared against equivalent C |
| 06 | Safer C23 | Bounds, ownership, lifetime, checked arithmetic, error contracts, integer overflow, UB, sanitizers, fuzzing, static analysis, ABI design | Small tested libraries, negative/boundary tests, tracked lifetime/ownership rules |
| 07 | Compiler and build engineering | CMake targets/presets, Ninja, Make, Meson, GCC, Clang, linking, symbol visibility, static/shared libraries, cross-compilation, packaging | Windows and Linux build tutorials using real applications; reproducible config/build/test evidence |
| 08 | Package management and C libraries | MSYS2/pacman, apt/dnf, vcpkg, Conan, package metadata, licenses and SBOM; GLib, SQLite, libcurl, zlib, OpenSSL, libgit2, PCRE2, GTK4 and selected libraries | Every library lesson defines a concrete use case, minimal working example, dependency provenance and cleanup |
| 09 | Network and HTTP fundamentals | TCP/UDP, sockets, DNS, HTTP parsing, request routing, MIME, streaming, URL validation, Host/Origin, TLS overview | Bounded C service and traffic-inspection exercises, isolation tests and architecture diagrams |
| 10 | Framework web and developer services | Integrate native preview into stable `umicom` CLI, unify with Framework web service contracts, graceful shutdown, Windows Unicode paths, better streaming | No app-local network stack; deterministic tests; Windows/Linux acceptance; no 16 KiB static response limit |
| 11 | Kernel and operating-system foundations | Freestanding C, Assembly entry, linker scripts, boot, UART, exceptions, memory, paging, scheduler, VFS, drivers, privilege/IPC | Umicom Kernel QEMU RISC-V runbook and reproducible boot evidence; correct distinction between Kernel/OS/Framework |
| 12 | Other compiled languages | C++, Java/JVM, Rust, Zig, Go, C#, Fortran/Ada orientation, FFI/JNI, interoperability and error boundaries | Same Notes/Account exercise compared across languages; explicit build and memory models |
| 13 | Scripting and full-stack applications | PowerShell, Bash, Python, HTML, CSS, JS/TS, PHP, files, databases and service APIs | Scripted and native versions of related real-world app exercises; tests and clear security limits |
| 14 | Umicom Framework and applications | Architecture, Master/Slave Controllers, modules, GTK4, Data Server, Studio, Desk, Trader, Bank, TMS and OS Control Centre | Source-linked, release-qualified tutorials that actually build against current Umicom revisions |
| 15 | Finance and ethics | Purpose and service, Islam volume, financial history, accounting, double-entry, account types, banking, project management/Kanban | Original books preserved; topics clearly distinguish ethical viewpoints from testable technical mechanisms |
| 16 | Treasury and trading projects | Products, positions, lifecycle, workflow, pricing, settlement, risk, execution, controls, reconciliation | Working simulated TMS/trading/accounting labs; no live order/payment permissions |
| 17 | Video and learning media | 5–30 minute scripts, demonstrations, diagrams, transcripts, subtitles, accessible downloads | Every published video references a stable lesson and executable lab; scripts are version-controlled |
| 18 | Interactive learning, localisation and contributor path | Quizzes, feedback, exercises, mentor guidance, localisation, publishing QA, linked source revision | Clear first contribution from fork to reviewed PR; progress evidence and updated translations |

## Native migration: what is and is not replaced

The C23 utility provides native `doctor`, `prepare`, `verify`, `book list`, `book assemble` and read-only `serve`. `build` chooses an interpreter with MkDocs and Material (preferring the repository's `.venv`) before invoking MkDocs as a child, so Python and MkDocs remain required for generating the website. Existing Python, PowerShell, BookForge, Pandoc and book-output scripts are preserved for comparison. PDF/DOCX creation is not yet implemented in C. No command publishes a website or pushes to Git automatically.

The current Framework Web Server has a bounded 16 KiB response body for static files. The new standalone Framework-owned preview uses streaming file reads so real generated pages and artwork can be served without that restriction. It remains loopback-only and is **not** a production-facing HTTP/TLS host. Integration with the established Framework web contracts follows in Update 10 after source and test review.

## Repository ownership

- `C:\umicom\Umicom-Applications\framework`: reusable C23 education library, native tooling and tests.
- `C:\umicom\Umicom-Bits2Banking`: lessons, source labs, book inputs, video scripts and website.
- `C:\umicom\umicom-kernel`: real kernel implementation and QEMU acceptance.
- `C:\umicom\umicomOS`: operating-system integration, images, system services and user-space applications.

The original manuscripts under `dropzone/documents` remain the authoritative source for existing editions until a reviewed authoring migration is approved. The original `mkdocs.yml` retains every historic Islam chapter. Each repository is versioned and committed separately; the Framework is committed first when shared functionality changes.

## Definition of completion for each update

A native code update is complete after its CMake configuration, compilation, focused tests, edge-case checks, manual usage instructions and (where relevant) platform-specific acceptance succeed. A learning update is complete after its internal links, commands, examples, exercises and book navigation have been verified, including cross-repository links. A publication update additionally proves that historical books and the Islam volume remain accessible.

## Publication verification and next milestone

The native `umicom-education publish manifest/verify` commands hash a complete local website using the existing Umicom Framework SHA-256 library. The new `learning-pages.yml` publishes the MkDocs lessons and existing BookForge catalogue together; the legacy workflows retain their book-artifact builders but their former deploy jobs are disabled, with the code kept for engineering review. Publication to GitHub Pages is not treated as proven until a successful run is inspected on GitHub.

Continue Volume 1 and the computing architecture track without changing the original manuscripts: expand registers, caches, buses, number formats and RISC-V ISA, then connect each concept to current Umicom Kernel code and validated QEMU tests.
