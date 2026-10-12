# Chapter 187 — Install Git, authenticate GitHub and create repositories

**Bits to Banking · Version-control track · Umicom Foundation**  
**Tools:** Git, GitHub CLI (`gh`), Windows PowerShell interactive commands.  
**Prerequisites:** Chapters 182–184.

## Git is local; GitHub is a service

You can create commits, inspect history and compare versions without an internet connection. That is **Git**. GitHub hosts repositories, handles authorised collaboration, stores issues and pull requests and can run automated build checks. The GitHub CLI, named `gh`, provides access to GitHub operations in a terminal; it is not a replacement for Git's repository history commands.

Umicom maintainers often manage multiple independently versioned repositories. A new contributor should learn to confirm both **where a command runs** and **which remote it is about to change** before authenticating or pushing anything.

## Step 1 — Inspect installed tools

Open a PowerShell terminal:

```powershell
Get-Command git -ErrorAction SilentlyContinue
Get-Command gh -ErrorAction SilentlyContinue
git --version
gh --version
```

If Git or `gh` is missing, you can install them with Windows Package Manager where available:

```powershell
winget install --id Git.Git --exact
winget install --id GitHub.cli --exact
```

Review the publisher and installation prompt; versions and package availability change over time. Reopen PowerShell if the executable path is not yet visible. For the C23 laboratories, install MSYS2 UCRT64, CMake and Ninja separately according to the project's toolchain guide. Git does not compile C source.

## Step 2 — Configure a human commit identity

```powershell
git config --global user.name "YOUR_PUBLIC_DISPLAY_NAME"
git config --global user.email "YOUR_COMMIT_EMAIL"
git config --global --get user.name
git config --global --get user.email
```

Use your own values. Avoid putting credentials, passwords, private tokens or security answers into Git config, source files or command examples. Git author metadata is public in a public repository; consider GitHub's supported no-reply email if you prefer to protect a personal address.

## Step 3 — Authenticate safely

```powershell
gh auth login --hostname github.com --git-protocol https --web
gh auth status
```

The CLI can open a browser-based authorisation process. Verify that you have authenticated to the intended GitHub account. Do not paste authentication codes into a team chat, and do not store a token in a committed `.env` file. A credential manager is preferable to manual token handling.

## Step 4 — Create a new local practice repository

Work outside the real Umicom checkout:

```powershell
New-Item -ItemType Directory -Force "$HOME\UmicomLearning\cash-position-lab" | Out-Null
Set-Location "$HOME\UmicomLearning\cash-position-lab"
git init -b main
Set-Content -LiteralPath ".\README.md" -Value "# Cash position laboratory"
git add README.md
git diff --cached --check
git commit -m "docs: introduce cash position laboratory"
```

This is a teaching repository containing a Markdown document, not a banking service that moves money.

## Step 5 — Create a GitHub remote

Only after checking the intended account and repository name:

```powershell
gh repo create cash-position-lab --private --source . --remote origin --push
```

This command **creates a real remote repository** under the selected GitHub account and pushes the existing local branch. Check existing repositories first with `gh repo list` and inspect `git remote -v` if you have run the exercise previously. Do not overwrite an existing `origin` or repository name without explicit review.

After creation:

```powershell
git remote -v
git status --short --branch
gh repo view --web
```

Creating a private repository does not make it suitable for secrets. Use supported secrets management for credentials, and commit sample configuration without passwords.

## Clone versus initialise

`git init` starts tracking a directory in place. `git clone URL` downloads an existing repository, its history and normally a remote named `origin`. Do not run `git init` over a directory you assumed was a clone; check for an existing `.git` and `git rev-parse --show-toplevel` first. Similarly, do not clone into a directory already holding valuable uncommitted work.

## Practice assignment

Create the local practice repository above, publish it privately, and explain what each of these names refers to: `main`, `origin`, `HEAD`, `gh` and `README.md`. Run `gh auth status` and `git remote -v`, but **do not share tokens** when documenting the results.

**Next:** [Inspect commit history and find regressions](188-read-history-diffs-and-provenance.md).
