# Major Update 40 — Validation Report

**Umicom Foundation · 14 October 2026 · educational source delivery**

## What was tested

The C23 laboratory was built **against the unmodified Update 39 `sysadmin-evidence` source** extracted from the previous ZIP. The Update 40 native target links that library using CMake `add_subdirectory` and runs both sets of CTest registrations. This is a focused teaching build, not a complete Umicom Framework or OS build.

| Check | Environment | Result |
|---|---|---|
| CMake configuration and C23 compile | GCC 14.2.0, Ninja, Linux | **Passed** |
| New service-readiness tests | GCC CTest | **16/16 passed** |
| Prior Update 39 evidence regression | GCC CTest | **16/16 passed** |
| Integrated CTest total | GCC CTest | **32/32 passed** |
| C23 compilation with sanitizers | Clang 17.0.0, ASan/UBSan | **Passed** |
| New + prior CTest with sanitizers | Clang, serial run | **32/32 passed** |
| Deterministic mutation coverage | 50,000 varied evidence rounds | **Passed** |
| GCC static analyser and strict warnings | GCC 14, `-fanalyzer` and `-Werror` | **No diagnostics** |
| SVG syntax and render | lxml + CairoSVG | **7/7 passed** |
| New lesson image and Markdown links | Source-local checking | **59 links checked, 0 unresolved** |
| Standalone offline course | HTML parser | **48 chapter anchors verified** |
| ZIP reconstruction | Rebuilt extracted payload with unchanged Update 39 source | **32/32 passed** |
| ZIP payload and CRC integrity | SHA-256 manifest, ZIP CRC | **47/47 payload hashes passed; ZIP CRC valid** |

All `BTB_SERVICE_OK` results from evaluation mean that the classroom **evaluation operation** succeeded. They are not proof that every service was READY; BLOCKED and REVIEW may be correct results. None of the tests observe real services or use privileged OS operations.

## Intentionally not claimed

- Windows MSYS2 UCRT64 build and native tests: **NOT RUN** on the user's computer.
- Complete MkDocs strict build and GitHub Pages publication: **NOT RUN** in a configured website environment.
- Production Framework service supervision integration: **NOT IMPLEMENTED** by this educational batch.
- Real Windows Service Control Manager, systemd, networking or filesystem inspection by C23 code: **NOT IMPLEMENTED**.
- Live security, trading, bank, healthcare or other Umicom services: **NOT TESTED**.

These are explicit limitations, not hidden successes. After merging into the user's actual repository, use `UPDATE_40_BUILD_TEST_AND_GIT.md` and record real Windows outcomes.

## Review boundaries

- No current or previous repository files were removed or replaced by the partial ZIP.
- New native executable source is ISO C23; the earlier Update 39 library is consumed rather than copied.
- No new `.py`, `.ps1`, `.js` or other scripting implementation files are delivered.
- CMake is declarative build metadata; PowerShell/Bash commands inside lesson Markdown are interactive student instructions.
- The historical *Islam: Blueprint for Life* site navigation and original Umicom new-project guide were not edited.
- Offline complete-course HTML is a **new** reading artefact, preserving the previous 36 chapters and extending with 12 new chapters.

## Acceptance after the ZIP is merged

The owner should verify that Update 39 exists, the new C23 project builds and runs 32/32 tests under the chosen Windows toolchain, the reviewed website navigation preserves existing records and the MkDocs site passes its own strict publication checks. Commit to `main` only after the staged files are inspected.
