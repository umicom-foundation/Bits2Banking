# Major Update 38 — Validation and release gates

**Environment:** available Linux development runtime.  
**Native language:** ISO C23.  
**GCC:** Debian GCC 14.2.0, configured with CMake 3.31.6 and Ninja 1.12.1.  
**Clang:** 17.0.0 with AddressSanitizer and UndefinedBehaviorSanitizer.  
**Test suite:** 10 registered CTest cases: LF, CRLF, final fragment, empty file, binary refusal, capacity refusal, missing path, invalid parameters, failure-atomic output and 10,000 repeat calls.

## Completed validations

- GCC C23 configure/build: **passed** with `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`.
- GCC CTest: **10/10 passed**.
- Clang C23 ASan/UBSan configure/build: **passed** with the same diagnostic warnings and explicit sanitizers.
- Clang ASan/UBSan CTest: **10/10 passed**.
- Editable Markdown chapters: 24 standalone course + 4 engineering bridge chapters; navigation targets checked against packaged filenames.
- The supplied HTML guide is preserved byte-for-byte; its checksum is recorded separately.
- Offline HTML course is generated without scripts; static embedded illustrations and chapter anchors verified.

## Not yet verified in the owner's Windows environment

- MSYS2 UCRT64 GCC compilation and the 10 native CTests: **NOT RUN**.
- Complete MkDocs `build --strict` against the user's currently merged repository: **NOT RUN**.
- Actual publishing to GitHub Pages: **NOT RUN**.
- Windows shell and package-manager exercises on the learner's specific machine: **NOT RUN**.

Use the included PowerShell steps and report the actual outputs. A Linux passing result must never be represented as Windows acceptance evidence.
