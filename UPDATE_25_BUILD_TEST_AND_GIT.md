# Update 25 — Build, test and run the C23 static website server

## 1. Merge the reviewed files

Extract the Update 25 ZIP into a separate review folder. Compare its single
`Umicom-Bits2Banking` directory with `C:\umicom\Umicom-Bits2Banking`, then merge
reviewed files using Beyond Compare. Existing Framework, Applications, OS and
Kernel repositories must not be changed by this update.

The seven changed C23 server/CMake/README files are **complete replacements**,
not patches or truncated fragments. The original fixed-route server and all
four original CTests remain available when no `--root` argument is selected.

## 2. Configure, compile and test

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "HTTP lab configuration failed." }

cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "HTTP lab compilation failed." }

ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "HTTP lab tests failed." }
```

The laboratory currently registers **six tests**: the four established
HTTP tests and two additional checks (`bits2banking.http.static_parsing`,
`bits2banking.http.static_files`). Do not interpret a passed test as proof
of public-network security.

## 3. Start the sample site

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path

& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

Open `http://127.0.0.1:8765/`. It should display the **Bits2Banking — Static
website served by C23** heading. Open `/assets/site.css` and `/health` as
additional checks. The HTML/CSS files in `sample_site/` exist only as the
webpage demonstration; the server itself is implemented in native C23.

Press Ctrl+C to stop the server. If the port is already in use, select 8766.

## 4. Confirm the original server mode

```powershell
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765
```

This mode still serves its original fixed HTML page and JSON `/health` route.
It does not read website files, and it does not need a static root.

## 5. Optionally preview the complete Bits2Banking website

This step uses the **already existing** MkDocs environment, because converting
Markdown to a finished website remains a separate publishing operation.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "The website build failed." }

Test-Path ".\site\index.html"
```

The expected result from `Test-Path` is `True`. Stop if it is `False`.

```powershell
$Root = (Resolve-Path ".\site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

Open `http://127.0.0.1:8765/` and inspect the new chapters and the original
*Islam: Blueprint for Life* volume.

The local C23 server **does not** render Markdown, generate MkDocs output,
create Word/PDF books, offer TLS or replace a supported production HTTP server.
Its current path grammar is a documented ASCII teaching subset.

## 6. Review changes and commit to main

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current
git diff --check

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(learning): extend C23 web server with static-file streaming"
git push origin main

git status
```

Confirm the active branch is `main`. Review the staged file list before the
commit, including unexpected generated files. Do not commit if Windows testing
or the website build revealed an unresolved error. **No Framework or
Umicom Applications commit is required for this batch.**
