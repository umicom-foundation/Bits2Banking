# Episode 48 — How a Programme Opens a File

**Running time:** approximately 12–16 minutes  
**Companion chapters:** [142 — Virtual filesystems](../../lessons/05-engineering/142-how-a-virtual-filesystem-finds-a-file.md) and [143 — Descriptors](../../lessons/05-engineering/143-file-descriptors-open-descriptions-and-offsets.md)  
**Demonstration:** `labs/native/vfs-descriptors/`

## 00:00–01:40 — The question behind the Save button

**On screen:** A Notes window showing `PROJECT.TXT`. Draw an arrow from the
Open button to the pathname `/notes/PROJECT.TXT`.

**Narration:**

"When you open a document in a Notes application, you usually see a filename
and an Open button. But there is much more happening behind those two things.
The application needs to find the document, check whether it is allowed to
read it, decide which storage system owns it, and keep track of the reading
position. Later, the application will close that document and release the
resources it borrowed.

"A real operating system may support memory-backed files, disk files,
read-only installation resources and several filesystem formats. We do not
want every application to contain four different implementations of Open.
Instead, we provide a virtual filesystem — usually shortened to VFS. Today
we will build a small one in C23 and see how its parts fit together."

**Demonstration:** Show the site chapter and click its source-code link.

## 01:40–04:00 — Mounts and providers

**On screen:** Display `vfs-path-to-provider.svg`.

**Narration:**

"Start with the name `/notes/PROJECT.TXT`. The slash at the beginning tells
us the path is absolute. The first component, `notes`, identifies where a
filesystem provider is mounted. The final component names a file within that
provider. In our small experiment there are no deeper directories.

"The VFS checks that the path is well formed. It refuses attempts to jump
out of a mount using dot-dot segments. It also checks the mount boundary:
`/notes` must not accidentally match `/notes-old`. Once it finds the correct
mount, it asks that provider to open the named object.

"Now the important distinction: the VFS owns the lookup and the descriptor
lifetime. The provider owns the actual bytes. This lets us replace the
provider later without rewriting the application."

**Demonstration:** Open `vfs.h`; highlight `BtbVfsProviderOps` and read the
`open`, `read` and `release` signatures. Explain the `void *context` pointer
as the address of provider-owned storage.

## 04:00–06:15 — Build the demonstration

**On screen:** PowerShell in `C:\umicom\Umicom-Bits2Banking`.

**Narration:**

"We will build only the classroom VFS. We are not modifying Umicom Kernel or
Umicom Framework. CMake prepares the build instructions, Ninja runs the
compiler, and CTest runs the checks that exercise the code."

**Commands shown and executed one at a time:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\vfs-descriptors" `
  -B ".\output\learning-build\vfs-descriptors" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\vfs-descriptors" --parallel 2
ctest --test-dir ".\output\learning-build\vfs-descriptors" --output-on-failure
& ".\output\learning-build\vfs-descriptors\btb-vfs-demo.exe"
```

**Narration:**

"The expected programme output is `Mounted /notes: Umicom Studio (13 bytes)`.
The thirteen is a byte count. A file is a sequence of bytes; it does not need
to end with the zero byte used by ordinary C strings. This programme reserves
one extra byte before displaying the copied text."

## 06:15–09:20 — Two handles, one position

**On screen:** Display `vfs-descriptors-and-open-descriptions.svg`.

**Narration:**

"Opening a file returns a descriptor. In our C23 project, this descriptor is
a 64-bit token. It is not a pointer to the file's storage. Inside the VFS,
the token refers to a descriptor record, and that record refers to an
open-file description.

"The open-file description owns the current position. Think of a page marker
in a book. After reading two bytes from the five-byte file `ABCDE`, the
marker moves from zero to two. If we duplicate the descriptor, the new token
points at the same description. Reading two more bytes through the duplicate
returns `CD`; the original token will then read `E`.

"Opening the filename again would create a different open-file description.
Its position would start at zero. That difference is easy to miss, and it
matters whenever a programme uses more than one handle to the same data."

**Demonstration:** Locate the sequence of `BtbVfsRead` and `BtbVfsDuplicate`
calls in `test_vfs.c`. Predict the first three outputs before running CTest.

## 09:20–12:10 — Ownership, rights and closing

**On screen:** Source calls `BtbVfsDuplicate`, `BtbVfsClose`, followed by an
attempt to use an already-closed token.

**Narration:**

"A duplicate may receive narrower permissions, but it may not gain new
permissions. If we duplicate a read/write handle as read-only, the duplicate
cannot write. If another client tries to use that token, the VFS rejects it.

"Every descriptor also has a generation number. Closing it advances that
number, so an old token cannot unexpectedly point to a completely different
file when the VFS reuses the same internal slot.

"Finally, the provider's underlying file node must remain alive while any
open-file description depends on it. Closing one duplicate does not mean the
file is released. The VFS calls the provider's final release only when the
last reference closes. If that release fails, our test retains the handle so
cleanup can be retried deliberately."

**Demonstration:** Run the ownership CTest with `-V`. Show the successful
checks and briefly explain the status codes for wrong-client use and stale
handles.

## 12:10–15:00 — Your turn

**On screen:** Show the chapter exercise and full code files.

**Narration:**

"Change the filename in both the create and open operations. Does the
programme still display the same contents? Now change only the open path.
The programme should report a missing file; it should not quietly select
another object.

"For an additional challenge, open the same path twice rather than duplicating
a handle. Read two bytes through each. You should see that each independent
open-file description starts at position zero. This is the difference between
sharing a file *object* and sharing the same *open-file description*.

"The next episode will connect a writable Notes provider and a read-only
reference library to the same VFS. We will also see why removing a filename
does not have to destroy an open file."

**End screen:**

- [Chapter 142 — A pathname and its provider](../../lessons/05-engineering/142-how-a-virtual-filesystem-finds-a-file.md)
- [Chapter 143 — Descriptors and positions](../../lessons/05-engineering/143-file-descriptors-open-descriptions-and-offsets.md)
- [Source laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/vfs-descriptors)
- [Umicom Kernel VFS](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c)
