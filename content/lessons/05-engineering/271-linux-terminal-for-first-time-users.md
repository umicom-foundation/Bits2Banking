# Chapter 271 — Launch a Linux terminal and understand the same ideas

**Bits to Banking · Absolute Beginner Course · Unit 2**  
**Time:** 30–45 minutes · **Applies to:** common desktop Linux distributions. Installation commands differ by distribution.

## Same purpose, different shell

On Windows our principal shell is **PowerShell 7**. On Linux a common choice is **Bash**, displayed in a terminal such as GNOME Terminal or Konsole. You still type commands and press Enter. The important concepts remain the same: current directory, files, processes, permissions, storage and networking. **The syntax is not identical**: `Get-Location` is a PowerShell command; `pwd` is a standard Unix-style command. Git, CMake and Ninja use largely similar command names on both operating systems.

## Step 1 — Open the terminal

Open your desktop's Applications menu, search for **Terminal**, then start it. Many distributions also support **Ctrl+Alt+T**, but do not assume that shortcut works everywhere. You should see a prompt, commonly containing a username and current directory.

```bash
pwd
```

This prints your current working directory, typically `/home/student`. On Linux, forward slashes `/` separate path segments. Unlike Windows, a path generally does not start with a drive letter.

## Step 2 — Work in a safe course folder

```bash
mkdir -p "$HOME/UmicomLearning/notes-practice"
cd "$HOME/UmicomLearning/notes-practice"
pwd
ls -la
```

`mkdir -p` creates the requested folder and missing parents. `cd` changes directory. `ls -la` shows detailed entries including dot-prefixed hidden files. Paths are generally case-sensitive: `README.md` and `readme.md` may be different files.

Create the same simple text document as the Windows course:

```bash
printf '%s\n' '# My first Umicom Notes project' > README.md
cat README.md
```

**Warning:** `>` redirects output and **overwrites** the named file. We use it only inside a disposable new practice folder. Do not run this command against a real source file that may contain important content. Prefer a text editor for ongoing changes.

## Step 3 — Ask about the operating system and hardware

```bash
uname -a
lscpu
df -h
free -h
```

`uname` reports kernel information. `lscpu` describes processor architecture and CPU topology. `df -h` reports filesystem capacity. `free -h` reports memory. Exact options and results depend on the distribution and installed tools. For an account name, run `whoami`; for identity and groups, run `id`.

## Step 4 — Check essential development commands

```bash
git --version
cmake --version
ninja --version
gcc --version
```

If a command is missing, use your distribution's official package manager instructions rather than pasting an unfamiliar `curl | bash` command from a website. On Debian- or Ubuntu-based systems, packages such as `git`, `cmake`, `ninja-build` and `build-essential` are often provided through APT; Fedora and other distributions use different tools. Installation needs the appropriate account permissions and update policy.

## Linux and Windows orientation

| Task | Windows PowerShell 7 | Linux Bash |
|---|---|---|
| Current folder | `Get-Location` or `pwd` | `pwd` |
| List files | `Get-ChildItem` | `ls -la` |
| Change folder | `Set-Location` or `cd` | `cd` |
| Create folder | `New-Item -ItemType Directory` | `mkdir -p` |
| Show text | `Get-Content README.md` | `cat README.md` |
| CPU / memory | `Get-CimInstance` | `lscpu` / `free -h` |
| Git status | `git status` | `git status` |

**Practice:** Create a private Linux Notes folder, list it, and explain one difference between a Windows drive path and a Linux path. Do not run administrative or destructive commands while exploring.

**Next:** [Configure Git identity and GitHub authentication](272-configure-git-and-sign-in-to-github.md).
