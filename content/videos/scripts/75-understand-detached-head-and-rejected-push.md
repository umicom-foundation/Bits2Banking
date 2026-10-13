# Episode 75 — Understand detached HEAD and a rejected Git push

**Bits to Banking · Umicom Foundation · Author: Sammy Hegab**  
**Format:** 10–12-minute narrated Git troubleshooting session.  
**Reading:** Chapters 218–221.

## Objective

Demonstrate why `git push` may fail in a Framework submodule, why `git push origin main` can fail for a different reason, and why neither problem is solved by blindly forcing Git to overwrite remote history.

## Opening (0:00–1:30)

Display two errors in separate cards: *“You are not currently on a branch”* and *“non-fast-forward”*. Explain that the first refers to checked-out HEAD, while the second concerns the branch supplied as the push source. A submodule is commonly at a pinned detached commit by design.

## Inspect the three references (1:30–4:00)

Use a harmless practice checkout or pre-recorded terminal output. Run `git branch -vv`, `git log -1 --oneline HEAD`, `git log -1 --oneline main`, and `git log -1 --oneline origin/main`. Draw lines between the labels and the commit graph in `git-ref-triangle-update33.svg`. State clearly that a remote-tracking branch is the locally stored result of the latest fetch, not proof of the remote's state at this instant.

## Investigate ancestry (4:00–7:00)

Show `git fetch origin main` only on a clean practice repository. Continue with `git log --oneline --left-right HEAD...origin/main` and `git rev-list --left-right --count HEAD...origin/main`. Explain a pure fast-forward versus a split history. Mention that `git pull --ff-only origin main` is safe only when the checkout is clean and the commits to preserve are understood; it refuses divergent histories.

## Preserve work (7:00–9:30)

Discuss tracked, untracked and ignored paths. Read `git status --short`, `git status --ignored --short`, `git log origin/main..HEAD` and `git stash list`. A stash can preserve reviewed untracked files with `--include-untracked`, but it does not preserve ignored files or make unpublished commits appear in remote `main`. Never demonstrate destructive cleanup as a routine fix.

## Application to Umicom OS (9:30–12:00)

Show how Framework source is published once from the canonical Framework repository. Then explain consumer checkout synchronisation, OS build/test and parent gitlink publication. Finish with a verbal checkpoint: “Do not commit the parent until the child SHA is published and tested.”

## Questions

Why is `git push origin main` not a synonym for pushing detached HEAD? How does local `origin/main` become stale? Where must the Umicom OS parent record its tested child SHA?
