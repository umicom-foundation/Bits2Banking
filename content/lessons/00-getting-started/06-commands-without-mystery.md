# Read a command before running it

Recognise a command name, an argument, a prompt and a working folder.

**Before you begin:** read [Give instructions and check what happens](05-instructions-and-checking.md), or use it for a refresher.

## Another way to give an instruction

A graphical interface lets you choose visible controls such as buttons. A command-line interface accepts typed instructions. Neither is automatically more intelligent or more correct. A terminal is a window or device for text interaction. A shell is the program interpreting commands in that interaction. PowerShell and Bash are different shells, with different rules.

A prompt is text indicating that the shell is ready for input. A Windows example is PS C:\Learning>. Do not type the example prompt as part of the command. The location displayed often indicates the working directory: the folder from which relative paths are interpreted.

## Read the parts separately

In PowerShell, Get-Location asks for the current working location. The command name is Get-Location. Pressing Enter asks the shell to carry it out. Output is the response; afterwards a new prompt generally indicates that the shell is ready again. The displayed location depends on your session.

An argument is information supplied to a command. A parameter identifies an option the command understands. For example, Get-ChildItem -LiteralPath . asks PowerShell to list items at the exact path supplied. Here the dot means the current location; -LiteralPath identifies the parameter and the dot is its value. Listing a folder is different from changing or deleting its contents.

## An optional read-only practice

On a Windows computer where you have permission, open PowerShell normally. Do not choose Run as administrator for this activity. Type only Get-Location and press Enter. Read the displayed location. Then type Get-ChildItem -LiteralPath . and press Enter. You may see names, dates and sizes. An empty folder can produce no item rows; that is not necessarily an error.

These are PowerShell examples, not instructions for every shell. If you use a different device or cannot open a terminal, practise reading the example on paper. Do not install tools merely to finish this lesson. If a command reports an error, keep its exact text and the command you typed. Do not repeat unfamiliar commands from search results to make the message disappear.

## Commands have consequences

Some commands read information; others write, install, remove or publish it. Before running a new command, ask which program receives it, what its arguments mean, which location it uses and what it can change. Quotation marks often keep a path with spaces together; the exact rules depend on the shell.

Later you will see cmake, a tool that prepares build instructions, and a compiler, a tool that translates source code. Being able to read a command comes before needing those tools. A lesson should explain the command's purpose, its expected result and what to check if it fails. You should not need to guess which computer or folder it applies to.

## Try it step by step

1. On paper label PS C:\Learning> as the prompt and Get-Location as the command.
2. Explain why the example prompt should not be copied into the command.
3. Predict whether listing a folder saves a new file. Explain your reasoning.
4. If you try the optional activity, record the actual location without posting private folder names publicly.

## Check your understanding

If a command works in PowerShell, must the same text work in Bash?

**Explanation:** No. They are different programs with different syntax and built-in commands. Use the instructions for the named shell and environment.

## Before you continue

Continue when you can separate the prompt from the command and explain what a working folder is.

[Course contents](index.md) · [Words explained](../../courses/computing-from-the-beginning/glossary.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [Give instructions and check what happens](05-instructions-and-checking.md).

**Next:** [How applications, an OS and a kernel fit together](07-applications-os-and-kernel.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
