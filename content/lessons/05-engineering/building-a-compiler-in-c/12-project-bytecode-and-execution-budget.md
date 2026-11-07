<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/12-project-bytecode-and-execution-budget.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Project: inspect bytecode and bound execution

[Course contents](index.md) · [Previous: Project: specify and run a small language](11-project-a-small-language.md)

## Store the result of compilation
Bytecode is a file representation of instructions for a virtual machine. Saving it separates compilation from execution. This lesson uses a four-instruction program so that the execution limit is easy to reason about.

## Prepare
Build Umicom C using its docs/execution-guide.md. Review [the compiler course](index.md) if tokens or stacks are unfamiliar. Open labs/languages/umicom-c-project/budget.uc:
~~~c
int main(void) { return 6 * 7; }
~~~
Use a new output filename in a practice folder. Compilation refuses an existing output path, so a repeat attempt needs another name.

## Predict the instructions
~~~text
instruction       temporary values
push 6            [6]
push 7            [6, 7]
multiply          [42]
return            result 42
~~~
A stack stores temporary values with the most recently pushed value available first. Multiplication consumes two operands and produces one value.

## Compile, inspect and execute
From the Umicom C checkout in PowerShell, after creating your practice directory:
~~~powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" compile "C:\umicom\Umicom-Bits2Banking\labs\languages\umicom-c-project\budget.uc" "C:\umicom\practice\budget-first.umcb"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" disassemble "C:\umicom\practice\budget-first.umcb"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" exec "C:\umicom\practice\budget-first.umcb" --max-steps 4
~~~
Disassembly displays instructions in readable form. Compare the displayed operations with the four-step trace. Successful execution should print Result: 42 and Instructions: 4.

Bash uses the same subcommands:
~~~bash
./build/native-debug/bin/umicom-c compile ../Umicom-Bits2Banking/labs/languages/umicom-c-project/budget.uc ./budget-first.umcb
./build/native-debug/bin/umicom-c disassemble ./budget-first.umcb
./build/native-debug/bin/umicom-c exec ./budget-first.umcb --max-steps 4
~~~
Stop if a command fails; later commands should not accidentally use an older file.

## Observe a deliberate failure
Run exec again with --max-steps 3. The machine can calculate 42 but cannot execute the return instruction within that budget. Expect a failed execution. Inspect $LASTEXITCODE in PowerShell or echo $? in Bash immediately afterwards.

An instruction budget is a limit on counted operations. It is not a complete security sandbox, a wall-clock deadline or proof that all host resources are bounded.

## Exercise and answer
Why must three steps fail even though 42 is on the stack? Returning is part of the program's defined completion. Stopping early cannot be reported as a completed run.

## Compare the two routes
Run budget.uc directly and execute its compiled file. Both should produce the same result under a sufficient budget. The compiler repository's round-trip tests exercise that relationship across more examples.

## Extend the project responsibly
Before adding a language feature, specify its syntax, value rules, invalid cases and expected instructions. Add focused tests, then update the parser and execution support. Keep one language implementation in Umicom C and share its integration through the existing Framework interfaces.

## Source map
Read `umicom-c/src/bytecode.c` in the Umicom C checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Project: specify and run a small language](11-project-a-small-language.md)

[Next: Build an instruction viewer](13-build-an-instruction-viewer.md)
