# Notes word-count practice project

This small C23 project counts words separated by ASCII whitespace. It is an independent teaching example. The console program and test share one implementation in a static library.

## Get the complete source

If you have the Bits2Banking repository, copy this whole folder into your own practice folder. From a website, save the following files and recreate their subfolders exactly. Open the file link and use your browser’s Save As command; keep the original filename.

- [CMakeLists.txt](CMakeLists.txt)
- [include/note_words.h](include/note_words.h)
- [src/note_words.c](src/note_words.c)
- [src/main.c](src/main.c)
- [tests/test_note_words.c](tests/test_note_words.c)

## Build, test and run

Open PowerShell in the copied project folder. Make sure your UCRT64 tools are available. Run each command separately and stop if it reports an error.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
.\build\notes-word-count.exe
```

Expect two passing tests and `Words: 4` from the program. On Linux with GCC, CMake and Ninja installed, the first three commands are the same; run `./build/notes-word-count`. Each external command returns its own exit code; in PowerShell check `$LASTEXITCODE` immediately.

[Step-by-step explanation](../../lessons/10-build-and-test-a-small-project.md)

## Contract

`note_word_count` borrows a valid zero-terminated string and does not change it. A null pointer returns zero. Space, tab, carriage return, line feed, form feed and vertical tab separate words. Punctuation and non-ASCII bytes do not split words. This intentionally small exercise does not replace a multilingual text-processing service.
