# Video script: Write, compile and run a C program

**Aim:** Turn a small C source file into an executable and recognise each step.

**Preparation:** PowerShell, Notepad and GCC from MSYS2 UCRT64. Put C:\msys64\ucrt64\bin first on PATH for this terminal and check gcc --version. Choose a new practice folder you own. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/09-build-your-first-c-program.md)

## Opening words

Next, we will take this topic one step at a time: write, compile and run a c program. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Type the program slowly and explain each punctuation mark as it is introduced. Keep the source and terminal visible together.

## Scene 2

Compile, inspect the exit code and then run. Label those as three different actions: save, compile, run.

## Scene 3

Create the missing-semicolon error. Explain the first diagnostic, repair it and rebuild before running again.

## Walkthrough and pauses

### Source and executable

**Say:** The source file is the text you write. The executable is the program produced from it. Saving text does not compile it, and compiling does not run it. We will do those steps separately.

**Say:** Create a new folder called first-c in your practice area, enter it with Set-Location and open notepad main.c. If Notepad asks whether to create the file, choose Yes.

### 1. Type this source and save it

**On screen — type one line at a time:**

```c
#include <stdio.h>

int main(void)
{
    puts("Welcome to Umicom learning.");
    return 0;
}
```

Pause. Read the result before continuing.

**Say:** #include <stdio.h> brings in declarations for standard input and output functions. A declaration tells the compiler a function’s name and how to call it. main is where this hosted C program starts. int says it returns an integer. void inside the parentheses means it takes no arguments.

**Say:** The braces { and } enclose the function body. puts prints a string and then a new line. A string is text between double quotes. The semicolon ends the statement. return 0 reports successful completion to the environment that started the program.

### 2. Compile it

**On screen — type one line at a time:**

```powershell
Get-Content -LiteralPath ".\main.c"
gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o hello.exe
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** -std=c23 selects the C23 language mode. -Wall, -Wextra and -Wpedantic request useful diagnostics. -o names the output. A successful compile may print nothing. Check the exit code immediately: 0 means this command succeeded. If your older compiler does not recognise c23, update the toolchain before following these examples.

### 3. Run the executable

**On screen — type one line at a time:**

```powershell
.\hello.exe
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** You should see Welcome to Umicom learning. The .\ prefix explicitly selects the executable in this folder. PowerShell does not normally search the current folder for an unqualified command name.

### 4. Make and diagnose one deliberate error

**Say:** Remove the semicolon after puts, save, and compile again. Read the first error and its source line. Put the semicolon back, save and compile again. Run hello.exe only after the new compilation succeeds. A previous executable can remain after a failed build, so running it would not test your latest source.

### Your turn

**Say:** Change the greeting and add a second puts statement. Predict the two output lines before you run it. Keep main.c; it is the source you can review and version with Git.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
