# Progress records and a Pascal unit

A record groups related values. This lab keeps a course total and completed count together, then uses a unit to share checked operations between programs. The original terminal example remains available.

## Prepare

1. Install Free Pascal, CMake and Ninja and open a new terminal.
2. Run `fpc -iV`, `cmake --version` and `ninja --version`.
3. Copy this complete lab folder to your practice directory. Keep lessonprogress.pas beside the programs.
4. From that directory, use the following commands in PowerShell or bash.

~~~text
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
~~~

In PowerShell launch `& "./build/progress_records.exe"`. In bash launch `./build/progress_records`. Expected output:

~~~text
Course 1: 2 lessons remaining
Course 2: 3 lessons remaining
~~~

The supplied checks also cover invalid creation, full and empty courses, the integer limit and damaged record values. They are authored checks; run them to obtain results for your compiler.

## Read the source

- lessonprogress.pas declares the record and public functions in its interface section, then implements them below.
- progress.pas uses the shared RemainingLessons function for terminal input.
- progress_records.pas keeps two records in an array and advances only the first.
- progress_checks.pas verifies rejected calls preserve existing values.

`var State` lets a function modify the caller's record. A normal value parameter gives the function its own value. These operations check all input before publishing a change.

The unit is a language-teaching model. A production Umicom client should use the appropriate Framework service through a defined native boundary. Do not copy this teaching rule into a second production engine.

## Troubleshooting

If the compiler cannot find LessonProgress, check the unit file name and search directory. Each program has its own compiled-unit output directory, avoiding simultaneous writes to the same unit artifacts during a parallel build.

A record's in-memory layout is compiler-dependent. Do not save its raw bytes as a portable file format or send them to another language. Define a documented serialization or C-compatible interface first. See the [Free Pascal record reference](https://www.freepascal.org/docs-html/ref/refsu15.html).

