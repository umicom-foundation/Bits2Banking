# Major Update 30 — Validation report

**Date:** 12 October 2026 · **Evidence level:** local Linux execution plus source review; Windows and complete-site tests pending.

## Tests actually executed

| Gate | Environment | Result |
|---|---|---|
| Configure and compile C23 source (strict `-Werror`) | Debian Linux, GCC 14.2.0, Ninja 1.12.1, CMake 3.31.6 | PASS; no compiler diagnostics |
| CTest dispatch lab | GCC 14.2.0 | **9/9 PASS** |
| Configure and compile C23 source with ASan+UBSan | Linux, Clang 17.0.0 | PASS; no compiler diagnostics |
| CTest dispatch lab (ASan+UBSan) | Clang 17.0.0 | **9/9 PASS** |
| Deterministic mutation test | `dispatch.stress` in both suites | PASS, 80,000 operations per run and clean final drain |
| Negative tests | invalid arguments, full queues, stale generations, final states, ID exhaustion, rejection output stability | PASS |
| Demo | `btb-work-dispatch-demo` | PASS, three mock requests delivered |
| SVG document parsing | XML parser for seven new diagrams | PASS |
| Existing Update 29 CTest regression | GCC 14.2.0, standalone prior work-handoff lab | **5/5 PASS** |
| Existing completion-queue sources | Linked unchanged into new dispatcher | PASS as dependencies in both new test matrices |

## Important qualification notes

The native test environment did **not** contain the entire user's current Windows checkout. For compilation, the test workspace used the **unchanged** Update 29 work-handoff source and existing completion-queue sources retrieved for reference. Those dependency sources are **not delivered or overwritten** by the Update 30 ZIP. The new CMake project will require these directories to exist in the user's repository exactly as documented.

## Not yet run

- MSYS2 UCRT64 GCC compilation and CTest on Windows.
- MSYS2 Clang Windows compilation and relevant sanitizers.
- Complete earlier HTTP network/conditional-cache regression suites.
- Full MkDocs strict site build and historical-book navigation preservation test in the user's working repository.
- GitHub Pages publication/CI and branch/permission checks.
- Real multithreaded dispatch, socket I/O, application integration, production Framework task-service tests.

## Exit criteria

The update should not be described as fully platform-qualified until Windows native tests, reviewed navigation integration, strict site build and applicable earlier regressions pass. The educational dispatcher is **single-owner and synchronous**; even complete acceptance would not turn it into a real worker pool.

## Reproducibility

See `UPDATE_30_BUILD_TEST_AND_GIT.md` and `labs/native/work-dispatch/README.md`. Both supply direct PowerShell commands for local verification. No new `.py` or `.ps1` files are shipped.
