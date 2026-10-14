# Major Update 39 — Navigation and non-destructive merge review

The existing MkDocs navigation includes original manuals, the *Islam: Blueprint for Life* volume and previous advanced lessons. **Do not replace `mkdocs.yml` with a partial file.**

1. Ensure the original System Administration Chapters 1–24 from Update 38 are present in the repository and, if you publish them, in your locally reviewed MkDocs navigation.
2. Open `UPDATE_39_MKDOCS_NAV_SNIPPET.yml` next to the current `mkdocs.yml` in Beyond Compare or your editor. It contains *only* the new Part II course and bridge-lesson navigation. Insert those sections beneath the existing `nav:` list, matching indentation exactly. The snippet is **not** a standalone MkDocs configuration.
3. Check that no labels or paths have been duplicated and that existing navigation entries are still present; do not remove older educational or faith material.
4. Verify local paths for all 12 course chapters, four engineering chapters, five video scripts and intermediate resources.
5. Run `mkdocs build --strict` using the publisher already installed for this project. If MkDocs fails, retain the complete log and fix the actual issue without deleting source. No new Python scripts are supplied.
6. Open the fully self-contained Update 39 offline HTML course to check the 36 sequential course chapters without installing MkDocs.

## Pre-existing guide preservation

The contributed *Creating a New Umicom Application* HTML remains at `content/assets/reference/umicom-new-project-beginner-guide-original.html`. Update 39 does not contain a replacement or migration of it. Chapter 21 and the intermediate course index link back to this original reference. Do not merge a substitute copy over that path.

## Command checks

From the Bits2Banking root, check that the new files exist before editing navigation:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Test-Path ".\content\lessons\08-system-administration\25-users-groups-and-real-identity.md"
Test-Path ".\content\lessons\08-system-administration\36-capstone-a-safe-umicom-support-runbook.md"
Test-Path ".\content\assets\reference\umicom-new-project-beginner-guide-original.html"
```

The answers should be True after merging Update 38 and Update 39. False for the third answer means the earlier contributed guide has not yet been merged; stop rather than invent or overwrite it.
