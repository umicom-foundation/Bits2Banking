# Major Update 13 — Build, Test, Preview and Git

## 1. Review and merge the batch

The ZIP contains only new and changed files. Its top-level folders match the local checkouts: `Umicom-Applications` and `Umicom-Bits2Banking`. Extract into a separate directory and use Beyond Compare to merge reviewed files. **Do not replace the entire repositories.**

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-13-Processes-Page-Faults-and-WX-Review.zip" -DestinationPath ".\Bits2Banking-Update13-Review" -Force
```

Compare the extracted `Umicom-Applications\framework` against `C:\umicom\Umicom-Applications\framework`, then compare extracted `Umicom-Bits2Banking` against `C:\umicom\Umicom-Bits2Banking`. Review the complete replacements for `main.c`, `CMakeLists.txt` and `mkdocs.yml` carefully: none of their previous commands, content or historical book navigation should be lost.

## 2. Configure, build and test Umicom Framework Education

Use Windows PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Framework Education configure failed" }
cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Framework Education build failed" }
ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Framework Education tests failed" }
```

Expected: **18/18** tests, two more than Update 12. The new tests are `framework.education.memory_audit` and `framework.education.memory_audit.cli`.

Inspect the actual generated RISC-V64 ELF fixture. The parser test generates it before the CLI test runs:

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Fixture = ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
& $Education memory-audit --file $Fixture
if ($LASTEXITCODE -ne 0) { throw "ELF permission audit reported a review finding" }
```

The fixture should show **two mapped virtual pages** and **zero writable and executable pages**. The command does not start the Kernel.

## 3. Build and test Page Fault Model

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\page-fault-model" `
    -B ".\output\learning-build\page-fault-model" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Page Fault Model configure failed" }
cmake --build ".\output\learning-build\page-fault-model" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Page Fault Model build failed" }
ctest --test-dir ".\output\learning-build\page-fault-model" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Page Fault Model tests failed" }
& ".\output\learning-build\page-fault-model\btb-page-fault-demo.exe"
```

Expected: **2/2 tests**. The demonstration reports one permitted instruction fetch, one protection fault and one unmapped-page fault. It performs no privileged memory mapping.

## 4. Build and test Process Lifecycle Model

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\process-lifecycle" `
    -B ".\output\learning-build\process-lifecycle" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Process Lifecycle configure failed" }
cmake --build ".\output\learning-build\process-lifecycle" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Process Lifecycle build failed" }
ctest --test-dir ".\output\learning-build\process-lifecycle" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Process Lifecycle tests failed" }
& ".\output\learning-build\process-lifecycle\btb-process-demo.exe"
```

Expected: **2/2 tests**. The process transitions from `new` to `terminated` with revisions 1 through 7; no real process is created.

## 5. Build and preview the educational website

The established MkDocs renderer remains required for publication. It is **not** a new application implementation language introduced by this batch.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "Strict website build failed" }
Test-Path ".\site\index.html"
```

Expected: `True`. The original Islam volume and the 151 previously linked website pages must remain in navigation alongside the 7 new pages.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education audit --repo $Books
if ($LASTEXITCODE -ne 0) { throw "Navigation audit failed" }
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and check Lessons 92–96, Episodes 28–29, diagrams, existing books and the ten original Islam chapters. Stop with Ctrl+C.

## 6. Stage and publish the Git repositories

**Framework first:**

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): audit ELF executable page permissions in C23"
git push origin main
```

**Bits2Banking next:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach process memory page faults and W-X policy"
git push origin main
```

**Umicom Applications last, to record the updated Framework commit:**

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record education memory audit update"
git push origin main
```

Confirm `main` before each commit. Inspect the staged changes, and stop on unexpected deletions or unrelated modifications. Do not force-checkout, reset, or commit on a detached submodule HEAD. If a repository has no changes, do not create an empty commit.
