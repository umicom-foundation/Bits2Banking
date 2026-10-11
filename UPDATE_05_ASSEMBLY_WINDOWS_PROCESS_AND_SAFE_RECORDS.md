# Update 05 — Assembly functions, safe binary records and Windows renderer paths

The Framework-owned native education programme builds the Bits2Banking website through a separately installed MkDocs renderer. An earlier Windows CTest failure showed that `_spawnvp` did not launch a test Python executable from a filename containing spaces in the MSYS2 UCRT64 test environment. The new renderer transport uses a separately specified executable path with `CreateProcessW`, UTF-8-to-UTF-16 conversion and per-argument quoting. The previous implementation is retained in a disabled source block for comparison.

## Prepare the merge

The ZIP contains `Umicom-Applications/framework/` and `Umicom-Bits2Banking/`. Compare the full files against your current checked-out repositories. Review `src/education/site_renderer.c`, `tests/education/test_renderer.c` and `tests/education/mock_python.c` before merging. The package does not delete historical books, Islam manuscripts, published assets or existing publishing scripts.

## Verify the focused Windows failure

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" `
  -B ".\build\umicom-education" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "CMake configure failed" }
cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "C build failed" }
ctest --test-dir ".\build\umicom-education" -R "^framework\.education\.renderer$" -V
if ($LASTEXITCODE -ne 0) { throw "Renderer regression failed" }
ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Education CTest suite failed" }
```

The renderer test runs a native fake Python programme and does **not** require MkDocs or Python packages. It now checks the interpreter path containing spaces, the full MkDocs build argument vector with spaced paths, and the failure of a child that exits zero without creating `index.html`. This verifies the calling contract on the computer running CTest; it does not prove that a live MkDocs site has been rendered.

## Render the real website

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"
& $Education doctor --repo $Books --python $Python
& $Education build --repo $Books --python $Python
if ($LASTEXITCODE -ne 0) { throw "Website build failed" }
& $Education serve --repo $Books --port 8765
```

The server remains a **loopback-only educational preview**, not a production-facing TLS web server. The unified historical-book catalogue is preserved by the preceding publishing update. Preview locally before pushing the publication workflow.

## Build the two new labs

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\assembly-functions" `
  -B ".\output\learning-build\assembly-functions" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\assembly-functions" --parallel 2
ctest --test-dir ".\output\learning-build\assembly-functions" --output-on-failure

cmake -S ".\labs\native\binary-payment-records" `
  -B ".\output\learning-build\binary-payment-records" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\binary-payment-records" --parallel 2
ctest --test-dir ".\output\learning-build\binary-payment-records" --output-on-failure
```

## What's included in the learning update

- **53** — Call an Assembly function from C23, including the Windows x64, System V and RISC-V64 calling conventions.
- **54** — Move from a normal application to Umicom Kernel's first Assembly boot instructions and freestanding C23.
- **55** — Safely encode and decode a fixed-width, fictional payment record using exact capacity and validity checks.
- **56** — Diagnose a Windows programme path containing spaces using the real education subprocess case.
- **57** — Find object files, symbols, linking errors and disassembly.
- Two CMake/CTest labs, three editable SVG diagrams and two 14–20-minute video scripts.

## Files and acceptance

The package ships additive lessons and the **complete versions of every modified source file**. No Framework public API names or existing library contracts are renamed. The current Windows child-launch adapter remains scoped to the education bootstrap programme; full Framework application integrations should use the canonical `umi_process_execute` process service.

Linux/GCC and Linux/Clang builds test the portable and POSIX paths. A native Windows UCRT64 run is required to establish that `CreateProcessW` fixes the reported failure. Do not call the bug closed until the focused Windows CTest, full native suite and real MkDocs build all pass.

## Commit after acceptance

Commit the Framework submodule first, Bits2Banking second, and the parent Umicom-Applications repository last. Use `git add -A`, `git diff --cached --check`, a descriptive commit and `git push origin main` independently in each changed repository. In the parent repository, stage only the intended `framework` submodule revision; do not commit unrelated application changes.
