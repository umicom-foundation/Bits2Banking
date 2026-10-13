# Major Update 36 — Release notes

**Title:** Change Impact, Framework VCS Reuse, Native Testing and Build Recovery  
**Repository scope:** `Umicom-Bits2Banking` only  
**Delivery type:** merge-reviewed educational addition  
**Implementation:** C23; SVG diagrams; Markdown education and video scripts; CMake build metadata  
**No new `.py`, `.ps1`, `.js`, or C++ implementation files. No deletion of existing files.**

## What is new

- Chapters **252–263** extend the software-engineering track from Git and compiler diagnostics into dependency impact, verification gates, source/evidence identity, failure triage, crashes, submodule recovery, optional SDK reuse and a complete professional capstone.
- Episodes **86–89** include practical demonstrations and explicit safety boundaries.
- Six editable SVG diagrams illustrate dependency impact, Framework tool ownership, gate outcomes, build triage, failure atomicity and Framework/OS publication sequence.
- A standalone native C23 laboratory models at most twelve named modules and performs bounded reverse-dependency impact selection and verification-gate assessment. The optional SDK consumer reuses **the existing Framework Automated Build System planner (`UmiBuildAutomation`)**, Framework VCS and compiler diagnostics when the SDK is installed. The separate 12-node bitset example is instructional only and must not be migrated into an application as a competing planner.
- A new quick reference and instructor guide support independent study and contribution reviews.

## Tests and evidence

The isolated Linux development run completed **43/43 GCC CTest tests** and **43/43 Clang AddressSanitizer/UndefinedBehaviorSanitizer tests**, including a 50,000-iteration deterministic mutation case. Real Windows, full MkDocs site and optional Framework SDK acceptance remain outstanding.

## What is explicitly not delivered

This batch does **not** introduce production change-impact automation in Framework, a new Git client, a standalone compiler parser, executable PowerShell/Python automation, an OS boot validator, network workers, a release publisher or an installer. In particular, a passing educational assessment must not be described as authorisation to publish a production revision. No code from Umicom Framework, Applications, Kernel or OS is modified.

## Merge and commit

Extract into a separate `Bits2Banking-Update36-Review` folder, inspect with Beyond Compare, merge only reviewed additions, integrate the supplied **additive** navigation entries without removing historical books, build/test, and commit **Bits2Banking only** on `main` using `git add -A`, staged diff review, `git commit` and `git push origin main`.

**Next suggested phase:** target-level build evidence, reproducible regression selection and product-level launch acceptance, with reusable capabilities remaining in Umicom Framework.
