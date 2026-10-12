# Bits2Banking — Major Update 28: Release Notes

**Subject:** Nonblocking Networking, Connection Timeouts and Graceful Shutdown in C23  
**Status:** Source batch for review and host qualification; no GitHub commit or publication performed.  
**Reference point:** `umicom-foundation/Bits2Banking` commit `6a30bcfea3240f64e8605770955d5f710f2c6036` (Update 27).

## Delivery summary

This update preserves the Update 27 HTTP server as the default. An explicitly selected `--nonblocking` mode adds a single-threaded readiness reactor to the same C23 laboratory. It controls at most eight accepted connections, uses bounded request and output memory, applies monotonic idle/overall connection deadlines and drains existing accepted connections after stop is requested. It composes the **existing** parser, routing, static-file, cache-validation and response-accounting contracts; no existing `tcp_server.c` or library implementation is replaced.

The teaching programme continues its existing scheme, numbering and location: Lessons **167–171**, Episodes **58–59** and three editable SVG diagrams. Source files have authorship, purpose, ownership and lifetime comments; names retain `Btb` UpperCamelCase public function style. The solution does not introduce a Python HTTP service, C++ implementation, TLS, public network interface or framework application dependency.

**Two full existing file replacements:** `main.c` and `CMakeLists.txt`. All other ZIP entries are additions. After merging, one checked append-only PowerShell helper adjusts the existing `mkdocs.yml`, roadmap and existing HTTP README without erasing earlier content. **No deleted files.**

## Expected test registration

- 16 inherited CTests, unchanged.
- 2 newly registered native C23 lifetime tests.
- 1 optional Python 3 standard-library integration driver exercising actual C23 sockets.

**Expected:** 18 CTests without Python, **19 CTests** with Python. This is a registered-test count, not a claim of a full Windows test pass.

## Current validation boundaries

GCC/Clang strict compilation of the new isolated C23 policy and test code passed. The C23 reactor passed Linux socket-level smoke tests using mock implementations of the existing HTTP contracts; this is valuable subsystem evidence, but **the complete existing repository was not available for direct compile/link in the packaging environment**. A full Windows UCRT64 build, all historical CTests, manual Ctrl+C and `mkdocs build --strict` remain explicit acceptance steps in `UPDATE_28_BUILD_TEST_AND_GIT.md` and `UPDATE_28_VALIDATION_REPORT.md`.

## Next planned increment

**Update 29 — Work ownership and bounded asynchronous handoff.** Develop a separately testable task-ownership model with clear cancellation and completion rules. Do not present the existing Update 27 admission model as a concurrent worker pool, and do not copy educational socket implementations into Umicom Framework.
