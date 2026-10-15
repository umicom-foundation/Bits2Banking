# Major Update 46 — navigation and preservation checklist

This is an **additive** documentation batch. All source code from previous batches stays in place. The website already has historical material and earlier user changes; do not overwrite your entire `mkdocs.yml` with a short generated file.

## What to add

1. Open the current local `C:\umicom\Umicom-Bits2Banking\mkdocs.yml` in your editor or Beyond Compare.
2. Open `UPDATE_46_MKDOCS_NAV_SNIPPET.yml` from this package.
3. It contains a complete standalone `nav:` YAML mapping for easy syntax review. Copy only its **indented child groups** into your existing `nav:` group list. **Do not create a second `nav:` root key.**
4. Ensure the Stage 1–8 items from Updates 38–45 have been merged before presenting Stage 9 as a complete course. Earlier Git/C23 batch navigation may also need separate review.
5. Preserve the complete original *Islam: Blueprint for Life* and all previous books, video scripts and previously authored lesson links.
6. Confirm every new chapter, video and Stage 9 reference path exists under `content/`.
7. Run the site's existing `mkdocs build --strict` (see `UPDATE_46_BUILD_TEST_AND_GIT.md`) and resolve any errors before committing a publication change.

## What was preserved

The Update 45 offline HTML was extended with the 12 new chapters and Stage 9 references while keeping the older 108 chapter articles and their embedded diagrams intact. The original Umicom New Project Beginner Guide remains a separate, unmodified document. Older C23 labs are linked through their original sources and targets, not copied or reimplemented.

## Verify publication without guessed results

A successful YAML syntax parse is **not** equivalent to a strict MkDocs build. A strict build is not proof that a GitHub Pages deployment completed. Windows UCRT64 compilation and tests must also be checked separately on a Windows host. Log any gate that you did not run as **Not Run**, not Passed.
