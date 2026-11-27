First programs · Lesson 2 of 7

# Build and run your first C program

![Umicom](../../assets/branding/umicom-wordmark.svg)

This is the single-file practice route. [Prepare, build and run a project with CMake](02-build-and-run-one-step.md) to continue with a project build.

In the previous lesson you read `hello.c`. Now you will turn that text into a program you can run. We will use one file and one command to build it. Project generators and large application builds come later.

## 1. Understand the three things involved

An **editor** changes source text. A **compiler** translates C instructions into machine instructions. An **executable** is a file your operating system can start as a program. On Windows its name often ends in `.exe`. The GCC command used here also arranges the final **link** step, which connects your program to the library operations it uses.

```text
hello.c (source text) → compiler and linker → hello.exe (program)
                                                  ↓ run
                                        Hello from Bits2Banking.
```

## 2. Prepare a practice folder

The following example uses Windows PowerShell and an already installed C23-capable GCC compiler. A **terminal** is a place to type commands; PowerShell reads them. A command is an instruction to a tool, not a line to paste into a C source file. If you do not yet have the tools, use the [practical setup guide](../../courses/learning-c/practical-guide.html) first, or continue by reading the expected results.

1. Create a folder for your exercises, for example `C:\umicom-learning\first-c`, using File Explorer.
2. Copy `hello.c` from the Bits2Banking laboratory into that folder. Keep the original example unchanged. [Open the original hello.c](../../labs/learning-c/build-one-c-file/hello.c) and save a copy as `hello.c` if you are reading online.
3. Open PowerShell. Type the following command, changing the folder if you chose a different one:

```text
Set-Location "C:\umicom-learning\first-c"
```

`Set-Location` chooses the folder in which commands will work. Double quotation marks keep the path together if it contains spaces.

## 3. Build the program

```text
gcc -std=c23 -Wall -Wextra hello.c -o hello.exe
```

| Part | Meaning |
| --- | --- |
| `gcc` | Start the compiler tool. |
| `-std=c23` | Ask it to use the C23 language rules. |
| `-Wall -Wextra` | Request useful warnings about suspicious code. |
| `hello.c` | Read this source file. |
| `-o hello.exe` | Name the output program `hello.exe`. |

A successful build may print nothing and return to the prompt, the line where you can enter another command. Confirm that `hello.exe` exists. If there is an error, read it and fix the source before going on. Running an old executable after a failed build does not show your latest edit.

## 4. Run it

```text
.\hello.exe
```

`.\` means “in the current folder”. The output should be:

```text
Hello from Bits2Banking.
```

Building prepares the executable. Running starts it. These are separate actions. In Studio, the editor shows the same source file, while its build and run commands manage these actions for a configured project.

## 5. Change, build and compare

1. Change the message in `hello.c` to `I am learning C.`
2. Save the file in your editor.
3. Repeat the build command.
4. When it succeeds, repeat the run command.

You should now see the new message. Saving alone cannot change an executable that was already built.

## If a step fails

**“gcc is not recognised”** means PowerShell cannot find the compiler; return to the setup guide. **“hello.c: No such file”** means the current folder or filename is wrong. A message containing a line number points into the source; check punctuation on that line and the line above it. Do not delete your source folder to fix a compiler error.

## Check your understanding

You changed the message but ran the old executable without rebuilding. Which message appears?

### Answer

The old one. Rebuild successfully after saving before expecting the executable to contain your change.

---

[Read this lesson in HTML](../../courses/learning-c/lessons/02-build-and-run-one-step.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

First programs · Lesson 2 of 7.

[Previous: Your first C program](01-read-your-first-program.md) · [Next: Variables and simple calculations](03-values-and-calculations.md)
