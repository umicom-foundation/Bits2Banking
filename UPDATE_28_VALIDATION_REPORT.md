# Bits2Banking — Major Update 28: Validation Evidence and Remaining Gates

**Baseline:** Connected GitHub repository `umicom-foundation/Bits2Banking`, commit `6a30bcfea3240f64e8605770955d5f710f2c6036` (Major Update 27, 12 October 2026). The existing 16-test CMake registration and real public C headers were inspected before this additive batch was authored.

## Checks completed in this preparation environment

| Check | Observation | Limit |
|---|---|---|
| GCC C23 lifetime policy compilation | Passed with `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` | Only the new policy and its test source |
| Pure C23 deadline/transition test | Passed | Uses deterministic timestamps; no sockets |
| Pure C23 mutation test | Passed, including 30,000 iterations | Does not establish cross-platform OS behaviour |
| POSIX socket reactor strict syntax check | Passed against actual Update 27 public header shapes | Existing library function definitions were not re-linked |
| Actual C23 reactor run with test-only mock HTTP implementations | Passed slow/fast socket overlap, routes, static GET/HEAD, 304, 404, idle close and POSIX signal shutdown | **Mock contract implementations**, not original Update 27 implementations |
| Clang AddressSanitizer/UndefinedBehaviorSanitizer reactor test | Passed against the same test-only mock boundary setup | Does not prove the original HTTP library is sanitizer clean |
| SVG XML parsing | Passed, all three | Visual review still recommended |

The mock boundary source and validation binaries are **not included in the ZIP**. They were diagnostic scaffolding used because the container did not contain the full repository source tree. The reusable HTTP parser and static-file modules were left unchanged in the deliverable; their previous reported results are not reasserted as freshly tested results.

## Outstanding acceptance gates

1. Apply the ZIP onto your complete existing checkout and run GCC UCRT64 CMake configure/build.
2. Verify 18/18 CTests, or 19/19 when optional Python 3 integration is enabled, using the real Update 27 library implementations.
3. Run static-file, route, conditional request and socket overlap checks on Windows; verify Ctrl+C and a clean listening-port release manually.
4. Verify `mkdocs.yml` is valid following the checked additive navigation script and run `mkdocs build --strict` in your own project `.venv`.
5. Review the original Islam book entries and historically published site paths, and review the exact `git diff` before committing.

No claim of full upstream CI, complete MkDocs, Windows runtime or hosted GitHub publication is made until those gates have been observed. See `UPDATE_28_BUILD_TEST_AND_GIT.md` for reproducible commands.
