# Bits2Banking — Major Update 35 validation report

**Authoring environment:** Linux x86-64, 13 October 2026  
**Scope:** New independent `labs/native/build-evidence` C23 library, tests, Markdown, SVG and additive ZIP.

## Native code: completed gates

| Gate | Result | Meaning |
|---|---|---|
| GCC 14.2.0 C23 compilation | **PASS** | Strict `-Wall -Wextra -Wpedantic -Wconversion -Wshadow` with no reported diagnostics |
| GCC 14.2.0 CTest | **56/56 PASS** | 55 named source cases + 1 executable demonstration |
| Clang 17 C23 with ASan/UBSan | **56/56 PASS** | Source tests and demonstration under instrumentation |
| GCC `-fanalyzer` source check | **PASS** | No reported diagnostics from the standalone `evidence.c` analysis |
| Deterministic mutation scenario | **50,000 operations PASS** | Owned status, stale identity and exact comparison invariants |
| SVG parsing and rendering | **5/5 PASS** | Original images parsed as XML and rendered to PNG for review |
| New Markdown relative links | **PASS** | All new cross-file and diagram targets resolved in the package; historic external index remains in the repository |
| Additive MkDocs YAML fragment | **PASS** | YAML parses and all 18 listed targets exist in the package |
| Source licence and language inventory | **PASS** | C23 executable source, CMake metadata, Markdown and SVG; no `.py`/`.ps1` added |
| Manifest integrity | **PASS** | All 39 payload-file SHA-256 values verified after extracting the ZIP |
| ZIP source reconstruction | **56/56 PASS** | Recompiled from the extracted archive with GCC 14.2.0 and executed its registered CTest cases |

The two compiler test results are scoped to the standalone default configuration with `BTB_ENABLE_FRAMEWORK_SDK=OFF`. They are not evidence that the source was built against a installed Framework SDK.

## Still required on the user's environment

| Gate | Current status | Required proof |
|---|---|---|
| Windows UCRT64 C23 build | **NOT RUN** | Configure, compile and CTest output from Windows |
| Optional Framework-backed target | **NOT RUN** | Compatible SDK found; `Umicom::vcs` and `Umicom::build` link; CTest and read-only demo |
| Complete MkDocs website build | **NOT RUN** | Strict MkDocs build after reviewed navigation merge |
| GitHub Pages publication | **NOT RUN** | Successful public deployment and navigation check |
| Full existing Bits2Banking regressions | **NOT RUN** | Existing labs and publishing checks after merging |
| Umicom Framework, OS, Studio and Bank product tests | **NOT RUN** | Separate source-specific integration test runs, not claimed here |

## Interpretation of the test suite

The suite includes legitimate negative tests. `assessment_dropped` passes by detecting discarded diagnostics; `assessment_stale_sha` passes by rejecting evidence for another commit; `compare_toolchain_refused` passes by reporting incomparable profiles. A test passing in those cases is **proof of refusal**, not permission to ignore the underlying problem.

The standalone teaching implementation does not run Git or a compiler. It accepts already-normalised fictional records and evaluates them. Its C23 evidence assessment is not a Framework production release gate or a replacement for product-level sign-off.

## Archive validation

The release ZIP contains only new files under `Umicom-Bits2Banking/`. Its `UPDATE_35_FILE_MANIFEST_SHA256.txt` records SHA-256 checksums for the other delivered files. Validate the ZIP itself with the separate `Umicom-Bits2Banking-Update-35-SHA256.txt` file and PowerShell `Get-FileHash` before merging. No code or test is deleted from the destination by the ZIP alone.

**Next:** Run the commands in `UPDATE_35_BUILD_TEST_AND_GIT.md` on Windows, then record the actual platform result and review `mkdocs.yml` before committing.
