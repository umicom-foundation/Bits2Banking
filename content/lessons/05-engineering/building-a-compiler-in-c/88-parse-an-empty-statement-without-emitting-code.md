<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/88-parse-an-empty-statement-without-emitting-code.md

PURPOSE:
Parse an empty statement without emitting code

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Parse an empty statement without emitting code

[Course contents](index.md)

## Start with a semicolon

A statement is one instruction in the source language’s grammar. That does not mean it always becomes a machine or virtual-machine instruction. In C, a semicolon on its own is an empty statement: it asks the program to do nothing. This lesson follows that small language feature through the lexer, parser, bytecode and runtime. You will see why accepting more source syntax does not always require enlarging the virtual machine. Umicom C remains a deliberately bounded C-shaped language; it is not a complete implementation of C23.


## Separate characters, tokens and instructions

Source text is a sequence of characters. A lexer groups those characters into tokens, such as an integer, a brace or a semicolon. A parser checks whether tokens appear in an allowed order. The compiler then emits instructions for operations that must happen when the program runs. Bytecode is the saved representation of those instructions. The virtual machine reads bytecode instructions, not the original semicolons. Keeping these stages separate helps us choose the correct place for a feature.


| Stage | Input | What happens to a standalone semicolon? |
| --- | --- | --- |
| Lexer | Source characters | Produces a SEMICOLON token |
| Parser | Tokens | Consumes an allowed empty statement |
| Emitter | Accepted operations | Emits no instruction for the empty statement |
| Runtime | Validated instructions | Has no empty-statement operation to execute |


## Read the smallest useful example

main names the program’s entry function in this subset. int declares its integer result. void says that this form takes no parameters. The braces enclose the body. return supplies the final value. The star means multiplication. Each standalone semicolon is an empty statement. The semicolon immediately following 7 is instead the delimiter required by return.

~~~c
int main(void) {
    ;
    { ;; }
    return 6 * 7;
    ;;
}
~~~


## Predict the result before using a tool

Six multiplied by seven is forty-two. The compiler needs to push 6, push 7, multiply the two values and return the result. It therefore emits four instructions. The empty braces establish a lexical scope but contain no values or operations. The extra semicolons require no local slots and no runtime instruction. A lexical scope controls which source names are visible; it is not automatically a separately allocated object.


| Instruction | Operand stack after success |
| --- | --- |
| PUSH 6 | 6 |
| PUSH 7 | 6, 7 |
| MULTIPLY | 42 |
| RETURN | Result is published as 42 |


## Prepare a hosted compiler build

Use a terminal in your Umicom C checkout. The Windows preset selects the installed UCRT64 GCC compiler and Ninja generator. CMake configuration checks the project and writes build rules; building follows those rules to create executable files. Run each command separately and stop on unexpected errors. If your checkout is elsewhere, change the first path. These commands are for the learner to execute and are not a claim that an independently installed copy has already passed.

~~~powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug --parallel 2
.\build\windows-ucrt64-debug\bin\umicom-c.exe check examples/empty_statements.uc
~~~


## Interpret a source check correctly

check parses and compiles the file into a bounded instruction buffer. It should report accepted: 4 instructions for this example. It does not execute the program, prove every possible input safe, or imply support for every C construct. A diagnostic reports a source location and a reason when admission fails. The example file contains an attribution header; comments contribute source bytes but do not add instructions.


## Give execution an exact budget

Fuel is the maximum number of virtual-machine instructions permitted during one run. It is not milliseconds, CPU cycles or a memory allowance. Give the four-instruction program fuel four. It should print Result: 42 and Instructions: 4. Then deliberately use fuel three: execution must refuse to publish a result because RETURN is still pending. An expected failed exercise is different from an unexpected failed build.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/empty_statements.uc --max-steps 4
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/empty_statements.uc --max-steps 3
~~~


## Save instructions without saving a new opcode

The compile command writes a new bytecode file. exec reads and validates that file before execution. Choose an unused output name: the command refuses to overwrite an existing artifact. This example uses wire format 1 because it contains ordinary arithmetic instructions. A wire format defines bytes exchanged between programs. Adding a source spelling does not justify changing that format when the emitted operations are unchanged.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe compile examples/empty_statements.uc build/empty-lesson.umcb
.\build\windows-ucrt64-debug\bin\umicom-c.exe exec build/empty-lesson.umcb --max-steps 4
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace-bytecode build/empty-lesson.umcb
~~~


## Follow the parser’s ownership

Open src/compiler.c and locate compile_source and if_body. The top-level statement list and the braced-body statement list each recognize TOKEN_SEMICOLON. They call advance to consume it and continue parsing. They do not call emit. After the required final return, the parser also consumes trailing semicolons before checking the closing brace. The existing lexer owns token boundaries, the parser owns grammatical admission, and the emitter owns instruction storage. Reusing these responsibilities avoids inventing a second token scanner or a meaningless runtime NOP.


## Do not confuse nothing with anything

Supporting an empty statement does not mean accepting every expression as a statement. Nor does it introduce loops, early returns or unbraced conditional bodies. The compiler still requires a final return with an expression. Inside this subset an if body must use braces, even though full C permits a broader statement grammar.

~~~c
int main(void) { ;;; }
int main(void) { return ; }
int main(void) { 1 + 2; return 42; }
int main(void) { if (1); return 42; }
~~~


## Notice the else boundary

An else belongs immediately after the preceding if body in this grammar. In if (1) {}; else {}, the semicolon after the first closing brace is a separate statement. It breaks that connection. The parser must reject the separated else instead of silently ignoring the semicolon to guess the author’s intent. By contrast, if (1) {;} else {;;} has two properly attached braced bodies containing empty statements. Both bodies are still parsed, even when the condition is a constant.


## Keep four resource limits separate

A program with thousands of semicolons may still emit only two instructions for return 42. The source limit nevertheless counts all input bytes, and the lexer must visit the tokens. Nested braces consume structural parser depth even when their bodies emit nothing. Instruction capacity bounds the generated records. Fuel bounds executed records. None of these quantities substitutes for the others.


| Limit | What it bounds | Effect of extra semicolons |
| --- | --- | --- |
| Source bytes | Borrowed text admitted by the compiler | Increases |
| Parser depth | Nested expression and statement structure | Unchanged unless braces or expressions are nested |
| Instruction capacity | Stored bytecode records | Unchanged for empty statements |
| Runtime fuel | Executed virtual-machine operations | Unchanged for empty statements |


## Ask the linked component for its capability

profile.h declares UMC_FEATURE_EMPTY_STATEMENTS with value 16777216. Test that bit in umc_compiler_profile(UMC_PROFILE_FEATURES). The runtime must not advertise it because runtime-only programs never parse source text. Installing a newer header cannot give an older linked library a new parser. This distinction matters when Studio uses an installed Umicom C library or Kernel consumes precompiled bytecode.

~~~c
#include "umicom_c/profile.h"

uint32_t features = umc_compiler_profile(UMC_PROFILE_FEATURES);
if ((features & UMC_FEATURE_EMPTY_STATEMENTS) == 0U) {
    /* Select a matching compiler before offering this source form. */
}
~~~


## Exercise the regressions

The regression suite compares ordinary and semicolon-rich programs instruction by instruction. It checks successful values, unchanged fuel cost, bytecode round trips, exact borrowed spans without a trailing NUL, malformed boundaries and never-read-local warnings. It also checks that thousands of semicolons do not require thousands of instruction slots. A failed compile reports count zero; its partially written instruction buffer must not be executed.

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R "umicom.c.(empty-statements|cli-empty-statements|profile|cli-profile)" --output-on-failure --no-tests=error
~~~


## Make and explain your own variation

1. Copy the source example to a new lesson file so the original remains available for comparison.
2. Change 6 * 7 to 40 + 2. Predict both the value and instruction count before running check.
3. Add ten semicolons before return and ten after its required delimiter. Check that the operation count remains four.
4. Introduce if (1) {}; else {} before return. Read the refusal, then move the extra semicolon inside the first body and check again.
5. Write down which stage changed in each experiment: lexing, parsing, instruction generation or execution. Do not describe every refusal as a runtime error.


## Recover from common mistakes

If the executable is missing, read the first build error and confirm the actual output directory. If the compiler rejects a standalone semicolon, inspect the linked compiler profile and source revision instead of removing the test. If compile reports an existing destination, select a fresh artifact filename. If a fuel-three run prints a result, keep the source, command, binary identity and full output for investigation: that contradicts this example’s four-operation contract. Never interpret a new grammar bit as a complete C23 compatibility promise.


[Previous: Inspect managed memory without collecting](87-inspect-managed-memory-without-collecting.md)

[Next: Decode ASCII character constants at the lexer](89-decode-ascii-character-constants-at-the-lexer.md)
