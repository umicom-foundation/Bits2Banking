# Bits2Banking — Major Update 30 · Release notes

**Title:** C23 Work Dispatch and Advanced Git / Version-Control Workshops  
**Date:** 12 October 2026 · **Publisher:** Umicom Foundation  
**Primary language:** ISO C23 · **Assembly:** none required for this increment.

## Scope

A fully additive learning and laboratory update. No older source implementation is replaced, deleted or disabled. No Umicom Framework, Studio, Trader, Kernel or OS repositories are modified. The new executable code lives in `labs/native/work-dispatch` and is a deterministic **educational integration adapter**, not a production task scheduler.

The educational content continues at **Chapters 177–190**:

- **177–181:** Request ownership, library composition, completion notification, backpressure, cancellation, drainage, C23 testing and Framework integration boundary.
- **182–190:** Git fundamentals, status/diff/staging, internal direct-to-main workflow, remotes, fast-forward, non-fast-forward rejection, submodules, detached HEAD, stash, recovery, GitHub CLI, revision investigation and multi-repository release practice.
- **Reference:** `content/lessons/05-engineering/git-safe-commands-quick-reference.md`, organised by safety category.

Four educational videos continue the series as **Episodes 62–65**. Seven source-controlled, accessible SVG diagrams illustrate the two-queue composition and Git work/recovery flows.

## Native design

The new `BtbDispatch` composes unchanged source from `labs/native/work-handoff` (Update 29) and `labs/native/completion-queue` (an existing C23 lesson). Its contract deep-copies requests via the former, retains copied completions via the latter, associates a token generation with a monotonic request ID, and only recycles the work slot after consuming a terminal receipt.

**Deliberate limits:** single owner, synchronous Step, no sockets, no worker threads, no real banking or trading instructions, no cryptographic guarantee from the demonstration's FNV diagnostic digest.

## Code and source-preservation policy

- New executable code is C23 only; no Python (`.py`) or PowerShell (`.ps1`) script files are created.
- PowerShell appears in the educational text only as **interactive build/Git commands**.
- Existing project files, including historical scripts and their comments, remain untouched by this update. Any earlier policy-incompatible scripts must be reviewed separately rather than silently deleted.
- The reusable production responsibility remains with **Umicom Framework**; no speculative duplicate service is deployed into applications.
- No copy of the two already-existing native queue implementations is included in this ZIP.

## Publication boundary

The new Markdown files are additive. The existing `mkdocs.yml`, earlier course index and source roadmap are **not overwritten** because those files may have evolved; `UPDATE_30_NAVIGATION_AND_REVIEW.md` provides the exact reviewed insertion block for chapters **167–190** and Episodes **58–65**. This includes the missing navigation registrations for Updates 28 and 29. After merging, register the entries and run strict MkDocs verification; publication is not treated as complete until that passes.

## Validation

See `UPDATE_30_VALIDATION_REPORT.md` for tests actually executed on Linux GCC and Clang with sanitizers, alongside the remaining Windows and full-site acceptance requirements. The ZIP does not claim that Windows, full-repository or GitHub Pages builds have passed.
