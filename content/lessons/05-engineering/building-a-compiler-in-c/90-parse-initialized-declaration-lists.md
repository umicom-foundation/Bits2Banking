<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/90-parse-initialized-declaration-lists.md

PURPOSE:
Parse initialized declaration lists without changing the virtual machine

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Parse initialized declaration lists without changing the virtual machine

[Course contents](index.md)

## What you will build

You will teach the existing Umicom C parser to accept two or more initialized integer names after one type prefix. The virtual machine, or VM, is the small interpreter that executes the compiler’s instructions. It already knows how to store and load local integers, so this feature belongs in source parsing. You will follow the exact declaration order, identify what the comma means, and check that the old one-name form still behaves the same. This lesson extends the bounded Umicom C language; it does not turn that language into complete ISO C23.


## Start with words you can point to

A variable is a named storage location. A declaration introduces its name and type. An initializer supplies its starting value. A declarator is the part of a declaration that describes one name. In our supported subset, a declarator is simply a name, an equals sign and an integer expression. A type tells the compiler what kind of value the name holds. Here that type is a signed 32-bit integer. The semicolon ends the declaration. The comma separates declarators within it.

~~~c
int first = 6, second = first * 7;
~~~


## Predict the result before running

Writing the two declarations on separate lines has the same meaning. Grouping names is a spelling choice, not an optimization claim. Prefer separate lines when that makes a real program easier to understand.

1. Read int once: both names use the supported integer declaration form.
2. Read first = 6: the first name starts with six.
3. Read the comma as “there is another name in this declaration”. It is not multiplication or a runtime command.
4. Read second = first * 7: read six from first and multiply it by seven.
5. Read the semicolon: the list is complete. A later return second; supplies 42 as the program result.


## A complete source file

Save this as declarator_lists.uc or use the supplied examples/declarator_lists.uc. A plain-text file contains source characters, not compiled machine instructions. The .uc suffix identifies this teaching language in our examples. main is its required entry function, void says there are no parameters, and braces enclose the supported statement sequence.

~~~c
int main(void) {
    int first = 6, second = first * 7;
    return second;
}
~~~


## Draw the lowering one instruction at a time


| Step | Operation | Reason |
| --- | --- | --- |
| 1 | PUSH 6 | Compute the first initializer. |
| 2 | STORE_LOCAL 0 | Store first in slot zero. |
| 3 | LOAD_LOCAL 0 | Read first for the next initializer. |
| 4 | PUSH 7 | Supply the second multiplication input. |
| 5 | MULTIPLY | Compute 42 with checked arithmetic. |
| 6 | STORE_LOCAL 1 | Store second in slot one. |
| 7 | LOAD_LOCAL 1 | Read the returned value. |
| 8 | RETURN | Publish the completed result. |


## Why the VM does not need a comma operation

Lowering means translating a convenient source form into simpler instructions. The comma controls which parser rule runs next; it has no remaining job after compilation. Both combined and separate declarations produce the same operations and operands. An operand is a value or index attached to an instruction, such as slot zero. Source offsets still point to the relevant token in each original file, so artifacts for differently spaced programs need not have identical bytes. Compare operations and operands when checking meaning, and check offsets separately when checking diagnostics.


## Separate prefix parsing from one-name parsing

The parser first consumes int, const int, or int const. It stores whether the declaration is read-only. It then calls the same one-declarator routine repeatedly while a comma is present. The routine requires an identifier, checks for a visible duplicate and checks the local capacity. It then consumes the equals sign and parses one expression. After a valid delimiter is found, it registers that local and emits its store. Keeping this routine shared avoids different initialization or warning rules for the first name and every later name.

~~~text
declaration = prefix declarator ("," declarator)* ";"
declarator  = identifier "=" expression
prefix      = "int" | "const" "int" | "int" "const"
~~~


## Visibility begins after the initializer

Visibility means that name lookup can find a declaration at the current source position. Consider int a = 6, b = a * 7;. The initializer for a is parsed before a is registered. Therefore a cannot refer to itself during initialization. Once it is registered, b can read it. A later name is not available early: int a = b, b = 6; is refused. This rule makes sequential initialization explicit and keeps the existing one-name semantics. Declaring the same visible name twice is also refused; this language deliberately does not provide shadowing of an active outer name.


## Apply const to the whole list

Const marks both base and answer as read-only in source. The alternative prefix int const has the same meaning. The compiler refuses later assignments, compound updates and prefix or postfix increments of either name. This is a source contract. A VM that receives raw local-store instructions does not know their original const spelling. Do not describe this source feature as protection against arbitrary bytecode writes or as a complete implementation of C type qualification.

~~~c
int main(void) {
    const int base = 6, answer = base * 7;
    return answer;
}
~~~


## Keep every boundary explicit


| Attempt | Why it is refused |
| --- | --- |
| int a=1,b; | Every local must have an initializer. |
| int a=1,b=b; | b is not visible in its own initializer. |
| int a=b,b=1; | b is declared too late for the first initializer. |
| int a=1,a=2; | The name is already visible. |
| int a=1,; | A comma must be followed by a complete declarator. |
| int a=1,int b=2; | The type prefix is not repeated after a comma. |
| a=1,b=2; | Comma-separated assignment statements are unsupported. |
| return (1,2); | A comma expression is a different language feature. |


## Scope and capacity are still owned by the block

A scope is the part of the source where a name can be found. Braces introduce the supported nested scopes. Both names from a declaration list belong to that same scope. They disappear from lookup when the block ends, and later disjoint blocks may reuse their numeric slots. The limit is 32 simultaneously visible locals, not 32 comma-separated statements. The instruction limit remains 256 and the source limit remains 65,536 bytes. A compiler must report an exceeded limit instead of assuming that a short source line has a small storage requirement.


## Warnings use the same lookup

A warning is an observation that does not itself reject valid source. The current warning service reports locals that are never read. In int a=1,b=a+1; return b;, the use of a inside b’s initializer counts as a read. Both names are used, even though a does not occur in the final return. In int a=1,b=2; return 0;, both are never read, and their warnings appear in declaration order. Reusing the compiler’s name resolution prevents a separate warning parser from disagreeing with actual compilation.


## Run the example with a matching compiler

Run commands separately and stop on unexpected errors. Your checkout may be in another folder; change only that location. An older executable may reject a newly documented source form. Check the binary you actually invoked instead of assuming that editing a header rebuilt it.

~~~powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug
cmake --build --preset windows-ucrt64-debug --parallel 2
.\build\windows-ucrt64-debug\bin\umicom-c.exe check examples/declarator_lists.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/declarator_lists.uc --max-steps 8
~~~

1. Open PowerShell and enter the Umicom C checkout after integrating its matching source and headers.
2. Select the existing UCRT64 toolchain and configure the documented preset.
3. Build with a small parallel count so this focused exercise does not compete heavily with other builds.
4. Run check first; it checks syntax and emitted structure without executing the arithmetic.
5. Run with eight instruction steps. Expect Result: 42 and Instructions: 8.


## Use deliberate failures to understand the contract

Repeat run with --max-steps 7. The execution budget, often called fuel, permits seven instructions, so the final return cannot complete. This is an intentional refusal. Next try int a=1/0,b=2;. Source checking can accept it, but execution fails at division before the second initializer runs. The completed result must remain unpublished on that failure. A syntax failure is different: failed compilation publishes an instruction count of zero. Partly written output storage is not a valid program and must never be executed.


## A line-ending test is also source code

To check diagnostics for a two-line guest program, the native test places the guest source in a C string. There are two languages to keep straight: the host C test and the text interpreted by Umicom C. A physical newline cannot appear unescaped inside an ordinary host C string. Write the escape sequences backslash-r and backslash-n to place carriage-return and line-feed bytes in the guest buffer. The guest parser then sees two lines. This distinction is useful whenever a test generates source, SQL, JSON or another nested format.

~~~c
const char *guest = "int main(void){int a=1,\r\n b=;return a;}";
~~~


## Verify meaning and compatibility separately

The regression suite compares the combined declaration with separate declarations, tests const on every name, checks exact capacities and malformed input, verifies source-order warnings, and round-trips the existing bytecode representation. The supplied example uses format 3 because it stores local integers; the comma adds no wire version. Query UMC_FEATURE_DECLARATOR_LISTS in the linked compiler’s feature mask. Do not require that bit from the runtime: it executes records and does not parse commas.

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R "umicom.c.(declarator-lists|cli-declarator-lists|profile|cli-profile)" --output-on-failure --no-tests=error
~~~


## Practice and explain your answer

Successful completion means you can explain the source rule, emitted instructions, failure publication and lifetime boundary. It does not establish support for pointers, arrays, function calls, loops, arbitrary C or embedded foreign-language execution.

1. Change the first value to five. Predict the result and instruction count before running: 35 and eight.
2. Add a third initialized name that reads second. Count its extra load/store instructions rather than guessing from the number of commas.
3. Declare a const pair and try to change only the second name. Explain why the whole declaration prefix applies to it.
4. Move the pair into a nested block and try to return its name outside. Explain visibility rather than treating the rejection as a parser accident.
5. Write a pair where only the first name is unused. Run the warning service and compare the warning location with the source token.


[Previous: Decode ASCII character constants at the lexer](89-decode-ascii-character-constants-at-the-lexer.md)

[Next: Count structural paths before running bytecode](91-count-structural-paths-before-running-bytecode.md)
