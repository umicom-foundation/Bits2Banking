# Major Update 40 — Merge, Build, Test and Git (Interactive PowerShell)

**Umicom Foundation · Sammy Hegab · 14 October 2026**  
**Repository affected:** `C:\umicom\Umicom-Bits2Banking` only.  
**Prerequisite:** Update 39 must already be merged because the Update 40 C23 target **links** `labs/native/sysadmin-evidence`; it does not include another copy of the old source.

## A. Check the ZIP and review location

Save `Umicom-Bits2Banking-Update-40-Practical-System-Administration-and-C23-Readiness.zip` under `C:\umicom`.

```powershell
Set-Location "C:\umicom"
Get-FileHash -Algorithm SHA256 -LiteralPath ".\Umicom-Bits2Banking-Update-40-Practical-System-Administration-and-C23-Readiness.zip"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-40-Practical-System-Administration-and-C23-Readiness.zip" -DestinationPath ".\Bits2Banking-Update40-Review" -Force
```

Compare with Beyond Compare:

- **Left:** `C:\umicom\Bits2Banking-Update40-Review\Umicom-Bits2Banking`
- **Right:** `C:\umicom\Umicom-Bits2Banking`

**Merge reviewed additions only.** Do not mirror/delete the destination or overwrite an entire repository with a partial batch. Check that `labs/native/sysadmin-evidence/admin_evidence.h` and its original implementation remain unchanged.

## B. Configure and compile C23

Open **PowerShell 7**. These are interactive instructions; no `.ps1` or `.py` implementation scripts are introduced.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\service-readiness" -B ".\output\learning-build\service-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\service-readiness" --parallel 2
```

If CMake reports that `../sysadmin-evidence` is missing, stop and merge Update 39 first. Do not create fake files or modify the old library to suppress the error.

## C. Run regression tests

```powershell
ctest --test-dir ".\output\learning-build\service-readiness" --no-tests=error --output-on-failure
```

**Expected:** 32 registered tests (16 new and 16 retained from Update 39). This is an expectation from the package; it has **not yet been verified on your Windows/UCRT64 machine**.

Run the fictional demonstration:

```powershell
& ".\output\learning-build\service-readiness\btb-service-readiness-demo.exe"
```

Expected text includes `Ready: 2, review: 0, blocked: 0`. The demonstration does not inspect any real Windows service or Umicom application.

To isolate one negative test:

```powershell
ctest --test-dir ".\output\learning-build\service-readiness" -R "service-readiness.inherited-block" --no-tests=error --output-on-failure
```

A **passing test** deliberately checks that a fictional service was marked **BLOCKED** when its prerequisite failed.

## D. Verify navigation and the complete site separately

This package **does not replace** `mkdocs.yml`. Read `UPDATE_40_NAVIGATION_AND_REVIEW.md` and merge the additive section from `UPDATE_40_MKDOCS_NAV_SNIPPET.yml`. The live repository's `mkdocs.yml` may still lack some earlier Update 28–39 entries. Review and reconcile those separately; do not publish a navigation file that drops existing chapters or the historical *Islam: Blueprint for Life* material.

If your existing MkDocs environment is installed, run its existing publishing tool:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes the **existing** MkDocs tool; the batch does not create a Python implementation. If `.venv` is missing, record this site-build gate as **NOT RUN** rather than claiming success.

## E. Commit Bits2Banking only

After passing your Windows tests and reviewing changes:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): extend system administration and compose C23 readiness checks"
git push origin main
git status
```

Verify you are on `main`. `git add -A` includes **all** additions, modifications and deletions in this repository, so inspect staged files for unrelated work. Do not force-push if rejected; inspect the histories and preserve the changes.

**Do not commit or push Umicom Framework, Applications, Kernel or OS as part of this learning batch.**
