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
| 05 | Assembly and low-level C **(Windows renderer host acceptance confirmed: all focused tests passed)** | x86-64 Windows/System V ABI, RISC-V ABI, ELF/PE, symbols, instructions, registers, stack, debugging/disassembly; native launch-path regression repair | x86-64 assembly lab and portable C23 record lab build and pass; Windows interpreter path with spaces must pass real UCRT64 CTest before closure |
| 06 | Safer C23 **(first increment delivered)** | Deep-copy Notes model, failure-atomic replacement, capacity limits, checked unsigned pence balances and two-record training transfers, negative CTest cases, compiler warnings and sanitizer lessons; fuzzing and extended API qualification remain planned | GCC/Clang compile and tests for owned-notes and checked-money; Framework native preview preflight test; Windows and full-site build require host acceptance |
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

The numbered rows above are the original thematic programme plan. The later
"Update XX" checkpoints record actual integration batches as they are delivered;
the two sequences are not necessarily one-to-one. An integration batch can
advance several subjects while earlier programme stages remain open.

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

## Update 05 checkpoint — native subprocesses and processor contracts

The renderer fix replaces only the Windows bootstrap launch path that could not start the spaced mock executable. Previous `_spawnvp` logic is retained in an explicit disabled block. Tests now exercise spaced executable, MkDocs configuration and output-directory arguments, and a child that exits successfully without creating a website. Windows UCRT64 acceptance is required before marking the regression resolved. The general Framework process service remains the preferred choice for non-bootstrap callers.

New lessons 53–57 teach application calling conventions, Umicom Kernel's freestanding boot, safe fixed-width C23 records, Windows process arguments, object files and linking. Complete source laboratories and video scripts are included. Historical Islam manuscripts, original book generators and single-site publishing configuration are not modified by this update.

The next planned material extends **Update 06** with memory ownership, integer arithmetic, ASan/UBSan, C23 contracts, fuzzing and API design, alongside real Umicom Framework source examples.

## Update 06 checkpoint — safe C and generated-site preflight

The previous Windows report confirms that `framework.education.renderer` now passes its spaced-executable, interpreter-selection and missing-output cases. The complete six-test native suite and both previously delivered learning laboratories also passed. The RISC-V assembly compiler check reported **not supported by the selected x86-64 compiler**, which is expected and is not a failed test.

The final `serve` refusal in that report is a missing generated website, not a failed server test. Users must build the site first. The new native `serve --build` option explicitly builds using the same Framework renderer and then starts the read-only localhost server, with no fallback if an explicitly selected Python executable fails. A seventh native preflight test checks the missing-page diagnostic and non-launch on build failures.

New source laboratories teach deep ownership, failure-atomic document edits, bounded dynamic arrays, exact minor currency units, checked arithmetic and source-linked CMake projects. The next increment should add documented allocator-injection tests, fuzzing, static analysis and cross-platform build qualification before introducing new native publishing formats.


## Update 07 checkpoint — YAML navigation, failure injection and bounded input

The previous Windows report confirmed 7/7 native education tests passed, and the owned-notes and checked-money laboratories each passed 1/1. The remaining failed website build reported a YAML configuration parse error at lines 65 and 78; the C web server correctly refused to start because no `site/index.html` had been generated. This update supplies the complete, syntax-verified MkDocs configuration; a structural checker with line-level diagnostics; and a website workflow gate that checks the configuration before expensive publishing steps. The ten original *Islam: Blueprint for Life* chapters remain in their established order.

The next two C23 laboratories teach deterministic allocation failures, retained edits, bounded byte-oriented parsing and seeded adversarial tests. The laboratories are independent teaching examples; shared production memory and web services continue to belong to Umicom Framework. The next milestone is verifying the complete native website and unified GitHub Pages build against the real historical manuscripts.

## Delivery checkpoint — Major Update 08: native checks and low-level C23

The Framework-owned Umicom Education tool gains a read-only `audit --repo` navigation-target checker written in C23. It checks missing, repeated and unsafe local `.md` references; it is not a replacement for complete YAML validation in MkDocs. The existing `build` and `serve --build` commands remain unchanged.

The educational track adds chapters 67–71, two C23-only laboratories for arena allocation and bounded fictional ledger messages, and two narrated video scripts. The laboratories use CMake as build metadata, and the website retains Markdown and YAML because these are required by the existing publishing system. No new Python, PowerShell, C++, PHP or JavaScript application source is introduced.

**Release gate:** standalone Framework education tests including `framework.education.navigation_audit`, both new C23 laboratory suites, complete original-book navigation, and a strict MkDocs site build on Windows. A native audit pass does not by itself qualify the published website.

## Delivery checkpoint — Major Update 09: native file formats and linking

Umicom Framework adds a reusable, read-only C23 header inspector for ELF32/ELF64, PE32/PE32+ and ordinary COFF objects. Its public API checks byte ranges, declared section tables and unchanged-on-failure outputs; the standalone `umicom-education binary --file PATH` command displays the resulting report without invoking a shell, loader or Python. The inspector deliberately does not parse archive files, symbol tables, relocations or full executable contents; those remain later topics. Framework tests cover fixed-header fixtures, malformed offsets, actual compiler-produced images, spaced paths and the CLI.

The Bits2Banking track adds Lessons 72–76, a C23 course-catalogue static-library laboratory (separate client and tests), three SVG diagrams and Episodes 20–21. The Kernel tutorial links directly to the actual RISC-V64 bootstrap and QEMU build documentation. No existing Islam volume, historical manuscripts, source applications or site publication logic are removed. New implementation code uses C23; Assembly remains in the existing architecture-specific training files. CMake, Markdown, YAML and SVG are retained as necessary build and publication formats.

**Acceptance gate:** Framework's 10 focused tests, course-catalogue laboratory's two tests, strict MkDocs rendering, and Windows UCRT64 validation of both PE image and COFF object inspection. Linux GCC and Clang tests cannot replace Windows qualification. Check that the live repository contains the update 08 sources before applying this additive batch.

**Next:** extend binary inspection with explicitly bounded section summaries and test fixture corpora, then teach cross-compilation, linker scripts, symbol visibility and native packaging using existing Framework and Kernel contracts. Do not replace production services with teaching copies.

## Update 10 checkpoint — native archive inspection and cross-target build laboratories

This update adds a standalone Framework-owned C23 `umicom-education archive --file` command for reading ordinary GNU/BSD `ar` static-library members without extraction or execution. It recognises short names, GNU string-table references and BSD embedded names; refuses thin archives and malformed sizes; preserves the report on failure; and uses only bounded standard-C file I/O. The education tool has two additional CTest cases: the native parser and a real compiler-generated archive.

The educational track now includes Lessons 77–81, a static-library and linker-map laboratory, a compile-only Clang RISC-V64 laboratory, editable diagrams and Videos 22–23. The new build teaching material uses C23 and target-specific Assembly; CMake, Markdown and SVG serve their necessary build/documentation roles. No additional interpreted application is introduced.

Windows UCRT64 and complete MkDocs acceptance remain host checks, not claimed results of Linux testing. The existing original books, Volume 1 Islam chapters and publishing workflows remain intact. The next milestone should add deeper C23 linker and target-ABI introspection only where reusable, and strengthen site/build release qualification before claiming production status. Native PDF/DOCX rendering has not been replaced.

## Update 11 checkpoint — native ELF symbols, relocation metadata and kernel linker lessons

This batch adds a read-only native C23 ELF symbol and relocation **metadata** inspector to Umicom Framework. The `umicom-education symbols --file ELF_PATH` command accepts ELF32/ELF64 and either encoded byte order, validates section and string-table bounds, counts defined and undefined symbols and `REL`/`RELA` entries, and displays a bounded sample of names. It explicitly refuses non-ELF files and inputs above 32 MiB. It is not an ELF loader, a linker, a kernel debugger or a replacement for established binary-analysis tools.

Cumulative standalone Framework acceptance now includes 14 tests. The two additional cases validate synthetic ELF32/64, malformed offsets, a deterministic mutation corpus, a path with spaces and CLI formatting. The test suite runs on Windows without requiring the native host compiler to emit ELF objects.

Bits2Banking adds Lessons 82–86, the C23/Assembly `linker-relocations` laboratory with two CTest cases, three editable diagrams and Episodes 24–25. Source explanations link to the real Umicom Kernel RISC-V64 bootstrap rather than copying Kernel code into the educational repository. The website navigation preserves *Islam: Blueprint for Life* and its ten original manuscripts. All previously configured chapter navigation remains active.

**Qualification boundary:** Linux GCC and Clang sanitizer validation is development evidence. Windows UCRT64 compilation, complete strict MkDocs rendering with historical book assets, and the live GitHub Pages workflow still need explicit user-host acceptance. Do not infer their success from portable C tests.

**Next proposed checkpoint:** inspect relocation entries beyond aggregate counts, explore symbol-version and dynamic-linker boundaries, build a C23 linker-map reader where justified, and teach the first Umicom Kernel memory-translation mechanisms from their actual RISC-V source. Preserve the original application services and books.


## Update 12 — ELF Load Plans, Frame Ownership and Sv39

**Status:** Source delivery for host qualification (October 2026). This update does not assert that the Umicom Kernel or OS can launch arbitrary ELF user programmes.

- Extend Framework Education's read-only native ELF inspection with validated ELF32/ELF64 PT_LOAD programme headers, file-backed byte ranges, memory byte ranges, file/memory alignment, R/W/X flags and entry-point containment.
- Preserve the existing `binary`, `archive` and `symbols` commands. Add independent `load-plan` tests that construct a synthetic RISC-V64 ELF image in a path containing spaces. Exercise malformed values and 12,000 deterministic header mutations.
- Build a C23 physical-frame-ownership laboratory covering reservations, exhaustion, double-release protection and failure atomicity.
- Build a separate C23 Sv39 software page-walk laboratory covering canonical addresses, 4 KiB pages, VPN[2:0] and R/W/X. This is a learning simulation, not the actual kernel or a replacement for Umicom Framework.
- Publish Chapters 87–91, diagrams and Videos 26–27. Refer to the authoritative `umicom-kernel` sources and original *Islam: Blueprint for Life* without changing historical manuscripts.

**Acceptance gates:** 16 Framework Education CTest cases; two tests per new laboratory; strict YAML parsing; no lost MkDocs navigation entries; same test results under GCC and Clang with sanitizers where supported; Windows UCRT64 and the complete MkDocs site must be verified by the maintainer. Do not mark QEMU or GitHub Pages deployed without separate evidence.

**Next: Update 13 — Process creation, page faults and executable-memory protections.** Study loader policy, guarded process address spaces and RISC-V privilege transitions through small C23/Assembly exercises and actual Umicom Kernel code. Continue keeping live-kernel responsibilities in the Kernel repository and reusable hosted functionality in Framework.

## Update 13 — Process memory, page faults and W^X review

**Scope:** Add a read-only ELF page-permission audit to the Framework-owned education tool, using the existing ELF load-plan parser rather than a second ELF reader. It reports conservative 4 KiB permission unions, segment sharing, unknown flag bits and pages that would require both write and execute. Nothing is loaded or executed; there is no kernel memory change.

**Curriculum:** Lessons 92–96 introduce process address spaces, unmapped and protection faults, page-rounded ELF permission collisions, C23 process lifecycle state machines and RISC-V privilege boundaries. Two independent hosted C23 laboratories model page access and process state. Two video scripts and three SVG diagrams accompany the lessons. The authoritative Umicom Kernel source is linked, not copied.

**Acceptance:** 18 standalone Umicom Education CTest cases, two tests in each new laboratory, no lost MkDocs navigation targets or original Islam chapters, valid SVG source and strict MkDocs website generation on the maintainer's Windows checkout. GCC and Clang ASan/UBSan are development checks; the native Windows build, final hosted site and GitHub Pages must be separately qualified.

**Next: Update 14 — System calls, IPC and message ownership.** Explain protected user/kernel service boundaries and supervised communication with C23 models, then connect those lessons to actual Umicom Kernel channels, user services and Framework messaging. Preserve legacy publishing and all established public interfaces.

## Update 14 — System calls, IPC and message ownership

**Framework:** Add a read-only C23 `umicom-education ipc-trace --file` inspector for the explicit `UMIIPC1` teaching format. The inspector validates little-endian headers, one-based record ordinals, bounded payload lengths, sender/recipient identities, FIFO receive order and a 64-message pending limit. It rejects malformed input and leaves its report unchanged on failure. It does not use kernel IPC, map memory, grant rights or execute a syscall. No existing Framework message service is replaced.

**Curriculum:** Lessons 97–101 connect ordinary C function calls, RISC-V environment calls, protected user/kernel boundaries, copied payload ownership, service request checks, trace inspection and actual Umicom Kernel IPC source. A bounded-channel laboratory and service-dispatch laboratory remain single-threaded, hosted C23 simulations. RISC-V `ecall` Assembly is source-reading material, not a runnable Kernel ABI wrapper. Videos 30–31 and three source-editable diagrams accompany the lessons.

**Acceptance:** 20 native Framework CTest cases, two cases per new laboratory, no loss of any of the previous 158 navigation entries, preserved original *Islam: Blueprint for Life* volume, valid diagrams and a strict MkDocs build. Linux GCC/Clang and sanitizer tests do not replace Windows UCRT64 acceptance. The synthetic trace report does not constitute evidence of actual RISC-V Kernel execution or GitHub deployment.

**Next: Update 15 — Process scheduling, wake-ups and bounded service lifetimes.** Teach why a blocked task is not runnable, how a service avoids lost notifications, and how message handles remain valid or become stale. Link to the existing Kernel scheduler and blocking IPC rather than inventing another production queue.

## Update 15 — Process scheduling, blocked IPC and service lifetimes

**Framework:** Introduce a native read-only `umicom-education schedule-trace --file`
inspector for an explicitly versioned `UMISCH1` classroom format. The C23 parser
accepts at most 4,096 fixed-size records and 32 distinct task identities,
validates monotonic logical ticks, FIFO ready order, Running/Waiting transitions,
matching wait/wake/cancellation keys, and preserves the report after failed
validation. Two regression tests cover synthetic spaced paths, corrupt headers,
invalid state transitions and 20,000 deterministic one-byte mutations. This
teaching trace is not a real kernel trace, and it does not schedule threads.

**Curriculum:** Lessons 102–106 cover cooperative round-robin selection, blocked
receivers, lost-wake races, generation-tagged task handles, resource lifetime,
a bounded scheduler trace and the actual Umicom Kernel user scheduler/IPC source.
Two C23 laboratories demonstrate (1) a ready/waiting state machine and (2) a
service that composes the already-existing bounded-channel and scheduling labs.
Videos 32–33 and three editable technical diagrams accompany the lessons.

**Compatibility:** This update adds one Framework inspector and CLI command,
without replacing any existing Framework service or Umicom Kernel code. It
preserves previous educational chapters, video scripts and all ten original
*Islam: Blueprint for Life* navigation entries and manuscripts. Other-language
publishing infrastructure remains intact; the newly delivered programming
implementations use C23 only. CMake, MkDocs YAML, Markdown and SVG are retained
as necessary build and documentation formats.

**Acceptance:** 22 CTest cases in the standalone native Umicom Education project;
two cases each in the round-robin and blocking-IPC laboratories; strict C23
warnings and Clang sanitizer qualification; parseable MkDocs YAML, cumulative
navigation and diagram validation. Windows UCRT64, the complete historical
MkDocs publication and live GitHub Pages remain separate maintainer checks.

**Next: Update 16 — Timer-driven scheduling, bounded events and recovery.** Study
monotonic clocks, finite timeouts, event multiplexing, cancellation ownership,
privileged interrupt delivery and the real Umicom Kernel timer-service source.


## Update 16 — Monotonic deadlines, event outcomes and interrupt boundaries

**Framework:** Add `umicom-education timer-trace --file` with a native C23
read-only inspector for `UMITMR1` classroom records. A strict 16-byte header
and 32-byte records carry WAIT, SIGNAL, CANCEL and ADVANCE events. Each wait
has a unique identity/key, optional finite deadline and checked addition.
Monotonic ADVANCE settles due waits before subsequent signals, making the
exact-deadline tie deterministic. Input is bounded to 4,096 records and 32
identities. Parsing preserves caller reports on failure. The CTest pair
includes spaced paths, malicious record cases and 20,000 deterministic
single-byte mutations. This is neither real Kernel event evidence nor a timer
interrupt source.

**Curriculum:** Chapters 107–111 connect wall clocks versus monotonic counters,
deadline overflow, manual/auto-reset remembered events, lost-wake hazards,
single-owner timed service coordination, event-trace inspection and the real
Umicom Kernel RISC-V trap/scheduler/event source. The two laboratories are
(1) a standalone checked C23 logical timer and (2) a timed Notes service which
*reuses* the previously delivered scheduler/timer sources. Two complete video
narrations and three SVG diagrams support the material.

**Acceptance:** 24 Framework Education CTest cases; one monotonic deadline
laboratory case; three timed-service laboratory cases; GCC/Clang and sanitizer
qualification; zero removed navigation targets; original Islam book chapter
order preserved; valid SVG/XML; strict MkDocs build on the maintainer Windows
checkout and real GitHub Pages delivery remain separate qualification steps.
No new Python/C++/JavaScript program implementation is introduced in this
batch. Legacy tools, book manuscripts and existing public contracts remain.

**Next: Update 17 — Interrupt ownership, cancellation under failure and
safe service recovery.** Distinguish IRQ-level mechanism from serialised C23
policy, teach fault-safe cancellation and deterministic restoration of retained
state, and continue checking against the authoritative Umicom Kernel source.

## Update 17 — Interrupt ownership, cancellation and reviewed recovery

**Framework:** Introduce `umicom-education interrupt-trace --file`, a read-only native C23 validator for the fictional `UMIIRQ1` source-ownership record format. The 16-byte header and 32-byte records describe CLAIM, ARM, ENTER, ACK, RETURN, CANCEL, FAULT, RECOVER and RELEASE. The parser bounds source identities, records and file size, checks a nondecreasing logical clock, refuses owner or generation mismatch and preserves the caller's report after a malformed record. Fault review is a simulation, not machine-state restoration. Two CTest cases cover an authentic fixed fixture path with spaces, strict byte validation, refused state transitions and 20,000 deterministic single-byte mutations. No real Kernel CSR or source is touched.

**Curriculum:** Chapters 112–116 explain hardware interrupts, critical-section nesting, source lease ownership, acknowledgement versus cancellation, explicit service recovery, native binary trace validation and the actual `kernel/interrupts.c`, `kernel/trap_guard.c` and `arch/riscv64/trap.S` source. Two C23 laboratories model source-lease contracts and compose them into a fictional Notes service with an in-memory checkpoint. The second laboratory reuses the same source implementation without copying it. Video episodes 36–37 and three editable SVG diagrams accompany the lessons.

**Acceptance:** 26 Framework Education CTest cases, two CTest cases per new laboratory, GCC C23 and Clang ASan/UBSan qualification, preserved existing navigation and Islam volume manuscripts, validated SVG diagrams and local reviewer build of the complete MkDocs website. Linux acceptance does not imply Windows UCRT64 or QEMU acceptance. No Python/C++/JavaScript implementation code is added by this update; existing publishing infrastructure and other-language educational material remain intact.

**Next: Update 18 — Interrupt diagnostics, driver lifetimes and retained evidence.** Extend learning into reviewable stop/restart diagnostics, bounded service snapshots and safely published device events. The native educational models must stay distinct from the authoritative Kernel and Framework services.

## Update 18 — Driver lifetimes, diagnostics and reviewed evidence

**Framework:** Add `umicom-education evidence-trace --file PATH`, a read-only
C23 inspector of a 24-byte `UMIEVD1` header and bounded 80-byte records.
Each record's metadata is linked to the previous digest through Framework's
existing SHA-256 implementation. Driver slots, owner identity, increasing
generations, ordered observations, checkpoints and stop/release transitions
are checked before a complete report is published. Hash chaining detects
changed bytes but does not authenticate the producer, and a recovery record
is not proof of physical repair. Two focused CTest cases check the parser
and CLI fixture, with 10,000 repeatable damaged-input mutations.

**Curriculum:** Chapters 117–121 teach ordered interrupt diagnostics,
composing a driver lifetime from the earlier `service-recovery` and
`interrupt-ownership` libraries, fixed-capacity diagnostic rings,
SHA-256-linked classroom traces and the authoritative C23/Assembly source
of Umicom Kernel. Videos 38–39 and three SVG diagrams accompany the new
lessons. Existing books, historical manuscripts, Python-based MkDocs and
other-language chapters remain untouched. All new executable implementation
code is C23; CMake remains the build-system language.

**Acceptance:** 28 standalone Framework Education tests, two new driver
tests plus the two inherited service-recovery tests, two diagnostic-ring
tests, GCC and Clang ASan/UBSan qualification, preserved prior site
navigation and Islam chapters, valid SVGs, and Windows UCRT64/MkDocs
qualification by the maintainer. No existing code or configuration lines
are removed or disabled by this update.

**Next: Update 19 — Device I/O, driver request lifetimes and bounded
completion queues.** Connect checked device requests to cancellation,
completion and explicit resource release without duplicating authoritative
Umicom Kernel device services.


## Update 19 — Device I/O request lifetimes and bounded completions

**Framework:** Extend the existing `umicom-education` command with
`device-io-trace --file PATH`. The new standalone C23 inspector reads a bounded
`UMIDIO1` binary teaching format (24-byte header and 40-byte records). It
validates device slot generations, owner identities, increasing request IDs,
accepted transfer lengths, requested versus acknowledged cancellation, FIFO
completion collection and quiescent device release. It refuses completion
queue overflow without reporting partial success. Two registered CTest cases
produce a deterministic 27-record fixture and exercise the independent CLI.
The parser test checks output preservation on refusal and 20,000 deterministic
record mutations. This is not a privileged Kernel/device trace.

**Curriculum:** Chapters 122–126 teach the request lifecycle, the copied FIFO
completion queue, cancellation and completion races, controlled driver stop,
native C23 trace inspection and real Umicom Kernel VirtIO block ownership.
The two C23 laboratories are built from a single shared completion queue
source: the request-lifecycle lab consumes the queue by CMake composition.
Episodes 40–41 and three editable SVG diagrams accompany the lessons.

**Acceptance:** Prior 28 Framework Education CTest cases remain registered,
plus two new device-I/O cases. Each new C23 laboratory has two focused tests;
they must pass under GCC and Clang sanitizers. Windows UCRT64 and the real
MkDocs website still require maintainer qualification. No historical books,
Islam volume manuscripts, public APIs or prior lesson navigation are removed.

**Next: Update 20 — Device discovery, transport negotiation and DMA ownership.**
Teach how the device tree describes available hardware, why an address alone
is not an MMIO capability, how drivers negotiate safe transport features, and
when a DMA-capable device may still own a buffer. Reference the actual
Umicom Kernel hardware catalogue and VirtIO implementation without copying
privileged production mechanisms into the classroom laboratories.


## Update 20 — Device discovery, MMIO and VirtIO (Bits2Banking only)

**Curriculum:** Chapters 127–131 cover FDT firmware descriptions, checked big-endian structure parsing, memory-mapped I/O and feature negotiation, DMA-buffer ownership, VirtIO split queues and the corresponding authoritative Umicom Kernel source. Episodes 42–43 provide complete demonstrations. Three editable SVG diagrams connect firmware description to driver admission and copied-buffer lifetimes.

**Native practice:** The `device-tree-inspector` standalone C23 laboratory inspects an explicitly bounded synthetic FDT image and rejects malformed header, reservations and structure input. The `virtqueue-lifetime` standalone C23 laboratory simulates descriptor submission, FIFO completion, generation-tagged tokens, cancellation, reset and buffer retention. Both use CMake and CTest and contain no privileged device access.

**Repository boundary:** This update changes **only Umicom-Bits2Banking**. Umicom Framework, Umicom Applications, Umicom OS and Umicom Kernel remain read-only educational references. No new commands, APIs, modules or build targets are added to any of those repositories.

**Acceptance:** The four new CTest checks must pass on the contributor's Windows UCRT64 toolchain. Compiler warnings, malformed input and negative cases are part of the curriculum. Existing chapters 1–126 and the Islam: Blueprint for Life volume remain navigable. The complete MkDocs build is a separate acceptance step.

**Next: Update 21 — Persistent storage, filesystem structures and durable publication.** Examine sectors, filesystem metadata, ordered writes, flush, journal concepts, retention and recovery, using the current Umicom Kernel filesystem/storage documentation as a source. Continue with C23 and Assembly where appropriate; make no changes outside Bits2Banking unless explicitly authorised.


## Update 21 — Filesystems, durable writes and C23 recovery laboratories

**Delivery scope:** Bits2Banking educational repository only. No source changes to Umicom Framework, Umicom Applications, Umicom Kernel or Umicom OS.

Five new chapters (132–136) connect the preceding device I/O course to block sectors, VFS path ownership, filesystem metadata, ordered writes, flush boundaries and Notes recovery. The two independently configurable C23 laboratories are `writeback-sector-store` and `journalled-notes`. The latter composes the former's `block_store.c` as a library, rather than duplicating an existing storage implementation. Four new editable SVG illustrations and video scripts 44–45 accompany the material.

**Acceptance gates:** Both CMake projects configure with C23, build with GCC and Clang, pass their registered CTests, and pass a sanitizer build where the toolchain supports it. The Markdown links and SVG syntax are checked, and no previous MkDocs navigation item is removed. Validate the complete site using the repository's existing MkDocs installation before publication. This batch neither claims real power-failure durability nor changes a Kernel production storage service.

**Next planned milestone — Update 22:** Continue into FAT16 structures, sector allocation, safe directory lookup, storage format integrity and read-only filesystem inspection, with a standalone C23 image-reader laboratory before any mutation facility. The Kernel's VFS and FAT16 source remain references, not modification targets.
