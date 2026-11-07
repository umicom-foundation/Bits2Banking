# Write, compile and run a C program

Turn a small C source file into an executable and recognise each step.

**Before you start:** PowerShell, Notepad and GCC from MSYS2 UCRT64. Put C:\msys64\ucrt64\bin first on PATH for this terminal and check gcc --version. Choose a new practice folder you own.

[Community learning route](../index.md) · [Printable HTML](../handouts/09-build-your-first-c-program.html)

## Source and executable

The source file is the text you write. The executable is the program produced from it. Saving text does not compile it, and compiling does not run it. We will do those steps separately.

Create a new folder called first-c in your practice area, enter it with Set-Location and open notepad main.c. If Notepad asks whether to create the file, choose Yes.

## 1. Type this source and save it

```c
#include <stdio.h>

int main(void)
{
    puts("Welcome to Umicom learning.");
    return 0;
}
```

#include <stdio.h> brings in declarations for standard input and output functions. A declaration tells the compiler a function’s name and how to call it. main is where this hosted C program starts. int says it returns an integer. void inside the parentheses means it takes no arguments.

The braces { and } enclose the function body. puts prints a string and then a new line. A string is text between double quotes. The semicolon ends the statement. return 0 reports successful completion to the environment that started the program.

## 2. Compile it

```powershell
Get-Content -LiteralPath ".\main.c"
gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o hello.exe
$LASTEXITCODE
```

-std=c23 selects the C23 language mode. -Wall, -Wextra and -Wpedantic request useful diagnostics. -o names the output. A successful compile may print nothing. Check the exit code immediately: 0 means this command succeeded. If your older compiler does not recognise c23, update the toolchain before following these examples.

## 3. Run the executable

```powershell
.\hello.exe
$LASTEXITCODE
```

You should see Welcome to Umicom learning. The .\ prefix explicitly selects the executable in this folder. PowerShell does not normally search the current folder for an unqualified command name.

## 4. Make and diagnose one deliberate error

Remove the semicolon after puts, save, and compile again. Read the first error and its source line. Put the semicolon back, save and compile again. Run hello.exe only after the new compilation succeeds. A previous executable can remain after a failed build, so running it would not test your latest source.

## Your turn

Change the greeting and add a second puts statement. Predict the two output lines before you run it. Keep main.c; it is the source you can review and version with Git.

## Continue when you are ready

[Previous: Set up the Windows C toolchain](08-set-up-the-c-toolchain.md) · [Next: Build and test a small notes project](10-build-and-test-a-small-project.md)

[Explore the related course](../../courses/learning-c/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/09-build-your-first-c-program.md) · [Short community message](../messages/09-build-your-first-c-program.md)
