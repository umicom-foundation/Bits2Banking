# Major Update 45 — Validation and acceptance record

**Date:** 15 October 2026 · **Owner:** Umicom Foundation / Sammy Hegab  
**Scope:** new Update 45 source combined with unmodified prior Update 39–44 learning libraries.

| Check | Observed result | Interpretation |
|---|---|---|
| GCC 14.2.0, ISO C23/Ninja configure and build | **Passed** | All seven linked teaching layers configured and compiled |
| Strict new-target warnings `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` | **Passed** | No compiler diagnostics from new target source |
| GCC CTest complete dependency chain | **161/161 passed** | 131 prior regression cases + 30 Update 45 cases |
| Clang 17 ASan/UBSan full chain | **161/161 passed** | Cumulative teaching labs built with address/undefined-behaviour sanitizers |
| GCC `-fanalyzer` on new operations-review source | **No diagnostics** | Static-analysis scope is limited to new policy code |
| Deterministic negative mutations | **30,000 passed** | Twelve kinds of deliberately withheld/stale/mismatched review evidence |
| Failure-atomic output checks | **Passed** | Invalid init/attach/evaluate/cadence leaves caller destinations untouched |
| Upstream restored-only propagation | **Passed** | Earlier release restoration never becomes new-release success |
| MkDocs additive navigation syntax and file targets | **27/27 resolved** | 12 Stage 8 chapters, six references, four native chapters, five videos |
| Relative Markdown links in new material | **59 checked; none unresolved** | Local links within the new course and known prior content |
| Original SVG syntax + PNG render for visual review | **8/8 passed** | Original editable SVG diagrams; rendered previews are not shipped |
| Offline course chapter count | **108/108** | 12 new Stage 8 lessons appended |
| Earlier HTML chapter-body preservation | **96/96 verified unchanged** | The previous chapter elements were compared against the supplied Update 44 offline HTML |
| Added `.py` / `.ps1` source or other script implementation | **0** | Only C23 executable source; PowerShell commands appear as text in manuals |
| Native Windows UCRT64 build and CTest | **Not Run** | Must be verified on the user's Windows computer |
| Complete MkDocs site build (`--strict`) | **Not Run** | Requires merging current navigation and the original MkDocs environment |
| Live Framework/OS/Applications integration | **Not Run** | No production repositories were changed |

## Actual Linux build configuration

```
cmake -S labs/native/operational-resilience -B build-gcc -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build build-gcc --parallel 4
ctest --test-dir build-gcc --output-on-failure --parallel 4
```

Clang passed with `-fsanitize=address,undefined -fno-omit-frame-pointer -g`, matching flags on the executable link step. This verifies runtime safety only for executed paths and cannot prove the absence of every defect.

## Bounded and failure-atomic contracts verified

- `BtbOpsInit` retains existing destination on malformed policy or mismatched source identity.
- `BtbOpsAttach` refuses duplicate records, bad booleans, future timestamps and source mismatch without partial evidence writes.
- `BtbOpsEvaluate` refuses malformed input without rewriting the caller's previous decision; it separately checks missing/stale heartbeat, backup, restore exercise, response owner, alert routing, RPO, RTO and queue bound.
- `BtbOpsNextDue` refuses zero cadence or unsigned overflow without overwriting the previous due-time value.
- `BtbOpsEvaluate` calls the existing `BtbSecurityEvaluate`; it is not a duplicated implementation of the prior security review.

## Strict limits of conclusions

`REVIEWABLE` is **not** security authorisation, operational acceptance, proof of backup recoverability or successful live delivery. Test records are entirely fictional. No real scheduled tasks, live SSH servers, operating-system services, Git repositories, Windows ACLs, Linux permissions, deployment artifacts or backup datasets are read or modified by the native laboratory. Classroom logical timestamps must not be confused with production monotonic and UTC clock handling.

User-host Windows and publication checks remain open acceptance gates. Do not commit an integration claiming those checks have passed without recording their real results.
