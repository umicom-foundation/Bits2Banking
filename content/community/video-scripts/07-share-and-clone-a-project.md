# Video script: Share a practice project and clone it

**Aim:** Publish your own practice repository deliberately, then download a separate copy.

**Preparation:** PowerShell, Git, GitHub CLI, your own GitHub account and a practice repository with at least one commit. Use git status and git log --oneline -1 to check it. Do not publish an employer’s or another person’s repository. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/07-share-and-clone-a-project.md)

## Opening words

Next, we will take this topic one step at a time: share a practice project and clone it. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Begin with a harmless local project. Show the tracked-file review and explain visibility before running any publication command.

## Scene 2

Pause recording during authentication. Show only the successful account status with personal details hidden.

## Scene 3

Clone into a different folder. Compare the two logs and explain why editing one copy does not update the other.

## Walkthrough and pauses

### Local and online copies

**Say:** A remote is a named address for another repository. origin is a common remote name. Push sends commits to a remote. Clone downloads a repository into a new folder. GitHub authentication proves which account you can act as; it is separate from the author name stored in commits.

### 1. Sign in through the browser

**On screen — type one line at a time:**

```powershell
gh auth login --hostname github.com --git-protocol https --web
gh auth setup-git
gh auth status
```

Pause. Read the result before continuing.

**Say:** Follow the interactive instructions. Complete sign-in yourself in the browser. Do not paste passwords, tokens or authentication codes into project files, lessons or group messages. gh auth status should identify the account you intended to use.

### 2. Review before publishing

**On screen — type one line at a time:**

```powershell
Get-Location
git status
git log --oneline -2
git ls-files
git remote -v
```

Pause. Read the result before continuing.

**Say:** Read the tracked-file list. Remove private information from the project before publishing; if it was already committed, merely deleting the current file does not erase history. Use a fresh harmless practice project if you are unsure. The example below creates a private repository first. Private limits visibility; it is not a place to store secrets.

### 3. Create your remote

**On screen — type one line at a time:**

```powershell
gh repo create YOUR-ACCOUNT/notes-practice --private --source . --remote origin --push
```

Pause. Read the result before continuing.

**Say:** Replace YOUR-ACCOUNT with your GitHub account name. --source . uses the current project. --remote origin adds that remote, and --push uploads your local commits. Choose --public instead only when you intend anyone to view the work. If origin already exists, inspect it rather than replacing it blindly.

### 4. Clone into a different folder

**On screen — type one line at a time:**

```powershell
Set-Location ..
git clone https://github.com/YOUR-ACCOUNT/notes-practice.git notes-practice-clone
Set-Location notes-practice-clone
git status
git log --oneline -2
```

Pause. Read the result before continuing.

**Say:** Replace the account name again. A clone must have a new destination; do not clone over the first project. You should see the same commits and files. A clone is a separate working copy: an edit in the first folder does not instantly appear in the second.

### If the command fails

**Say:** If the repository name is already in use, inspect it on GitHub or choose a new practice name. If authentication fails, run gh auth status. If cloning reports a non-empty destination, keep that folder and choose a different destination.

### Your turn

**Say:** Add and commit a harmless sentence in the first copy, then push with git push origin main. In the clean clone, use git pull --ff-only. Fast-forward-only refuses to combine diverging histories automatically. Stop and inspect if it refuses.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
