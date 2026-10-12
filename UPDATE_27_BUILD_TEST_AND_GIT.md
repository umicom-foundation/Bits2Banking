# Update 27 — Build, test and publish the C23 caching lessons

Only `C:\umicom\Umicom-Bits2Banking` changes in this update. The Framework, Applications, Kernel and OS repositories are read-only references and require no Git commits.

## 1. Review the update before merging

Download `Umicom-Bits2Banking-Update-27-Conditional-HTTP-and-Bounded-Admission.zip` to `C:\umicom`. In Windows PowerShell:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-27-Conditional-HTTP-and-Bounded-Admission.zip" `
    -DestinationPath ".\Bits2Banking-Update27-Review" `
    -Force
```

In Beyond Compare, review `C:\umicom\Bits2Banking-Update27-Review\Umicom-Bits2Banking` against `C:\umicom\Umicom-Bits2Banking`. Merge selected complete files into the existing checkout. Do not replace the Git directory, delete unrelated work or copy the extracted top folder into the repository as a nested directory.

## 2. Configure and build (MSYS2 UCRT64 GCC)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "HTTP CMake configuration failed" }

cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "C23 compilation failed" }
```

Expected targets include `btb-http-server.exe`, `btb-admission-demo.exe`, `btb-http-cache-test.exe`, and `btb-http-admission-test.exe`. The existing server and test targets remain.

## 3. Run the complete CTest suite

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "HTTP laboratory tests failed" }
```

Expected: **16/16 passing** (11 existing, five new). To run only the new tests:

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R '^bits2banking\.http\.(cache|admission)\.' -V
```

## 4. Check live HTTP revalidation

Start the C23 server in the first PowerShell window:

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes
```

In a **second** PowerShell window:

```powershell
curl.exe -i http://127.0.0.1:8765/index.html
curl.exe -I http://127.0.0.1:8765/index.html
curl.exe -i http://127.0.0.1:8765/api/courses
```

Note the actual `ETag` from the first GET response. Reuse it in a new request:

```powershell
curl.exe -i -H 'If-None-Match: PASTE_ACTUAL_ETAG_HERE' `
    http://127.0.0.1:8765/index.html
```

The expected result for a matching tag is **304 Not Modified**, with `ETag` and `Cache-Control` headers and **no response body**. An unmatched tag returns 200 and file content. Stop the server using Ctrl+C.

## 5. Run the bounded-admission demonstration

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\http-loopback-server\btb-admission-demo.exe"
```

Expected:

```text
Capacity: 4; maximum simulated in-flight: 2; queued: 2
Next admitted request: 3; active: 2
```

This tests a single-owner C23 queue, **not actual concurrent network execution**. The original socket accept loop remains serial.

## 6. Build and validate the complete educational website

The existing website generator is MkDocs. It requires the repository-local Python environment created for earlier batches. This update introduces no new Python source files.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs build failed" }
Test-Path ".\site\index.html"
```

The last check should be `True`. Confirm navigation reaches chapters 162–166, videos 56–57, the previous 161 chapters, and *Islam: Blueprint for Life*. This website build must be performed against the complete local repository; the delivery ZIP contains changes only.

To preview the generated HTML with the native C23 server, set `--root` to `(Resolve-Path '.\site').Path`. The server's 64 MiB per-file limit and loopback-only policy remain unchanged.

## 7. Review, commit and push only Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git diff --check

git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add C23 HTTP revalidation and bounded admission model"
git push origin main
git status
```

Check staged paths carefully: `git add -A` also stages deletions and unrelated local changes. Publish only after Windows tests and website review succeed. If the branch is not `main`, stop and investigate rather than creating an unintended commit. No other Umicom repository is modified or pushed.

## Validation boundary

The new C23 modules and the cumulative web laboratory were tested with GCC and Clang (AddressSanitizer/UndefinedBehaviorSanitizer) in Linux, including live HTTP 200/304/HEAD, unchanged JSON routing and malformed conditional headers. Windows UCRT64, file timestamp edge cases and the full historical MkDocs site remain separate host acceptance requirements. The local teaching server is not a TLS or production hosting platform.
