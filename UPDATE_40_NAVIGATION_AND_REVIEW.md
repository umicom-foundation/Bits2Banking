# Major Update 40 — Website Navigation and Review

The current repository's `mkdocs.yml` contains historical *Islam: Blueprint for Life* lessons and many foundational chapters. Do **not** replace it with the partial navigation snippet in this package. The snippet in `UPDATE_40_MKDOCS_NAV_SNIPPET.yml` is a syntactically valid **top-level `nav` list fragment** and must be merged manually as a new topic block **under the existing `nav:` key**.

## Merge order

1. Compare the extracted package with `C:\umicom\Umicom-Bits2Banking` using Beyond Compare. Merge new files, not entire folders by mirror/delete.
2. Confirm Chapters 1–36 remain in `content/lessons/08-system-administration/` (Updates 38–39).
3. Confirm the native library `labs/native/sysadmin-evidence` exists (Update 39).
4. Open existing `mkdocs.yml`. Preserve the entire current navigation tree. Insert the new **System Administration Stage 3** block from the snippet. Avoid duplicate entries if earlier integration already added them.
5. Reconcile any previously unregistered Chapters 167–295 and Episodes 58–110 from earlier update nav snippets **separately**. The new excerpt does not imply those previous entries were already published.
6. Run the strict existing MkDocs build when its environment is available. If it is unavailable, report **NOT RUN** rather than asserting publication succeeded.

## New paths

- `content/lessons/08-system-administration/37-...` through `48-...` (12 complete chapters).
- `content/lessons/08-system-administration/advanced-*.md` and `safe-command-reference.md` (five supporting documents).
- `content/lessons/05-engineering/292-...` through `295-...` (four engineering chapters).
- `content/videos/scripts/106-...` through `110-...` (five scripts).
- `content/assets/diagrams/sysadmin-*-update40.svg` (seven diagrams).

The offline HTML course `UPDATE_40_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` is independent of MkDocs navigation and can be opened as a local file. It embeds its illustrations and retains the earlier 36 chapters. It is **not a replacement for the live website**.

## Link and spelling checks

New Markdown chapters reference existing source-relative lesson paths. Verify local links after merging prerequisite updates. Prior history and original contributor credits are preserved. Do not mechanically replace historical lesson prose, illustrations, authorship or documentation to make navigation shorter.
