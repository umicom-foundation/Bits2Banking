# Major Update 39 — Review, Build, Test and Git (interactive PowerShell only)

**Scope:** Only `C:\umicom\Umicom-Bits2Banking`. Framework, Applications, Kernel and OS source must remain unchanged. No `.ps1` or `.py` implementation files are delivered.

## 1. Extract into a review directory

Save the ZIP under `C:\umicom`, then run:

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-39-Intermediate-Sysadmin-and-C23-Evidence.zip" -DestinationPath ".\Bits2Banking-Update39-Review" -Force
```

Compare **left** `C:\umicom\Bits2Banking-Update39-Review\Umicom-Bits2Banking` against **right** `C:\umicom\Umicom-Bits2Banking` in Beyond Compare. Merge the **new files only**. Do not mirror/delete existing directories or overwrite `mkdocs.yml`. The navigation snippet requires manual review against the latest local configuration. Existing original manuscripts and the contributed project creation guide from Update 38 are not modified.

## 2. Configure native C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sysadmin-evidence" -B ".\output\learning-build\sysadmin-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
```

This is an independent educational laboratory and does not invoke Git, system service managers or administrative commands. Configuration creates build output under the ignored `output/learning-build` directory.

## 3. Build and run the tests

```powershell
cmake --build ".\output\learning-build\sysadmin-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-evidence" --no-tests=error --output-on-failure
& ".\output\learning-build\sysadmin-evidence\btb-sysadmin-evidence-demo.exe"
```

Expected **16/16 CTest cases**. The demonstration prints `REVIEW` for two fictional required PASS observations plus one optional WARNING. It does not inspect your PC or qualify a production operating system.

## 4. Optional existing native regression and publication gates

```powershell
cmake --build ".\output\learning-build\sysadmin-readonly-text" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-readonly-text" --no-tests=error --output-on-failure
```

Only run the above if the prior Update 38 build directory has been configured; otherwise report NOT RUN. To verify MkDocs after merging the reviewed site navigation, invoke the **existing installed publishing tool** (do not create Python scripts):

```powershell
mkdocs build --strict
```

If MkDocs is not installed or there are errors from other unmerged historical batches, record that accurately. Confirm original *Islam: Blueprint for Life* navigation remains in the site and the course chapters 25–36 appear in order. The offline HTML course can be opened without MkDocs.

## 5. Git add, commit and push (main only)

**Only after reviewing and testing:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): extend system administration and C23 evidence course"
git push origin main
git status
```

`git add -A` stages **all** additions, modifications and deletions in the current repository. Review the staged diff before committing. Do not commit if the branch is detached, tests fail, or the staging area contains unrelated work. Do not use force push or reset/clean to bypass a Git error. If the remote rejects the push, inspect and reconcile the history safely.
