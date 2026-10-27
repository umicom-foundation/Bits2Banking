# Introduction to C programming

## Start with an everyday instruction

Imagine a notebook in which you record one completed exercise. Your starting count is zero. Completing one exercise changes the count to one. Before asking a computer to do this, describe the rule in words: read the current count, check that another exercise is allowed, add one, and report the result.

A program expresses rules in a language a compiler can translate. C is one such language. Source code is the text you edit. A compiler translates it into machine instructions. The executable is the resulting program you launch. Editing the source does not automatically change an executable you built earlier.

## Read a complete small program

Open [the greeting source](../../../labs/native/first-c-programs/greeting.c). Read it without running anything. Its opening comment identifies the file, author and licence. Comments explain intent to people; they are not executed.

The line beginning with #include makes declarations available. A declaration tells the compiler how a function can be called. A function is a named operation, such as printing a message. The main function is the entry point of this ordinary hosted program. Hosted means that an operating system and C runtime prepare its starting environment.

Curly braces group the instructions belonging to main. A semicolon ends a statement. Double quotation marks delimit text. A sequence such as \n inside text means a new line. A return value of zero tells the launching environment that this program completed successfully. It does not prove that an arbitrary program has no bugs.

~~~text
Text in greeting.c
       |
       v
Compiler and linker
       |
       v
Executable in a build folder
       |
       v
A message in the terminal
~~~

## Give a value a name

In [the activity console](../../../labs/native/framework-activity/console.c), unsigned completed = 0U introduces a variable. A variable is named storage for a value. unsigned means the integer cannot represent a negative number. The suffix U on a number asks for an unsigned integer constant.

The expression &completed gives the address of this storage. An address tells a function where it may write an answer. It is not the answer itself. The function call passes the current value and the address of the result. Our function copies the current value before updating the result, so this particular in-place call is supported.

Do not guess whether another function permits this. Its contract must say so. Reading the contract is part of programming, just as reading a measuring instrument's scale is part of using it.

## Prepare, build, then run

First follow [Windows tool setup](../../umicom/windows-development.md). For the first small C examples, an installed Framework SDK is not required.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\first-c-programs" -B ".\build\first-c-programs" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DBUILD_TESTING=ON
cmake --build ".\build\first-c-programs" --target btb-first-greeting
& ".\build\first-c-programs\btb-first-greeting.exe"
~~~

Run one line at a time. If configuration or building reports an error, stop there. Compare the output with [the expected greeting](../../../labs/native/first-c-programs/expected/greeting.txt). The ampersand before the quoted executable path is PowerShell's call operator: it launches that path.

## Make one change you understand

Read the greeting text first. Predict what changing one word inside its quotation marks will print. Save your edited file, build the same target again, and launch it again. Keep the braces, quotation marks and semicolon in place. An accidental missing quotation mark is a compiler error, not evidence that you cannot learn programming.

Then restore the original greeting text and rebuild so its existing expected-output test still describes the example. When intentionally changing a program's behaviour, review the test expectation too; do not change a test just to hide a defect.

## Check your understanding

**Question:** You edit a greeting but launch the old executable without rebuilding. Which message should you expect?

**Answer:** The old executable still contains the earlier translated program. Save the source, build successfully and then launch the new executable.

Continue through [Learning C: For beginners](../../courses/learning-c/index.html) for decisions, repetition, functions, arrays and borrowed memory. You can trace values on paper before installing any tools.

[Course contents](index.md)
