# Episode 70 — Review the Git index before committing

**Bits to Banking · Umicom Foundation · Approximate running time: 12–14 minutes**  
**Source chapters:** [204](../../lessons/05-engineering/204-observe-git-through-umicom-framework.md), [205](../../lessons/05-engineering/205-review-index-and-working-tree-evidence.md).  
**Production:** Terminal capture, Beyond Compare and one vector diagram; no scripted automation.

## Learning outcome

The viewer should be able to distinguish HEAD, index and working-tree contents, inspect staged and unstaged changes, and explain why `git add -A` needs a deliberate review before `git commit`.

### 00:00–01:15 — Opening problem

**Visual:** Umicom Studio workbench next to a terminal showing a modified C23 file and a new documentation file.

**Narration:** “A Git commit should describe a specific engineering change. If we stage everything without checking it, the next commit may also include an unrelated local file, a removed lesson, or a changed submodule pointer. Git does not decide which changes belong together. The reviewer does.”

Show the diagram `git-index-review-update32.svg`. Point to the distinction between disk files, the index, and HEAD. Say explicitly that each stage can differ. A new untracked file appears in `git status`, but not in a normal tracked-file `git diff`.

### 01:15–04:00 — Establish the real repository

**Visual:** PowerShell opened in `C:\umicom\Umicom-Bits2Banking`. Run:

```powershell
Get-Location
git status
git branch --show-current
git diff --stat
git diff --cached --stat
```

**Narration:** “The location tells us which repository we are about to change. Git commands generally act on the current repository; Framework, Umicom OS and Bits2Banking are independent. `git status` tells us whether anything is staged, unstaged or untracked. The two diff commands inspect different boundaries.”

Do not assume the repository is dirty. If the worktree is clean, show a prepared disposable practice repository instead of changing production files solely to create a video.

### 04:00–07:00 — Stage and review

**Visual:** A disposable repository with `README.md` and a fictional C23 Notes example. Run `git add -A`, followed by `git diff --cached --name-status`, `git diff --cached --check`, and `git diff --cached`.

**Narration:** “`git add -A` stages all changes in scope. It does not publish anything. We now inspect the exact staged content. If a file was staged unintentionally, we unstage only that path with `git restore --staged -- path`. We must not confuse this with restoring the working file, which can discard modifications.”

Use Beyond Compare to show a removed explanatory comment and its restored version. Explain the Umicom source-preservation policy: an apparently unnecessary block may provide ABI behaviour or educational context.

### 07:00–09:30 — A submodule is different

**Visual:** `git ls-files --stage framework` in the Umicom OS parent. Do not modify the child.

**Narration:** “The parent records a Git commit identifier, called a gitlink, rather than duplicating every Framework source file. A single changed gitlink may represent many Framework commits. Inspect it with `git diff --cached --submodule=log` and verify that the target child commit is published and tested before committing the parent.”

Show the Framework observer in `include/umicom/vcs/working_tree.h` and explain why application code must use its native contract, not parse human-oriented Git strings.

### 09:30–12:30 — Safe commit sequence

**Visual:** Only after a passing build and test in the disposable practice repository:

```powershell
git status
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "docs: clarify the native Notes learning exercise"
git log -1 --oneline
```

**Narration:** “A commit records the reviewed index. It does not prove deployment or remote publication. The next action is a separately authorised push, after checking remote history.”

**Assessment prompt:** “A new file remains untracked after staging only `README.md`. Will it be included in the next commit? How would you confirm?” Pause, then answer: “No. Inspect `git status` and `git diff --cached`.”

**Closing:** “The index is a controllable boundary. Review it with the same care as a C23 public header.”
