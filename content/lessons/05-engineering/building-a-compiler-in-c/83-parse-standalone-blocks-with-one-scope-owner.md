<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/83-parse-standalone-blocks-with-one-scope-owner.md

PURPOSE:
Parse standalone blocks with one scope owner

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Parse standalone blocks with one scope owner

[Course contents](index.md)

## Begin with a group that always runs

A statement is one unit of work in a program. A compound statement groups several statements between an opening brace and a closing brace. The group can contain another group. In this lesson you will extend the idea of branch-local scope to a standalone block: a block that is not introduced by if or else. You will trace how the parser enters it, learns temporary names and forgets those names when the closing brace is reached. You will also see why this change belongs to the compiler rather than the virtual machine.

Complete the preceding lesson about branch-local names first. It introduces the symbol table, which connects source spellings to numeric local slots. Keep the complete Umicom C checkout and a configured hosted build available. The accepted language remains a small integer language. The fact that its implementation is written in C23 does not mean it can compile every C23 program, a FreeBASIC program or a D program.


## Run the complete example

~~~c
int main(void) {
    int result = 0;
    {
        const int answer = 42;
        result = answer;
    }
    return result;
}
~~~

The first pair of braces encloses main. The inner pair groups the temporary calculation. result begins as zero in the outer scope. answer begins as 42 in the inner scope. The assignment reads answer while it is visible and copies its integer value to result. The final return uses result, whose declaration still belongs to the surrounding function body. There is no condition in front of the inner opening brace, so the block executes whenever execution reaches it.

~~~powershell
.\build\bin\umicom-c.exe check .\examples\compound_statements.uc
.\build\bin\umicom-c.exe run .\examples\compound_statements.uc --max-steps 8
.\build\bin\umicom-c.exe trace .\examples\compound_statements.uc
~~~

1. Open examples/compound_statements.uc in the Umicom C checkout. Match each opening brace to its closing brace before changing anything.
2. In PowerShell, run the commands below separately. They assume the configured executable is in build/bin; use the actual path of your build.
3. Expect check to accept eight instructions and run to report Result: 42 and Instructions: 8. Read the trace to connect source names to numeric local slots.
4. Run a copy with a seven-step budget. Expect instruction-budget exhaustion and no completed result. The budget counts VM operations, not lines or braces.


## Express recursive syntax without an unbounded parser

A grammar is a description of accepted source shapes. The relevant production is statement = local-declaration | update | conditional-statement | body, with body = "{" statement* "}". A vertical bar means choose one possibility. The star means repeat zero or more times. Because a body contains statements and a statement can itself be a body, the grammar is recursive. Recursive means that a structure is defined partly in terms of another instance of itself.

A recursive grammar does not give an implementation permission to use unlimited machine stack space. The parser has a 64-level shared depth budget. A standalone block checks that budget before calling the body parser at depth + 1. A nested block, an if condition and a nested expression all use the same accounting. This prevents a caller from avoiding the limit by alternating different syntactic forms. Empty blocks are valuable boundary fixtures because they test brace nesting without also introducing expression recursion.


## Reuse a single owner for lexical state

1. Read block_statement in src/compiler.c. If an earlier parse already failed, it returns without further work. It checks depth before descending.
2. Follow its call to if_body. The existing function name reflects its first use for branches; the same owner now handles a standalone body.
3. At body entry, save parser->local_count as outer_count. This is a mark: the number of entries that belong to surrounding scopes.
4. Dispatch initialized declarations, local updates, nested if statements and nested blocks through their existing handlers. A closing brace ends the sequence.
5. After expecting that closing brace, restore parser->local_count to outer_count. Do this even if a nested operation failed. Do not create a second table or a separate implementation of declaration validation.

Ownership here means responsibility for maintaining a piece of state. The body parser owns the temporary change to the visible-name count. It is responsible for restoring that count at every exit. A declaration handler owns validation of its initializer, duplicate spelling and read-only qualifier. A block does not need to repeat those checks. Reusing the existing handler reduces the chance that a const declaration works differently in a branch and a standalone group.


## Trace nested marks by hand

~~~c
int main(void) {
    int result = 0;
    {
        int amount = 6;
        {
            const int factor = 7;
            result = amount * factor;
        }
    }
    return result;
}
~~~

Write three rows on paper: result, amount and factor. After result is declared, the visible count is one. The first inner block saves one, then amount raises the count to two. The next block saves two, then factor raises it to three. At the inner closing brace, restore two: factor is no longer found. At the next closing brace, restore one: amount is no longer found. result was never removed, so the final return can use it. The multiplication has already copied its result into that outer variable.

This is lexical visibility, determined by the structure of source text. It is separate from whether a branch happens to run. Every body must use valid names even when its condition is false. Conversely, an arithmetic expression such as 1 / 0 can be syntactically valid but fail only when execution reaches it. Name lookup and runtime arithmetic protect different boundaries.

Neither brace emits an instruction. The const spelling adds no runtime operation either. The compiler reports a new source capability, UMC_FEATURE_COMPOUND_STATEMENTS, with bit value 2097152. The runtime still executes the same load, store, arithmetic and return operations. The simple example uses canonical bytecode format 3. A program containing a conditional may require format 4, and other supported operations can require a newer format. Select the wire format from operations, not from the number of source braces.


## Do not confuse scope exit with memory release

A local slot is a storage location for a signed 32-bit integer. Restoring the compiler name count does not erase that runtime slot. A later nonoverlapping declaration may reuse it after initializing it again. This is sufficient for the current integer semantics, but it is not a promise to wipe secrets, close a file, release a GPU allocation or collect a heap object. If a future language feature owns resources, its lifetime and cleanup rules need a separate design and tests.

The limit of 32 locals applies to simultaneously visible names. One outer result plus 30 temporary names fits. Three successive blocks of that shape can have 90 temporary declarations in the source while never needing more than 31 visible entries at once. The program still must fit its 256-instruction limit. Slot reuse saves a bounded table from unnecessary growth; it does not make arbitrary programs fit or remove the need for capacity checks.


## Keep the supported subset explicit

1. Try return answer after the block in a separate practice file. Expect an undeclared-or-uninitialized-name diagnostic at answer. Restore return result.
2. Try int result = 7 inside the block. The active outer name makes this shadowing, which this Umicom C subset refuses. Full C has broader rules.
3. Try int value = value in an otherwise empty block. The initializer is parsed before the new name is registered, so it cannot initialize itself.
4. Try a return inside a block. Early returns remain unsupported. Keep the required final return at the top level of main.
5. Try {} before the final return. It is accepted and adds no operations. Try {;} in a practice file: the empty statement spelled as a semicolon is not supported, although an empty body is.

These distinctions are small but important when maintaining tests. The old branch-scope suite rejected a standalone block because the earlier grammar did not admit it. That exact source is now a positive case. The former expectation is retained for engineering review, while genuinely invalid scope escapes and early returns remain active refusals. A grammar extension must change both implementation and the tests that describe the old boundary. Do not weaken unrelated error checks to make a new test run appear green.


## Compare source execution with saved bytecode

~~~powershell
.\build\bin\umicom-c.exe compile .\examples\compound_statements.uc .\standalone-scope.umcb
.\build\bin\umicom-c.exe exec .\standalone-scope.umcb --max-steps 8
.\build\bin\umicom-c.exe trace-bytecode .\standalone-scope.umcb
.\build\bin\umicom-c.exe profile
~~~

Choose an artifact filename that does not already exist. Compile refuses to overwrite it. Compare the saved-bytecode result and trace with the source run, including source offsets. A successful compilation publishes a nonzero instruction count. On failure the count is zero; the output array is scratch storage and must not be executed. Keeping the public count unpublished is different from promising that every scratch byte remains unchanged.


## Verify the feature from independent expectations

The regression source tests/test_compound_statements.c checks native C reference calculations, exact opcode and operand sequences, format selection, every fuel boundary for the simple program, shared nesting depth, slot capacity and reuse. It also checks CRLF source locations, every truncated prefix of a complete source span, const-write refusal and checked runtime overflow. A separate CLI test invokes the actual executable and confirms that rejected source does not produce an artifact and existing files are unchanged.

1. Predict the nested multiplication example result before running it. Then identify each name that remains visible after each brace.
2. Explain why changing a name scope does not require a new VM opcode.
3. Explain why 64 empty blocks can reach a structural boundary while 64 blocks containing an expression may exceed the shared budget.
4. Design one test that alternates blocks and conditions, so a depth-accounting bug cannot hide in one syntax handler.
5. Record the executable path, command, status and result you actually observed. A source review does not establish that a different installed compiler or Studio integration supports the feature.


## The simple eight-instruction example

| Step | Operation | Effect |
| --- | --- | --- |
| 1 | PUSH 0 | Prepare the result initializer |
| 2 | STORE_LOCAL 0 | Initialize the outer local |
| 3 | PUSH 42 | Prepare the answer initializer |
| 4 | STORE_LOCAL 1 | Initialize the temporary local |
| 5 | LOAD_LOCAL 1 | Read answer inside its scope |
| 6 | STORE_LOCAL 0 | Copy the integer into result |
| 7 | LOAD_LOCAL 0 | Read the returned integer |
| 8 | RETURN | Publish the completed result |

## Further reading

- [Complete standalone-block source](https://github.com/umicom-foundation/umicom-c/blob/main/examples/compound_statements.uc)
- [Compiler scope implementation](https://github.com/umicom-foundation/umicom-c/blob/main/src/compiler.c)
- [Regression source](https://github.com/umicom-foundation/umicom-c/blob/main/tests/test_compound_statements.c)
- [Standalone scope walkthrough](https://github.com/umicom-foundation/umicom-c/blob/main/docs/compound-statements.md)

[Previous: Give branch locals a lexical scope without changing the VM](82-give-branch-locals-a-lexical-scope.md)

[Next: Report source warnings without running a program](84-report-source-warnings-without-running-a-program.md)
