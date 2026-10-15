# Major Update 45 — Navigation review and source preservation

**Do not replace your current `mkdocs.yml`.** The package contains an additive fragment `UPDATE_45_MKDOCS_NAV_SNIPPET.yml`, not a complete MkDocs configuration. The full repository may contain additional pages already committed after the previous batch. Review with Beyond Compare and append only the new sections below the existing `nav:` root key.

The snippet references 12 Stage 8 chapters, six Stage 8 reference files, four native engineering chapters and five video scripts. All paths are relative to `docs_dir: content`. New SVG diagrams are linked by the lessons. The current navigation for *Islam: Blueprint for Life*, the first seven system-administration stages and the previous engineering material must remain untouched.

**Offline reading:** `UPDATE_45_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` is a standalone 108-chapter edition. The previous 96 parsed chapter-body elements are preserved exactly in the generated copy; only top-level page metadata/navigation and appended Stage 8 materials are changed. The external downloadable HTML is byte-for-byte the same file.

**Repository scope:** Only add new files to `Umicom-Bits2Banking`. Do not migrate production functionality into educational labs, do not copy Framework implementation files, and do not remove previous source or educational credits. The original Umicom New Project Beginner Guide is already included in earlier course source at `content/assets/reference/umicom-new-project-beginner-guide-original.html` and must remain preserved.

After merging, run the native C23 CTest chain. If the existing MkDocs environment is available, invoke its strict build. Mark unavailable checks *Not Run* rather than assuming they passed. Use the standard Git commands in `UPDATE_45_BUILD_TEST_AND_GIT.md` only after checking `main` and the entire staged diff.
