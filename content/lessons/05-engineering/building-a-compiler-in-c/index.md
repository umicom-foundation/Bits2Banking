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


## Use a Small Language in Studio

Build an arithmetic starter, trace its Framework recipe, select the preview profile, observe incremental checks, exercise negative cases and plan language extensions.

1. [Open an arithmetic project in Studio](17-open-an-arithmetic-project-in-studio.md)
1. [Follow a Framework project recipe](18-follow-a-framework-project-recipe.md)
1. [Select the preview build profile](19-select-the-preview-build-profile.md)
1. [Check only affected preview inputs](20-check-only-affected-preview-inputs.md)
1. [Test language failures through the tool](21-test-language-failures-through-the-tool.md)
1. [Separate editor support from language semantics](22-separate-editor-support-from-language-semantics.md)


## Inspect and Embed a Small Compiler

Inspect resource requirements without executing a program, trace stack behavior, distinguish structural checks from arithmetic checks, embed the shared library and design precise boundary tests.

1. [Inspect a program before running it](23-inspect-a-program-before-running-it.md)
1. [Trace the evaluation stack with a table](24-trace-the-stack-with-a-table.md)
1. [Distinguish structure from arithmetic safety](25-distinguish-structure-from-arithmetic-safety.md)
1. [Count execution budgets and encoded bytes](26-count-execution-budgets-and-wire-bytes.md)
1. [Embed the inspector in a C application](27-embed-the-inspector-in-a-c-application.md)
1. [Preserve output when inspection fails](28-preserve-output-when-inspection-fails.md)
1. [Design boundary tests for a virtual machine](29-design-boundary-tests-for-a-virtual-machine.md)
1. [Present program facts in an IDE](30-present-program-facts-in-an-ide.md)

## Compile and qualify logical negation

- [Recognise prefix negation without changing not-equal](47-recognise-prefix-negation.md)
- [Lower logical negation without a new opcode](48-lower-negation-to-existing-operations.md)
- [Observe operand failure before negation](49-observe-negation-failures-and-budgets.md)
- [Qualify negation through source and bytecode commands](50-qualify-negation-through-the-cli.md)

## Linked compiler and runtime profiles

- [Query the linked compiler and runtime](51-query-the-linked-compiler-and-runtime.md)
- [Prove capability declarations with real operations](52-prove-capabilities-with-real-operations.md)

## Native linkage and trustworthy test fixtures

- [Give private C helpers a linker namespace](53-give-private-helpers-a-linker-namespace.md)
- [Check the bytes of a C test fixture](54-check-the-bytes-of-a-c-test-fixture.md)
- [Keep regression observations type correct](55-keep-regression-observations-type-correct.md)

## Bounded integer spellings and evidence

- [Read hexadecimal and binary source without overflowing](56-read-hexadecimal-and-binary-source.md)
- [Separate source spelling from wire format](57-separate-source-spelling-from-wire-format.md)
- [Test source spans without a terminator](58-test-source-spans-without-a-terminator.md)

## Execution and supervision budgets

- [Separate instruction fuel from wall-clock time](59-separate-instruction-fuel-from-wall-clock-time.md)

## Configuration input observation

- [Record configuration inputs with honest limits](60-record-configuration-inputs-with-honest-limits.md)
- [Refuse stale input records without repairing them](61-refuse-stale-input-records-without-repairing-them.md)
- [Keep template-looking text as data](62-keep-template-looking-text-as-data.md)

## Native operation comparison and exit contracts

- [Compare operations without running programs](63-compare-operations-without-running-programs.md)
- [Handle comparison exits without hiding errors](64-handle-comparison-exits-without-hiding-errors.md)

## Buffered report failures

- [Test buffered report failures](65-test-buffered-report-failures.md)

## Bounded local integers

- [Bind local names to integer slots](66-bind-local-names-to-slots.md)
- [Prove local initialization before execution](67-prove-local-initialization-before-execution.md)

## Short-circuit control flow

- [Lower short-circuit logical expressions](68-lower-short-circuit-logical-expressions.md)
- [Validate joins on all forward paths](69-validate-joins-on-all-forward-paths.md)
- [Compare logical programs with native C](70-compare-logical-programs-with-native-c.md)

## Conditional values and parser recursion

- [Select values with conditional expressions](71-select-values-with-conditional-expressions.md)
- [Bound recursive expression parsing](72-bound-recursive-expression-parsing.md)

## Checked compound assignments

- [Lower checked compound assignments](73-lower-checked-compound-assignments.md)

## Braced conditional statements

- [Lower braced conditional statements](74-lower-braced-conditional-statements.md)

## Ordered else-if chains

- [Lower ordered else-if chains](75-lower-ordered-else-if-chains.md)

## Checked signed remainder

- [Add checked signed remainder without breaking bytecode](76-add-checked-signed-remainder.md)

## Signed unary complement

- [Lower signed bitwise complement through checked arithmetic](77-lower-signed-bitwise-complement.md)
- [Add binary bitwise operators and preserve bytecode compatibility](78-add-binary-bitwise-operators.md)

## Bounded execution and shared consumers

- [Run bytecode in bounded slices](79-run-bytecode-in-bounded-slices.md)
- [Preserve progress when a slice fails](80-preserve-progress-when-a-slice-fails.md)
- [Share slices with Framework and OS](81-share-slices-with-framework-and-os.md)

1. [Give branch locals a lexical scope without changing the VM](82-give-branch-locals-a-lexical-scope.md)

1. [Parse standalone blocks with one scope owner](83-parse-standalone-blocks-with-one-scope-owner.md)

1. [Report source warnings without running a program](84-report-source-warnings-without-running-a-program.md)

1. [Check document snapshots before building](85-check-document-snapshots-before-building.md)

1. [Check bit shifts before publishing a result](86-check-bit-shifts-before-publishing-a-result.md)

1. [Inspect managed memory without collecting](87-inspect-managed-memory-without-collecting.md)

1. [Parse an empty statement without emitting code](88-parse-an-empty-statement-without-emitting-code.md)

1. [Decode ASCII character constants at the lexer](89-decode-ascii-character-constants-at-the-lexer.md)

1. [Parse initialized declaration lists without changing the virtual machine](90-parse-initialized-declaration-lists.md)

1. [Count structural paths before running bytecode](91-count-structural-paths-before-running-bytecode.md)

1. [Show source errors without printing control bytes](92-show-source-errors-without-printing-control-bytes.md)

1. [Lower Boolean words without changing the VM](93-lower-boolean-words-without-changing-the-vm.md)

1. [Supply a signed input in a browser worker](94-supply-a-signed-browser-input.md)

1. [Pause before a reached source line](95-pause-before-a-reached-line.md)
1. [Read versioned interpreter reports](96-read-versioned-interpreter-reports.md)
1. [Check a constant before running C](97-check-a-constant-before-running.md)

1. [Name values before the entry](98-name-values-before-the-entry.md)

1. [Count bytes from an admitted type](99-count-bytes-from-an-admitted-type.md)

1. [Align the fields in a record](100-align-record-fields.md)
1. [Read adjacent assertion messages](101-read-adjacent-assertion-messages.md)
1. [Require a complete debugger command](102-require-a-complete-debugger-command.md)
1. [Translate whitespace that both languages admit](103-translate-whitespace-that-both-languages-admit.md)
1. [Keep the exact filename on Windows](104-keep-the-exact-filename-on-windows.md)
1. [Translate hexadecimal and binary](105-translate-hexadecimal-and-binary.md)
1. [Translate a checked local update](106-translate-a-checked-local-update.md)
1. [Count reached source statements](107-count-reached-source-statements.md)
1. [Translate one return between C and D](108-translate-one-return-between-c-and-d.md)
1. [Translate an initialized local between C and D](109-translate-an-initialized-local-between-c-and-d.md)
1. [Inspect paused integer slots](110-inspect-paused-integer-slots.md)
1. [Translate checked shifts between C and D](111-translate-checked-shifts-between-c-and-d.md)
1. [Translate grouped integer literals between C and D](112-translate-grouped-integer-literals-between-c-and-d.md)
1. [Compare signed integers between C and D](113-compare-signed-integers-between-c-and-d.md)
1. [Watch one integer slot](114-watch-one-integer-slot.md)
