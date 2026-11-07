# Share a practice project and clone it

Publish your own practice repository deliberately, then download a separate copy.

**Before you start:** PowerShell, Git, GitHub CLI, your own GitHub account and a practice repository with at least one commit. Use git status and git log --oneline -1 to check it. Do not publish an employer’s or another person’s repository.

[Community learning route](../index.md) · [Printable HTML](../handouts/07-share-and-clone-a-project.html)

## Local and online copies

A remote is a named address for another repository. origin is a common remote name. Push sends commits to a remote. Clone downloads a repository into a new folder. GitHub authentication proves which account you can act as; it is separate from the author name stored in commits.

## 1. Sign in through the browser

```powershell
gh auth login --hostname github.com --git-protocol https --web
gh auth setup-git
gh auth status
```

Follow the interactive instructions. Complete sign-in yourself in the browser. Do not paste passwords, tokens or authentication codes into project files, lessons or group messages. gh auth status should identify the account you intended to use.

## 2. Review before publishing

```powershell
Get-Location
git status
git log --oneline -2
git ls-files
git remote -v
```

Read the tracked-file list. Remove private information from the project before publishing; if it was already committed, merely deleting the current file does not erase history. Use a fresh harmless practice project if you are unsure. The example below creates a private repository first. Private limits visibility; it is not a place to store secrets.

## 3. Create your remote

```powershell
gh repo create YOUR-ACCOUNT/notes-practice --private --source . --remote origin --push
```

Replace YOUR-ACCOUNT with your GitHub account name. --source . uses the current project. --remote origin adds that remote, and --push uploads your local commits. Choose --public instead only when you intend anyone to view the work. If origin already exists, inspect it rather than replacing it blindly.

## 4. Clone into a different folder

```powershell
Set-Location ..
git clone https://github.com/YOUR-ACCOUNT/notes-practice.git notes-practice-clone
Set-Location notes-practice-clone
git status
git log --oneline -2
```

Replace the account name again. A clone must have a new destination; do not clone over the first project. You should see the same commits and files. A clone is a separate working copy: an edit in the first folder does not instantly appear in the second.

## If the command fails

If the repository name is already in use, inspect it on GitHub or choose a new practice name. If authentication fails, run gh auth status. If cloning reports a non-empty destination, keep that folder and choose a different destination.

## Your turn

Add and commit a harmless sentence in the first copy, then push with git push origin main. In the clean clone, use git pull --ff-only. Fast-forward-only refuses to combine diverging histories automatically. Stop and inspect if it refuses.

## Continue when you are ready

[Previous: Record two versions with Git](06-make-two-local-commits.md) · [Next: Set up the Windows C toolchain](08-set-up-the-c-toolchain.md)

[Explore the related course](../../courses/introduction-to-version-control/index.html). You can finish this exercise without leaving this page.

## Further reading

- [GitHub CLI: create a repository](https://cli.github.com/manual/gh_repo_create)
- [GitHub CLI authentication](https://cli.github.com/manual/gh_auth_login)

[Video teaching script](../video-scripts/07-share-and-clone-a-project.md) · [Short community message](../messages/07-share-and-clone-a-project.md)
