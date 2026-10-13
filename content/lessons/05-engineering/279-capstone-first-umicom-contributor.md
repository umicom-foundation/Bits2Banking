# Chapter 279 — Capstone: become a prepared Umicom contributor

**Bits to Banking · Absolute Beginner Course · Unit 4: Assessment**  
**Time:** 60–90 minutes, preferably split into two sessions. Instructor rubric in `UPDATE_37_INSTRUCTOR_GUIDE.md`.

## Capstone objective

Demonstrate that you can open the correct shell, work in a safe folder, inspect essential computer information, configure Git identity, publish a **practice** GitHub repository, and build and test a small native C23 application. You will also learn to distinguish what each successful check actually proves. This is an onboarding assessment, **not** a qualification to deploy production banking software or modify the Umicom Kernel.

## Part A — Shell and machine (20 points)

1. Open PowerShell 7. If you are on Linux, use a terminal and explain your shell.
2. Show the current directory without changing it.
3. Identify your shell version, Windows edition (where applicable), CPU, RAM and available disk space.
4. Create a practice folder under your own home directory, enter it, and make a small Markdown file.
5. Show how to preview, without executing, the deletion of a disposable file using `-WhatIf` on Windows.

**Evidence to retain:** your commands, what they do, and a few non-sensitive lines of output. Never submit serial numbers, passwords, private paths or full token output.

## Part B — Local Git history and online hosting (30 points)

1. Enter `notes-practice` and explain why this is safer than experimenting inside Framework.
2. Create or inspect the `main` branch, then stage and commit a Markdown change.
3. Run `git diff`, `git diff --cached`, `git status` and `git log --oneline -3`; explain why some are empty depending on state.
4. Authenticate GitHub CLI using the official browser flow if required.
5. Publish or verify a **private** practice repository using `gh repo create ... --push` and `gh repo view --web`.
6. Make a further *reviewed* change and demonstrate `git add -A`, `git diff --cached --check`, `git commit` and `git push origin main`.

**Evidence to retain:** the public/private visibility setting, latest commit summary (not secrets), and an explanation of local commit versus remote push. There is no need to make your repository public for marking.

## Part C — C23 build and automated tests (30 points)

1. Explain the purpose of `notes.h`, `notes.c`, `main.c`, `test_notes.c` and `CMakeLists.txt`.
2. Confirm GCC, CMake and Ninja versions using the correct executable paths.
3. Configure the `labs/native/contributor-notes` project using CMake and Ninja.
4. Build its executable, then run the **eight** registered CTest checks.
5. Run the demonstration and explain why its notes do not persist after exit.
6. Identify a negative test that refuses invalid input without changing existing state.

**Evidence to retain:** the configure result, build outcome and test count; record failures accurately rather than editing the report to show green results.

## Part D — Safety and communication (20 points)

1. Explain why normal learning commands should not require `Run as Administrator`.
2. Distinguish the system login, Git author and GitHub account.
3. Explain what an upstream Git repository is and why you cannot push to every repository you can clone.
4. Explain the danger of `git add -A` when run in the wrong folder.
5. Describe the safe first response to a detached HEAD or a submodule conflict.

**Success standard:** 80/100 with no safety-critical misunderstanding, or a reviewed resubmission of the affected section. Instructors should value accurate failure reporting over a falsely claimed successful build.

## Learner reflection

Which step was unfamiliar? Which error message did you learn to read? What would you want a future new contributor to see in the guide? Submit a suggested wording improvement through the normal course review channel. Teaching improves when each learner can report a precise obstacle.

## Your next path

You now have enough fundamentals to work through the optional advanced Units 5 and 6 in Chapters 280–283. These explain native Framework repository checks, build automation, regression selection and versioned delivery. You may also return to the existing introductory Git Chapters 16–17 for more practice.

**Next:** [Verify Umicom repositories through existing Framework tools](280-use-framework-repository-verify.md).
