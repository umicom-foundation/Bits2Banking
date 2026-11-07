# Record two versions with Git

Create a local repository, inspect a change and record two commits.

**Before you start:** Git and PowerShell. Make a new practice folder with a README.md and no private data. You do not need a GitHub account for this lesson.

[Community learning route](../index.md) · [Printable HTML](../handouts/06-make-two-local-commits.html)

## What Git records

A repository is a project folder with version history. A commit is a recorded checkpoint. The working files are what you edit. The staging area is your selection for the next commit. git add changes that selection; git commit records it. Neither uploads files.

Git tracks file contents, not empty directories on their own. A branch is a name pointing to a line of commits. We will call the first branch main.

## 1. Check your folder and identity

```powershell
Get-Location
Get-ChildItem -Force
git config --global user.name
git config --global user.email
```

If .git already exists, use a fresh practice folder for this exercise. If your identity is missing or incorrect, set your own name and email:

```powershell
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

Replace those example values. Commit identity is recorded in history and may become public if you publish it. A GitHub-provided noreply email can avoid exposing a personal address. --global sets a default for your account; it does not sign you in to GitHub.

## 2. Create the local history

```powershell
git init -b main
git status
git add README.md
git diff --cached
git commit -m "Add project introduction"
```

Read git diff --cached before committing: it shows the selected changes. A successful commit prints its identifier and a summary. If there is nothing to commit, read git status rather than making a meaningless edit.

## 3. Change and inspect the note

```powershell
Add-Content -LiteralPath ".\README.md" -Value "Next I will build a small C program." -Encoding utf8
git diff
git status
```

git diff shows unstaged changes. Lines beginning with + were added; lines beginning with - were removed in this comparison. These signs describe the change; they are not part of your document.

## 4. Record the second checkpoint

```powershell
git add README.md
git diff --cached
git commit -m "Describe the next learning step"
git log --oneline -2
git status
```

You should see two commits. A clean working tree means tracked working files match the recorded state. It does not mean the program is correct or that anything was uploaded.

## If a commit fails

If Git asks who you are, check the name and email settings. If it reports not a git repository, inspect Get-Location. Do not initialise a repository in an unrelated folder just to silence the message.

## Your turn

Write a third sentence, inspect it with git diff, then stage and commit only README.md. Explain the difference between editing, staging and committing before moving to online publication.

## Continue when you are ready

[Previous: Install and find your everyday tools](05-install-and-find-tools.md) · [Next: Share a practice project and clone it](07-share-and-clone-a-project.md)

[Explore the related course](../../courses/introduction-to-version-control/index.html). You can finish this exercise without leaving this page.

## Further reading

- [Git basics: recording changes](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository)

[Video teaching script](../video-scripts/06-make-two-local-commits.md) · [Short community message](../messages/06-make-two-local-commits.md)
