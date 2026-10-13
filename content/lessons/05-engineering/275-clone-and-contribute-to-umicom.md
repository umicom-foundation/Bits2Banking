# Chapter 275 — Clone, read and contribute to an Umicom repository

**Bits to Banking · Absolute Beginner Course · Unit 3**  
**Time:** 35–55 minutes · **Requirements:** Git; internet access for cloning. No organisation write permission is required to read the public repository.

## Work on a copy, not someone else's live folder

When you **clone** a repository, Git downloads its history into a new local folder. You can read code and lessons without editing the online original. A **fork** is your own GitHub-hosted copy of another person's repository. A **pull request (PR)** invites maintainers to review a proposed change. These are tools for collaboration, not replacements for C23 tests or source preservation.

## Step 1 — Clone the public learning repository

```powershell
Set-Location "$HOME\UmicomLearning"
git clone "https://github.com/umicom-foundation/Bits2Banking.git" "Bits2Banking-Study"
Set-Location ".\Bits2Banking-Study"
```

We explicitly chose a different destination name (`Bits2Banking-Study`) so the exercise does not collide with `C:\umicom\Umicom-Bits2Banking` or with any other existing working copy. If you already have a `Bits2Banking-Study` directory, inspect it rather than cloning over it.

Verify:

```powershell
Get-Location
git status
git remote -v
git log --oneline -3
```

You should see a clean branch and a remote called `origin`, pointing to the Umicom Foundation project. **Cloning grants no permission to push into the organisation's `main` branch.**

## Step 2 — Browse real project learning material

List the Markdown lessons and open a guide:

```powershell
Get-ChildItem ".\content\lessons\05-engineering" | Select-Object -First 8 Name
notepad ".\BEGINNERS.md"
```

The structure shown on GitHub may evolve; verify actual paths before telling others to use them. Our training documentation comes from the project's existing `content/lessons`, `content/videos/scripts` and `labs/native` directories.

## Step 3 — Decide the contribution workflow

**For learners without direct write permission:** use your GitHub fork and a focused pull request. First explore the existing Chapter 17, `content/lessons/05-engineering/17-first-pull-request.md`, which shows the entire process. This workflow may use a small contribution branch so maintainers can review it without changing the contributor's own `main`.

**For the Umicom project owner and authorised integration maintainers:** the established local house rule is different: make reviewed changes directly on `main`, build and test, then `git add -A`, commit and push in the correct repository order. Do not create extra branches or silently rewrite this policy for owner-controlled Umicom work.

## Step 4 — Know what you can safely suggest

A good first contribution might correct a typo, improve an ambiguous command explanation, report a broken link or add a reproducible test. Before editing an existing file, read the surrounding documentation, identify the actual problem and avoid removing author credits, features or historical explanations. Do not assume a source file is obsolete because it appears lengthy.

In a serious repository, a simple-looking change to a public header can affect many consumers. Umicom Framework owns reusable capabilities. Education owns lessons and small teaching labs. Applications should consume the Framework instead of duplicating its systems.

## Step 5 — Avoid unexpected changes

Read-only checks for your study clone:

```powershell
git status
git diff
git log --oneline -5
```

If a later operation reports a detached HEAD, a dirty submodule or a push rejection, record the exact output and stop. **Do not use `git reset --hard`, `git clean -fd`, `git push --force`, or Git options that overwrite changes as a beginner workaround.**

**Practice:** Explain the difference between clone, fork, branch, pull request, commit and push. Name which workflow applies to an external volunteer and which applies to the authorised project owner.

**Next:** [Prepare the Windows C23 toolchain](276-install-msys2-ucrt64-cmake-and-ninja.md).
