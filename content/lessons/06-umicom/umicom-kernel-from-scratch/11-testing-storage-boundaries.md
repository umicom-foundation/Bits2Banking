# Test storage boundaries without changing a disk

Use the Kernel's real parser with a controlled byte reader to distinguish a complete answer from an unfinished observation.

## 1. What does a test control?

A **test fixture** supplies repeatable starting conditions. In [`tests/fat16_space/space_tests.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/fat16_space/space_tests.c), the fixture is an original synthetic disk image loaded into process memory. A test changes those memory bytes to describe a particular situation. It does not modify a physical disk.

The production parser is the same C implementation used in the Kernel. Only the sector reader is supplied by the host test. A **host test** runs as a normal program on your development computer. A **guest test** runs inside the emulated RISC-V machine. Passing one does not automatically prove the other.

 <svg viewbox="0 0 700 110" role="img" aria-label="The fixture supplies bytes; the parser computes; the test checks the result." style="width:100%;max-width:700px"><title>The fixture supplies bytes; the parser computes; the test checks the result.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Known image bytes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Real Kernel parser</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Independent checks</text></svg>

The fixture supplies bytes; the parser computes; the test checks the result.

## 2. Why a partial answer is dangerous

Imagine counting a book's pages but stopping halfway because the remaining pages are missing. Reporting the number already seen as the total would mislead the reader. Storage counting has the same problem. If read 60 fails, the counts from reads 1 to 59 are not a complete volume result.

The implementation accumulates counts in a local variable called `staged`. **Local** means the variable belongs to that function call. On success, it copies the complete value to the caller. On failure, it leaves the caller's result alone and returns an error code.

```text
/* Trace of the actual publication rule, expressed as pseudocode. */
prepare local counters
for every table sector:
    read both copies
    if either read fails: return an error without publishing
    if copies disagree: return an error without publishing
    classify usable entries
publish complete counters
return success
```

This rule concerns the result structure. It does not say that a device write is atomic, and this query performs no writes.

## 3. Follow the sentinel test

A **sentinel** is a recognizable starting value. Find `SpaceSentinel`. It fills the result with byte value `0xa5`, keeps a copy, calls the parser and compares every result byte after a refusal. The comparison also checks padding: bytes that a C compiler may place between fields for alignment.

Find `all_read_failures`. The fixture has 48 sectors in each table, so a complete scan needs 96 sector reads. The test fails read 1, then read 2, and continues through read 96. For each refusal, the result must remain unchanged and the owner must leave its busy state. It then removes the injected failure and checks that a new scan succeeds.

## 4. Check the boundary, not only the usual case

- `last_cluster` checks the final usable entry, where an off-by-one mistake can lose capacity.
- `padding_ignored` places a value after the last usable cluster. Matching padding is compared but not counted as storage.
- `padding_mirror` changes one copy's last byte. Even though that byte is padding, the complete table comparison must notice the mismatch.
- `callback_reentry` asks for a second scan and a close while a read is in progress. Both must refuse as busy without changing the nested result.
- `guard.overlap` attempts to place the output inside the inspector itself. The API rejects this rather than overwrite its own ownership state.

## 5. Distinguish a count from an integrity proof

An **orphan** is an allocated cluster with no file referring to it. A **cycle** is a chain that eventually points back to a cluster already visited. The tests named `orphan_not_ownership` and `cycle_not_ownership` deliberately show that a count can still be produced. This API counts entry categories; it does not walk the directory graph.

In contrast, the Kernel's mutation planner requires stronger ownership checks before any separate writer can act. Read `UmicomFatPlanNamespace` and `UmicomFatPlanAllocation` in [`fat16_inspector.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_inspector.c). Different operations need different evidence. Do not turn a display statistic into permission to repair or write.

## 6. Follow device cleanup

The [transport tests](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/fat16_space/transport_tests.c) also use the real block driver with a controlled register model. They require every request to be a read and compare the complete synthetic image afterward.

A **lease** here is the live device ownership held by the command. The command must release it successfully before emitting `disk.space.` result lines. If a device reset fails, it retains the handle for a later cleanup attempt and emits an error instead. Losing a handle would not make outstanding device work safe.

## 7. Run the focused checks when your environment is ready

The [Kernel allocation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_SPACE_GUIDE.md) gives exact configure, build and test commands. Configuration creates build rules. Building creates the executable. Testing runs it and compares results. Stop at a failed stage so an older executable is not mistaken for the new one.

## Exercise and explanation

A scan finds free entries in its first 47 table sectors. The last sector of the second copy cannot be read. Should it return the partial free-byte total?

<details>

<summary>Show the reasoning</summary>

No. The scan has not compared all declared sectors, and the unknown part may contain allocated entries or disagreement. Return an error, preserve the caller's result, release the scan's busy ownership and keep the evidence for investigation.

</details>

Connect this to [Learning C](../../../courses/learning-c/index.html): pointers name storage, structures group results and return values tell callers whether a result is valid.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/11-testing-storage-boundaries.html) · [Learning sequence](../../../start/learning-sequence.md)
