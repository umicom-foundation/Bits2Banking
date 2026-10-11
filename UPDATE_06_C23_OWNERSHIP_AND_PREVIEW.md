# Bits2Banking Major Update 06 — C23 ownership, checked arithmetic and preview readiness

The existing Windows acceptance report shows **nine successful test executions across four CTest commands**: one focused renderer test, all six standalone native Education tests, and one test each for the Assembly and binary-record laboratories. No test in that report failed. Its final `serve` error was a missing generated `site/index.html`. The `doctor` output confirmed MkDocs was installed but did not render pages.

## Native development changes

The Framework-owned `umicom-education` application now accepts `serve --build [--python PATH]`. This explicitly invokes the already-qualified `UmicomEducationBuildSiteWithPython` service, then uses the existing C preview server. Ordinary `serve` still performs no build. An unsuccessful build never starts the server. The existing ability to serve an alternate generated directory remains unchanged and cannot be combined with `--build`.

A new CTest preflight checks the important failure and option boundaries. Existing renderer, publication, book and path tests are retained without replacing their implementations.

## New educational projects

The owned-notes laboratory introduces an opaque C23 model with dynamic text copies, one clear owner, checked array growth, stable note IDs, refused partial reads, and failure-atomic replacement. Its tests cover input deep copying, deletion, wrong IDs, oversized input, output buffers that are too small and the note-count limit.

The checked-money laboratory demonstrates exact fictional pence amounts, bounded arithmetic, revisions and a single-process, two-record transfer that refuses to modify either record if an overflow, underflow or revision failure occurs. It does not provide durable postings, authorisation or payment connectivity.

Both projects contain complete CMake builds, independent demonstrations, automated CTest checks and source-linked chapters. The programming lessons also introduce compiler warnings, ASan and UBSan, a static library, and how to build before starting a web preview.

## Files owned by this update

- Framework: full-file replacements of `tools/umicom-education/main.c`, `CMakeLists.txt` and `README.md`, plus one new CMake test script.
- Bits2Banking: two new C23 laboratories, new chapters 58–62, three editable SVG diagrams, two video scripts, navigation/index additions, and an updated roadmap.
- Original Islam manuscripts, historic BookForge scripts and existing GitHub Pages workflows are unchanged.

## Host acceptance requirements

On Windows UCRT64, reconfigure and rebuild `framework/tools/umicom-education`, run the seven registered native tests and build the two new laboratory projects. Run the complete MkDocs build using the repository `.venv` and then verify the preview at `http://127.0.0.1:8765/`. Compare the ZIP folders directly with the user's checkout before merging and pushing to `main`.

The Linux isolated validation confirms the relevant source and tests on Linux; it cannot establish that the user's Windows toolchain and complete historical MkDocs materials work until the commands are run on that host.
