# How Git keeps track of your work

**Estimated video length:** 7–9 minutes  
**Related lesson:** [Git: remember and review your changes](../../lessons/05-engineering/16-git.md)

## Introduction — 0:00 to 1:10

**On screen:** A source file named `notes.py` appears beside a list of changes.

**Narration:**

When you write software, change is unavoidable. You add a feature, fix an error or improve an explanation. Sometimes a change makes things better. Sometimes it introduces a problem that you only discover later. How can you remember what changed, why it changed and how to compare two versions of a project?

Git is a version-control system designed to answer those questions. It tracks the history of files inside a repository. A repository is a project directory with information that lets Git remember earlier versions. It is not limited to programming: you can use Git for lessons, diagrams, scripts and documentation.

In this demonstration, we will make a small change to a simple project, inspect it, create a commit and understand what GitHub adds to the process.

## Working directory, staging and commits — 1:10 to 2:40

**On screen:** Three labelled areas: Working directory → Staging area → Commit history.

**Narration:**

Git has three ideas worth learning before the commands. The working directory contains files you can edit. The staging area is the collection of specific changes you have selected for the next commit. A commit is a saved point in the project's history, normally accompanied by a message explaining what was changed.

Suppose a note-taking project contains a file called `README.md`. We can edit a sentence and save the file in our editor. At this moment, Git can see that something changed, but we have not created a commit. We first inspect the change, decide that it belongs in the next commit, and stage the file. Only then do we create the commit.

This separation is useful. You might edit three files and realise that only one is ready to share. Git lets you choose exactly which files to stage. It also lets you inspect the proposed change before creating permanent history.

## Demonstration — 2:40 to 4:50

**On screen:** Use a disposable project folder in PowerShell, entering each command and showing the output.

**Narration:**

Let's create a local practice project without touching your existing Umicom checkout. Open PowerShell and create a folder named `GitPractice` inside your home directory. Enter that directory. Now type `git init -b main`. Git creates the repository's local history information, and the project begins on a branch called main.

Create a README file by typing `Set-Content README.md '# Notes project'`. Git will see it as a new file. Type `git status` to inspect the current state. You should see that README is untracked. This means it exists on disk, but Git has not yet been asked to include it in a commit.

Stage it with `git add README.md`. Then run `git diff --cached --check` to check for whitespace problems in the staged changes. Run `git diff --cached` to examine what will be committed. When you are satisfied, run `git commit -m 'docs: add notes project introduction'`.

The first time you commit, Git may ask you to configure your name and email. Use your own information, not someone else's. After the commit, type `git status` again. If you have made no other edits, Git should tell you that the working tree is clean.

You have not sent anything to the internet. Every command so far has worked inside your local folder.

## Git and GitHub — 4:50 to 6:10

**On screen:** Show the local project on the left and the GitHub repository on the right, connected by arrows labelled push and pull.

**Narration:**

Git and GitHub are related, but they are not the same thing. Git is the version-control system that keeps track of your history. GitHub is an online hosting service that can store copies of repositories and help people collaborate.

When a repository has a remote address, a push sends local commits to that remote. A pull brings remote changes into your local repository, under the chosen integration rules. Before pushing, inspect the remote using `git remote -v` so you know exactly where your work will go.

GitHub also offers pull requests. A pull request is a proposed change that others can review before it is merged into a shared branch. You might fork Bits2Banking, make a small documentation improvement in your own copy and then open a pull request asking the Umicom maintainers to review it. You do not need to be a maintainer to suggest a useful improvement.

## Why review matters — 6:10 to 7:25

**On screen:** Show two versions of a short document and highlight the edited line.

**Narration:**

A commit message helps explain your intention, but it does not prove that every change is correct. A developer should inspect the diff, run the relevant checks and make sure no unrelated files or secrets have been staged. In a project that includes multiple submodules, each submodule has its own history, and a parent repository records which child commit it uses.

Clear, small commits are easier to review than large changes that mix unrelated subjects. For a first contribution, a better link or a clearer instruction is enough. The important skill is being able to explain what you changed and how you checked it.

## Closing — 7:25 to 8:10

**On screen:** The sequence appears: Edit → Review → Stage → Commit → Share → Review.

**Narration:**

Try making a second change to your practice README. Before committing, use `git diff` to see what you changed and use `git status` to check which files are involved. Then stage only the README file and make a new commit.

When those steps feel familiar, continue with the [first contribution lesson](../../lessons/05-engineering/17-first-pull-request.md). It walks through forks, branches, pull requests and review using the actual Bits2Banking project. Sharing a clear improvement is one practical way to help someone else learn.
