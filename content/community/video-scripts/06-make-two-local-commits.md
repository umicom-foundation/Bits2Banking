# Video script: Record two versions with Git

**Aim:** Create a local repository, inspect a change and record two commits.

**Preparation:** Git and PowerShell. Make a new practice folder with a README.md and no private data. You do not need a GitHub account for this lesson. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/06-make-two-local-commits.md)

## Opening words

Next, we will take this topic one step at a time: record two versions with git. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Use three labels on screen: working file, staging area, commit. Move the explanation through them as the commands run.

## Scene 2

Make the first commit, then add exactly one sentence. Show the added line with git diff before staging.

## Scene 3

Record the second commit and inspect the short log. Finish by saying that all of this still lives on the local computer.

## Walkthrough and pauses

### What Git records

**Say:** A repository is a project folder with version history. A commit is a recorded checkpoint. The working files are what you edit. The staging area is your selection for the next commit. git add changes that selection; git commit records it. Neither uploads files.

**Say:** Git tracks file contents, not empty directories on their own. A branch is a name pointing to a line of commits. We will call the first branch main.

### 1. Check your folder and identity

**On screen — type one line at a time:**

```powershell
Get-Location
Get-ChildItem -Force
git config --global user.name
git config --global user.email
```

Pause. Read the result before continuing.

**Say:** If .git already exists, use a fresh practice folder for this exercise. If your identity is missing or incorrect, set your own name and email:

**On screen — type one line at a time:**

```powershell
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

Pause. Read the result before continuing.

**Say:** Replace those example values. Commit identity is recorded in history and may become public if you publish it. A GitHub-provided noreply email can avoid exposing a personal address. --global sets a default for your account; it does not sign you in to GitHub.

### 2. Create the local history

**On screen — type one line at a time:**

```powershell
git init -b main
git status
git add README.md
git diff --cached
git commit -m "Add project introduction"
```

Pause. Read the result before continuing.

**Say:** Read git diff --cached before committing: it shows the selected changes. A successful commit prints its identifier and a summary. If there is nothing to commit, read git status rather than making a meaningless edit.

### 3. Change and inspect the note

**On screen — type one line at a time:**

```powershell
Add-Content -LiteralPath ".\README.md" -Value "Next I will build a small C program." -Encoding utf8
git diff
git status
```

Pause. Read the result before continuing.

**Say:** git diff shows unstaged changes. Lines beginning with + were added; lines beginning with - were removed in this comparison. These signs describe the change; they are not part of your document.

### 4. Record the second checkpoint

**On screen — type one line at a time:**

```powershell
git add README.md
git diff --cached
git commit -m "Describe the next learning step"
git log --oneline -2
git status
```

Pause. Read the result before continuing.

**Say:** You should see two commits. A clean working tree means tracked working files match the recorded state. It does not mean the program is correct or that anything was uploaded.

### If a commit fails

**Say:** If Git asks who you are, check the name and email settings. If it reports not a git repository, inspect Get-Location. Do not initialise a repository in an unrelated folder just to silence the message.

### Your turn

**Say:** Write a third sentence, inspect it with git diff, then stage and commit only README.md. Explain the difference between editing, staging and committing before moving to online publication.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
