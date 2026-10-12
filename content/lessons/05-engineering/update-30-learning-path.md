# Major Update 30 — C23 work dispatch and professional Git workflows

**Bits to Banking · Umicom Foundation**  
**Audience:** contributors moving from foundational C23 and Git to maintainable Umicom development.  
**Implementation policy:** C23 and Assembly first; this increment uses C23 only. No new Python or PowerShell scripts.

## Learning pathway

This update has two complementary tracks. You can complete the **native work-dispatch sequence** first, then use the **version-control sequence** to record, test and safely publish the code. You can also start the Git sequence independently if you need to resolve a current checkout problem.

### Track A — C23 composition and result ownership (Chapters 177–181)

1. [177 — From request handoff to completion delivery](177-from-work-handoff-to-completion-delivery.md): accepted, processed and delivered are three different facts.
2. [178 — Compose existing C23 libraries](178-compose-existing-c23-libraries.md): reuse earlier queue contracts without copying their implementation.
3. [179 — Downstream capacity and backpressure](179-downstream-capacity-and-fair-scheduling.md): refuse work before losing a terminal notification.
4. [180 — Cancellation, identity and graceful drain](180-cancellation-identity-and-graceful-drain.md): prevent stale tokens from affecting reused storage.
5. [181 — Verification and Framework integration](181-verify-and-integrate-umicom-services.md): build, test and identify the safe production boundary.

**Native source:** `labs/native/work-dispatch` · **New named CTest cases:** 9 · **Video demonstrations:** [Episode 62](../../videos/scripts/62-from-handoff-to-owned-completion.md), [Episode 63](../../videos/scripts/63-when-the-completion-queue-is-full.md).

### Track B — Git, GitHub and source preservation (Chapters 182–190)

1. [182 — Working tree, staging area and HEAD](182-git-working-tree-index-and-history.md): understand where each edit lives.
2. [183 — Daily Umicom Git workflow](183-daily-umicom-git-workflow.md): inspect, test, stage, review, commit and push.
3. [184 — Remotes and non-fast-forward rejection](184-git-remotes-fetch-pull-and-non-fast-forward.md): distinguish fetch, pull and push.
4. [185 — Umicom submodules and detached HEAD](185-umicom-git-submodules-and-detached-head.md): understand OS's exact Framework commit reference.
5. [186 — Stash, preservation and recovery](186-stash-preserve-and-recover-work.md): protect both tracked and untracked changes without force checkout.
6. [187 — GitHub CLI setup and repository creation](187-github-cli-setup-and-repository-creation.md): install, authenticate and publish a practice repository.
7. [188 — History, diffs and provenance](188-read-history-diffs-and-provenance.md): investigate a regression by source revision.
8. [189 — Review and revert safely](189-review-recover-and-revert-safely.md): unstage without deletion and undo published errors without rewriting shared history.
9. [190 — Multi-repository capstone](190-umicom-git-capstone-and-cheat-sheet.md): Framework first, OS gitlink second, learning repository last, with test evidence.

**Reference:** [Git commands quick reference](git-safe-commands-quick-reference.md) · **Videos:** [Episode 64](../../videos/scripts/64-git-from-working-files-to-main.md), [Episode 65](../../videos/scripts/65-rescue-a-blocked-framework-submodule.md).

## Recommended 6-session teaching plan

| Session | Focus | Deliverable |
|---|---|---|
| 1 | Request lifecycle and composition (177–178) | Annotated diagram of owned, borrowed and copied bytes. |
| 2 | Backpressure, cancellation and verification (179–181) | Passing CTest result and a completed ownership worksheet. |
| 3 | Git working tree and daily workflow (182–183) | Two practice commits with reviewed staged patches. |
| 4 | Remote synchronisation and submodules (184–185) | Two ancestry diagrams: fast-forward and divergent. |
| 5 | Preservation, authentication and investigation (186–188) | Reviewed stash recovery and a source revision incident note. |
| 6 | Revert and capstone (189–190) | Dependency-order release checklist and a clean practice repository. |

## Important boundaries

The new dispatcher is a deterministic **teaching adapter**, not a production worker pool. It composes source already present in the repository. Production queue, task, messaging, VCS and lifecycle services belong in **Umicom Framework**. The Git learning commands must be used on a **practice repository** where indicated; do not experiment with destructive commands in the real Framework or Umicom OS checkout.

For build, source merge and navigation instructions, read `UPDATE_30_BUILD_TEST_AND_GIT.md` and `UPDATE_30_NAVIGATION_AND_REVIEW.md` at the repository root. A page is not fully published merely because its Markdown file exists: it must be included in the current site's navigation and pass the strict documentation build.
