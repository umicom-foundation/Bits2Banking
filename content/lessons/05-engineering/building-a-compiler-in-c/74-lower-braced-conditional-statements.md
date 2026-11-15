<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/74-lower-braced-conditional-statements.md

PURPOSE:
Lower braced conditional statements

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Lower braced conditional statements

A conditional statement chooses which updates to execute. It differs from a conditional expression, which chooses a value. This lesson extends the existing Umicom C compiler without adding a virtual-machine opcode. Work through the previous local-variable, forward-branch and compound-assignment lessons first. You will trace the generated control flow, predict instruction budgets and test a consumer independently of the compiler.

## 1. State the language boundary before changing the parser

The supported function has initialized integer locals, braced if statements, an optional braced else and one final return. Bodies can update existing locals and contain another braced if. They cannot declare locals or return early. There is one flat name scope. These restrictions describe an intentionally small language profile; familiar C spelling does not establish support for all C23 programs.

~~~c
int main(void)
{
    int value = 1;
    if (0) {
        value = 7;
    } else {
        value = 42;
    }
    return value;
}
~~~

Save this program as conditional.uc in your Umicom C checkout. The condition is zero, so the false body stores 42. Empty bodies are also permitted. A nested braced if inside else remains valid. The following lesson adds supported else-if chains through the same forward-branch runtime. The lexer recognizes if and else as complete keywords; if_value and elsewhere remain ordinary names.

## 2. Lower the statement into existing branches

Lowering means translating a source construct into simpler instructions. Read if_statement in src/compiler.c. First compile the condition, then reserve a JUMP_IF_ZERO target. Compile the true body. When an else follows, emit JUMP to skip it, patch the earlier false target to the start of that body and finally patch the join target. Without an else, the false target is simply the next instruction after the true body.

~~~text
0 PUSH 1            6 JUMP 9
1 STORE_LOCAL 0     7 PUSH 42
2 PUSH 0            8 STORE_LOCAL 0
3 JUMP_IF_ZERO 7    9 LOAD_LOCAL 0
4 PUSH 7          10 RETURN
5 STORE_LOCAL 0
~~~

JUMP_IF_ZERO consumes the condition. Each assignment consumes its computed value when STORE_LOCAL writes it. Consequently both paths reach instruction 9 at the same stack depth. The existing verifier checks this property independently. The compiler does not gain permission to produce malformed bytecode merely because it generated the instructions itself.

## 3. Observe a path, rather than counting the whole program

~~~powershell
cmake -S . -B build -G Ninja -DUMICOM_C_BUILD_TESTS=ON
cmake --build build
.\build\bin\umicom-c.exe check .\conditional.uc
.\build\bin\umicom-c.exe trace .\conditional.uc
.\build\bin\umicom-c.exe run .\conditional.uc --max-steps 8
~~~

Run each command separately and stop on errors. A supported C23 host compiler and Ninja must be available. Check accepts eleven instructions. Trace visits 0, 1, 2, 3, 7, 8, 9 and 10; run completes with 42 after eight steps. Source offsets depend on whitespace and comments, so compare instruction indices and operations when following this table.

Change the condition to one. The selected path now includes the extra jump at index 6 and requires nine steps. An eight-step budget must fail before completion, although the accepted program still contains eleven instructions. Fuel is an execution limit, not a count of source statements or a wall-clock timeout. Use a nine-step budget to observe the result seven.

## 4. Check both arms, execute only one

Compilation must parse and resolve names in both bodies. Put an unknown name in the skipped body: compilation still fails. In contrast, division by zero inside a syntactically valid skipped body does not run. Selecting that body must produce the checked arithmetic error. An error while evaluating the condition prevents either body from executing.

1. Add a local declaration inside a body and confirm rejection. Move the declaration before the if and use assignment inside it.
2. Remove a required brace and confirm a diagnostic rather than accepting an ambiguous statement.
3. Use value += 1 in the true body and a nested braced if in the false body. Predict and inspect each path.
4. Run with too little fuel and confirm that the caller checks failure instead of using an uncompleted result.

Keeping declarations outside bodies avoids suggesting block scope that the current symbol table does not implement. It also prevents a newly declared name from appearing initialized only on one path. Runtime validation still proves initialization on every structural path, even one a constant condition would not select.

## 5. Share recursion limits across statements and expressions

An attacker can nest a statement and then place a deeply recursive expression inside it. Separate counters that restart at each boundary would miss the combined depth. The parser therefore carries the enclosing depth from if_statement to if_body, local_statement and expression parsing. This uses the same limit as the existing expression parser.

The boundary tests admit 63 nested literal-condition statements and reject a 64th. An additional recursive unary expression at the deepest admitted point can also exceed the combined limit. Test these exact boundaries and mixed nesting, not just a very large input. Flat instruction capacity is separate: 127 empty if statements followed by return fill the current 256-instruction limit, while one more is refused.

## 6. Qualify the artifact and its consumers

~~~powershell
.\build\bin\umicom-c.exe compile .\conditional.uc .\build\conditional.umcb
.\build\bin\umicom-c.exe disassemble .\build\conditional.umcb
.\build\bin\umicom-c.exe exec .\build\conditional.umcb --max-steps 8
ctest --test-dir build -R "if-statement" --output-on-failure --no-tests=error
~~~

Choose a fresh artifact name: compile refuses to overwrite an existing file. These operations use existing format 4. Source syntax is advertised separately by UMC_FEATURE_IF_STATEMENTS; the runtime profile does not claim it can parse that syntax. Test individual capability bits instead of assuming one complete feature-mask value will never change.

Read tests/test_if_statement.c alongside the CLI regression. A literal byte fixture checks encoding independently of the writer. Other groups exercise exact byte spans, embedded NUL, diagnostics, selected arithmetic failures, trace order and every fuel boundary. A native C comparison corpus uses defined small integer inputs, avoiding undefined native overflow as a supposed oracle.

The Kernel CVM consumer has a different entry contract: a selector requests a predefined scenario. Keep its host expectations aligned with the guest dispatch table. A selector that once meant unknown may later become a valid profile query. Add all supported cases and move the unknown-selector assertion to a genuinely unsupported value; retain a maximum-value refusal too.

Run host and guest qualification separately and record the tested source identities. A passing compiler suite does not establish a Kernel boot, a Framework preview or a Studio GUI interaction. Framework preview coverage uses the same conditional examples but remains a separate consumer check. This separation makes a successful result precise and exposes missing coverage instead of hiding it behind one large test count.

[Course contents](index.md) · [Previous lesson](73-lower-checked-compound-assignments.md)

[Next lesson: Lower ordered else-if chains](75-lower-ordered-else-if-chains.md)
