# Bits2Banking — Major Update 37 release notes

**Title:** Absolute Beginner System Administration, PowerShell, Git, GitHub and C23 Onboarding  
**Project:** `Umicom-Bits2Banking` only  
**Author/project originator:** Sammy Hegab · Umicom Foundation  
**Delivery type:** additive review ZIP; **no existing repository files overwritten or deleted**.

## New content

- A structured absolute-beginner course with **20 chapters (264–283)**, covering launching PowerShell 7 from confusing Windows 11 search results, installing tools, files/directories, hardware, permissions, processes, services, networking, Linux, Git/GitHub, native build and safe troubleshooting.
- **Five narrated video scripts (90–94)** with timed demonstrations and instructor notes.
- **Five SVG diagrams** covering shell choices, Git staging/commit/push, native C23 build, safe administration and Framework ownership.
- The **learner-provided Windows search screenshot**, unchanged and used solely to clarify launcher choices.
- A one-page command sheet, instructor guide, source baseline and manual reviewed navigation fragment.
- A **self-contained offline HTML edition** of the 20 lessons, with the supplied screenshot and five embedded SVGs. It opens locally in a browser without installing MkDocs or running JavaScript.
- Native C23 `contributor-notes` laboratory: in-memory Notes model, demonstration executable and **eight CTest registrations**. An optional Framework SDK consumer demonstrates actual reuse through `umi_build_automation_*`; this target is not part of the standalone default build.

## Boundaries

No `.py` or `.ps1` implementation files are added. PowerShell is taught as a shell and used for **interactive commands**. The existing repository's publishing infrastructure is preserved. No Framework, OS, Kernel or Applications source files are modified by this package. The Notes lab does not claim production durability, authentication or thread safety.

## Validation status

See `UPDATE_37_VALIDATION_REPORT.md` for actual compile/test results and outstanding host acceptance. Successful local Linux tests must not be mistaken for Windows UCRT64 or full MkDocs publication evidence. Before publishing, review the manifest and merge the new navigation without erasing previous entries.

## Next proposed update

Major Update 38 may extend the beginner system-administration track with backups, permissions, Windows and Linux services, controlled updates, GitHub pull requests and practical repository incident recovery; native exercises will reuse approved Framework services first.
