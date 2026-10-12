# Chapter 211 — Investigate failing CI without replacing working source

**Bits to Banking · Release engineering · Umicom Foundation**  
**Prerequisites:** [Chapter 198](198-bisect-a-c23-regression.md), [Chapter 210](210-release-tags-provenance-and-qualification.md).

## A red check is a diagnostic, not a deletion instruction

Imagine the Framework build fails after a GTK4 component change. A quick “fix” that removes the component from CMake may make the compiler green while silently dropping an application feature. The test outcome would then be misleading: the build passes because the implementation is no longer compiled. Umicom's preservation rule prohibits solving failures by removing code, comments or behaviour without an approved migration and review.

A CI investigation must identify the **first real error**, determine its layer, construct a reproducible local case and verify a minimal repair. Common categories include configuration and dependency discovery, C23 compilation, linking, CTest execution, application start-up, resource packaging, documentation and deployment. A warning can be the earliest signal of an ABI or ownership defect; do not automatically suppress it.

## Collect the exact failure context

Record the repository, commit SHA, build preset, compiler, toolchain environment, failing target and command. These commands help establish source identity:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git log -1 --format=%H
git submodule status
git diff --cached --check
```

For a failed CMake build, rerun the specific target with the same preset and bounded parallelism rather than changing dozens of files at once. Save the first error, not only the final `ninja: build stopped` message. A compiler failure in `src/chart/...` belongs to a different problem class from a packaging failure involving GTK runtime DLLs.

## Tests can be missing, not merely failed

CTest distinguishes failed tests from `Not Run` cases. A `Not Run` result may mean that an executable was not generated or a dependency was absent, not that the code passed. Check the configuration before interpreting any percentage. For multi-repository Umicom builds, distinguish Framework tests, Studio application tests and OS boot tests; one green set is not a substitute for the others.

As a simple local exercise, build the Update 32 C23 evidence laboratory and deliberately run it with a non-existent scenario name. The test executable prints a failed scenario and exits nonzero. Restore the normal invocation to verify that the issue is command misuse, not implementation breakage. Do not change or remove a test simply to make the report green.

## Investigate changed code with Git

```powershell
git log --oneline -12
git diff --stat HEAD~1 HEAD
git show --format=fuller --stat HEAD
```

These are read-only observations. `git bisect` can help locate a regression if you have a deterministic good/bad test and a **clean disposable worktree**; the earlier chapter describes its limits. Do not run a bisect across local uncommitted work without preserving it first. CMake configuration can be cached; stale builds can mislead a bisect unless each candidate uses an appropriate clean build directory. Build artefacts must remain outside the tracked source.

## Correct the underlying problem

A credible patch retains interfaces and features, adds or updates a focused regression test, and proves the result at the affected boundary. If a GTK4 pane crashes because a callback outlives a widget, correct lifetime management; do not remove the pane from registration. If a Framework header and source declaration differ, reconcile the interface and all consumers; do not silence the diagnostic with an unsafe cast.

When a behaviour is superseded, document why, where the replacement lives, and which existing logic remains preserved for review. Physical removal requires the project's explicit approval. The repair should be backed by an audit of the staged diff and a successful build/test run, not simply a new commit message claiming resolution.

## A reproducible incident record

Create a Markdown note with: environment, observed failure, expected behaviour, first diagnostic, impacted capability, root-cause hypothesis, minimal change, tests added, test results, remaining risks, and recovery plan. This document becomes useful input to a human reviewer or the future Umicom Studio diagnostics perspective. Keep passwords and secrets out of logs.

## Questions

What is the difference between a CTest failure and `Not Run`? Why might deleting a file from CMake conceal a defect? Which evidence proves that a fix retained user-visible behaviour? Why should a failed integration test not be replaced with an untested mock simply to satisfy CI?

**Next:** [Chapter 212 — Preserve public C23 contracts during review](212-review-native-source-and-abi-preservation.md).
