# Major Update 33 — Release notes

**Feature:** Advanced Git evidence and repository recovery lessons with native C23 teaching model.  
**Scope:** `Umicom-Bits2Banking` **only**. Framework, Studio, Trader, Bank, Umicom OS and Kernel remain unchanged.

## New material

- Chapters 216–227: 12 detailed lessons on Framework Git observation, structured status, reference identity, submodule gitlinks, preserving work, remote divergence, versioned C23 evidence, optional Framework adapter, reuse of the existing release gate, 100,000-transition verification and a complete Umicom OS capstone.
- Episodes 74–77: narrated demonstrations of Git evidence, detached HEAD recovery, C23 evidence lifecycle and OS gitlink qualification.
- Five new SVG diagrams, a learning-path index and a safe Git command reference.
- `labs/native/git-review-timeline`: C23 library, deterministic named tests, standalone demonstration, optional compile-only Framework header bridge and optional reuse of the existing Update 32 release gate source.

## Preservation rule

All delivered paths are additions. **No existing source, lessons, diagrams, navigation, scripts, comments, history or functionality are replaced or deleted.** The ZIP's top-level directory matches the established local folder name. Merge using Beyond Compare; do not mirror the partial package over an entire repository.

The package intentionally does **not** include a replacement `mkdocs.yml`. The current remote `mkdocs.yml` has navigation for earlier volumes, but previous Update 28–32 navigation may not all be merged. `UPDATE_33_NAVIGATION_AND_REVIEW.md` supplies safe additions and a checklist to preserve the original *Islam: Blueprint for Life* content.

## Build/test status

The self-contained C23 code and existing Update 32 gate composition have been exercised under GCC and Clang sanitizer builds in the provided development container. Consult `UPDATE_33_VALIDATION_REPORT.md` for exact observed results and unverified platform checks. No claims are made about a Windows UCRT64 run or a complete website publish.

## Git release policy

After local build, tests and review, commit **Bits2Banking only** to `main` with `git add -A`, `git diff --cached --check`, `git commit` and `git push origin main`. Framework/OS are not changed and must not be committed merely because their code is referenced in teaching material.
