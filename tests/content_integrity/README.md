# Read-only C23 course inventory smoke test

**Owner:** Umicom Foundation · **Author:** Sammy Hegab · **Licence:** MIT.

This is a test-only validator for Bits2Banking repository layout. Production
Knowledge Centre validation remains a responsibility of the C23 Umicom
Framework; this does not create another production RAG/indexing implementation.

## Windows PowerShell (from `C:\umicom\Umicom-Bits2Banking`)

```powershell
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path
cmake -S '.\tests\content_integrity' -B '.\build\content-integrity' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build '.\build\content-integrity' --parallel 2
ctest --test-dir '.\build\content-integrity' --output-on-failure --no-tests=error
```

Expected registration: `btb.education.inventory` and
`btb.education.rejections`. The inventory test checks all 114 published-format
HTML source paths **in your local checkout**, four relocated Markdown lessons,
four existing scripts and absence of the four old duplicate paths.

The test does **not** follow every link in the HTML pages; it does not audit
publication workflows, content semantics, rights, signatures or AI training.
Inspect the complete browser catalogue and run the existing website tests as
separate review gates. The test creates or modifies no course files.

## Batch 03 — full-file course navigation and source coverage

The existing instructions above are preserved. Batch 03 adds the read-only
`btb.education.navigation.selftest` and `btb.education.navigation` tests and
the native staging executable `btb-lesson-navigation`.

**Important:** run the full four-test CTest suite **after** staging and merging
the complete generated `index.html`, `course-map.html` and relationship TSV.
Before that merge, the full navigation test correctly reports missing links.
The standalone self-test can be run before merging.

Use the exact merge workflow in `docs/BITS2BANKING_BATCH03.md`. The staging
executable never modifies original course pages: it reads from the current
repository and creates complete proposed copies in an explicit external folder.
