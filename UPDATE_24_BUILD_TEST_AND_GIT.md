# Update 24 — Build, test, review and commit

## 1. Review the batch

Download `Umicom-Bits2Banking-Update-24-Process-File-Services-and-C23-Networking.zip` into `C:\umicom` and extract it to a review directory:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-24-Process-File-Services-and-C23-Networking.zip" `
    -DestinationPath ".\Bits2Banking-Update24-Review" `
    -Force
```

Compare `C:\umicom\Bits2Banking-Update24-Review\Umicom-Bits2Banking` with `C:\umicom\Umicom-Bits2Banking` in Beyond Compare. Merge only reviewed files. The five replacement files (`mkdocs.yml`, `ROADMAP_MAJOR_UPDATES.md` and three existing learning indexes) preserve their previous content and append new links. Do not replace the whole checkout.

## 2. Set up the compiler and build tools

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
```

If any tool is missing, use the project's contributor setup lessons before continuing.

## 3. Build process-owned file services

```powershell
cmake -S ".\labs\native\process-file-services" `
    -B ".\output\learning-build\process-file-services" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Process file configuration failed." }

cmake --build ".\output\learning-build\process-file-services" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Process file compilation failed." }

ctest --test-dir ".\output\learning-build\process-file-services" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Process file tests failed." }

& ".\output\learning-build\process-file-services\btb-process-files-demo.exe"
if ($LASTEXITCODE -ne 0) { throw "Process file demonstration failed." }
```

Expected: 3 CTest cases pass. The demonstration prints `Process 11 read: Umicom Notes`.

## 4. Build the native C23 HTTP server

```powershell
cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "HTTP configuration failed." }

cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "HTTP compilation failed." }

ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "HTTP tests failed." }
```

Expected: 4 CTest cases pass.

## 5. Test the real loopback listener

In the first PowerShell window:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" --port 8765
```

Use port 8766 instead if Umicom Education or another programme is already using 8765. In a second PowerShell window:

```powershell
Invoke-WebRequest -Uri "http://127.0.0.1:8765/health" |
    Select-Object StatusCode, Content
```

Expected: `StatusCode` 200 and JSON containing `"status":"ready"`. Open `http://127.0.0.1:8765/` in the browser to see the fixed HTML page. Stop the server in the first console with **Ctrl+C**.

If the browser cannot connect, verify the server is still running and that the port matches. This test does not involve the previously built `umicom-education` website.

## 6. Build the educational website

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs build failed." }
Test-Path ".\site\index.html"
```

Expected: `True`. MkDocs remains an existing website-rendering dependency; this update adds no Python implementation files or packages. The old *Islam: Blueprint for Life* volume and previous chapters must still appear in site navigation.

## 7. Review and publish only Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git diff --stat
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach process file services and native C23 networking"
git push origin main
git status
```

**Before committing:** confirm the branch is `main` and examine `git diff --cached --stat` so unrelated changes and generated files are not included. If `git diff --cached --check` fails, fix the reported issue before committing. Do not run Git operations in Umicom Framework, Kernel, OS or the Applications superproject for this batch.
