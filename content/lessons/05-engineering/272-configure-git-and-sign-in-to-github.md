# Chapter 272 — Configure Git and sign in to GitHub

**Bits to Banking · Absolute Beginner Course · Unit 3: Version control**  
**Time:** 25–40 minutes · **Requirements:** Git and GitHub CLI installed; a GitHub account you control.

## Three identities you must not confuse

Your **computer login** gives you access to Windows or Linux. Your **Git author identity** is the display name and email stored alongside new Git commits. Your **GitHub account** is your online account with permissions to hosted repositories. These can have different names. Git commit author information is not itself proof that the person was authenticated to GitHub; authentication is a separate step.

Before this lesson, sign up at the official GitHub website if you do not already have an account: https://github.com/signup . Confirm your email according to GitHub's instructions. Choose a strong, unique password and enable multi-factor authentication. **Never send a password, authentication token or recovery code to an instructor.**

## Step 1 — Check that Git and GitHub CLI work

Open PowerShell 7, then type each command on its own line:

```powershell
git --version
gh --version
```

Both should print version information. If either says it cannot find the command, revisit Chapter 265; authentication cannot repair an installation problem.

## Step 2 — Configure the name recorded in future commits

```powershell
git config --global user.name (Read-Host "Your display name")
```

After pressing Enter, PowerShell asks for a name. Type the name you want on your commits and press Enter. **Do not type your name into the source code or the parentheses**; `Read-Host` collects the answer for this one command. This operation changes Git's global configuration for your account; it does not register a GitHub username.

Next configure an email associated with your GitHub account, or your GitHub-provided private no-reply email if you prefer privacy:

```powershell
git config --global user.email (Read-Host "Your verified Git commit email")
```

**Do this once, not three times.** Repeating the same command is unnecessary. Be aware that commits can make the configured email visible in repository history; use an appropriate privacy setting and never use somebody else's address without authorisation.

## Step 3 — Confirm what Git stored

```powershell
git config --global --get user.name
git config --global --get user.email
```

You should see the values you entered. If they are wrong, rerun only the relevant `git config` command. Global configuration is usually stored in a configuration file in your home folder; you should not need to edit it manually.

## Step 4 — Sign into GitHub CLI

First ask whether you are already authenticated:

```powershell
gh auth status
```

If it reports you are not signed in, start the guided login:

```powershell
gh auth login
```

Choose **GitHub.com** when asked for the host. Follow the prompts, normally selecting **HTTPS** for Git operations and **Login with a web browser**. GitHub CLI may display a short one-time device code and open a browser where you confirm it. Use the official GitHub login page, not a link supplied by an unknown person. After finishing, return to PowerShell and run `gh auth status` again. This command checks which account `gh` can currently use; it does not prove your permission to every repository.

## Step 5 — Understand what was *not* done

You have not created a local Git repository, made a commit, or uploaded any files. You have installed tools, given future commits an author label and authorised a CLI to communicate with GitHub. That separation helps diagnose later errors.

**Security note:** GitHub CLI normally stores credentials through the available operating-system credential store, but storage behaviour depends on the environment. Do not display or share saved tokens. Review the official manual if your account is managed: https://cli.github.com/manual/gh_auth_login .

**Practice:** Explain the differences between Git identity, GitHub authentication and repository write permission. Record the output of `git --version`, and state whether `gh auth status` succeeds, without posting any secret values.

**Next:** [Create your first local repository](273-create-and-commit-first-local-git-repository.md).
