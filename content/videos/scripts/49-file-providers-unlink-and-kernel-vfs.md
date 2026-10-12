# Episode 49 — File Providers, Safe Removal and Umicom Kernel

**Running time:** approximately 14–19 minutes  
**Companion chapters:** [144 — Notes provider](../../lessons/05-engineering/144-build-a-notes-filesystem-provider.md), [145 — Two providers](../../lessons/05-engineering/145-compose-two-filesystem-providers.md) and [146 — Kernel VFS](../../lessons/05-engineering/146-follow-the-umicom-kernel-vfs.md)  
**Demonstration:** `labs/native/vfs-provider-composition/`

## 00:00–02:10 — One application, two kinds of storage

**On screen:** Open the diagram `vfs-path-to-provider.svg`; highlight the
Notes and Library branches separately.

**Narration:**

"Our Notes application can already open a file through a virtual filesystem.
Now imagine that the same programme must display a course handout. The Notes
file is writable, but the course handout is deliberately read-only. We could
write separate open and read functions for each document type, but then every
application would have to know how each storage system works.

"Instead, both types of document use the same VFS interface. The VFS selects
the provider from the pathname. The provider decides whether it can fulfil
the requested operation. This makes the application simpler and allows us to
add more providers without copying the VFS implementation."

## 02:10–04:30 — A callback can be missing on purpose

**On screen:** Open `reference_provider.c` next to `ram_provider.c`.

**Narration:**

"Our RAM provider has functions for opening, reading, writing, removing a name
and releasing an open node. The reference provider exposes immutable documents.
Its callback table leaves both `write` and `unlink` as null pointers.

"That omission is intentional. A null callback means the operation is not
available. The VFS checks for this and returns `READ_ONLY`. It does not call
through a null function pointer. More importantly, it does not claim that
writes have succeeded when the provider has ignored them.

"A filesystem interface is a contract. Success means something happened that
the contract permits; refusal should not be hidden just to make the user
interface look successful."

**Demonstration:** Highlight `BtbReferenceProviderOperations()`, then
`BtbVfsOpen` checking the write callback. Show the test that opens
`/library/MISSION.TXT` for writing and expects `BTB_VFS_READ_ONLY`.

## 04:30–07:15 — Build the composed programme

**On screen:** A PowerShell window and the CMake project file.

**Narration:**

"CMake gives us a way to reuse the VFS library from the first laboratory.
Notice this line: `add_subdirectory` points to `vfs-descriptors`. The new
project builds the existing library rather than maintaining a different copy
of descriptor management. Our new source adds only a reference provider."

**Commands:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\vfs-provider-composition" `
  -B ".\output\learning-build\vfs-provider-composition" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\vfs-provider-composition" --parallel 2
ctest --test-dir ".\output\learning-build\vfs-provider-composition" --output-on-failure
& ".\output\learning-build\vfs-provider-composition\btb-vfs-provider-demo.exe"
```

**Narration:**

"The two tests should pass. The demonstration prints one line identifying the
C23, Assembly and Umicom Kernel course collection. The same `BtbVfsRead`
function retrieves those bytes as retrieved our editable Notes file."

## 07:15–10:10 — Removing a name without destroying a reader

**On screen:** Display `vfs-unlink-and-retained-node.svg`.

**Narration:**

"Imagine two windows showing a document. One window has already opened it.
The other removes the document's filename from the directory. Should the first
window immediately start reading some different file? No.

"A pathname is how we *find* a file; it is not necessarily the complete
lifetime of the file object. In our RAM provider, removing a name marks its
node unlinked. A new Open for that name fails, but the old open-file
description can still read the original bytes.

"We can even create a new file under the same name. New Open calls reach the
new object; older descriptions still refer to the old one. When the last
reference closes, the provider can scrub and reclaim the unlinked storage."

**Demonstration:** In `test_vfs.c`, walk through `BtbVfsUnlink`, the failed
new Open, creation of a replacement file and the two final closes.

## 10:10–12:45 — Recovery after a failed release

**On screen:** Show `test_composition.c`, `FlakyRelease()`.

**Narration:**

"Suppose the reference provider refuses a final release because cleanup has
not completed. If the VFS invalidated the handle anyway, the caller could lose
its last way to retry that cleanup. Our test deliberately makes the first
release fail. The VFS retains the descriptor and refuses to unmount the
provider. On the next attempt, the provider completes the release and the
mount can be removed.

"This is a general systems-programming rule: asking for cancellation is not
proof of completion, and asking for release is not proof that a resource has
been safely released. The software must keep enough ownership information to
retry or report the unfinished operation."

## 12:45–16:30 — Follow the real Umicom Kernel

**On screen:** Open public GitHub pages for `include/umicom/kernel/vfs.h`,
`kernel/vfs.c`, `kernel/ramfs.c` and `kernel/user_files.c`.

**Narration:**

"The lesson's VFS is a small C programme. Umicom Kernel has a separate,
real research implementation with much wider responsibilities. Its public VFS
contract describes file clients, descriptors, provider operations and
namespace rights. The RAMFS owns physical pages and node lifetimes. The
process-file service connects requests from a scheduled task to a trusted
Kernel-owned client and validates the user memory boundary.

"The code contains an important separation. A descriptor identifies a
client's open description. It does not give a programme an arbitrary pointer
into privileged Kernel memory. The process-file service checks the request
and stages it before operations that may allocate storage.

"The Kernel also has a FAT16 provider. We covered FAT16 image structures in
the previous course. The read-only provider can be connected to the same VFS
contract while retaining its own mount and block-device lifetimes.

"Studying those real source files shows the same architectural pattern that
we have practised today — one stable interface, independently owned providers
and explicit cleanup. The details are more demanding because the real Kernel
must protect privileged memory and hardware resources."

## 16:30–18:30 — Exercises and continuation

**On screen:** Show the five new chapters, the tests and the source directory.

**Narration:**

"For your first exercise, add one more reference document called
`SAFETY.TXT`. Its contents can explain why every operation checks its return
status. Extend the reference-provider table, rebuild and verify that a
read works but a write is refused.

"Next, change one test so that a provider's first release fails. Confirm that
the descriptor remains valid and that unmount returns `BUSY`. Only after an
explicit successful close should the mount disappear.

"Finally, open the Umicom Kernel VFS header and identify three differences
between it and the classroom model. Do not edit the Kernel as part of this
exercise. Our objective is to understand real engineering boundaries before
attempting production changes.

"The next course will follow the file-descriptor boundary into file services,
serialization and durable storage, and then on to sockets and native web
servers. Each step will reuse concepts we have already tested."

**End screen:**

- [Chapter 144 — RAM-backed Notes files](../../lessons/05-engineering/144-build-a-notes-filesystem-provider.md)
- [Chapter 145 — Compose independent providers](../../lessons/05-engineering/145-compose-two-filesystem-providers.md)
- [Chapter 146 — Umicom Kernel VFS](../../lessons/05-engineering/146-follow-the-umicom-kernel-vfs.md)
- [Provider laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/vfs-provider-composition)
- [Umicom Kernel source](https://github.com/umicom-foundation/umicom-kernel)
