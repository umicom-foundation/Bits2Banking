# Episode 92 — Create a Git repository and publish it to GitHub

**Bits to Banking · Umicom Foundation · Beginner video series**  
**Companion lessons:** Chapters 272–275 · **Suggested duration:** 14–18 minutes.

## Opening — Git is not GitHub (0:00–3:00)

**On screen:** Show the SVG `git-first-commit-journey-update37.svg`. Point to working files, staging, local commits and the GitHub remote.

**Narration:** “Git records versions of files on this computer. GitHub hosts repositories online. GitHub CLI helps us sign in and create remote repositories. We can make commits without internet access. A push requires network access, appropriate authentication and permission to update the destination.”

## Configure identity and authentication (3:00–6:00)

```powershell
git --version
gh --version
git config --global user.name (Read-Host "Your display name")
git config --global user.email (Read-Host "Your verified commit email")
gh auth status
```

Demonstrate `gh auth login` only if needed. Show the official browser flow but keep codes, email, account information and tokens off the recording. Explain that Git identity and GitHub login are distinct.

## Create a safe local practice repository (6:00–11:00)

```powershell
Set-Location "$HOME\UmicomLearning\notes-practice"
git init -b main
git status
git add README.md
git diff --cached --check
git commit -m "docs: add Notes project introduction"
git log --oneline -3
```

**Narration:** “Staging is choosing the content of the next snapshot. A commit records that snapshot locally. There is still nothing on GitHub.” If the directory was already initialised, show `git status` and do not rerun `git init` blindly.

## Create the remote (11:00–15:00)

```powershell
gh repo create notes-practice --private --source . --remote origin --push
git remote -v
gh repo view --web
```

Demonstrate on a disposable instructor account, not an organisation-owned repository. Tell learners that a name collision means we must inspect before retrying. Show the first commit visible online, then explain how `git push origin main` publishes a later reviewed commit.

## Safety recap and activity (15:00–18:00)

Ask: “What happens to Git history when I close PowerShell? What does `git add -A` include? Can a learner who cloned an Umicom repository push directly to the Foundation's `main` without access?” Explain fork/PR for external contributors and direct-to-main for authorised owner-controlled Umicom integration.

**Student evidence:** `git log --oneline -3`, a correct explanation of `origin`, and a private repository opened in the browser. Do not request the repository to be made public.
