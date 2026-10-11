# Update 17 — Build, test and publish

## 1. Review and merge the ZIP

Extract `Umicom-Bits2Banking-Update-17-Interrupt-Ownership-and-Recovery.zip` into an empty review folder. The archive contains the two same-named repository folders. Use Beyond Compare to merge the source and lesson changes, **not** the complete repository folders. The Framework changes are limited to its standalone education tool; the Umicom Kernel repository is untouched.

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-17-Interrupt-Ownership-and-Recovery.zip" `
    -DestinationPath ".\Bits2Banking-Update17-Review" `
    -Force
```

Compare:

```text
C:\umicom\Bits2Banking-Update17-Review\Umicom-Applications\framework
C:\umicom\Umicom-Applications\framework

C:\umicom\Bits2Banking-Update17-Review\Umicom-Bits2Banking
C:\umicom\Umicom-Bits2Banking
```

## 2. Build Framework's Umicom Education command

Use your existing CMake/Ninja configuration and UCRT64 compiler. Do not erase the incremental build tree.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "Education configuration failed." }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Education build failed." }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Education tests failed." }
```

The cumulative Update 17 source registers **26 tests**. The two new cases are `framework.education.interrupt_trace` and `framework.education.interrupt_trace.cli`; CTest orders their shared synthetic fixture correctly even with parallel execution.

## 3. Inspect the teaching trace

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Trace = ".\build\umicom-education\education-interrupt-trace-test\fixture with spaces\owned interrupt.irq"

& $Education interrupt-trace --file $Trace
if ($LASTEXITCODE -ne 0) { throw "Interrupt trace inspection failed." }
```

Expected: **20 records, 3 claims, 4 arms, 3 entries, 2 acknowledgements, 2 returns, 1 cancellation, 1 fault, 1 recovery, 3 releases, peak owned 2, final owned 0**. These records are classroom evidence, not a physical interrupt log.

## 4. Build the C23 ownership laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\interrupt-ownership" `
    -B ".\output\learning-build\interrupt-ownership" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Ownership lab configuration failed." }

cmake --build ".\output\learning-build\interrupt-ownership" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Ownership lab build failed." }

ctest --test-dir ".\output\learning-build\interrupt-ownership" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Ownership lab tests failed." }
```

Expected: **2/2 tests passed**.

## 5. Build the C23 service-recovery laboratory

```powershell
cmake -S ".\labs\native\service-recovery" `
    -B ".\output\learning-build\service-recovery" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Recovery lab configuration failed." }

cmake --build ".\output\learning-build\service-recovery" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Recovery lab build failed." }

ctest --test-dir ".\output\learning-build\service-recovery" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Recovery lab tests failed." }
```

Expected: **2/2 tests passed**. This lab reuses `interrupt-ownership/owner.c`; it does not introduce another owner implementation.

## 6. Build and preview the lesson website

The established MkDocs publishing pipeline still requires the repository's existing Python virtual environment. Update 17 does not add new Python source.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs website build failed." }

if (-not (Test-Path ".\site\index.html")) {
    throw "MkDocs did not produce site/index.html."
}
```

Preview using the native Framework C server:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education serve --repo $Books --port 8765
```

Visit `http://127.0.0.1:8765/`. Check chapters 112–116, video episodes 36–37, all three illustrations and the historical Islam volume. Stop with Ctrl+C.

## 7. Commit the updated repositories to main

Only publish after reviewing actual local test results and staged files. Stop if the Framework submodule is detached; attach it to the intended branch before committing. Do not include unrelated submodules.

### Framework first

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): inspect interrupt ownership and recovery traces"
git push origin main
```

### Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach interrupt ownership and checked recovery"
git push origin main
```

### Umicom Applications parent last

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record interrupt education inspection"
git push origin main
```

Do not create empty commits when a repository has no staged changes. If any test fails, retain the output and do not publish that repository's changes yet.
