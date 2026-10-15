# Chapter 299 — Framework ownership and Umicom OS change capstone

**Bits to Banking · Engineering track · Umicom Foundation**  
**Author:** Sammy Hegab · ISO C23  
**Source rule:** One reusable Framework, thin applications, preserved history.

## The difference between a teaching model and a production service

The Update 41 C23 project is an offline demonstration of change-window decisions. It deliberately **does not** authenticate the reviewer, read operating-system logs, connect to a Data Server, trigger a Git commit, schedule real services or perform rollback. Those capabilities have established owners in Umicom Framework. Turning a teaching library into a second production supervisor would violate the Framework-first rule and create duplicated security decisions.

In the real Umicom architecture, a Master Controller coordinates lifecycle and policy while Slave Controllers own bounded domain operations. Build and test execution use the existing native Framework tooling. Repository checks and gitlink updates use the Framework-owned repository/VCS services. Authentication, audit, configuration and observability remain under their existing shared contracts. Applications should compose those capabilities instead of implementing new automation scripts.

## A realistic repository change sequence

Imagine an approved change to the Framework's Notes-storage service, consumed by Umicom Studio and Umicom OS. Before coding, identify the true source owner: `C:\umicom\Umicom-Applications\framework`. A separately checked-out `C:\umicom\umicomOS\framework` submodule is **another working copy of the same remote repository**, not a second independent source owner.

The safe engineering order is: review source differences, configure and test Framework, commit and push Framework to `main` from its clean, attached branch, update consumer checkouts to a published revision, rebuild consumers and only then commit/push their parent gitlinks. A parent Git repository records an exact submodule commit; `git pull` on the parent alone does not automatically advance the child to remote `main`.

### Review Framework without changing it

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git diff --stat
git log -1 --oneline
```

If `git branch --show-current` returns nothing, the checkout may be detached. Do **not** push blindly or switch while unpublished commits or uncommitted work remain. Investigate the current and remote commit identities first. For local modifications use reviewed preservation (a backup, stash or approved commit) and never run `git reset --hard`, `git clean -fd` or a force push to make status green.

### Publish reviewed Framework work only after validation

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(framework): improve approved shared capability"
git push origin main
```

These commands are an **illustration for genuinely approved Framework work**, not instructions to commit Update 41 in Framework. If you are merging this learning batch, **only the Bits2Banking repository is changed**.

### Review and publish a parent gitlink separately

After updating the parent checkout to a fully published Framework commit, run the existing native Framework `umicom repo verify .` and `umicom repo lock .` commands from the relevant parent root (where their built executable is available). These commands inspect/stage the pinned submodule revisions; they do not fetch, commit or push remote changes automatically. Always review the result:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git submodule status framework
git diff --submodule=log -- framework
git add framework
git diff --cached --check
git diff --cached --submodule=log
```

Only an authorised OS maintainer should commit that parent reference after the relevant OS build/test gates pass. Do not update Umicom OS gitlinks merely because a new Framework commit exists: reproducibility requires an explicitly tested revision.

## Build and test *this* learning update

The classroom source belongs in Bits2Banking. Build and verify the [maintenance-review laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/maintenance-review/README.md). Review Markdown links, preserved history and the current `mkdocs.yml` navigation before publishing the website. The existing MkDocs build is a separate publication gate; native C23 tests do not guarantee it succeeded.

## Architecture capstone

Write a one-page architecture map with four columns: capability, authoritative repository, owning controller/service and verification evidence. Use at least Framework build automation, VCS, Data Server, security, OS user-space composition and the Bits2Banking learning site. Explain why the maintenance-review teaching model remains within the education repository, and specify which existing Framework service would need to be connected for a production workflow.

**Review questions:** What is a gitlink? Why is a clean checkout not sufficient proof of release readiness? Why should `RESTORED` remain a separate audit outcome? Which Umicom repository is modified by Major Update 41?

**Suggested answers:** A gitlink stores the exact child commit in the parent. Build/test and application checks are separately required. Recovering from a failed update does not make the update itself successful. Only `Umicom-Bits2Banking` receives new files.

**Next:** Stage 5 System Administration will progress through application installation, OS user-space operations, reproducible environments and service deployment reviews, all under explicit authorised boundaries.
