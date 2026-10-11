# Major Update 08 — Native C23 navigation audit and memory contracts

The update extends the Framework-owned `umicom-education` command with `audit --repo`, a **read-only C23 navigation-target preflight**. The public contract is `include/umicom/education/nav_audit.h` and the implementation is `src/education/nav_audit.c`. A dedicated CTest covers valid, missing, duplicated, unsafe, malformed and empty navigation fixtures. No existing `umicom-education` commands or source implementations are removed.

The learner-facing course adds five chapters (67–71), two independently buildable C23 laboratories, and two video scripts. The arena laboratory introduces temporary memory regions and checked alignment. The bounded ledger-line laboratory demonstrates exact-byte parsing, integer overflow checks, failure-atomic output and a deterministic 20,000-case mutation harness.

The update retains the original *Islam: Blueprint for Life* navigation and the other published lessons. The canonical Framework source remains the authority for reusable education-tool functionality. The new code introduces no Python, JavaScript or other non-C executable implementation files. Markdown, CMake and YAML remain necessary inputs for the existing publishing and build systems.

## Boundaries

The native audit is an early source check, not a complete YAML parser. Run a strict MkDocs build to validate and render the complete site. The new financial records are fictional teaching inputs, not a live banking protocol. The arena is a training allocator, not a replacement for Umicom Framework's general allocator abstraction.

## Test before publishing

From `C:\umicom\Umicom-Applications`, configure, build and run CTest for `framework/tools/umicom-education`. Expect eight tests, including `framework.education.navigation_audit`. Run the two native lab builds and their tests separately. In `C:\umicom\Umicom-Bits2Banking`, run the native audit followed by a strict MkDocs build. Open the rendered site to check the ten historical Islam chapters, new chapters, and videos before committing.

Repository changes should be reviewed as complete files. Publish Framework first, Bits2Banking second and the Umicom Applications parent submodule revision last. Do not stage unrelated application-submodule updates.
