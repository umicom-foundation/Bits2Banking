# Chapter 274 — Publish your first repository to GitHub with `gh`

**Bits to Banking · Absolute Beginner Course · Unit 3**  
**Time:** 25–40 minutes · **Requirements:** a local `notes-practice` repository with at least one commit, GitHub CLI authentication and internet access.

## Git and GitHub do different jobs

Git has already saved your Notes history locally. **GitHub** is a hosting service where you can place a copy of that history. A **remote** is a named address for another repository, often called `origin`. **Push** sends your local commits to the remote. **Fetch** downloads information about remote history without automatically changing your working files. The repository can remain private while you practise.

## Step 1 — Check the local project

```powershell
Set-Location "$HOME\UmicomLearning\notes-practice"
Get-Location
git status
git branch --show-current
git log --oneline -3
```

Before continuing, make sure the branch is `main`, there is at least one commit, and you are not in a real Umicom shared repository. If `git status` shows uncommitted work, review and commit it first or leave it uncommitted intentionally; the command below only publishes commits.

## Step 2 — Check authentication

```powershell
gh auth status
```

If not authenticated, run `gh auth login` and follow Chapter 272. A GitHub account may be permitted to create private repositories even if it cannot write to an organisation-owned repository.

## Step 3 — Create the remote and push the current commits

```powershell
gh repo create notes-practice --private --source . --remote origin --push
```

Read this command from left to right: `gh repo create` requests a new online repository; `notes-practice` names it; `--private` limits its visibility; `--source .` means *this local directory*; `--remote origin` adds an address called `origin`; and `--push` uploads the existing commits. It does not change the project's C23 code.

**Before pressing Enter:** confirm again that you are inside `notes-practice`. If the repository already exists online or `origin` is already configured, **stop and inspect** instead of running the create operation repeatedly.

## Step 4 — Confirm what was published

```powershell
git remote -v
git status
gh repo view --web
```

`git remote -v` shows the remote address. `gh repo view --web` opens the repository in your browser. You should find your `README.md` and recent commits. If the browser shows a private repository, that is expected. Do not change it to public merely to make the class exercise work.

## Step 5 — Make another safe change and upload it

```powershell
Add-Content -LiteralPath ".\README.md" -Value "Version control preserves our editing history."
git status
git diff
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "docs: explain why Git history matters"
git push origin main
```

Only the **last** command sends the new commit to GitHub. If it reports “Everything up-to-date”, there may be no unpublished commit; verify with `git log`. If it reports “non-fast-forward”, do not force push. The remote may contain newer commits; inspect `git fetch origin` and `git log --oneline --left-right HEAD...origin/main` before deciding what to do.

## Security and common failures

Never commit `.env` credential files, passwords, private keys or access tokens. Private repositories are still subject to account access, backups and permissions. If `gh` asks you to authorise a browser login again, verify it is the official GitHub flow. If the repository is owned by an organisation, its policies may restrict creation or pushing.

**Practice:** Explain what `origin` is, why `--push` sends only committed content and what `--private` changes. Compare your local `git log -3` to the History/Commits view in the browser.

**Next:** [Clone and collaborate with the Umicom community](275-clone-and-contribute-to-umicom.md).
