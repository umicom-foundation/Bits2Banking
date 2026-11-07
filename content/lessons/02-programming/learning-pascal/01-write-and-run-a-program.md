<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/01-write-and-run-a-program.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Write and run a Pascal program

[Course contents](index.md) · [Next: Values, functions and input validation](02-values-functions-and-validation.md)

## Your first result
Pascal is a programming language: a vocabulary and grammar for describing operations. In this lesson you will compile a source file and run the resulting program. You do not need to have studied C first.

## Prepare the tools
Use the installation summary on [the course contents page](index.md). Install Free Pascal for your operating system, open a new terminal, and type fpc -iV to check that the compiler can be found. The command should print its version. A missing command means setup is incomplete; it is not a fault in your source.

1. Open labs/languages/pascal-progress/hello.pas in your Bits2Banking checkout.
2. Read the program name following program. The semicolon ends that declaration.
3. Find begin and end. They enclose the main instructions. The final end has a full stop because it finishes the program.
4. Find WriteLn. It writes text and then moves to a new line.
5. Build and run using the course commands. Compare the greeting with the source.

## A complete practice program
In a separate folder of your choice, save greeting.pas as plain text:
~~~pascal
program Greeting;
begin
  WriteLn('Welcome to Learning Pascal.');
end.
~~~
Single quotation marks enclose a string: a sequence of characters. The marks themselves are not printed. WriteLn is supplied by the runtime library that accompanies the compiler.

In PowerShell, from that folder:
~~~powershell
fpc greeting.pas
.\greeting.exe
~~~
In Bash:
~~~bash
fpc greeting.pas
./greeting
~~~
Expect Welcome to Learning Pascal. on one line. Compilation may also create an object file. An object file is intermediate machine code used while producing the executable; it is not the source you edit.

## Follow the stages
~~~text
greeting.pas -> Free Pascal compiler -> executable -> printed greeting
edit here                              run this
~~~
An editor changes text. A compiler checks and translates that text. A terminal starts the tools. These are separate jobs even when an IDE puts them in one window.

## Make and explain a change
Add a second WriteLn containing 'Today I will build a small program.'. Predict two lines, compile, then run. Next temporarily remove a closing quotation mark. Read the compiler diagnostic and restore the mark. Do not run an old executable after a failed compilation and assume it includes your change.

## Exercise and answer
Why does changing the greeting in the source leave the previous executable unchanged? The executable is a separate file produced by compilation. Recompile successfully before checking the new output.

## Where this fits
This Pascal lab belongs to the Bits2Banking learning collection. Its progress example follows the same count-and-validate idea used by the C first-program lab. Each implementation is a teaching example; applications continue to use the shared Umicom Framework services.

## Help when a command fails
Check the current directory and the exact .pas filename. If fpc cannot be found, revisit installation and PATH. If the output differs, confirm that the file was saved and that you ran the executable from the folder you just compiled.

## Source map
Read `labs/languages/pascal-progress/hello.pas` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Values, functions and input validation](02-values-functions-and-validation.md)
