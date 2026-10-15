# Major Update 44 — MkDocs navigation and source preservation

**Do not replace the current `mkdocs.yml`.** The supplied `UPDATE_44_MKDOCS_NAV_SNIPPET.yml` is an **additive fragment** to merge under the existing `nav:` root, not a complete website configuration. It does not remove the historical *Islam: Blueprint for Life* book, finance volumes, earlier training videos or any chapter.

Use Beyond Compare to place the snippet alongside the **current local version** of `mkdocs.yml`. Append the Stage 7 chapters 85–96 and five companion references under the existing System Administration group; the native engineering chapters 308–311 under your engineering curriculum; and videos 126–130 under Videos. If those groups do not exist, create headings under the **existing** nav key (not another nav root). Avoid duplicate labels or paths.

All snippet paths are relative to `docs_dir: content`. Eight new SVG illustrations live under `content/assets/diagrams/`. The **96-chapter offline HTML** is in the repository as `UPDATE_44_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` and as a standalone download; it can be reviewed even before site navigation is updated.

A complete strict site build depends on the installed MkDocs environment and the current repository tree. A YAML fragment parse or link test is not a substitute. After merging, run the existing `python -m mkdocs build --strict` only as an invocation of the existing publishing tool—do not create new Python scripts.

## Review checklist

- [ ] Updates 39–43 exist, with their C23 source files preserved.
- [ ] All 84 previous System Administration chapter bodies remain unchanged.
- [ ] All 12 new chapters, four engineering chapters and five video scripts are present.
- [ ] All eight SVGs are present and render at desktop and mobile widths.
- [ ] No replaced or deleted source, licences, credits, documented APIs or comments.
- [ ] No `.ps1` or `.py` application implementation files introduced.
- [ ] Native C23 tests run, and failures/not-run checks are reported accurately.
- [ ] User's Git index has only reviewed new changes and the intentional navigation edit.

The original beginner guide on creating a new Umicom project remains included in the older update. Its proposed automatic module-discovery mechanism should not be represented as implemented unless current Framework source and executable acceptance prove that implementation.
