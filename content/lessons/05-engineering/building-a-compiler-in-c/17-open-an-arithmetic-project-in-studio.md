<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/17-open-an-arithmetic-project-in-studio.md

PURPOSE:
Open an arithmetic project in Studio

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Open an arithmetic project in Studio

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## What the starter contains

A project is a group of source files plus instructions for working with them. Open `src/main.uc`. Its complete program is:

```c
int main(void) { return 6 * 7; }
```

Here `int` names an integer result, `main` names the entry function, `void` says this function takes no arguments, and braces enclose its body. `return` supplies the result. The multiplication sign combines two integer literals. A semicolon ends the statement. These spellings belong to the small subset accepted by this interpreter; they do not establish support for every feature of C.

1. Select **Open Folder** in Studio and choose the generated project if it is not already open.
2. Open `src/main.uc` from the project tree. Save a change from `6 * 7` to `9 + 4`.
3. Open a terminal in the same directory. Run `umicom-c check src/main.uc`. A zero exit status means the compiler accepted the source. This command does not execute it.
4. Run `umicom-c run src/main.uc --max-steps 256`. Look for `Result: 13`. The instruction count describes work performed by the interpreter, not processor clock cycles.
5. Restore `6 * 7` and save. The supplied result test expects 42.

If Studio cannot open or edit the file, keep the generated folder and use another editor for this lab. Record that as an editor problem separately from whether the compiler accepts the file. Project generation does not prove that editing and debugging work.

## Exercise

Predict `2 + 3 * 4` before running it, then compare `(2 + 3) * 4`. Expected values are 14 and 20. Explain how parentheses change grouping. Restore the supplied 42 result before running project tests.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/templates/umicom_c_preview.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Next: Follow a Framework project recipe](18-follow-a-framework-project-recipe.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](16-budget-execution-and-publish-results.md)

[Written course contents](index.md)
