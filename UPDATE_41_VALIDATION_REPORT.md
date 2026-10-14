# Major Update 41 — Validation Report

**Scope:** New C23 educational maintenance-review module, previous training-lab regressions, source Markdown, SVGs, and standalone offline course. **This is not a production system certification.**

## Native build evidence

| Check | Result |
|---|---|
| GCC 14.2.0, ISO C23, CMake + Ninja configure | **Passed** |
| GCC compile with `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` for new targets | **Passed** |
| GCC CTest (Updates 39 + 40 + 41) | **57/57 passed** |
| Clang 17, ASan/UBSan configure/build | **Passed** |
| Clang ASan/UBSan CTest (Updates 39 + 40 + 41) | **57/57 passed** |
| New deterministic mutation case | **30,000 seeded iterations passed** |
| GCC static analysis of new maintenance-review implementation (`-fanalyzer`) | **No diagnostics** |
| Native demonstration | **Passed**: ROLLBACK_REQUIRED → RESTORED |

The complete suite contains 16 existing Update 39 cases, 16 existing Update 40 cases and 25 Update 41 cases (24 named scenarios plus the demonstration). The previously delivered library implementations are linked unchanged for test reconstruction. No user computer or remote repository was modified.

### Demonstration excerpt

```text
Fictional post-change decision: ROLLBACK_REQUIRED
State: RESTORED
Baseline capture: 100
After capture: 200
Restore capture: 300
```

These capture identifiers are fictional and supplied by the demonstration. They do **not** prove that a real service was restarted, upgraded, restored, authenticated or inspected.

## Documentation checks

- 12 new Stage 4 chapters numbered **49–60** with detailed step-by-step Windows/PowerShell and Linux exercises.
- 4 new engineering chapters numbered **296–299**.
- 5 new narration/video scripts numbered **111–115**.
- 7 original SVG illustrations parsed and rendered successfully.
- Markdown local image/document links and 26 MkDocs snippet targets checked within the new payload; none missing.
- Standalone offline HTML contains sequential Chapters **1–60**; text for previous **48/48** chapters is unchanged. New images are embedded using data URLs.
- The originally supplied Umicom application-creation guide remains untouched in its earlier source location; it is not republished under a new modified name.

## Acceptance gates not performed here

- **Windows UCRT64 build/test:** not run in this Linux environment. The Windows host instructions in `UPDATE_41_BUILD_TEST_AND_GIT.md` are supplied for verification.
- **Complete MkDocs `build --strict`: not run.** The required MkDocs package is absent from the validation runtime and existing repository navigation must be merged by the maintainer first.
- **Real OS service administration, package upgrades, firewall modifications, Git pushes, Framework SDK integration or recovery:** not performed. These operations are outside the scope of the isolated classroom simulation.

A full course/site acceptance requires reviewing all navigation, running the MkDocs publication build against the current repository and checking historical book routes after merging. Never replace a missing test result with a claimed pass.
