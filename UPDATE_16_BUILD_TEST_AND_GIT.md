# Major Update 16 — Build, Test, Preview and Git

This delivery contains complete repository files organised under two directory
roots, matching the local checkouts:

- `Umicom-Applications/framework` → `C:\umicom\Umicom-Applications\framework`
- `Umicom-Bits2Banking` → `C:\umicom\Umicom-Bits2Banking`

Nothing needs to be copied into Umicom Kernel or Umicom OS. They remain source
references, not dependencies of the hosted C23 exercises.

## 1. Extract for review

Download the ZIP into `C:\umicom`. Run:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-16-Timers-Events-and-Recovery.zip" `
    -DestinationPath ".\Bits2Banking-Update16-Review" `
    -Force
```

Use Beyond Compare before merging:

```text
LEFT  C:\umicom\Bits2Banking-Update16-Review\Umicom-Applications\framework
RIGHT C:\umicom\Umicom-Applications\framework

LEFT  C:\umicom\Bits2Banking-Update16-Review\Umicom-Bits2Banking
RIGHT C:\umicom\Umicom-Bits2Banking
```

Merge **only the reviewed incoming files**. The full replacement files preserve
previous lines and commands; do not overwrite or delete the entire repository.

## 2. Build Umicom Education on Windows UCRT64

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Umicom Education configure failed." }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Umicom Education build failed." }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Umicom Education regression tests failed." }
```

**Expected:** 24 passing tests. The two new tests are
`framework.education.timer_trace` and `framework.education.timer_trace.cli`.
They use an explicit CTest fixture so `ctest --parallel 2` is safe.

Inspect the synthetic trace after its test generates it:

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education timer-trace --file `
    ".\build\umicom-education\education-timer-trace-test\fixture with spaces\clock events.tmr"
if ($LASTEXITCODE -ne 0) { throw "Timer trace inspection failed." }
```

Expected: `Timer trace: 11 records`, four waits, one signal, two timeouts,
one cancellation and no remaining wait.

## 3. Build the checked timer laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\monotonic-deadlines" `
    -B ".\output\learning-build\monotonic-deadlines" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Timer laboratory configure failed." }

cmake --build ".\output\learning-build\monotonic-deadlines" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Timer laboratory build failed." }

ctest --test-dir ".\output\learning-build\monotonic-deadlines" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Timer laboratory test failed." }

& ".\output\learning-build\monotonic-deadlines\btb-deadline.exe"
```

**Expected:** 1/1 passing and deadline 105.

## 4. Build the timed-service laboratory

This project compiles the existing `round_robin.c` and `deadline.c` rather
than maintaining another scheduler or timer implementation.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\timed-service-waits" `
    -B ".\output\learning-build\timed-service-waits" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Timed-service configure failed." }

cmake --build ".\output\learning-build\timed-service-waits" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Timed-service build failed." }

ctest --test-dir ".\output\learning-build\timed-service-waits" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Timed-service tests failed." }

& ".\output\learning-build\timed-service-waits\btb-timed-service.exe"
```

**Expected:** 3/3 passing. The example reports a timeout at tick 105, then
shows a separate scheduler dispatch.

## 5. Validate the education website

MkDocs remains a required external renderer. The new C23 code does not install
Python or silently replace historical publishing tools.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Python = ".\.venv\Scripts\python.exe"

& $Python ".\tools\check_mkdocs_config.py" --syntax-only
if ($LASTEXITCODE -ne 0) { throw "YAML parsing failed." }

& $Python ".\tools\check_mkdocs_config.py"
if ($LASTEXITCODE -ne 0) { throw "Navigation check failed." }

& $Python -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "Strict MkDocs build failed." }

if (-not (Test-Path ".\site\index.html")) { throw "Website home page not found." }
```

The existing Islam volume chapters must remain visible. Check Lessons
107–111 and the two new video scripts before publishing.

Preview with the existing native C23 loopback server:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`. Stop with Ctrl+C. This is a read-only local
preview, not public HTTPS hosting.

## 6. Commit Umicom Framework first

Only after reviewing the staged files and confirming you are on `main`:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): inspect monotonic timer event traces in C23"
git push origin main
```

Do not commit from a detached HEAD. Do not remove earlier source or stage
unrelated work by accident.

## 7. Commit Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach timers events and Kernel recovery in C23"
git push origin main
```

## 8. Record Framework in Umicom Applications last

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record native timer education update"
git push origin main
```

Review the parent staged diff. It should record the intended Framework
submodule pointer without unintentionally advancing unrelated applications.
If the parent also contains another intentional staged change, review it
before deciding whether to publish.
