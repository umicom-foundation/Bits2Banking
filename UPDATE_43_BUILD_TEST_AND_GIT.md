# Bits2Banking Major Update 43 — PowerShell build, test and Git

**Umicom Foundation · 15 October 2026 · Review edition**

This is an additive learning update for `C:\umicom\Umicom-Bits2Banking`. It adds new Markdown chapters, illustrations, scripts for **educational videos in Markdown only** (not executable scripts) and an ISO C23 native lab. It does **not** modify Umicom Framework, Applications, Kernel, OS or any previous C source. No Python, JavaScript or PowerShell implementation scripts are introduced.

## 1. Review and merge the ZIP safely

Save `Umicom-Bits2Banking-Update-43-Secure-Remote-Administration-and-C23-Review.zip` to `C:\umicom`.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-43-Secure-Remote-Administration-and-C23-Review.zip" `
  -DestinationPath ".\Bits2Banking-Update43-Review" -Force
```

Compare the extracted `Umicom-Bits2Banking` tree on the **left** against your existing `C:\umicom\Umicom-Bits2Banking` on the **right** in Beyond Compare. Merge reviewed **additions only**. Do not mirror, clean, overwrite or replace the complete repository. The ZIP includes no existing code file replacements.

**Prerequisite:** Updates **39, 40, 41 and 42** must already be present because the Update 43 C23 laboratory composes their actual libraries. If they are missing, merge their reviewed additions first; do not transplant their internals into this lab.

## 2. Configure the native C23 laboratory

Open PowerShell **7** (start with `pwsh` if necessary). Do not create a `.ps1` file. Execute commands interactively:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\remote-access-review" `
  -B ".\output\learning-build\remote-access-review" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
```

The native policy review performs **no** SSH login, file-system change, service restart, firewall modification, Git operation or real human authorisation. A CMake error about prior libraries means the prerequisite batches are missing.

## 3. Build, test and run the demonstration

```powershell
cmake --build ".\output\learning-build\remote-access-review" --parallel 2
ctest --test-dir ".\output\learning-build\remote-access-review" `
  --no-tests=error --output-on-failure
& ".\output\learning-build\remote-access-review\btb-remote-access-review-demo.exe"
```

**Reference Linux result:** 101/101 tests passed with GCC 14.2.0 and 101/101 with Clang 17 ASan/UBSan. This includes **22 new** named cases/demo and **79 inherited tests** from previous releases. Windows UCRT64 acceptance is **not claimed** until these tests actually run on your machine. If there are `Not Run` results, do not count them as passing.

### Inspect specific refusal cases

```powershell
ctest --test-dir ".\output\learning-build\remote-access-review" `
  -R "bits2banking\.remote-review\.(host-key|transport|stale|rollback|restored|atomic-output)$" `
  --no-tests=error --output-on-failure
```

The `REVIEWABLE` teaching status **does not approve any real server access**. All host identity, deployment and access booleans are fictional caller-supplied claims.

## 4. Optional private staging of harmless demonstration

This step writes only to your chosen practice folder. Check whether the destination exists and contains important files first:

```powershell
Test-Path "C:\umicom\learning-stage-update43"
cmake --install ".\output\learning-build\remote-access-review" `
  --prefix "C:\umicom\learning-stage-update43"
Get-ChildItem "C:\umicom\learning-stage-update43\bin"
```

If a previous installation exists there, **choose a different empty practice prefix instead**. Do not install a system service or use administrator privileges to complete the course.

## 5. Merge MkDocs navigation manually

Open `UPDATE_43_MKDOCS_NAV_SNIPPET.yml` and `UPDATE_43_NAVIGATION_AND_REVIEW.md`. The snippet is an **additive fragment**, not a full `mkdocs.yml`. In your current `mkdocs.yml`, add Stage 6 chapters and references, engineering Chapters 304–307 and video Episodes 121–125 under the appropriate existing groups. Preserve the original *Islam: Blueprint for Life* volume and all earlier content.

After the reviewed edit, use your **existing** MkDocs installation if it is available:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
mkdocs build --strict
```

MkDocs is an existing publishing dependency. Update 43 adds **no Python implementation files**. If the publishing environment is unavailable, report the gate as **not run**; do not claim the full site passed.

## 6. Git Add, Commit and Push to `main`

Run only after reviewing the staged files and completing the applicable checks:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add remote administration course and C23 trust review"
git push origin main
git status
```

`git add -A` stages additions, modifications **and deletions** in this repository. It does not mean those changes are all intended; inspect them first. If `main` is not the current branch, stop and investigate. If a push is rejected, review remote history, not `--force`.

## 7. Linux build and test reference

```bash
cmake -S labs/native/remote-access-review -B output/learning-build/remote-access-review -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/remote-access-review --parallel 2
ctest --test-dir output/learning-build/remote-access-review --no-tests=error --output-on-failure
./output/learning-build/remote-access-review/btb-remote-access-review-demo
```

No background service or automation task is created. **Only the Bits2Banking educational repository is changed by merging this package.**
