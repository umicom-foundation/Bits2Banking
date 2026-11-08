# Building a Compiler in C

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Source, tokens and execution

Read text into tokens, define expression order and execute checked instructions.

1. [From source text to a result](01-source-and-execution.md)
1. [Read one token at a time](02-reading-tokens.md)
1. [Give expressions an unambiguous meaning](03-expression-order.md)
1. [Execute instructions with checked arithmetic](04-checked-execution.md)
1. [Store a program as portable bytes](05-portable-bytecode.md)
1. [Explain failures and test the boundaries](06-errors-and-tests.md)

## Optional native-system study

Connect an interpreter to a Kernel programme and understand the firmware boundary.

1. [Run the interpreter as a native Kernel program](07-a-native-kernel-program.md)
1. [Understand architectures, firmware and boot media](08-architectures-and-boot-media.md)

## Design a small language

Specify syntax and failures before observing bytecode and execution budgets.

1. [Design a small programming language in C](09-designing-a-language.md)
1. [Read past a comment without crossing the input](10-read-past-a-comment-safely.md)
1. [Project: specify and run a small language](11-project-a-small-language.md)
1. [Project: inspect bytecode and bound execution](12-project-bytecode-and-execution-budget.md)

## Project: an instruction viewer

Display instructions, admit literals, check stack shape and publish a bounded execution result.

1. [Build an instruction viewer](13-build-an-instruction-viewer.md)
1. [Admit decimal literals without overflow](14-admit-decimal-literals-without-overflow.md)
1. [Validate stack shape before execution](15-validate-stack-shape-before-execution.md)
1. [Budget execution and publish results](16-budget-execution-and-publish-results.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Building a Compiler in C

Follow the reading order below. Each lesson gives its own setup recap and links to supporting material. Later lessons use the ideas introduced earlier; return to the named prerequisite when a term is unfamiliar.

## Reading order

1. [From source text to a result](01-source-and-execution.md)
2. [Read one token at a time](02-reading-tokens.md)
3. [Give expressions an unambiguous meaning](03-expression-order.md)
4. [Execute instructions with checked arithmetic](04-checked-execution.md)
5. [Store a program as portable bytes](05-portable-bytecode.md)
6. [Explain failures and test the boundaries](06-errors-and-tests.md)
7. [Run the interpreter as a native Kernel program](07-a-native-kernel-program.md)
8. [Understand architectures, firmware and boot media](08-architectures-and-boot-media.md)
9. [Design a small programming language in C](09-designing-a-language.md)
10. [Read past a comment without crossing the input](10-read-past-a-comment-safely.md)

[Open the illustrated course](../../../courses/building-a-compiler-in-c/index.html).

## Continue with a programming-language project

11. [Project: specify and run a small language](11-project-a-small-language.md)
12. [Project: inspect bytecode and bound execution](12-project-bytecode-and-execution-budget.md)

- [Build an instruction viewer](13-build-an-instruction-viewer.md)

- [Admit decimal literals without overflow](14-admit-decimal-literals-without-overflow.md)

- [Validate stack shape before execution](15-validate-stack-shape-before-execution.md)

- [Budget execution and publish results](16-budget-execution-and-publish-results.md)

</details>

## Observe bounded execution across consumers

31. [Observe an execution trace](31-observe-an-execution-trace.md)
32. [Read successful and failed stack states](32-read-success-and-failure-states.md)
33. [Reserve trace storage before execution](33-reserve-trace-storage-before-execution.md)
34. [Count the rejected fuel step](34-count-the-rejected-fuel-step.md)
35. [Compare source and bytecode traces](35-compare-source-and-bytecode-traces.md)
36. [Present a fresh Framework trace](36-present-a-fresh-framework-trace.md)
37. [Qualify a freestanding trace](37-qualify-a-freestanding-trace.md)
38. [Record layered trace evidence](38-record-layered-trace-evidence.md)

## Extend integer expressions with comparisons

Follow a bounded language extension from token recognition and precedence to canonical wire profiles, Framework preview and Kernel consumer evidence.

- [Recognise comparison tokens without reading past the source](39-recognise-comparison-tokens.md)
- [Layer arithmetic, relational and equality precedence](40-layer-comparison-precedence.md)
- [Compare signed values without subtracting them](41-compare-signed-values-safely.md)
- [Observe operand failures before a comparison](42-evaluate-comparison-operands.md)
- [Version comparison bytecode without changing old artifacts](43-version-comparison-bytecode.md)
- [Qualify comparison commands through the real CLI](44-qualify-comparison-cli-workflows.md)
- [Reuse comparisons through Framework preview state](45-reuse-comparisons-in-framework.md)
- [Qualify comparison execution in a Kernel guest](46-qualify-comparisons-in-a-kernel-guest.md)
