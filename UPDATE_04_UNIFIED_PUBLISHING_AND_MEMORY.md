# Bits2Banking — Native Publication Integrity and Unified Website Delivery

The learning website and the historical BookForge books are generated from different sources. This update provides one published website without replacing either source or removing the earlier book-generation workflows.

## Build locally

Use the existing virtual environment and repository:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m pip install -r .\requirements.txt -r .\requirements-docs.txt
& ".\.venv\Scripts\python.exe" .\scripts\forge_all.py
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
& ".\.venv\Scripts\python.exe" .\scripts\publish_learning_portal.py assemble
& ".\.venv\Scripts\python.exe" .\scripts\publish_learning_portal.py verify
```

If previous book archive output already exists, review it and add `--refresh` to the assemble command. The refresh replaces generated `site/archive/books`, not original manuscripts.

The native C23 program now also records a SHA-256 inventory of the finished website:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education publish manifest --repo $Books
& $Education publish verify --repo $Books
& $Education serve --repo $Books --port 8765
```

Preview `http://127.0.0.1:8765/` and `http://127.0.0.1:8765/archive/books/`. Stop with Ctrl+C.

## What has changed

- The earlier BookForge jobs are retained. Their former Pages deployment jobs are disabled, not deleted; a single new workflow owns Pages deployment.
- The GitHub Pages build prepares Umicom Framework branding, generates original books, builds MkDocs, then assembles the two generated outputs.
- The new `umicom-education publish manifest/verify` commands use the existing Framework SHA-256 implementation. No duplicate digest library is maintained in Bits2Banking.
- A new C23 cache-memory lab, four related lessons and an accompanying video script extend the computing and publishing curriculum.
- Existing Islam volume chapters, book manuscripts, course materials, contributor guides and videos are preserved.

## Validation before publishing

Run the native tests:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

Run the educational regression tests and the new C23 memory lab:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m unittest discover -s tests -p "test_learning_portal.py" -v
cmake -S ".\labs\native\cache-memory" -B ".\output\learning-build\cache-memory" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cache-memory" --parallel 2
ctest --test-dir ".\output\learning-build\cache-memory" --output-on-failure
```

The C23 publication manifest test uses disposable test files. The complete GitHub Pages deployment requires a live GitHub Actions run; it has not been proven by local unit tests.

## Publication ownership

`learning-pages.yml` is the only enabled GitHub Pages deployment workflow. The old `books-build.yml` and `dropzone-build.yml` retain their build and artifact steps, and retain the old deployment code disabled for engineering review.

Review the workflow permissions and the generated Pages artifact on GitHub before regarding this update as production-ready. The unified publisher does not automatically commit generated files into your source repositories.
