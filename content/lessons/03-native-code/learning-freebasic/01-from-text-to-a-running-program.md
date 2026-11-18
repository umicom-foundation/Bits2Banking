<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/01-from-text-to-a-running-program.md

PURPOSE:
From typed text to a running FreeBASIC program

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# From typed text to a running FreeBASIC program

[Course contents](index.md)

## What you are building

A program is a set of instructions. Source code is the text you write; a compiler checks that text and produces an executable that the operating system can run. BASIC is a family of languages. This course uses FreeBASIC in its fb dialect. It is not Visual Basic for Applications, VB.NET or a promise that every older BASIC listing will compile unchanged. A dialect is a particular set of language rules.

You need a text editor, a terminal and the FreeBASIC compiler. A terminal displays commands and their output. PowerShell is the command interpreter used in the Windows examples. An executable contains machine instructions; it is different from the .bas source file. Reading the lessons needs no compiler, but running these exercises does.

1. Open the official FreeBASIC downloads page. Select a release and architecture matching your operating system. Read that release’s installation notes and keep its version with your notes. Do not download a compiler from an advertisement.
2. Install or extract the compiler as its documentation directs. Open a new PowerShell window after changing PATH. PATH is the list of folders the shell searches for commands.
3. Run fbc -version. If PowerShell cannot find fbc, use the full path to fbc.exe, or correct PATH. Do not rename a different compiler to fbc.
4. Create an empty practice folder such as $HOME\umicom-basic-practice, then use Set-Location to enter it. Save the code below as hello.bas using a plain-text editor. Check that the name is not hello.bas.txt.

~~~basic
' A comment explains the next instruction.
Print "Hello from Umicom BASIC lessons"
End 0
~~~

~~~powershell
fbc -lang fb -w all hello.bas -x hello.exe
if ($LASTEXITCODE -ne 0) { throw "Compilation failed" }
.\hello.exe
$LASTEXITCODE
~~~

Print writes text to the terminal. Double quotation marks delimit a string: a sequence of characters. The apostrophe begins a comment that the compiler ignores. End 0 ends this small console program with success status zero. The shell command .\hello.exe means run this file from the current folder; it is not BASIC source.


## Check your understanding

Expect the greeting and exit status 0. Change one word, save, compile again, and run again. Running an old executable after a compilation failure does not test your new source. Deliberately remove the closing quotation mark, read the compiler diagnostic, repair it, and recompile. A diagnostic identifies a location and a problem; begin with the first error because later errors may follow from it.

On a Unix-like shell use fbc -lang fb -w all hello.bas -x hello and then ./hello. Compiler and linker availability depends on the release and platform. The examples in this course are authored teaching material; compiler-specific qualification is required before embedding them in a product.


## Further reading

- [FreeBASIC downloads](https://www.freebasic.net/wiki/CompilerDownload)
- [FreeBASIC manual contents](https://www.freebasic.net/wiki/DocToc)

## Continue learning

[Course contents](index.md) · [Next: Names, values and number types](02-names-values-and-number-types.md)
