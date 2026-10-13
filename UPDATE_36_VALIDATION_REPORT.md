# Major Update 36 — Verification results and outstanding acceptance

**Project:** Bits2Banking · **Date:** 13 October 2026  
**Scope of validation:** New, isolated C23 educational change-impact lab and supplied documentation/diagrams.  
**Repository scope:** No Framework, Applications, Kernel or OS files have been modified.

## Tests actually executed

| Check | Environment | Observed result |
|---|---|---|
| Configure and compile | GCC 14.2.0, ISO C23, Ninja | Passed, no compile warnings reported |
| Native CTest | GCC 14.2.0 | **43/43 passed** |
| Configure and compile | Clang 17, ISO C23, ASan/UBSan | Passed, no compile warnings reported |
| Native CTest | Clang 17, ASan/UBSan | **43/43 passed** |
| Deterministic mutation case | Both test runs | 50,000 plan/evaluation iterations in each run, passed |
| Static analysis | GCC 14.2.0 `-fanalyzer` on `impact.c` | Exit 0, no diagnostics |
| C23 demonstration | GCC build | Passed: fictional OS boot not-run gate correctly blocked |
| SVG validation | 6 native `.svg` sources | All six XML documents parsed, rendered to PNG for inspection |
| Documentation source links | Local Markdown relative links | No unresolved relative Markdown links found in package |
| Additive MkDocs navigation | 18 new lesson/video/path entries | All 18 targets exist in payload |
| No new implementation scripts | Payload extension inventory | No `.py`, `.ps1`, `.js`, `.sh` or other script implementation files |

These results refer to this **educational laboratory**, not the entire Umicom Framework, applications or operating system. The new source is C23 with CMake metadata; a separate optional consumer demonstrates real Framework API reuse only when a compatible installed SDK is provided.

## Native test coverage

The 43 registrations include 42 focused cases and one demonstration. They test empty and corrupted graph input; invalid names and gate masks; duplicate nodes/edges; capacity limits; dependency cycles; full 40/64-character SHA syntax; invalid, empty and unknown changed-module masks; transitive impact; output preservation on errors; coherent passed/failed/not-run/missing states; stale source revisions; dropped diagnostics; incomplete capture; unreviewed source; overlapping evidence masks; a 50,000-iteration deterministic mutation sequence; and an end-to-end fictional demonstration.

A passing negative case means that a dangerous state was **correctly refused**. It does not mean the test accepted invalid or misleading evidence. The simulation's final zero-reasons result means **suitable for human review only**, never authorisation to publish, trade or deploy.

## Outstanding acceptance gates

| Gate | Status | Why |
|---|---|---|
| Windows 11 MSYS2 UCRT64 compilation | **Not run** | Requires the user's Windows host/toolchain |
| Windows UCRT64 CTest | **Not run** | Requires the user's Windows host/toolchain |
| Optional installed Framework SDK (`Umicom::vcs`, `Umicom::build`, `umi_build_automation_*`) | **Not run** | A compatible installed SDK is not available in the isolated validation environment |
| Full MkDocs website strict build | **Not run** | Requires the complete current repository and its existing publishing environment |
| GitHub Pages live publication | **Not run** | No website deployment was performed |
| Umicom Applications / Studio / Trader | **Not run** | No application or Framework repositories modified or built |
| Umicom OS image and QEMU boot | **Not run** | No OS image built or booted |
| Umicom Windows installer / desktop double-click launch | **Not run** | Requires installed product builds and runtime resources |

## Reuse and architectural review

Before producing this batch, public Umicom Framework APIs were reviewed, including `include/umicom/build/automation.h` and its native `UmiBuildAutomation` service, the `UmiVcsWorkingTree*` contracts, `umi_build_parse_diagnostic_line`, existing tests and the native build CLI adapter. **Actual Umicom source-change planning already belongs to Framework**, so this bundle does not introduce a production replacement. Its tiny bitset graph is for teaching first-principles algorithms only; the optional SDK consumer calls the actual native Framework planner.

## Reproducibility

The repository ZIP must be extracted into a review directory and merged without deleting or overwriting unrelated files. Build and run the exact commands in `UPDATE_36_BUILD_TEST_AND_GIT.md`. The file manifest contains a SHA-256 for every non-manifest file. The top-level archive SHA-256 is provided separately. Host verification gates remain the reader's responsibility.
