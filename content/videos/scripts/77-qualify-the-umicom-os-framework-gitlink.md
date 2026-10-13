# Episode 77 — Qualify the Umicom OS Framework gitlink

**Bits to Banking · Umicom Foundation · Author: Sammy Hegab**  
**Format:** 12–15-minute professional capstone.  
**Reading:** Chapters 219, 225–227, and Framework `SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`.

## Opening (0:00–1:45)

A Framework child is ahead of the OS parent's recorded gitlink, the OS desktop has not been retested, and a local Git stash still exists. Ask: “Would you press Commit now?” The correct professional response is “Not until we identify the child SHA, understand the preserved changes and verify the complete integration.”

## Build an evidence table (1:45–5:00)

Using the diagram `git-parent-child-evidence-update33.svg`, show parent HEAD, parent gitlink, Framework child HEAD, child `origin/main`, and build/test result as separate fields. Demonstrate read-only commands: `git ls-files --stage framework`, `git submodule status framework`, `git -C framework log -1 --oneline`, and `git diff --cached --submodule=log`.

Discuss why a current Framework checkout does not imply current OS integration. Show that Umicom Kernel is an independent repository and should not be forced into a Framework dependency.

## Reuse rather than duplicate (5:00–9:00)

Open Framework's `UmiVcsWorkingTree` API and the native `umicom repo verify .`/`repo lock .` contract. Explain that `verify` previews, while `lock` stages a reviewed pointer; neither runs `git pull`, `git commit` or `git push`. Present Update 32's release gate and Update 33's timeline as separate educational validation models, not substitutes for the Framework implementation.

## The guarded publishing sequence (9:00–12:30)

Narrate: Framework source verified and pushed once; consumer checkout updated after preservation checks; OS headless/GTK4 build/tests pass; parent gitlink staged and inspected; parent commit/push to main. Explicitly note that any missing test, untracked collision, unidentified local commit, stale remote view or misaligned SHA **blocks** the process. A working tree may be clean while these conditions remain unresolved.

## Final exercise (12:30–15:00)

Use Chapter 227's capstone rubric. Ask learners to produce an honest report with observed/expected SHAs, local and remote changes, staged diff, build/test output and unverified conditions. A “not ready” outcome with correct evidence is a valid result.

## Ending

“Reliable release engineering does not mean Git never refuses a command. It means you understand the refusal, preserve everyone's work and publish only revisions you can explain and test.”
