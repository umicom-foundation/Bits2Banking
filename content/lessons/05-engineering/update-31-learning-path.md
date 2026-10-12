# Major Update 31 — Professional Git engineering and C23 commit-graph laboratory

**Bits to Banking · Umicom Foundation · Instructor and learner index**

This update follows Chapters 182–190 and preserves the earlier single-owner work handoff lessons. It adds professional, safe Git recovery practices for Umicom Framework, Umicom OS and multiple application repositories. The native C23 laboratory explains Git ancestry but does not operate on live Git repositories.

## Read in this order

1. [191 — Resolve conflicts without losing code](191-resolve-merge-conflicts-with-evidence.md)
2. [192 — Understand fetch, push and divergence](192-fetch-and-divergent-history.md)
3. [193 — Synchronise Framework submodules](193-umicom-framework-submodule-integration.md)
4. [194 — Distinguish detached HEAD from `main`](194-detached-head-and-push-identity.md)
5. [195 — Preserve and review stashes](195-stash-and-collision-safe-recovery.md)
6. [196 — Safely use `git add -A`, commit and push](196-audit-git-add-a-and-commit.md)
7. [197 — Investigate seemingly lost commits](197-reflog-and-lost-commit-recovery.md)
8. [198 — Bisect a native C23 regression](198-bisect-a-c23-regression.md)
9. [199 — Tags, release manifests and evidence](199-annotated-tags-and-release-evidence.md)
10. [200 — Coordinate Framework, Applications and OS](200-coordinate-umicom-repositories.md)
11. [201 — Review and approve contributions](201-github-reviews-and-approvals.md)
12. [202 — Build a Git ancestry graph in C23](202-model-git-ancestry-in-c23.md)
13. [203 — Test the native model and reuse Framework VCS](203-verify-git-graph-and-framework-contracts.md)

**Additional reference:** [Update 31 Git command quick reference](git-operations-quick-reference.md), the native C23 laboratory at `labs/native/git-history/README.md`, and the original [Git and contributions lessons](16-git.md).

## Minimum completion evidence

The learner should be able to explain why detached HEAD is normal in submodules, why `git push origin main` does not push a detached checkout, what `git add -A` stages, why `fetch` is not `pull`, what a Framework parent gitlink records, and what a fast-forward relationship means. The C23 tests must pass independently of Git or network availability.
