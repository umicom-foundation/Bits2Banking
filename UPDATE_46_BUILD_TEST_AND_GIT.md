# Major Update 46 — Merge, Build, Test and Git (PowerShell commands only)

This update adds material to **Umicom-Bits2Banking only**. No new PowerShell or Python scripts are included. PowerShell below is for **interactive** commands, not an application implementation language.

## 1. Prepare and review

1. Save the update ZIP to `C:\umicom`.
2. Open **PowerShell 7** (or Windows PowerShell for extraction if necessary).
3. Extract to a separate folder and use Beyond Compare before merging.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-46-Multihost-Administration-and-C23-Fleet-Review.zip" -DestinationPath ".\Bits2Banking-Update46-Review" -Force
```

Compare `C:\umicom\Bits2Banking-Update46-Review\Umicom-Bits2Banking` with `C:\umicom\Umicom-Bits2Banking`. **Merge new files only**; never replace the entire repository with a partial batch. Preserve previous source, comments, authored guides, books, images and all earlier test configurations. Confirm Updates 39–45 are already present, because the C23 laboratory uses their original source.

## 2. Configure, compile and test with GCC UCRT64

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
cmake -S ".\labs\native\fleet-readiness" -B ".\output\learning-build\fleet-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\fleet-readiness" --parallel 2
ctest --test-dir ".\output\learning-build\fleet-readiness" --no-tests=error --output-on-failure
```

**Expected if every previous lab is present and configured as provided: 191/191 CTest cases.** Do not claim success if compilation fails, tests are Not Run, or a prior lab was omitted. The expected count is an acceptance target, not a claim that this precise Windows build has already been executed.

### Run the demonstration

```powershell
& ".\output\learning-build\fleet-readiness\btb-fleet-readiness-demo.exe"
```

Expected fictional decisions, in order: PENDING (one missing host), REVIEWABLE (two complete observations), BLOCKED (Notes operation failed), RESTORED_ONLY (previous version independently restored). No real operating-system services are read or modified.

## 3. Website integration and checks

`UPDATE_46_MKDOCS_NAV_SNIPPET.yml` contains a standalone valid YAML `nav:` value. Add its **child navigation groups**, not a second `nav:` key, to your existing `mkdocs.yml` in Beyond Compare. Do not remove previously published navigation, including the original *Islam: Blueprint for Life* book. Before publishing, check that every referenced new path exists. If earlier updates' navigation snippets have not been merged, register those first to avoid presenting a broken course sequence.

The website currently uses an existing MkDocs toolchain. **No Python implementation files are introduced** by this update. If you already have the project's configured virtual environment, the existing publication check is:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

If that environment is unavailable, mark the site build **Not Run**. Do not claim a successful complete website build based on YAML syntax checks alone. The self-contained offline HTML course can be opened in any modern browser, including without MkDocs.

## 4. Git add, commit and push — Bits2Banking only

Proceed **only after review**, build/test evidence and checking that the active branch is `main`. `git add -A` stages every deletion as well as additions; review its output carefully.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add multi-host administration course and C23 fleet review"
git push origin main
git status
```

If `git push` is rejected, inspect local and remote histories; never automatically force-push or discard work. No Framework, OS, Kernel or Applications gitlinks require changing for this **educational-only** batch.
