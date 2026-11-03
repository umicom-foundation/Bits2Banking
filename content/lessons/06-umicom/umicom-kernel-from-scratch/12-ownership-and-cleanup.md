# Keep results separate from the memory they describe

A function can calculate the right number and still damage a file if it writes that number into the wrong place. Follow the Kernel's real memory-backed filesystem to see why result storage has its own rules.

## 1. Name the parts before reading the code

**RAM** is the working memory used while a computer is running. A **filesystem** gives names to files and remembers where their bytes live. Umicom's RAM filesystem, called RAMFS, keeps those bytes in memory. It is useful for the console's temporary files; the contents disappear when that guest stops.

A **page** is a fixed-size block of memory. This Kernel uses 4,096-byte pages. A **node** is the filesystem's record for a file or directory. It stores facts such as the file length and the addresses of its pages. The **owner** is the structure that keeps track of all those records and their lifetimes.

A **snapshot** is a set of measurements copied out at one point during a serialized call. Here it counts nodes, pages and active references. It is not a saved copy of every file and cannot restore a deleted file.

 <svg viewbox="0 0 700 110" role="img" aria-label="The filesystem keeps its own metadata and file pages; a checked snapshot copies counts to separate caller-owned storage." style="width:100%;max-width:700px"><title>The filesystem keeps its own metadata and file pages; a checked snapshot copies counts to separate caller-owned storage.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Filesystem owner</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Checked snapshot</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Separate result</text></svg>

The filesystem keeps its own metadata and file pages; a checked snapshot copies counts to separate caller-owned storage.

## 2. An address is a location, not permission

In C, a pointer holds the address of storage. The expression `&info` means “the address of the variable named info.” It lets another function write a result there. It does not create extra storage or establish ownership by itself.

```text
UmicomKernelRamfsInfo info = {0};
UmicomKernelVfsStatus status =
    UmicomKernelRamfsSnapshot(&filesystem, &info);
if (status == UMICOM_VFS_OK) {
    /* Use info.nodes and info.dataPages here. */
}
```

This excerpt belongs inside Kernel code with an already initialized, valid `filesystem`. The type `UmicomKernelRamfsInfo` describes the result's fields. `{0}` initializes them. `UMICOM_VFS_OK` is the success result; the caller must inspect it before using the new measurements. This is not a complete standalone program.

Two pointers **alias** when the storage they refer to overlaps. If the result points into the owner's own record, writing a count may overwrite an address needed to find a file. If it points into a file's data page, writing a count changes that file. A pointer being non-null is not enough to prevent either mistake.

## 3. Work through the boundary check

1. Check that the owner and result pointers are non-null and suitably aligned. **Alignment** means the address starts at a boundary required by that type.
2. Check that the complete address range fits. Adding a result's size must not wrap around the largest address.
3. Reject a result that overlaps any part of the owner.
4. Validate the filesystem's own records under its execution rules.
5. Reject overlap with every owned metadata page and every file-data page, including unused bytes at a page's end.
6. Only then calculate and publish the snapshot.

Read [`kernel/ramfs_snapshot.inc`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs_snapshot.inc). `UmicomRamfsOutputAdmission` implements the shared checks. “Admission” means deciding whether an operation may start. The checks are for trusted Kernel storage; they do not prove that an arbitrary number is a readable address or replace the user-memory copying interface.

## 4. Why check the whole page?

Imagine a file containing 4,200 bytes. The first page holds bytes 0 through 4,095. The second page holds the remaining 104 bytes, plus 3,992 unused bytes. Those unused bytes still belong to the filesystem. A later append may use them. They are not a safe place for an unrelated result.

| Memory | Visible file bytes | Ownership |
| --- | --- | --- |
| First page | 4,096 | The filesystem owns all 4,096 bytes. |
| Second page | 104 | The filesystem also owns this whole page. |
| Separate result variable | None | The caller supplies independent storage. |

## 5. Deleting a name and freeing memory are different

**Unlinking** removes a file's name from its directory. Another part of the system might still have the file open. A **pin** is a counted reference that keeps the underlying node alive while it is being used. Reclamation, called `Reap` in the API, frees only nodes that have no directory link and no pins.

1. Create a file and open it: it has a name and an active reference.
2. Remove its name: an existing open handle can still keep it alive.
3. Close the final handle: the node can now be reclaimed.
4. Reap the eligible node: release its data pages, then its metadata record.

Read [`UmicomKernelRamfsReap`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c). Its result counter also uses the shared admission check. Even a small counter must not overwrite the owner or a page that the operation is about to release.

## 6. Distinguish refusal from partial progress

An invalid output location is refused before the result is changed or any page is released. A later release failure is different: some work may already be complete. If the first page is released and the second is refused, the remaining page stays owned. The node is not yet counted as reclaimed. A later call retries the remaining work.

A snapshot has another contract: it stages all totals in a temporary local structure and publishes them only after all checks succeed. It also checks addition before accumulating pin counts. A sum that would exceed the largest representable number returns an error instead of wrapping to a small count.

## 7. Study the regression as an experiment

Open [snapshot tests](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/ramfs/snapshot_tests.c) and [cleanup tests](https://github.com/umicom-foundation/umicom-kernel/blob/main/tests/ramfs/reap_tests.c). Each uses the real RAMFS and allocator in an isolated memory arena. The test creates a 4,200-byte file, deliberately supplies an overlapping result, and expects refusal. It compares the owner and complete backing arena with copies made before the call, then reads the file again.

These tests deliberately create invalid pointer relationships to check refusal. Do not copy those relationships into application code. The [Kernel ownership guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/RAMFS_RESULT_OWNERSHIP.md) gives focused build and test commands and explains which parts are modeled.

## Try explaining the result

A file has been unlinked but still has one open handle. Reap is called with a valid independent counter. How many nodes should it reclaim?

<details>

<summary>Reason through the answer</summary>

Zero for that file. The remaining handle pins its node. Losing the filename does not end the open handle's ownership. After the final handle closes, a later Reap call can reclaim it.

</details>

A second exercise: why is a result in unused page padding still unsafe? Explain it using a future append, rather than assuming that unused bytes are unowned.

Return to [Learning C](../../../courses/learning-c/index.html) for pointers, structures, bounds and return values. Continue reading the Kernel through its [wiki](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/wiki/index.md).

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/12-ownership-and-cleanup.html) · [Learning sequence](../../../start/learning-sequence.md)
