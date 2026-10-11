# Update 14 — Build, test, preview and commit

## 1. Merge into the existing checkouts

Extract the delivery ZIP to a separate review directory. Use Beyond Compare to inspect the full-file replacements and merge them into the corresponding repositories. The ZIP contains top-level folders `Umicom-Applications` and `Umicom-Bits2Banking` for direct folder matching. No repository folder is replaced wholesale; previously developed content is preserved.

## 2. Build the Framework-owned education command (PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "CMake configure failed." }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Education C23 build failed." }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Education CTest failed." }
```

**Expected:** 20 registered Framework Education CTest cases pass, including `framework.education.ipc_trace` and `framework.education.ipc_trace.cli`.

### Inspect the new native IPC trace fixture

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Trace = ".\build\umicom-education\education-ipc-trace-test\fixture with spaces\owned messages.ipc"
& $Education ipc-trace --file $Trace
```

Expected output:

```text
IPC trace: 4 records
Sends: 2 | Receives: 2
Pending: 0 | High-water: 2
Copied payload bytes: 5
Simulation only: no IPC or system call was executed.
```

If the file does not yet exist, run `ctest -R "^framework\.education\.ipc_trace$"` in the build directory to create it. The native trace inspector does not require a Python interpreter or a network connection.

## 3. Build the copied-message channel laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\bounded-channel" `
    -B ".\output\learning-build\bounded-channel" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Channel lab configure failed." }

cmake --build ".\output\learning-build\bounded-channel" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Channel lab build failed." }

ctest --test-dir ".\output\learning-build\bounded-channel" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Channel lab test failed." }

& ".\output\learning-build\bounded-channel\btb-bounded-channel.exe"
```

**Expected:** 2 CTest cases pass. The demonstration prints a copied Notes event received by endpoint 22.

## 4. Build the service-request laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\syscall-dispatch" `
    -B ".\output\learning-build\syscall-dispatch" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Service lab configure failed." }

cmake --build ".\output\learning-build\syscall-dispatch" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Service lab build failed." }

ctest --test-dir ".\output\learning-build\syscall-dispatch" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Service lab test failed." }

& ".\output\learning-build\syscall-dispatch\btb-service-dispatch.exe"
```

**Expected:** 2 CTest cases pass. The demonstration prints `Training service ticks: 125` and `Training events: 1; revision: 2`.

## 5. Verify the website and preview it

The existing MkDocs renderer still requires the repository's Python virtual environment; no new interpreted source has been introduced.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs build failed. Review the specific page or configuration error." }

Test-Path ".\site\index.html"
```

The final command should return `True`. Then start the native C server:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and review Chapters 97–101, Videos 30–31, the diagrams and the original *Islam: Blueprint for Life* volume. Stop the server with Ctrl+C. This preview binds to local loopback and does not provide public hosting or TLS.

## 6. Commit Framework first

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): inspect bounded IPC traces in native C23"
git push origin main
```

Stop if the branch is detached or is not `main`. Examine the staged files before committing; `git add -A` includes unrelated changes and deletions if they exist.

## 7. Commit Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach system calls IPC and message ownership"
git push origin main
```

## 8. Record the new Framework revision in the parent

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record native IPC education inspection"
git push origin main
```

Only record the Framework submodule after that Framework commit has been published successfully. Never add unrelated application submodules as part of this update. If the parent checkout uses an updated version-lock process, review and run its normal lock-update step before staging its generated lock files.
