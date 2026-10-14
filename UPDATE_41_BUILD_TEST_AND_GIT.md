# Major Update 41 — Merge, Build, Test and Git (interactive commands)

**Author:** Sammy Hegab · Umicom Foundation · UK English.

**No `.ps1` or `.py` scripts are created.** PowerShell 7 below is used interactively for build, test and Git instructions; executable project functionality is native C23. The repo is `C:\umicom\Umicom-Bits2Banking`. Only this repository should be committed for Update 41.

## 1. Extract and compare

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-41-Managed-Services-and-C23-Recovery.zip" -DestinationPath ".\Bits2Banking-Update41-Review" -Force
```

**Beyond Compare left:** `C:\umicom\Bits2Banking-Update41-Review\Umicom-Bits2Banking`  
**Beyond Compare right:** `C:\umicom\Umicom-Bits2Banking`

Review **new additions**; do not replace the complete repository. Updates 39 and 40 must already be present for the new C23 lab. Review `UPDATE_41_NAVIGATION_AND_REVIEW.md` and add navigation without removing old chapters.

## 2. Tool versions

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
ninja --version
& "C:\msys64\ucrt64\bin\gcc.exe" --version
```

Expected: programmes report installed versions. A missing command means the toolchain is unavailable and should be resolved before configuring; do not invent output.

## 3. Configure, build and test the native C23 lab

```powershell
cmake -S ".\labs\native\maintenance-review" -B ".\output\learning-build\maintenance-review" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\maintenance-review" --parallel 2
ctest --test-dir ".\output\learning-build\maintenance-review" --no-tests=error --output-on-failure
& ".\output\learning-build\maintenance-review\btb-maintenance-review-demo.exe"
```

Expected CTest count for the reconstructed dependency tree: **57/57** (16 from Update 39, 16 from Update 40, 24 new named scenarios, and 1 new demonstration). In the sample demonstration the expected states are `ROLLBACK_REQUIRED` then `RESTORED`; **no real OS service is modified**. If any tests are Not Run or fail, report that result and do not commit as verified.

To inspect specific negative cases:

```powershell
ctest --test-dir ".\output\learning-build\maintenance-review" -R "^bits2banking\.maintenance-review\.(baseline|ready-post|blocked-post|recovery-success|preserve)$" --no-tests=error --output-on-failure
```

## 4. Site validation

After reviewing and merging the nav snippet into the existing MkDocs configuration:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes the **existing** MkDocs website generator; it does **not** introduce Python source files or scripts. If the installed environment or historical manuscript inputs are missing, mark this gate not run and document the limitation. The standalone self-contained HTML course is separately available without MkDocs.

## 5. Git status, staging, commit and push

**Use the actual `main` branch**. Do not force a push or discard uncommitted work if the repository differs from expectations.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add managed-services course and C23 maintenance review"
git push origin main
git status
```

`git add -A` stages **all** new, modified and deleted items. Review the staged diff and remove unrelated changes from the intended batch **before** committing. If the push is rejected, inspect upstream divergence; do not force push. This batch does not require commits to Framework, Umicom Applications, Kernel or OS.
