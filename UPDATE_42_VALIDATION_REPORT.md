# Bits2Banking Major Update 42 — Validation and acceptance report

**Prepared:** 14 October 2026  
**Project:** `Umicom-Bits2Banking` (educational additions only)  
**Reference platform:** Linux x86-64 container, GCC 14.2.0, Clang 17.0.0, CMake/CTest 3.31.6, Ninja.

## 1. Native C23 checks actually executed

The new `labs/native/deployment-rehearsal` project was configured against **the original source files from the locally supplied Update 39, Update 40 and Update 41 ZIP packages**. No previous library implementation was rewritten. The build reuses their CMake target hierarchy.

| Verification | Result |
|---|---|
| GCC C23 Debug configuration | PASS |
| GCC compilation with `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` | PASS, no diagnostics |
| GCC CTest | **79/79 passed** |
| Clang C23 Debug with AddressSanitizer + UndefinedBehaviorSanitizer | **79/79 passed** |
| New Update 42 named CTest cases | **22/22 passed**, including the standalone demonstration |
| Inherited Update 39–41 regression cases | **57/57 passed** |
| Deterministic review mutations | **30,000** invalid or incomplete stage transitions correctly blocked |
| GCC `-fanalyzer` on the new C23 implementation | No diagnostics |
| Clean ZIP reconstruction with locally supplied Updates 39–41 | **79/79 passed** |
| CMake private `--install` staging to a disposable test prefix | PASS |
| Execute relocated staged demonstration | PASS |

The staged demonstration output in the test environment was:

```text
Before staging: PENDING (missing=0x00000041)
After complete fictional evidence: QUALIFIED (missing=0x00000000)
Teaching only: no package installed; no real signature, service or system inspected.
```

**Interpretation:** Those decisions refer only to supplied fictional records. The classroom program does not compute hashes, install OS services, verify production packages or change an operating system.

## 2. Documentation and package checks

| Verification | Result |
|---|---|
| New System Administration chapters 61–72 | 12/12 present |
| New engineering chapters 300–303 | 4/4 present |
| New video scripts 116–120 | 5/5 present |
| Original source SVG diagrams | 7/7 parsed and rendered |
| Image references in new Markdown | 16 checked, none missing |
| Offline HTML course | 72 distinct numbered chapters |
| Previous offline course chapters 1–60 | **Exact HTML article content preserved byte-for-byte** |
| Offline illustrations | 64 embedded images, no external image dependency |
| New Python/PowerShell/Shell implementation scripts | **0** |
| New MkDocs navigation targets | **26/26 exist** in the ZIP |
| Prior repository files replaced or deleted | **0** |

Package SHA-256 values and a complete file list are written to `UPDATE_42_FILE_MANIFEST_SHA256.txt`. The external checksum text verifies the final ZIP.

## 3. Checks not executed or not claimed

- **Windows UCRT64 compile/CTest:** NOT RUN in this Linux environment. Complete on the user's Windows host.
- **Complete repository MkDocs `build --strict`:** NOT RUN. The full website tree and publishing environment are not part of this incremental ZIP; merge the navigation snippet and run the existing site pipeline first.
- **Actual Umicom OS RISC-V QEMU guest boot:** NOT RUN; no Kernel or OS image has been modified.
- **Real package signature, code signing, installed-runtime DLL closure, Windows desktop icon start or Linux systemd service start:** NOT RUN.
- **Production Umicom Framework SDK integration:** NOT RUN; the teaching library is not promoted into Framework.
- **Human change approval or operational rollback:** NOT PERFORMED. All identity and lifecycle data are fictional.

## 4. Acceptance checklist on Windows

1. Confirm Updates 39–41 are merged in the Bits2Banking working directory.
2. Review new files with Beyond Compare and merge additions only.
3. Configure and compile the new C23 laboratory using UCRT64 GCC.
4. Run CTest and record the **actual** number of passed, failed, skipped and Not Run cases.
5. Run the demo. If desired, install to a reviewed **private** practice prefix and launch from there.
6. Check the MkDocs navigation snippet against the current `mkdocs.yml` while retaining prior books.
7. Run `mkdocs build --strict` in the existing publishing environment.
8. Inspect `git diff --cached --check`, `git diff --cached --stat` and the staged diff before committing and pushing only Bits2Banking.

**Status:** The reference Linux laboratory and course artifact checks passed. Full Windows and website publication acceptance remain open.
