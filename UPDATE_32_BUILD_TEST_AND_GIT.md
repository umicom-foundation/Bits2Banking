# Major Update 32 — Windows PowerShell build, test and Git instructions

**Applies to:** `C:\umicom\Umicom-Bits2Banking` only. These are **interactive commands**; this batch does not deliver `.ps1` or `.py` files. Confirm the checkout is `main`, inspect every staged path and finish the required tests before committing.

## 1. Save and extract the review package

Save `Umicom-Bits2Banking-Update-32-Git-Release-Qualification-and-C23-Evidence.zip` in `C:\umicom`. Verify its SHA-256 against the **separately supplied trusted checksum** before extraction.

```powershell
Set-Location "C:\umicom"
Get-FileHash -LiteralPath ".\Umicom-Bits2Banking-Update-32-Git-Release-Qualification-and-C23-Evidence.zip" -Algorithm SHA256
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-32-Git-Release-Qualification-and-C23-Evidence.zip" -DestinationPath ".\Bits2Banking-Update32-Review" -Force
```

Compare **Left** `C:\umicom\Bits2Banking-Update32-Review\Umicom-Bits2Banking` with **Right** `C:\umicom\Umicom-Bits2Banking` in Beyond Compare. Merge the reviewed new paths only. **Do not replace the complete repository or use mirror/delete synchronisation.**

## 2. Configure and compile native C23 tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
cmake -S ".\labs\native\git-release-evidence" -B ".\output\learning-build\git-release-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-release-evidence" --parallel 2
```

The build sets C23 and strict warning flags including `-Werror`. Fix legitimate diagnostics rather than turning off a warning without review.

## 3. Run the release-gate suite

```powershell
ctest --test-dir ".\output\learning-build\git-release-evidence" --output-on-failure
& ".\output\learning-build\git-release-evidence\btb-git-release-gate-demo.exe"
```

**Expected registered tests:** 34/34. The executable demonstration prints a READY line followed by BLOCKED lines; it does not use your real Git checkout. Compare output against the model in `gate_demo.c`.

## 4. Regression checks from prior batches

If the earlier laboratories are installed and have build configurations:

```powershell
cmake --build ".\output\learning-build\work-handoff" --parallel 2
ctest --test-dir ".\output\learning-build\work-handoff" --output-on-failure
cmake --build ".\output\learning-build\git-history" --parallel 2
ctest --test-dir ".\output\learning-build\git-history" --output-on-failure
```

Only claim these checks if they actually execute. The installed `work-dispatch` and HTTP builds require their existing configured dependencies and should be verified independently.

## 5. Publish and validate learning content

`UPDATE_32_NAVIGATION_AND_REVIEW.md` contains **additive** entries for Chapters 204–215 and Episodes 70–73. Merge the earlier Update 31 navigation additions first if Chapters 167–203 are not already registered. Preserve all old navigation, especially the historical *Islam: Blueprint for Life* material.

Once MkDocs is installed in the existing virtual environment, build the website using the **existing tool**, not a new Python script:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

If that existing environment is not available, mark the documentation build **NOT RUN**. Do not claim its success on the basis of YAML-only validation.

## 6. Commit to `main` — requested standard commands

After reviewing staged scope and passing required tests:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --name-status
git commit -m "feat(learning): add Git release qualification and native C23 evidence gates"
git push origin main
git status
```

**Safety:** `git add -A` stages all changes in this repository, not just the ZIP. Stop if the staged diff contains unrelated changes or deletions. On a non-fast-forward rejection, fetch and inspect ancestry; never force push as an automatic repair. No other Umicom repository should be committed merely to install this educational batch.
