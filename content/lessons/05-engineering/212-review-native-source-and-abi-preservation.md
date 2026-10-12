# Chapter 212 — Review C23 source and ABI preservation before Git commit

**Bits to Banking · Native engineering and Git review · Umicom Foundation**  
**Prerequisites:** [Chapter 205](205-review-index-and-working-tree-evidence.md), [Chapter 211](211-investigate-ci-without-replacing-code.md).

## A compiler cannot review an architectural contract for you

Umicom Framework is used by Studio, Trader, Bank and OS. A change to a public header may compile locally but break an older application or out-of-process plugin. A new parameter in a public C function, a changed structure size, a moved ownership boundary or a different error result can be a compatibility change even when the implementation remains valid C23.

The Framework design keeps a stable C ABI at module boundaries. It favours opaque handles, explicit capacities and ownership, documented failure behaviour and narrow service interfaces. The reviewer must check both **machine compatibility** and **semantic compatibility**. Git only tracks the text and history: it does not prove either property.

## Inspect the public surface before the implementation

When reviewing a native change, read the corresponding `include/umicom/...` public header, then the `src/...` implementation and affected tests. Ask who allocates and destroys each object, whether a returned pointer is borrowed or owned, what happens when a call fails, and which error states are contractual. In C23, failure-atomic updates are particularly important for finance and configuration data; a rejected input should not silently destroy a valid previous value.

For example, the Framework VCS observer exposes an opaque `UmiVcsWorkingTree`. Consumers borrow entries until the observation is destroyed. Replacing that API with a raw, mutable global array might simplify one GTK4 callback while breaking memory ownership and concurrency expectations. A correct refactor keeps the ABI and lifecycle documented and adjusts private implementation behind that contract.

## A repeatable review sequence

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git diff --name-status
git diff --cached --name-status
git diff --cached --check
git diff --cached -- include/umicom
git diff --cached -- src
```

Use the real paths present in the repository. Review complete affected files with Beyond Compare; small diffs alone may hide an unregistered callback, missing CMake target or duplicate service logic. Explicitly inspect any removed `#include`, symbol declaration, test registration, licence header, attribution or comments. Do not mechanically replace names, especially published identifiers or the established Master Controller / Slave Controller terminology.

## Source preservation versus dead code

Sometimes a previously active implementation must no longer execute. Under the project's preservation policy, retain it in a clearly documented disabled block (such as `#if 0` when appropriate), explain why it was superseded, and identify the tested replacement. This is not a blanket instruction to accumulate dead code indefinitely; it is an auditable migration safeguard until the project owner approves physical deletion. Preserve teaching examples and historical source independently of production compilation.

A Framework-owned capability should not also be reimplemented in Umicom OS or Bits2Banking. If native Git working-tree observation already exists in Framework, a new learning batch may teach its API or compose evidence from it, but should not create a second native Git parser. A documentation change must distinguish a **teaching-only model** from Framework's supported production implementation.

## ABI and application acceptance tests

A sound review strategy combines isolated CTest unit tests for the changed library, contract tests for its public header and independent integration tests from at least one consumer. For a GTK4 control, verify that users can still invoke the relevant menu, command or tooltip. For an OS startup change, a headless unit test does not replace a boot or application-start test. For a Data Server update, verify that the authoritative database boundary remains enforced and that consumer modules cannot bypass it.

## Exercise

A proposed pull request removes a five-line error recovery path from `src/...` because the developer believes it is redundant. Identify the contract it preserves, design a test that makes the error path execute, and explain where to retain the old logic pending review. Then inspect the staged diff for unintended changes to unrelated modules. The correct decision may be to refuse the patch until evidence is supplied.

## Questions

What is the difference between keeping a function's name and preserving its ABI? When does replacing an owned buffer with a borrowed pointer change a contract? Why can all tests pass after deleting a CMake source entry? Which repository should own a reusable C23 Git observer?

**Next:** [Chapter 213 — Build a release evidence model in C23](213-build-a-native-release-evidence-model.md).
