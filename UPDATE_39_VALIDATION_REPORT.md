# Major Update 39 — Validation report

**Validation environment:** available Linux development container on 14 October 2026.  
**GCC:** 14.2.0; C23 mode, strict `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror`.  
**Clang:** 17.0.0; C23 mode with AddressSanitizer and UndefinedBehaviorSanitizer.  
**CMake and Ninja:** standalone generated targets, no interpreter scripts introduced into the deliverable.

## Completed verification

| Test | Result |
|---|---|
| New `sysadmin-evidence` C23 GCC configure/build | PASS |
| New native GCC CTest | **16/16 PASS** |
| New Clang ASan/UBSan build | PASS |
| New Clang ASan/UBSan CTest | **16/16 PASS** |
| GCC `-fanalyzer -fsyntax-only` on model source | No diagnostics |
| New evidence demo | Prints REVIEW for fictional optional warning |
| Previous Update 38 `sysadmin-readonly-text` GCC CTest | **10/10 PASS** |
| Seven new SVG diagrams | Parsed and rendered successfully |
| Cumulative offline handbook | **36/36 chapters present**, local images embedded, no JavaScript scripts |
| MkDocs navigation snippet | Valid when nested under `nav:`; 2 sections |
| Source-preservation comparison | No existing Update 38 ZIP paths replaced by new payload |

The C23 test suite covers READY, optional warnings and failures, missing required evidence, required FAIL/NOT_RUN/WARNING, stale capture IDs, duplicate rejection, capacity rejection, invalid bounded labels, preserved outputs, zero capture ID, deterministic repetition (20,000 evaluations) and the demonstration.

## Not run / not proven

- **Windows MSYS2 UCRT64 GCC configure/build and CTest:** NOT RUN; owner acceptance required.
- **Complete MkDocs `build --strict` on the owner's current merged repository:** NOT RUN; navigation must be reviewed and merged first.
- **Remote publication to GitHub Pages:** NOT RUN.
- **Actual Windows/Linux system-management operations and end-to-end remote SSH:** NOT RUN; documentation instructions only, not automated qualification.
- **Production Umicom Framework API integration:** NOT RUN and not claimed. Educational model deliberately has no real service or Git side effects.

A classroom READY result for fictional input does not certify a real OS or application release. Exact compiler and test results should be rechecked after merging into the owner's Windows repository.
