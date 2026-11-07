<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/11-project-a-small-language.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Project: specify and run a small language

[Course contents](index.md) · [Previous: Read past a comment safely](10-read-past-a-comment-safely.md) · [Next: Project: inspect bytecode and bound execution](12-project-bytecode-and-execution-budget.md)

## Build a language in understandable stages
A language project starts with a promise about accepted source and its meaning. This guided project uses the existing Umicom C compiler rather than introducing a second compiler implementation.

You will write a short program, trace its tokens and verify its result. The preceding compiler lessons explain the lexer, expression parser and virtual machine in more detail.

## Set up
You need the Bits2Banking and umicom-c repositories on your development computer. Follow umicom-c/docs/execution-guide.md to install the C23 toolchain, configure, build and test the current compiler. The Windows executable is build/windows-ucrt64-debug/bin/umicom-c.exe within that repository. The Linux native-debug build produces build/native-debug/bin/umicom-c.

Use a terminal, a plain text editor and a folder you choose for outputs. Check that --version runs before diagnosing your example.

## State the supported contract
The project program contains one int main(void) function returning integer arithmetic. This exercise needs numeric literals, parentheses, addition and multiplication. It does not require variables, strings, loops or classes.

Open labs/languages/umicom-c-project/answer.uc in Bits2Banking:
~~~c
int main(void) { return (8 + 2) * 3; }
~~~
Its result is 30. Parentheses make the addition happen before multiplication. Without the parentheses, 8 + 2 * 3 would produce 14.

## Trace the pipeline
~~~text
source characters -> tokens -> expression structure -> instructions -> result
(8 + 2) * 3          + and *    multiply(add(8,2),3)     stack work     30
~~~
A token is a recognised piece of source, such as a number or operator. Expression structure records which operands belong to each operator. The virtual machine executes the emitted instructions.

## Run the project
From C:\umicom\umicom-c in PowerShell:
~~~powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" check "C:\umicom\Umicom-Bits2Banking\labs\languages\umicom-c-project\answer.uc"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" run "C:\umicom\Umicom-Bits2Banking\labs\languages\umicom-c-project\answer.uc"
~~~
Replace the checkout root if yours differs. Expect Result: 30. The check command examines the program without claiming its intended result is correct; compare execution with your independent calculation.

On Linux, from the umicom-c checkout:
~~~bash
./build/native-debug/bin/umicom-c run ../Umicom-Bits2Banking/labs/languages/umicom-c-project/answer.uc
~~~

## Exercise
Create another practice source returning (4 + 5) * 2. Predict 18 before running. Then remove one closing parenthesis. Expect a source diagnostic and a failure result, not a guessed execution.

## Read the real implementation
Follow src/lexer.c, src/compiler.c and src/vm.c in umicom-c. Locate the handling of numbers, precedence and multiplication. Describe each stage in your own words before attempting to extend the grammar.

## Completion checkpoint
You can explain the accepted syntax, predict a result, identify a malformed program and locate the implementation stages. This is a first language project; Umicom C remains a prototype and does not replace the C23 toolchain used to build Framework.

## Trace the parser by hand
A parser recognises how tokens fit together. Open [src/compiler.c](https://github.com/umicom-foundation/umicom-c/blob/main/src/compiler.c) and locate expression, product and unary. expression handles addition and subtraction. It calls product to obtain operands. product handles multiplication and division, and obtains its operands from unary. This call structure gives multiplication tighter binding than addition.

1. Trace 8 + 2 * 3. The first product is 8. The second product is 2 * 3. expression adds 8 and 6, giving 14.
2. Trace (8 + 2) * 3. Parentheses request an expression inside unary. That inner expression produces 10 before the outer product multiplies by 3.
3. Find emit. An emitted instruction is a request for later execution, not the arithmetic result itself.
4. Find umc_compile. Identify the output capacity check and the diagnostic result before trying to add another operator.

A useful extension exercise is to specify a remainder operator: define the token, precedence, behaviour for negative operands and rejection of a zero divisor before writing code. This lesson does not claim that extension is already implemented.

## Source map
Read `umicom-c/src/compiler.c` in the Umicom C checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Read past a comment safely](10-read-past-a-comment-safely.md) · [Next: Project: inspect bytecode and bound execution](12-project-bytecode-and-execution-budget.md)
