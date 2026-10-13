# Git and build diagnostics — professional Umicom quick reference

**Bits to Banking · Update 35 · Umicom Foundation**

This reference complements [Chapters 240–251](update-35-learning-path.md). Every PowerShell line is intended for direct interactive use, **not** as a saved `.ps1` file. Check the repository path before running a command. Never paste credentials, access tokens or secrets into terminal transcripts shared for support.

## Inspect source safely

| Question | Command | Important interpretation |
|---|---|---|
| What changed? | `git status` | Only local status, not proof of testing |
| Which branch? | `git branch --show-current` | Blank may mean detached HEAD |
| Which exact commit? | `git rev-parse HEAD` | Does not describe uncommitted edits |
| Which upstream branch? | `git branch -vv` | Tracking configuration may be absent |
| Is remote history newer? | `git fetch origin main` | Fetches metadata and objects; does not merge |
| What commits are local only? | `git log --oneline origin/main..HEAD` | Review before moving HEAD |
| What commits are remote only? | `git log --oneline HEAD..origin/main` | Avoid non-fast-forward pushes |
| What is staged? | `git diff --cached --stat` | Review before commit |
| What does a child checkout contain? | `git -C .\framework status --short` | Run inside the parent repository |
| Which gitlink does the parent track? | `git ls-files --stage -- framework` | Mode 160000 means submodule |

## Respond to a blocked submodule update

Check the submodule status and local work first. Preserve modified/untracked files through a reviewed commit or Git stash if necessary. A stash does not include ignored artefacts by default. After verifying that preservation succeeded, inspect the remote commits and choose the intended checkout revision. Do **not** run `git reset --hard`, `git clean -fd`, a forced submodule checkout or a forced push to make the error disappear.

A detached HEAD is normal for pinned submodules. Only switch a **clean, reviewed** Framework checkout to local `main` when you deliberately intend to modify/publish Framework itself. A parent repository records the selected child SHA in a gitlink; synchronising Framework's remote does not update the parent pointer until a separate parent commit.

## Build without making new scripts

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\build-evidence" -B ".\output\learning-build\build-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence" --output-on-failure
```

The standalone demo is `btb-build-evidence-demo.exe`. It reports a *fictional* before/after diagnostic comparison. Build/test evidence from a Linux GCC run is not a claim that Windows UCRT64 or an installed Framework SDK target passed.

## Diagnose the first real failure

| Observation | First action |
|---|---|
| `CMake Error` during configure | Verify preset, cache, compiler and dependency discovery |
| `FAILED:` compiling C source | Read the full compile command and earliest compiler error |
| `undefined reference` or duplicate symbol | Inspect target dependencies, exported symbols and ownership |
| CTest `Failed` | Examine named test output and source state |
| CTest `Not Run` | Verify executable was built; do not count it as passed |
| Program launches only with MSYS2 PATH | Verify packaged runtime DLL/resource staging and desktop launch |
| Git push rejected non-fast-forward | Fetch, compare histories, preserve local commits; never force-push reflexively |

## Standard direct-to-main Git sequence

Only after tests and staged diff review:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): extend native C23 build evidence and Framework Git lessons"
git push origin main
git status
```

`git add -A` stages **additions, modifications and deletions** throughout the current repository. Confirm the staged changes are intended; a correct command executed in the wrong repository is still a mistake. For a multi-repository Umicom change, publish Framework source first, then test and publish consumer gitlinks separately.

## Release-evidence checklist

Check exact source SHA and dirty state, Framework dependency pin, build profile and toolchain, compiler/linker exit, diagnostic count and dropped count, CTest outcomes including skipped/not-run, platform launch acceptance, and reproducibility. Incomplete information should be reported as **not run / unknown**, not silently treated as success.
