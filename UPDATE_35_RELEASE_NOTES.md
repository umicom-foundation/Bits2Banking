# Bits2Banking — Major Update 35: release notes

**Subject:** Native Framework VCS reuse, build diagnostics and C23 evidence  
**Author:** Sammy Hegab · Umicom Foundation  
**Date:** 13 October 2026 · **Release type:** additive educational ZIP, not a production binary release

## Contents

- **Chapters 240–251:** twelve sequenced lessons covering Framework VCS API use, working-tree/gitlink identity, compiler diagnostics, CMake/Ninja/CTest stages, complete source revision identity, bounded owned C23 snapshots, duplicate-safe comparison, dropped/stale/test evidence, real failure investigation, SDK reuse and a multi-repository capstone.
- **Episodes 82–85:** four narration and demonstration scripts with genuine Umicom-focused commands and safe boundaries.
- **Five original SVG illustrations:** Framework VCS ownership, compiler-diagnostic pipeline, snapshot lifecycle, multiset comparison and Framework-to-OS publication sequence.
- **C23 source lab `labs/native/build-evidence`:** fixed-capacity owned evidence, two complete snapshot workflows, reproducible named tests and demo.
- **Optional Framework adapter:** links existing imported `Umicom::vcs` and `Umicom::build` targets when a compatible Framework SDK is installed. No copying of Framework implementation.
- **Contributor references:** quick reference, instructor guide, learning path, navigation instructions, manifest and validation record.

## Change policy

- **No existing files replaced. No existing files deleted.**
- **No new Python or PowerShell scripts.** PowerShell is used solely as direct command instructions.
- The batch does not alter Umicom Framework, Applications, Kernel or OS.
- Real Git and diagnostic parsing remain owned by Umicom Framework; the native teaching model is intentionally read-only with respect to actual repositories.
- The original *Islam: Blueprint for Life* book and site navigation remain untouched. The additive navigation fragment requires review against the user's current complete `mkdocs.yml`.

## Verification status

The standalone C23 test suite was run in the available Linux build environment with GCC 14.2.0 and Clang 17 (AddressSanitizer/UndefinedBehaviorSanitizer). Both suites passed all **56 named tests**. SVG sources parsed and rendered. The final ZIP is separately reconstructed and checked as documented in `UPDATE_35_VALIDATION_REPORT.md`.

**Still not verified:** Windows UCRT64 build, optional installed Framework SDK target, complete historical MkDocs website, GitHub Pages deployment and product-level Umicom OS/Studio/Bank acceptance. These are not included in the standalone success count.

## Next batch

Major Update 36 can progress to Framework-owned change impact analysis, native build/test history and product startup qualification, subject to verifying the installed Framework C ABI. New production functionality belongs in Framework, while Bits2Banking continues to own learning content and isolated pedagogical experiments.
