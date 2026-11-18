<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/91-count-structural-paths-before-running-bytecode.md

PURPOSE:
Count structural paths before running bytecode

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Count structural paths before running bytecode

[Course contents](index.md)

## What you will learn

A program can be checked in more than one way. Syntax checking asks whether its written form is admitted. Bytecode validation asks whether its instructions, stack and local-variable uses form a valid program. Structural path analysis asks how many interpreter operations a route through that program contains. Execution actually performs the arithmetic and selects branches. This lesson separates those questions so that an early-feedback tool can be useful without pretending that a static check proves every future result.

1. Build Umicom C with the existing execution-course instructions and keep that build directory for incremental builds.
2. Open examples/path_budget.uc in the Umicom C checkout, not a text editor's temporary preview.
3. Keep a notebook for predicted path lengths and actual run results. Do not enter a predicted result as a completed test.


## Start with an instruction and a budget

An instruction is one small operation understood by the virtual machine, such as PUSH, ADD or RETURN. The host implementation of one such operation may itself execute many processor instructions. Fuel is the allowed count of VM operations in one run. A limit of seven therefore does not mean seven nanoseconds or seven native CPU instructions. A caller chooses the limit before execution; the runtime checks it as work proceeds.


## Read the complete expression

The source file contains an integer entry function returning a conditional expression. The condition appears before the question mark. The expression after the question mark is used when the condition is nonzero; the expression after the colon is used when it is zero. Only the selected value expression executes. Here the constant 1 selects 40 + 2, so a successful run returns 42.

~~~c
int main(void) { return 1 ? 40 + 2 : 7; }
~~~


## A graph is a set of permitted next steps

A graph consists of nodes and edges. Here each instruction record is a node, and an edge says which record may execute next. An ordinary PUSH has one edge to the following instruction. JUMP has one edge to its target. JUMP_IF_ZERO has two structural edges: the target and the next record. The following diagram describes the compiled example; a graph edge is not an extra executed instruction.

~~~text
0 PUSH 1 -> 1 JUMP_IF_ZERO 6
              | nonzero: 2 PUSH 40 -> 3 PUSH 2 -> 4 ADD -> 5 JUMP 7 --+
              | zero:    6 PUSH 7 ----------------------------------+
                                                                   7 RETURN
~~~


## Count complete routes

Count the entry and RETURN, not only the arithmetic. The number of records in an artifact and the number visited by one execution answer different questions. The longest structural route in this example omits record 6.


| Route | Visited records | Instruction count |
| --- | --- | --- |
| Nonzero condition | 0, 1, 2, 3, 4, 5, 7 | 7 |
| Zero condition | 0, 1, 6, 7 | 4 |
| All stored records | 0 through 7 | 8 records; this is not a route |


## Why the report includes an impossible alternative

For this exact source, the condition is always 1. The false route cannot be selected by a correct fresh execution. The bound service deliberately does not evaluate constants, local values or arithmetic. It considers both conditional edges. Its minimum of four is therefore conservative: every successful run takes at least four steps, but this source always needs seven. Adding value-sensitive analysis would be a separate feature with additional correctness and resource obligations.


## Run the analysis without running arithmetic

Open PowerShell in your Umicom C checkout after the tool has built. Execute commands separately. The report should say minimum 4 and maximum 7, followed by a statement that both branch alternatives were considered and arithmetic was not executed.

~~~powershell
Set-Location "C:\umicom\umicom-c"
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" budget examples/path_budget.uc
~~~


## Compare a sufficient limit with an insufficient limit

The maximum is sufficient interpreter fuel for a fresh valid run, provided no arithmetic fault occurs. Seven permits RETURN to complete. Six allows the preceding operations but cannot complete RETURN. The second command is a deliberate failing exercise; inspect the diagnostic and do not continue a larger automation as though it had succeeded.

~~~powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" run examples/path_budget.uc --max-steps 7
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" run examples/path_budget.uc --max-steps 6
~~~


## Repeat from a stored artifact

Compilation writes a bytecode artifact, a portable encoded representation of the admitted instructions. budget-bytecode first decodes and validates that representation, then calls the same analyzer. The result should agree with source analysis for an artifact generated from the same source. A filename ending in .umcb does not prove that its contents are valid.

~~~powershell
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" compile examples/path_budget.uc path_budget.umcb
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" budget-bytecode path_budget.umcb
~~~


## Work backward rather than enumerating every route

Dynamic programming means reusing answers to smaller subproblems. The supported graph has only forward jumps, so start at the last record and move backward. A successor always has a larger index and has already been measured. RETURN has a remaining cost of one. An ordinary instruction adds one to the next record. A jump adds one to its target. A conditional adds one to the smaller successor cost for the minimum, and one to the larger cost for the maximum. This visits each record once after validation instead of recursively enumerating a potentially large number of routes.


## Calculate the example by hand

The values at record zero are the public report. Notice that the cost at record 5 includes JUMP itself. The edge from record 5 to RETURN has no separate cost.


| Record | Minimum remaining | Maximum remaining |
| --- | --- | --- |
| 7 RETURN | 1 | 1 |
| 6 PUSH 7 | 2 | 2 |
| 5 JUMP 7 | 2 | 2 |
| 4 ADD | 3 | 3 |
| 3 PUSH 2 | 4 | 4 |
| 2 PUSH 40 | 5 | 5 |
| 1 JUMP_IF_ZERO 6 | 1 + min(5,2) = 3 | 1 + max(5,2) = 6 |
| 0 PUSH 1 | 4 | 7 |


## Validation owns the assumptions

The analyzer does not independently decide whether a jump target, opcode, operand, stack depth or local-variable read is valid. It first calls the runtime's complete validator. Only after success may it rely on a final RETURN, valid forward successors and complete reachability. Reusing that owner prevents two services from slowly disagreeing about what a valid program means. A backward edge is refused rather than assigned a fictional finite cost.


## Make output ownership explicit in C

The caller owns the decoded instruction array, diagnostic and bounds object. They must be valid disjoint objects; the input remains unchanged during the call. No pointer is retained. The implementation computes into local arrays and publishes the two result fields only after successful validation and analysis. A failure leaves the previous result fields intact. That promise does not repair dangling pointers supplied by a caller.

~~~c
UmcExecutionBounds bounds = {0};
UmcDiagnostic diagnostic = {0};
UmcStatus status = umc_execution_bounds(program, count, &bounds, &diagnostic);
if (status == UMC_OK) {
    /* The caller can present bounds.maximum_instructions as proposed fuel. */
}
~~~


## Budget the analyzer as well as the guest

Two fixed arrays of size_t hold remaining path costs. With the current 256-record limit and eight-byte size_t, their combined payload is 4096 bytes. Stack frames, the validator and callers need additional storage. No heap allocation does not mean no memory use. A Kernel user process needs enough stack for the entire nested call chain. The forward-only invariant bounds every successful route by the admitted record count.


## A valid length can still contain a fault

Change a separate source copy to return 1 / 0. The graph has PUSH, PUSH, DIVIDE and RETURN, so the structural report is four to four. Execution fails at division and does not reach RETURN. This demonstrates why a fault may happen before the minimum successful-route length. The bound is neither a proof of arithmetic safety nor a replacement for checked arithmetic, execution tests or application-level validation.


## Use independent oracles in regression tests

An oracle is a way to decide an expected answer. Repeating the production reverse-walk algorithm in a test would risk repeating its mistake. The regression instead includes explicit expected diamonds and an independent forward route enumerator over small compiled examples. It also compares runtime step counts, checks exact fuel boundaries, exercises the largest admitted chain, refuses malformed graphs and round-trips wire artifacts. Compare named fields in result structures; native padding bytes are not part of their public semantic value.


## Reuse the service inside the Kernel

The Kernel's optional CVM native user program links the same runtime. Selectors 69 through 72 check the diamond, sufficient fuel, arithmetic failure despite a valid count, and refusal with unchanged output. The diagnostic runs both O0 and O2 builds, observes real user-mode exit, refuses terminal reentry and checks frame restoration. The normal console is a separate route through the process loader. A native link, a host test and a guest execution are distinct pieces of evidence.


## Troubleshoot without weakening the contract

1. If budget is unknown, confirm that you rebuilt the tool and are invoking that executable rather than an older PATH entry.
2. If source analysis succeeds but bytecode analysis fails, regenerate the artifact from the same source and inspect its identity; do not bypass decoder checks.
3. If a run fails despite the maximum fuel, read the status. Overflow or division by zero needs a source correction, not more fuel.
4. If a future language extension introduces loops, redesign and qualify the bound contract before admitting backward edges.
5. Keep the old inspect output stable for consumers that already parse it; use the dedicated budget commands for the new report.


## Exercises with explained answers

Change the condition from 1 to 0 in a separate copy. Predict that the structural report remains four to seven because the graph still has both edges, while actual execution now visits four instructions and returns 7. Then replace 40 + 2 with the literal 42. The true route loses two records: two PUSH plus ADD become one PUSH. Its path becomes five steps, and the structural range becomes four to five. Explain why neither experiment estimates elapsed time or proves compatibility with arbitrary C23 source.


[Previous: Parse initialized declaration lists without changing the virtual machine](90-parse-initialized-declaration-lists.md)

[Next: Show source errors without printing control bytes](92-show-source-errors-without-printing-control-bytes.md)
