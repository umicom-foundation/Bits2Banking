# Major Update 41 — Navigation, merge and preservation review

**Scope:** `Umicom-Bits2Banking` additions only; no other Umicom repository is modified.

## Merge safely

1. Extract the ZIP into a separate review folder under `C:\umicom`.
2. Compare `Bits2Banking-Update41-Review\Umicom-Bits2Banking` (left) against the actual `Umicom-Bits2Banking` repository (right) with Beyond Compare.
3. Merge reviewed *new files* only. Do not mirror/delete the repository, replace a complete source directory, remove old comments or change unrelated files.
4. Confirm that Updates 39 and 40 are already merged. The C23 lab uses their existing headers/targets; never add copies of their implementation into this batch.
5. Review `UPDATE_41_MKDOCS_NAV_SNIPPET.yml`. Add its top-level `nav` children to your **current** `mkdocs.yml` in the appropriate location, preserving all previously published chapters, historic books and *Islam: Blueprint for Life*. The snippet is not a complete MkDocs configuration; it must not be used to replace one.
6. Check that every new Markdown page, illustration and video script can be opened and its links resolve. Test the actual MkDocs publication only after the merged navigation has been reviewed.

## Course identity

The dedicated course is **System Administration From Zero**. Update 41 continues its sequence with Chapters **49–60**, retaining the full previous 48 chapters in the separate offline HTML course. The old course is not modified in the repository. A **new** `UPDATE_41_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` is provided for convenience; it contains all 60 chapters and self-contained illustrations. The earlier, user-supplied new-project guide at `content/assets/reference/umicom-new-project-beginner-guide-original.html` remains in its original location from Update 38 and is not replaced here.

## Engineering curriculum

Update 41 adds Chapters **296–299** under `content/lessons/05-engineering/`. It introduces `labs/native/maintenance-review`, an offline composition that consumes the existing Update 39 and 40 models without duplicating their C23 source. Video scripts continue as Episodes **111–115**.

## Follow-up checks

Use the build/test instructions in `UPDATE_41_BUILD_TEST_AND_GIT.md`. Validate local links and `mkdocs build --strict` using the site's existing installed tools. **No new Python or PowerShell scripts are included**; a legacy MkDocs installation may depend on Python for website generation, which is separate from native implementation.

Do not label Windows UCRT64 or a complete published-site build as passed unless you ran it on that host and inspected the result. No action in this batch pushes to GitHub automatically.
