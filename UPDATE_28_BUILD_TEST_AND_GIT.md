# Bits2Banking — Major Update 28: Build, Test and Git

**Nonblocking Networking, Connection Timeouts and Graceful Shutdown in C23**  
**Project:** Umicom Foundation · Bits2Banking  
**Upstream baseline inspected:** `umicom-foundation/Bits2Banking`, `main`, commit `6a30bcfea3240f64e8605770955d5f710f2c6036` (Update 27).  
**Local destination:** `C:\umicom\Umicom-Bits2Banking`  
**Change policy:** Only Bits2Banking; review full files before replacing them; never delete or reset existing work automatically.

## 1. What the ZIP delivers

The ZIP contains one top-level `Umicom-Bits2Banking/` directory. This is a **review-and-merge update**, not a complete repository replacement. The existing native project stays at `labs/native/http-loopback-server`. New lessons continue at 167–171, video scripts at 58–59, and SVGs in the established diagram directory. The existing codebase, historical books, the Islam volume and its publication configuration are not bundled for replacement.

Only two **complete existing files** are replaced: `labs/native/http-loopback-server/main.c` and `labs/native/http-loopback-server/CMakeLists.txt`. `tcp_server.c` and all previous C23 parser, routing, static-file, cache, response-progress and admission implementations remain unchanged. New `nonblocking_server.*` and `nonblocking_policy.*` files extend the existing lab in a strictly opt-in mode, selected by `--nonblocking`.

`mkdocs.yml`, `ROADMAP_MAJOR_UPDATES.md` and the HTTP lab's `README.md` are **not provided as wholesale replacements**, to avoid overwriting your navigation and intervening edits. The checked PowerShell helper in `scripts/` adds only the next navigation group and Update 28 notes after verifying the existing Update 27 anchor. Run that helper **after** reviewing and merging the ZIP.

## 2. Review and merge using Beyond Compare

Download the ZIP into `C:\umicom`, then open PowerShell:

```powershell
Set-Location "C:\umicom"

Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-28-Nonblocking-Networking-and-Graceful-Shutdown.zip" `
    -DestinationPath ".\Bits2Banking-Update28-Review" `
    -Force
```

In Beyond Compare select **Folder Compare**:

**Left (batch):** `C:\umicom\Bits2Banking-Update28-Review\Umicom-Bits2Banking`  
**Right (working repository):** `C:\umicom\Umicom-Bits2Banking`

Review all differences, particularly the **full-file replacements** for `main.c` and `CMakeLists.txt`. Merge the files into the corresponding folders without copying the top-level project folder on top of the entire repository. The original `main.c` archived `#if 0` examples and option semantics must remain visible after merging. Do not stage `output/`, the generated site, or archive files.

Check the checkout before applying navigation:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git branch --show-current
git rev-parse HEAD
git status --short
```

The inspected base is `6a30bcf...`. If your local files have moved ahead since Update 27, compare rather than overwriting those edits. You remain the final decision maker about source deletion; this package deletes **zero** files.

## 3. Register lessons in the existing website

After merging and reviewing the package files, run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\scripts\Apply-Bits2Banking-Update28Navigation.ps1" `
    -RepositoryRoot "."

# Review the old and added lines before building the site.
git diff -- mkdocs.yml ROADMAP_MAJOR_UPDATES.md `
    labs/native/http-loopback-server/README.md
```

The script refuses a missing/duplicated navigation anchor and is safe to run again. It does **not** replace existing chapter navigation or modify original manuscripts. Do not bypass its refusal by resetting your site configuration: review the changed source first. Expected new nav section: **5 lessons + 2 videos**.

## 4. Windows UCRT64 build

The commands use the project's established MSYS2 UCRT64 GCC and Ninja configuration:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake --version
gcc --version
ninja --version

cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "C23 configure failed." }

cmake --build `
    ".\output\learning-build\http-loopback-server" `
    --parallel 2

if ($LASTEXITCODE -ne 0) { throw "C23 build failed." }
```

A previously configured build tree can be reused if its compiler and generator still match. Do not delete your build tree reflexively; inspect configuration errors first.

## 5. Automated tests

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

ctest --test-dir `
    ".\output\learning-build\http-loopback-server" `
    -N

ctest --test-dir `
    ".\output\learning-build\http-loopback-server" `
    --output-on-failure

if ($LASTEXITCODE -ne 0) { throw "C23 HTTP regression suite failed." }
```

The pre-existing suite registers **16 tests**. Major Update 28 adds two independent C23 tests for the socket-free connection lifetime contract and its 30,000 deterministic transitions. Where CMake detects Python 3, a further standard-library test launches the actual C23 executable and exercises **real loopback sockets**, overlapping requests, static-file GET/HEAD, weak `ETag` revalidation, registered routes, missing files and idle connection expiry. The expected count is **18 without Python**, or **19 with Python 3**. These are **expected registrations**, not an assertion that your Windows tests have already passed.

The Python script is only a test driver; the implementation remains C23. The 19th test takes about 4 seconds because it intentionally waits for an idle deadline. If Python is absent, follow the manual socket checks in Lesson 170.

## 6. Manual HTTP regression and nonblocking demonstration

Open **PowerShell window A**:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path

& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes --nonblocking
```

Open **PowerShell window B**:

```powershell
curl.exe -i http://127.0.0.1:8765/health
curl.exe -i http://127.0.0.1:8765/index.html
curl.exe -I http://127.0.0.1:8765/index.html
curl.exe -i http://127.0.0.1:8765/api/courses
curl.exe -i http://127.0.0.1:8765/does-not-exist.xyz
```

Expected: `200` for `/health`, `index.html` and `/api/courses`; `404` for missing file; the `HEAD` reply contains no message body. Copy the **actual** `ETag` displayed for `/index.html`, then use:

```powershell
curl.exe -i `
    -H 'If-None-Match: PASTE_ACTUAL_ETAG_HERE' `
    http://127.0.0.1:8765/index.html
```

Expected: **`304 Not Modified` without a body**, if the source file is unchanged. Check Chapter 170 and the new test file for a timed slow/fast-client scenario. Press **Ctrl+C** in window A and verify that the process exits cleanly and releases the listening port. On Windows the real console Ctrl+C behaviour is a distinct host validation gate. Re-run without `--nonblocking` to compare with the preserved Update 27 backend.

## 7. Strict website build and learning checks

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict

if ($LASTEXITCODE -ne 0) { throw "Strict MkDocs validation failed." }
```

If that `.venv` is missing, use the project's established Python/MkDocs installation procedure; do not silently install or replace another interpreter. Check the new navigation links and the established *Islam: Blueprint for Life* section, and inspect the rendered SVG diagrams. The existing `content/`, `dropzone/` and original manuscripts must remain unchanged except for the reviewed additive lesson files.

## 8. Git commit and push — Bits2Banking only

Only after the build, tests and site checks have passed and the diff has been reviewed:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current

git add -A

git diff --cached --check
git diff --cached --stat

# Review the actual staged changes; ensure no unrelated work or build output.
git diff --cached --name-status

git commit -m "feat(learning): add C23 nonblocking networking and graceful shutdown"

git push origin main

git status
```

Ensure the branch is `main` before the commit and push; **no branches are created** by this batch. No Git operations were performed against your remote repository as part of this delivery.

## 9. Qualification record

The source was checked against the connected Update 27 GitHub layout. The pure C23 lifetime tests and an isolated reactor/network test built with compatible mock HTTP boundaries were exercised under Linux compilers. **This does not prove that the complete real repository has compiled**, nor that all Windows, original CTests, publication and manual Ctrl+C gates pass. These must be completed using the commands above. Record compiler versions, the CTest summary, the strict MkDocs result and the reviewed commit SHA alongside your final acceptance.

See `UPDATE_28_TECHNICAL_OVERVIEW.md` and `labs/native/http-loopback-server/UPDATE_28_NONBLOCKING_GUIDE.md` for design and limitations.
