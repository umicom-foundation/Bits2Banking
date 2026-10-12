# Major Update 31 — MkDocs navigation and review

**This is an additive navigation recipe, not an instruction to replace `mkdocs.yml` or remove older volumes.** The live GitHub `main` revision inspected while preparing this update still lists lessons up through Chapter 166 in its final engineering groups. Earlier Update 28–30 lesson files are present in the repository, but navigation registration remains a separate integration task. This file provides the **complete missing continuation for Chapters 167–203 and Episodes 58–69**.

## Where to insert

Open the real, current `C:\umicom\Umicom-Bits2Banking\mkdocs.yml` in Beyond Compare or your editor. Find the existing last group **`"HTTP caching, conditional requests and bounded admission"`**. Insert the following groups **after that entire group** and **before** `"Framework integration examples"`. If a previous merge already added any of them, compare and add only the missing entries. Never insert duplicates.

Do not move or remove the historical *Islam: Blueprint for Life* block, existing lessons, book references, custom branding or theme settings. The new HTML/MkDocs pages are Markdown manuscripts; no new Python renderer or script is supplied.

## Reviewed additive YAML snippet

```yaml
  - "Native nonblocking HTTP (Update 28)":
      - "167. Why a slow connection should not stop everyone else": lessons/05-engineering/167-why-nonblocking-io-matters.md
      - "168. Build a bounded `select()` reactor in C23": lessons/05-engineering/168-build-a-c23-select-reactor.md
      - "169. Connection deadlines and graceful server shutdown": lessons/05-engineering/169-monotonic-timeouts-and-graceful-shutdown.md
      - "170. Test a nonblocking web server rather than trusting a demo": lessons/05-engineering/170-test-and-diagnose-the-nonblocking-server.md
      - "171. Connect the nonblocking reactor to Umicom's service boundaries": lessons/05-engineering/171-connect-reactors-to-umicom-service-ownership.md
  - "C23 request handoff (Update 29)":
      - "Chapter 172 – Why request handoff needs explicit ownership": lessons/05-engineering/172-why-request-handoff-needs-ownership.md
      - "Chapter 173 – Bounded FIFO work and backpressure": lessons/05-engineering/173-bounded-fifo-work-and-backpressure.md
      - "Chapter 174 – Cancellation, generations and late completions": lessons/05-engineering/174-cancellation-generations-and-late-completions.md
      - "Chapter 175 – Quiescence and deterministic verification": lessons/05-engineering/175-quiescence-and-deterministic-tests.md
      - "Chapter 176 – From a teaching queue to Umicom Framework services": lessons/05-engineering/176-from-teaching-queue-to-umicom-framework.md
  - "C23 work dispatch (Update 30)":
      - "Chapter 177 – From request handoff to completion delivery": lessons/05-engineering/177-from-work-handoff-to-completion-delivery.md
      - "Chapter 178 – Compose existing C23 libraries instead of duplicating them": lessons/05-engineering/178-compose-existing-c23-libraries.md
      - "Chapter 179 – Downstream capacity, backpressure and bounded scheduling": lessons/05-engineering/179-downstream-capacity-and-fair-scheduling.md
      - "Chapter 180 – Cancellation, request identity and graceful drain": lessons/05-engineering/180-cancellation-identity-and-graceful-drain.md
      - "Chapter 181 – Verify the composed C23 service and plan Framework integration": lessons/05-engineering/181-verify-and-integrate-umicom-services.md
  - "Git and repository safety (Update 30)":
      - "Chapter 182 – Git's working tree, staging area and recorded history": lessons/05-engineering/182-git-working-tree-index-and-history.md
      - "Chapter 183 – The daily Umicom Git workflow: inspect, stage, commit, push": lessons/05-engineering/183-daily-umicom-git-workflow.md
      - "Chapter 184 – Git remotes, fetch, pull and non-fast-forward rejections": lessons/05-engineering/184-git-remotes-fetch-pull-and-non-fast-forward.md
      - "Chapter 185 – Git submodules and detached HEAD in Umicom OS": lessons/05-engineering/185-umicom-git-submodules-and-detached-head.md
      - "Chapter 186 – Preserve local changes, use stash and recover deliberately": lessons/05-engineering/186-stash-preserve-and-recover-work.md
      - "Chapter 187 – Install Git, authenticate GitHub and create repositories": lessons/05-engineering/187-github-cli-setup-and-repository-creation.md
      - "Chapter 188 – Read Git history, compare versions and investigate regressions": lessons/05-engineering/188-read-history-diffs-and-provenance.md
      - "Chapter 189 – Review staging, recover changes and revert safely": lessons/05-engineering/189-review-recover-and-revert-safely.md
      - "Chapter 190 – Git capstone: reproduce and publish a verified Umicom update": lessons/05-engineering/190-umicom-git-capstone-and-cheat-sheet.md
      - "Update 30 learning path": lessons/05-engineering/update-30-learning-path.md
      - "Update 30 Git command reference": lessons/05-engineering/git-safe-commands-quick-reference.md
  - "Professional Git and commit graphs (Update 31)":
      - "Chapter 191 – Resolve Git merge conflicts without losing source": lessons/05-engineering/191-resolve-merge-conflicts-with-evidence.md
      - "Chapter 192 – Fetch, compare and resolve divergent history safely": lessons/05-engineering/192-fetch-and-divergent-history.md
      - "Chapter 193 – Git submodules: update Umicom Framework without duplicating it": lessons/05-engineering/193-umicom-framework-submodule-integration.md
      - "Chapter 194 – Detached HEAD, local `main` and what `git push` really sends": lessons/05-engineering/194-detached-head-and-push-identity.md
      - "Chapter 195 – Preserve untracked files and restore stashes carefully": lessons/05-engineering/195-stash-and-collision-safe-recovery.md
      - "Chapter 196 – Audit `git add -A`, commit precisely and push to `main`": lessons/05-engineering/196-audit-git-add-a-and-commit.md
      - "Chapter 197 – Use the Git reflog to investigate apparently lost commits": lessons/05-engineering/197-reflog-and-lost-commit-recovery.md
      - "Chapter 198 – Locate a C23 regression with `git bisect`": lessons/05-engineering/198-bisect-a-c23-regression.md
      - "Chapter 199 – Release tags, immutable evidence and reproducible Umicom builds": lessons/05-engineering/199-annotated-tags-and-release-evidence.md
      - "Chapter 200 – Integrate Umicom Framework, Applications and OS in the correct order": lessons/05-engineering/200-coordinate-umicom-repositories.md
      - "Chapter 201 – GitHub reviews, permissions and contributor collaboration": lessons/05-engineering/201-github-reviews-and-approvals.md
      - "Chapter 202 – Model Git commit ancestry and fast-forward rules in C23": lessons/05-engineering/202-model-git-ancestry-in-c23.md
      - "Chapter 203 – Verify the C23 graph laboratory and reuse Framework VCS services": lessons/05-engineering/203-verify-git-graph-and-framework-contracts.md
      - "Update 31 learning path": lessons/05-engineering/update-31-learning-path.md
      - "Git operations quick reference": lessons/05-engineering/git-operations-quick-reference.md
  - "Engineering videos: HTTP, Git and C23 (58–69)":
      - "Episode 58 – Two Clients, One Nonblocking C23 Reactor": videos/scripts/58-two-clients-one-nonblocking-reactor.md
      - "Episode 59 – Deadlines and Graceful Shutdown in C23": videos/scripts/59-deadlines-and-graceful-http-shutdown.md
      - "Episode 60 – Who Owns a Request After Handoff": videos/scripts/60-who-owns-a-request-after-handoff.md
      - "Episode 61 – Cancellation, Late Completions and Shutdown": videos/scripts/61-cancellation-late-completions-and-shutdown.md
      - "Episode 62 – From Handoff to an Owned Completion": videos/scripts/62-from-handoff-to-owned-completion.md
      - "Episode 63 – When the Completion Queue Is Full": videos/scripts/63-when-the-completion-queue-is-full.md
      - "Episode 64 – Git: From Working Files to Reviewed `main`": videos/scripts/64-git-from-working-files-to-main.md
      - "Episode 65 – Rescue a Blocked Umicom Framework Submodule": videos/scripts/65-rescue-a-blocked-framework-submodule.md
      - "Episode 66 – Why a Git push was rejected": videos/scripts/66-why-git-push-was-rejected.md
      - "Episode 67 – Rescue a blocked Umicom Framework submodule": videos/scripts/67-rescue-a-blocked-umicom-submodule.md
      - "Episode 68 – From reviewed source to a reproducible Umicom release": videos/scripts/68-from-source-to-reviewed-umicom-release.md
      - "Episode 69 – Understand Git's commit graph with native C23": videos/scripts/69-understand-git-history-with-c23.md
```

## Validation after review

1. Inspect `git diff -- mkdocs.yml` and confirm that no existing navigation entry was removed or renamed.
2. Verify all references in the new groups resolve under the current `content/` directory. **Chapters 167–190 and Episodes 58–65 require the previously merged Updates 28–30**; if those files are absent, do not add broken links.
3. Inspect for duplicate heading keys and paths before publishing. These groups are intended to appear **once**.
4. Run the existing Framework-owned `umicom-education audit --repo` where your built tool exposes it, followed by the installed MkDocs strict build. The Framework audit validates bounded local destinations; it does not replace MkDocs' YAML parser.
5. Review the original Islamic volume, previously published chapter navigation and generated website to confirm they remain intact.
6. Stage only reviewed changes, and use `git diff --cached --check` before the final commit.

**Claim boundary:** This package does not claim to have run a complete MkDocs build against your current Windows checkout, because it has not been provided here. The source files and additive snippet were checked for internal path consistency in the packaging environment; actual publication remains a local acceptance step.
