# Major Update 31 — Instructor guide and assessment rubric

**Target learner:** New contributor who understands source files, simple C23 and basic Git commits.
**Teaching philosophy:** Build accurate mental models with actual Umicom examples; do not hide complexity behind one-line recipes or introduce unnecessary scripting tools.

## Suggested four-session progression

| Session | Read | Practical evidence | Failure/recovery focus |
|---|---|---|---|
| 1. History and merge safety (75–90 min) | 191–192, 196 | Working-tree / index / remote comparison; staged diff reviewed | No destructive shortcut after conflict or rejected push |
| 2. Umicom Framework submodules (90 min) | 193–195, 200 | Compare OS gitlink to child HEAD; inspect detached/local/remote refs | Preserve tracked, untracked and unpublished work before update |
| 3. Forensics and publication (90 min) | 197–201 | Identify historical commit, deterministic test, evidence-led release manifest | Reflog expiry, bisect clean-worktree constraint, tag immutability |
| 4. Native model (90 min) | 202–203 | Compile C23 DAG, run 11 tests, explain detector limits | Distinguish a safe graph relation from a safe live Git operation |

## Instructor preparation

Use **disposable repositories**, test credentials, and fictional Notes or account files for exercises requiring writes. Do not demo forced checkout, hard reset, force push or destructive cleanup against Framework, OS, Kernel, Apps or Bits2Banking. The last step of a real publishing demonstration requires explicit authorisation and correct remote permissions. Snapshot the state of any practice repo before showing conflicts.

## Assessment rubric

A passing learner should correctly explain the following with evidence: (1) `git push origin main` pushes local `main` rather than detached HEAD; (2) `git fetch` is not `git pull`; (3) `git add -A` can stage deletions and unwanted artifacts; (4) a parent mode-160000 gitlink names a child commit; (5) `git stash --include-untracked` does not include ignored files or rescue detached-only commits; (6) a graph-level fast-forward does not imply remote authorisation; (7) a release claim must distinguish Linux/Windows and focused/full tests; (8) reusable repository tooling belongs in Umicom Framework.

For a stronger pass, require the learner to draw a divergent graph and a merge graph, correctly name all 11 native CTest cases, and explain one deliberately invalid case that preserves caller output. A useful capstone is a short incident note showing evidence before action, exact Git commands selected, and validation before Git commit/push.

## Do not accidentally teach these incorrect shortcuts

- Avoid `git push --force` or `git reset --hard` as a routine way to resolve a non-fast-forward rejection.
- Avoid suggesting that a clean worktree means all commits are published.
- Do not conflate a child Framework commit with the parent's gitlink commit.
- Avoid saying that stashing tracked changes also stashes untracked files unless `--include-untracked` was used.
- Avoid representing the native C23 graph demo as a real Git history validator or a substitute for Framework's VCS APIs.
- Do not invent Windows test results from successful Linux builds.

## Follow-on learning

Advanced instruction should next connect Framework's `UmiVcsWorkingTreeRead` and `umi_repository_submodule_lock` to a real client, with the existing process and repository contracts as the only source of truth. In Bits2Banking, keep executable demonstrations read-only and isolated until the Framework integration is separately approved and tested.
