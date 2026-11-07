# Build a Pascal course notebook

This project stores up to eight course names and their lesson counts in memory. It reuses LessonProgress for progress arithmetic. It is a language exercise, not a second implementation of Framework's production learning catalogue.

## Setup

Install Free Pascal, CMake and Ninja and confirm `fpc -iV`, `cmake --version` and `ninja --version` work in your terminal. From the Bits2Banking repository root, run separately:

```text
cmake -S labs/languages/pascal-progress -B output/learning-build/pascal-progress -G Ninja
cmake --build output/learning-build/pascal-progress
ctest --test-dir output/learning-build/pascal-progress --output-on-failure
```

Stop on a failed command. This lab uses CMake only to invoke Free Pascal and organise checks; it does not require compiling the entire ecosystem.

In PowerShell:
```powershell
& ".\output\learning-build\pascal-progress\coursebook_demo.exe"
```
In Bash:
```bash
./output/learning-build/pascal-progress/coursebook_demo
```

Expected lines are `1. Learning C: 2 remaining` and `2. Introduction to RISC-V: 3 remaining`. They describe the sample data, not your actual course completion.

## Source map

- `lessonprogress.pas`: existing arithmetic and checked progress records.
- `coursebook.pas`: bounded list, name validation and one-based public course numbers.
- `coursebook_demo.pas`: thin caller that creates and displays a list.
- `coursebook_checks.pas`: independent checks for refusal, capacity and indexing.

Names are one to forty printable ASCII bytes and must include a non-space character. Names are compared exactly. International text and persistence are future exercises requiring an explicit encoding and file-format design.

## Try a change

Add a third course through TryAddCourse, then complete one of its lessons. Predict the output before running. Try a ninth course and confirm refusal leaves the returned number unchanged.

Do not use an uninitialised book. InitialiseBook establishes the empty state. The public operations reject invalid counts and indices; this does not make arbitrary corrupted memory safe.

## Investigate errors

A missing unit usually means the source search path or working directory is wrong. The CMake file supplies the source directory and separate unit-output directories. A failed check prints its specific condition and exits unsuccessfully. Keep the first failure before changing expectations.

See the [Free Pascal reference manual](https://www.freepascal.org/docs-html/ref/ref.html) for language details.
