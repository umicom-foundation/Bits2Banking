# Major Update 18 — Build, test, review and publish

This update adds native C23 diagnostic inspection and a driver-lifetime
curriculum. It changes the Umicom Framework submodule and the separate
Bits2Banking repository, not the Umicom Kernel source. Complete files are
provided in a ZIP that contains the exact local directory roots:
`Umicom-Applications/` and `Umicom-Bits2Banking/`.

## 1. Compare before merging

In PowerShell, extract the downloaded ZIP to a *review* folder:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-18-Driver-Diagnostics-and-Evidence.zip" `
    -DestinationPath ".\Bits2Banking-Update18-Review" `
    -Force
```

Compare the **left** `C:\umicom\Bits2Banking-Update18-Review\Umicom-Applications\framework`
with the **right** `C:\umicom\Umicom-Applications\framework` in Beyond Compare.
Compare the corresponding `Umicom-Bits2Banking` directory with your local
`C:\umicom\Umicom-Bits2Banking`. Merge only the reviewed files, not entire
repositories or their `.git` directories. No files are intentionally deleted.

Review the complete replacements: the Framework CLI `main.c`, standalone
`CMakeLists.txt`, Bits2Banking `mkdocs.yml`, roadmap and index pages.
Previously delivered source is preserved; the new code is added alongside it.

## 2. Configure and build Umicom Education

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2

ctest --test-dir ".\build\umicom-education" `
    --output-on-failure
```

The standalone suite should register **28** tests. Two new cases are named
`framework.education.evidence_trace` and
`framework.education.evidence_trace.cli`. The first creates a deterministic
fixture, including spaced paths; the second reads the file using the CLI.

For a focused review:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.evidence_trace" `
    -V
```

After the fixture test has run, inspect the file directly:

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Fixture = ".\build\umicom-education\education-evidence-trace-test\fixture with spaces\driver evidence.evd"
& $Education evidence-trace --file $Fixture
```

The report begins with `Evidence trace: 20 records` and includes three
attachments, two observations, one checkpoint, two faults and one recovery.
Neither this command nor its fixture touches a real interrupt controller.

## 3. Build the C23 driver-lifecycle laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\driver-lifecycle" `
    -B ".\output\learning-build\driver-lifecycle" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\driver-lifecycle" --parallel 2

ctest --test-dir ".\output\learning-build\driver-lifecycle" `
    --output-on-failure

& ".\output\learning-build\driver-lifecycle\btb-driver-lifecycle.exe"
```

Expect **4 passing tests**: two from this update and two inherited from the
previous `service-recovery` laboratory. The demonstration should show
`Accepted revision: 101` and `Reviewed faults: 1`. The executable does not
operate actual hardware.

## 4. Build the bounded diagnostic-ring laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\diagnostic-ring" `
    -B ".\output\learning-build\diagnostic-ring" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\diagnostic-ring" --parallel 2

ctest --test-dir ".\output\learning-build\diagnostic-ring" `
    --output-on-failure

& ".\output\learning-build\diagnostic-ring\btb-diagnostic-ring.exe"
```

Expect **2 passing tests** and a demonstration of eight retained and two
overwritten records. This is an in-memory ring, not a durable log.

## 5. Build and preview the educational website

MkDocs still renders the existing Markdown content. Its Python dependency is
retained only for the published website: **all new executable components in
this update are C23**.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict

Test-Path ".\site\index.html"
```

The result must be `True` before starting the native server. If the build
reports a YAML or missing-page error, investigate that report before pushing.
The original *Islam: Blueprint for Life* navigation must remain accessible.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`, check Chapters 117–121 and Videos 38–39,
then stop the process with Ctrl+C. Public hosting and TLS are outside this
local preview server's contract.

## 6. Commit the Framework first

Do not commit from a detached HEAD. Inspect the working tree and staged files.
Only commit after all required Windows checks pass.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): inspect chained driver evidence traces in C23"
git push origin main
```

## 7. Commit Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach driver lifetimes and retained diagnostics"
git push origin main
```

## 8. Commit the parent Umicom Applications last

The parent records the Framework submodule commit; it does not own the
Framework's file changes. Stage only that submodule pointer unless you have
separately reviewed additional parent changes.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record driver diagnostics education update"
git push origin main
```

If `git status` reveals unrelated changes, inspect and reconcile them before
using `git add -A`. Do not reset, clean or overwrite another contributor's
work. This batch changes no Umicom Kernel files.
