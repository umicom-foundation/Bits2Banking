<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/69-validate-joins-on-all-forward-paths.md

PURPOSE:
Validate joins on all forward paths

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Validate joins on all forward paths

## Goal

Explain why validating each instruction alone is insufficient after introducing branches. A join is an instruction reached by more than one incoming edge. The runtime must prove that either path leaves a compatible state there.

## Read a diamond

Consider these records from the independent runtime fixture:

| Index | Operation | Operand |
| --- | --- | --- |
| 0 | PUSH | condition |
| 1 | JUMP_IF_ZERO | 5 |
| 2 | PUSH | 41 |
| 3 | STORE_LOCAL | 31 |
| 4 | JUMP | 7 |
| 5 | PUSH | 42 |
| 6 | STORE_LOCAL | 31 |
| 7 | LOAD_LOCAL | 31 |
| 8 | RETURN | 0 |

Both arms arrive at record 7 with an empty operand stack and initialized slot 31. The load is safe regardless of the condition. Change the store at record 3 to slot 30: one arm no longer initializes slot 31, so the whole program must be refused before execution, even when the condition selects the other arm.

## Merge facts conservatively

The first incoming edge establishes the target's stack depth and initialized-local bits. Every later edge must have the same depth. Intersect its initialization set with the recorded set. Intersection means a bit survives only if every incoming edge carries it; union would incorrectly accept a local initialized on just one arm.

Read merge_state and inspect_program in src/vm.c. Targets must be greater than the source index and smaller than count. Consequently, processing records in index order visits every predecessor before its target. No work queue, heap allocation or fixed-point iteration is needed for this forward-only graph. Backward edges are rejected rather than treated as a supported loop.

## Check the complete graph

Both edges of a conditional branch are structurally reachable even for a constant condition. The validator does not execute arithmetic or perform constant propagation. An unconditional jump that leaves hidden, unreachable records is refused. RETURN must remain the final record with exactly one stack value.

Inspection counts every admitted record, including alternative arms. Its instruction count is a sufficient fuel upper bound. A chosen path can need less. The maximum stack is calculated over all admitted paths, so callers can reason about storage without guessing the runtime condition.

## Run independent tests

~~~powershell
ctest --test-dir .\build\windows-ucrt64-debug -R "umicom[.]c[.]logical[.]forward_branches" --output-on-failure --no-tests=error
~~~

The target links UmicomC::Runtime without the compiler. It checks both arms, inconsistent stack depths, one-arm initialization, backward and out-of-range targets, hidden records, trace gaps and literal format-4 bytes. This separation catches cases that a well-behaved compiler would never generate.

## Exercise and recovery

Draw the two incoming states at record 7 after replacing STORE_LOCAL at record 3 with NEGATE. Explain the stack-depth mismatch. Then restore the store and replace its slot index with 32. The latter must fail before shifting a bit or indexing local storage. Keep result objects and trace bytes unchanged after admission failure; zero written rows is the observable contract.

A valid graph can still divide by zero on its selected path. Admission proves structure and bounded access, not the usefulness of a program or authorization to run it.

[Course contents](index.md) · [Previous lesson](68-lower-short-circuit-logical-expressions.md) · [Next lesson](70-compare-logical-programs-with-native-c.md)
