# Major Update 37 — Technical overview and educational architecture

## Why this batch changes direction

Updates 30–36 expanded professional Git and C23 build/verification engineering. Learners new to computers may not yet know how to launch PowerShell, recognise Windows PowerShell 5.1, navigate a folder, install Git, sign in to GitHub, or distinguish a Git commit from a push. Update 37 supplies a **complete preliminary foundation** without discarding any advanced material. The existing numbering continues: Chapters **264–283**, video Episodes **90–94**.

## Curriculum design

- **Unit 1 (264–266):** recognise the terminal/shell distinction; install PowerShell 7, Git, GitHub CLI and an editor; practise only under the learner's own home directory.
- **Unit 2 (267–271):** system administration through read-only Windows queries: CPU, memory, disks, processes, services, permissions and DNS; compare Linux terminals.
- **Unit 3 (272–275):** Git identity versus GitHub authentication, local commits, staging, private remote publication, cloning and contributor permissions.
- **Unit 4 (276–279):** approved MSYS2 UCRT64 C23 toolchain, a small real Notes model, CMake/Ninja/CTest, first-line failure diagnosis and a complete capstone.
- **Optional Units 5–6 (280–283):** use native Umicom Framework repository verification and build automation; distinguish plans from executed tests and controlled release evidence.

## Native code placement

`labs/native/contributor-notes/` contains only C23 source and CMake metadata. The small Notes type is a **bounded in-memory classroom model**, not an application Framework replacement. It neither touches Git nor persists bank data. `framework_planner_example.c` is an **optional consumer** of the installed Umicom Framework `Umicom::build` target. It uses the actual `umi_build_automation_*` API without copying implementation source or inventing a second production planner. The optional example is never enabled by default and needs compatible installed SDK testing on the host.

## Explicit exclusion policy

No `.py`, `.ps1`, JavaScript, or other new scripting-language implementation files. Existing MkDocs/Python dependencies remain outside the delivered implementation, are not rewritten and may be invoked interactively to validate the existing website. No automatic Git push, Git reset, secret storage, privileged process operations, or unexpected filesystem mutations occur in native code.

## Direct-to-learner offline material

`UPDATE_37_BEGINNER_COURSE_OFFLINE.html` embeds the complete numbered learning sequence, five vector diagrams and the supplied search screenshot, with responsive styling and no runtime JavaScript. This is an independently viewable handout. The canonical educational source remains Markdown under `content/lessons`, and changes should be made to that source rather than editing the generated HTML edition. The same HTML is also provided as a separate direct download for educators.

## Safety and disclosure

User input for examples is only learner-chosen Git author data or local Notes text, never passwords, tokens or account recovery codes. The lesson about `gh auth login` uses GitHub's existing browser flow. Network diagnostics use publicly named hosts without requesting port scans of third-party networks. Administrative inspection commands are read-only. The `Remove-Item` example explicitly includes `-WhatIf`.

## Curriculum progression evidence

The beginner capstone grades shell/file operations, local/remote Git, native C23 build verification, and safety/communication separately. A short evidence record is more useful than a green badge if the learner's actual toolchain is unavailable. The optional advanced chapters reinforce the same distinction at Framework/OS scale: a gitlink commit reference, a successful unit test and a published release are different kinds of evidence.

## References for instructors

Microsoft's PowerShell installation documentation; Windows Package Manager (Winget); official Git documentation; GitHub CLI `auth login` and `repo create` manuals; MSYS2 UCRT64 documentation; CMake Tutorial; and the existing Umicom Framework `include/umicom/build/automation.h` / `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`. These are referenced in the landing page and corresponding lessons; use current official documentation when installations or package behaviour change.
