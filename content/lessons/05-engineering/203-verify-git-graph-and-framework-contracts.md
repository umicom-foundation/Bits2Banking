# Chapter 203 — Verify the C23 graph laboratory and reuse Framework VCS services

**Bits to Banking · Native integration and quality · Umicom Foundation**
**Laboratory:** `labs/native/git-history`
**Prerequisites:** Chapter 202 and the [daily Git workflow](183-daily-umicom-git-workflow.md).

## Understand what the tests actually prove

A graph is small enough to inspect, but it can still contain incorrect assumptions: accepting a future parent introduces a cycle risk; treating an ID as a timestamp gives wrong ancestry results; and modifying an output argument before detecting a missing commit violates failure-atomic behaviour. The `git-history` suite makes these properties observable. It does not claim to test a real Git executable or a production Framework command. Each test corresponds to a documented function or invariant.

## The acceptance matrix

| CTest name | What it establishes | What it does not establish |
|---|---|---|
| `equal`, `behind`, `ahead` | Correct fixed-graph ancestry cases | Git remote permissions or network access |
| `diverged`, `merge` | Both-parent traversal and unrelated histories | Actual merge conflict resolution |
| `dirty` | Conservative review flags for edited work | Real path-level checkout collisions |
| `detached` | HEAD, local main and remote main remain distinct | Whether unpublished commits are safely backed up |
| `invalid` | Rejected duplicate/invalid parents and retained outputs | Arbitrary malicious .git object database detection |
| `capacity` | Maximum 64 nodes, no overflow beyond limit | Scalability to millions of commits |
| `stress` | 20,000 deterministic relation checks | Parallel safety or thread races |
| `demo` | Explain a stale local branch and detached checkout | Perform a remote push |

The tests use ordinary ISO C23, fixed-width integers and no network, Python, PowerShell scripts or Git subprocess. All tests return explicit status codes and avoid output mutation after rejection. The implementation's internal parent array and visited set have fixed capacity, with an invariant check before traversals.

## Read real Framework contracts

The *Umicom Framework* Git subsystem already offers reusable C interfaces:

- `include/umicom/vcs/working_tree.h` — read-only working-tree summaries, independently reporting staged, unstaged, untracked and child-repository state.
- `include/umicom/vcs/git_cli.h` — Git CLI provider behind the stable Framework VCS contract.
- `include/umicom/repository/gitlink.h` — validation of mode-160000 gitlinks.
- `include/umicom/repository/submodule_lock.h` — native C23 gitlink staging, with a dry-run option; **no commit or push**.
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` — the authoritative order for publishing a Framework change and synchronising consumer repositories.

These locations were verified against Framework `main` while preparing this edition. They are educational source references, not new dependencies; the laboratory **does not link to Framework** and does not duplicate repository process execution. Real applications should call the Framework contracts rather than copy this simplified graph into a product.

## Capstone: diagnose without changing tracked working files

In the Umicom OS checkout, run read-only commands:

```powershell
Set-Location "C:\umicom\umicomOS"
git submodule status framework
git ls-files --stage framework
git -C ".\framework" status --short --branch
git -C ".\framework" log -1 --oneline HEAD
git -C ".\framework" log -1 --oneline main
git -C ".\framework" fetch origin main
git -C ".\framework" log -1 --oneline origin/main
```

Note that `fetch` updates remote-tracking information and object storage but does not merge your working tree. Draw an ancestry graph of the three tips. Predict whether `git push origin main` would be an ancestry-compatible update, then check the real `git log main..origin/main` and its reverse. **Do not issue a push** as part of this diagnostic lab.

## Engineering completion checklist

A release-quality learning batch requires correct files, build and test evidence, readable diagrams, navigable chapters, reproducible commands and exact limitations. Before publishing a contribution, inspect its changed paths and review lesson navigation using the [website contribution guide](../../contributing/local-website.md). Retain the existing navigation and historical *Islam: Blueprint for Life* chapters; do not replace `mkdocs.yml` with a shortened generated list. Run the existing publisher in strict mode where available; report the gate as not run rather than claiming success without evidence.

**Next:** revisit the earlier [Git fundamentals](16-git.md) and [Framework ownership principles](176-from-teaching-queue-to-umicom-framework.md), then practise a complete checked contribution in a disposable clone before applying new tools to production repositories.
