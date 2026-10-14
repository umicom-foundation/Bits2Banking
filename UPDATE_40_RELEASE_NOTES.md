# Bits2Banking — Major Update 40 Release Notes

**Released for review:** 14 October 2026  
**Scope:** educational repository only. The existing Umicom Framework, Applications, Kernel and OS source trees are not modified.

## Delivered

- Twelve new `System Administration: From Zero` lessons, Chapters **37–48**, continuing the existing 36 chapters.
- Four new engineering lessons, Chapters **292–295**.
- Five instructor-ready video scripts, Episodes **106–110**.
- Seven accessible original SVG diagrams.
- One C23 composition laboratory, `labs/native/service-readiness` (six complete repository files).
- Stage 3 index, glossary, workbook, instructor guide and safe-command reference.
- One standalone complete offline HTML course containing **all 48 chapters**, with previous 36 chapters retained and new diagrams embedded.
- Build/test/Git instructions, tested source list, independent navigation snippet, source and verification notes, and file hashes.

## Native validation

The C23 demonstration composes (not copies) the unchanged Update 39 observation library. GCC 14.2.0 and Clang 17 with ASan/UBSan passed **32/32** focused tests on the available Linux host: **16 new + 16 previous regression tests**. Cross-platform host testing and MkDocs full-site publication verification remain open.

## Source preservation

**Zero existing repository files deleted or replaced.** No `.py` or `.ps1` implementation script added; PowerShell remains only an interactive lesson/build/test/Git interface. CMake is declarative native build metadata. The supplied new-project guide from Update 38 is preserved in its existing location and referenced where relevant.

## Known prerequisites

Merge Update 39 first: the new laboratory refers to `labs/native/sysadmin-evidence`. The `mkdocs.yml` published navigation currently requires reviewed integration of previous additions. Use `UPDATE_40_NAVIGATION_AND_REVIEW.md` and do not replace the existing entire file.
