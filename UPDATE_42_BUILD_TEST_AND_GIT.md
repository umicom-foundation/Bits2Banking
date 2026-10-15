# Bits2Banking Major Update 42 — Build, Test and Git

**Umicom Foundation · 14 October 2026 · Interactive PowerShell instructions only**

This batch is an **additive review package** for `C:\umicom\Umicom-Bits2Banking`. It contains only new lessons, supporting media and one ISO C23 laboratory. It does not replace `mkdocs.yml`, earlier lessons or any prior native source. Umicom Framework, Applications, Kernel and OS are unchanged.

## 1. Review and merge the ZIP

Save the ZIP to `C:\umicom`, then in PowerShell 7:

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-42-Reproducible-Systems-and-C23-Deployment.zip" -DestinationPath ".\Bits2Banking-Update42-Review" -Force
```

Open **Beyond Compare**. Compare:

- Left: `C:\umicom\Bits2Banking-Update42-Review\Umicom-Bits2Banking`
- Right: `C:\umicom\Umicom-Bits2Banking`

Review each new file and merge only intended additions. **Do not mirror, delete, or replace the complete repository.** This ZIP does not contain replacement versions of prior `.c`, `.h`, Markdown or CMake files.

**Prerequisites:** Updates 39, 40 and 41 already merged, because the new C23 example links their preserved laboratories. If any is missing, merge that update first without discarding your existing source.

## 2. Configure ISO C23

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\deployment-rehearsal" `
    -B ".\output\learning-build\deployment-rehearsal" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
```

The expected outcome is a configured build directory. Stop and report the first error if configuration fails. The commands do not create PowerShell scripts.

## 3. Compile and test

```powershell
cmake --build ".\output\learning-build\deployment-rehearsal" --parallel 2
ctest --test-dir ".\output\learning-build\deployment-rehearsal" --no-tests=error --output-on-failure
```

**Reference Linux validation:** 79/79 native tests passed, including **22 new Update 42** tests and **57 inherited tests** from Updates 39–41. The exact result must be verified on your Windows UCRT64 host; do not copy the reference result into your acceptance report without running the suite.

Run the demonstration:

```powershell
& ".\output\learning-build\deployment-rehearsal\btb-deployment-review-demo.exe"
```

Expected illustrative output includes `PENDING` and later `QUALIFIED`, with a clear warning that this is fictional evidence, not real installer or service verification.

## 4. Optional private installation exercise

This writes an executable **only** into the named practice prefix. Check that the folder is appropriate and contains no important existing files.

```powershell
Test-Path "C:\umicom\learning-stage-update42"
cmake --install ".\output\learning-build\deployment-rehearsal" --prefix "C:\umicom\learning-stage-update42"
Get-ChildItem "C:\umicom\learning-stage-update42\bin"
& "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe"
```

Do not run this part if the destination would overwrite personal work. Choose a different empty private prefix instead. No `Run as administrator`, service installation, OS image modification, firewall change or registry access is needed.

## 5. Confirm the documentation

Read `UPDATE_42_NAVIGATION_AND_REVIEW.md`. The file `UPDATE_42_MKDOCS_NAV_SNIPPET.yml` is **only a fragment** to merge into your current `mkdocs.yml`; it is not a standalone configuration. Preserve all previous chapters and the original *Islam: Blueprint for Life* navigation.

If the repository's existing MkDocs environment is available, use its already-installed CLI:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
mkdocs build --strict
```

This batch adds **no Python or PowerShell scripts**. MkDocs is a pre-existing publishing dependency, not newly introduced application logic. If the command is unavailable, report that the website publication gate was not run.

## 6. Git — stage, review, commit and push to `main`

After actual builds and documentation review:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add virtualisation and native C23 deployment rehearsal"
git push origin main
git status
```

**Important:** `git add -A` includes all changed and deleted files in this repository. Verify that `main` is selected, and review the staged diff for unrelated modifications before running `git commit` or `git push`. If the push is rejected, inspect the divergence instead of force-pushing.

## 7. Linux reference commands

```bash
cmake -S labs/native/deployment-rehearsal -B output/learning-build/deployment-rehearsal -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/deployment-rehearsal --parallel 2
ctest --test-dir output/learning-build/deployment-rehearsal --no-tests=error --output-on-failure
./output/learning-build/deployment-rehearsal/btb-deployment-review-demo
```

No software in this package controls a real OS service or publishes to GitHub automatically.
