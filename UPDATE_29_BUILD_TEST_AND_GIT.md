# Major Update 29 — Build, Test and Git (PowerShell commands only)

Extract the ZIP into a review folder under `C:\umicom`, and compare `Umicom-Bits2Banking` with the existing repository in Beyond Compare. Only merge approved additions. The top-level folder is preserved and existing files are not overwritten.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-29-C23-Work-Handoff.zip" -DestinationPath ".\Bits2Banking-Update29-Review" -Force
```

## Configure and compile the native C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-handoff" -B ".\output\learning-build\work-handoff" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-handoff" --parallel 2
ctest --test-dir ".\output\learning-build\work-handoff" --output-on-failure
& ".\output\learning-build\work-handoff\btb-work-handoff-demo.exe"
```

Expected: **5/5 native CTest cases**. This is a separate lab; the pre-existing 18 or 19 HTTP tests are not automatically executed. Run the existing HTTP and MkDocs suites as separate regression checks.

## Full regressions on your computer

```powershell
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

The last command invokes an already-installed publishing tool; **this batch does not create Python code or scripts**. If the environment does not have MkDocs installed, report that gate as not run. The five new chapters deliberately are **not** inserted into `mkdocs.yml` without the current repository file; navigation registration remains an outstanding integration task.

## Commit this repository only

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add native C23 bounded work handoff laboratory"
git push origin main
git status
```

Verify the active branch is `main` and exclude unrelated changes before committing. No extra repositories are modified.
