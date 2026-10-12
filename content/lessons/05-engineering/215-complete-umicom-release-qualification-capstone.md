# Chapter 215 — Capstone: qualify an Umicom Framework and OS update

**Bits to Banking · Professional integration capstone · Umicom Foundation**  
**Prerequisites:** Chapters [204](204-observe-git-through-umicom-framework.md)–[214](214-test-fail-closed-release-gates.md).  
**Safety:** This is an assessed runbook. On production repositories, execute write operations only for changes you have actually reviewed and approved.

## Scenario

Umicom Framework has received a C23 correction to its VCS working-tree observation. Umicom Studio uses the new library. Umicom OS still pins an older Framework revision. The educational website also needs this batch's new lessons. Your job is to decide whether these changes can be published **without losing existing source, creating duplicate services or breaking reproducibility**.

There are three independent releases: the canonical Framework source, the parent Applications integration and the OS parent gitlink. Bits2Banking is a separate learning-content repository. This capstone requires you to identify which repository actually changed, then plan the minimum number of commits. Do not manufacture commits where no change exists.

## Stage 1 — establish the source of truth

Read `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` in Framework. Identify the single canonical Framework repository and the two local consumer checkouts. Inspect each checkout's HEAD and working-tree status. Record the current parent gitlink with `git ls-files --stage framework`. Explain why an OS `git pull --ff-only origin main` may report success even while its child Framework revision is old.

A reviewable report should distinguish *working-tree clean*, *remote ancestry known*, *child revision published*, *parent pin changed* and *OS tested*. These are not synonyms. Inspect the Framework public VCS header: `UmiVcsWorkingTreeRead` and `UmiVcsWorkingTreeDescribe` are the supported native observation contracts, while `umicom repo verify .` and `umicom repo lock .` handle the parent’s repository-control workflow.

## Stage 2 — require real build and test evidence

For Framework changes, build and test using the existing Umicom Applications CMake configuration. For OS, run the appropriate headless and GTK4 presets. If the change affects the diskless image, provide actual QEMU boot evidence in addition to native tests. For Bits2Banking, run the Update 32 C23 laboratory and the existing MkDocs strict build when its environment is available.

Log any skipped gate explicitly as `NOT RUN`. A failing or unavailable tool is not a pass. Do not suppress or delete a failing test to make the total green.

## Stage 3 — safe Framework publication

Only the canonical Framework source checkout should publish new shared C code. Confirm that `main` is checked out, remote history is refreshed, and only intended changes are staged. The standard sequence is:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "fix(framework): qualify shared VCS observation"
git push origin main
```

This example commit must not be executed unless such a fix really exists and has passed review. If Framework has no new changes, use its existing published SHA and skip the Framework commit.

## Stage 4 — integrate Framework into the OS parent

In a clean `umicomOS/framework`, inspect local-only commits and untracked files before switching. Fetch and fast-forward its local `main` to the published Framework revision. Build and test OS against this exact checkout. Use the native Framework CLI `repo verify .` then `repo lock .` from the OS root. Review `git diff --cached --submodule=log` before running parent-wide staging.

The reviewed OS publishing commands are:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --submodule=log
git commit -m "chore(os): pin tested Umicom Framework revision"
git push origin main
```

The result is a parent commit pointing to a published and tested Framework revision. No Framework source files should be copied into OS as a workaround.

## Stage 5 — publish this educational batch independently

Merge the Update 32 ZIP using Beyond Compare into `C:\umicom\Umicom-Bits2Banking`. Add navigation entries from the included reviewed recipe, preserving historical lessons and the *Islam: Blueprint for Life* content. Build the `git-release-evidence` C23 laboratory and run its 26 tests. Run strict MkDocs in the existing environment; record `NOT RUN` if it is unavailable. Then review and commit **Bits2Banking only**:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Git release qualification and C23 evidence gates"
git push origin main
```

## Assessment rubric

A correct capstone submission includes (a) the correct commit SHA for each repository, (b) the expected and observed Framework gitlink, (c) working-tree and remote ancestry evidence, (d) exact build and test results, (e) a staged diff review, (f) a clear explanation of any blocked gate, and (g) a rollback/recovery plan that preserves source. No source should be deleted, no new runtime scripts should be introduced, and no test result should be invented.

## Discussion

How would the process change if Framework passed tests but OS failed at GTK4 startup? What if the child commit was not yet pushed? What if Bits2Banking navigation contained a duplicate lesson? What if a release report referred to a snapshot taken before a new upstream commit? For each case, answer **which gate blocks**, **who owns the correction**, and **what evidence would unblock it**.

**Next major update:** Extend the professional engineering track with release provenance, CI diagnostics, security review and a Framework-owned native integration path. Do not develop a competing application-local Git implementation.
