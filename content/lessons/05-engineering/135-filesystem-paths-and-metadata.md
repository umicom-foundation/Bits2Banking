# 135. Filesystem paths, directories and checked changes

Our previous laboratory can recover the contents of one note, but it has no filenames. To grow into a complete Notes application, it must be able to distinguish `/notes/meeting.txt` from `/notes/budget.txt`, reject unauthorised changes and keep directory information consistent with stored bytes.

That is the job of a **filesystem namespace**, together with the filesystem's storage and metadata rules.

## 1. A name is not a storage address

Consider this path:

```text
/students/samira/notes/treasury.txt
```

A path has components. The system begins at a root namespace, finds the `students` directory, then `samira`, then `notes`, and finally the file named `treasury.txt`. Each component must have a defined interpretation; the filesystem cannot assume every byte string is a safe existing directory.

A path may name the same object through more than one entry when a filesystem supports links. A symbolic link can redirect resolution to another location. A directory rename can change a pathname without moving the file's data sectors.

These features are valuable, but a path resolver must check them carefully to avoid reading or writing outside the selected namespace.

## 2. Separate three kinds of authority

A caller can have access to an **open file description**, a particular **directory** and a set of **operations**. These authorities should not be conflated.

For example, being allowed to read a course note does not imply permission to delete the directory containing it. Having an open file descriptor does not mean the user can browse every path on the same device.

File descriptors also have lifetimes: one program might open a file twice, or duplicate one already-open description. The filesystem must decide whether the two descriptors share a current position and how close operations release references.

The [Umicom Kernel VFS source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c) separates path parsing from provider data operations. Its [RAM filesystem](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c) copies file data and retains open files after unlink until the last reference is released.

## 3. Validate a complete requested path first

Before creating a file, a small path resolver should check its complete input:

- Is the path absolute within the intended namespace?
- Are components empty, too long or repeated unnecessarily?
- Does any `..` step attempt to escape the authorised root?
- Do directory and file entries exist with the expected types?
- Does the caller have the required namespace and object permissions?
- Can the operation finish without exceeding directory or storage capacity?

Path-checking a string and then separately opening it by its original path may still permit a race if another actor changes the directory. Production systems often use directory-relative handles, open-at operations and retained authority so the object checked is the object used.

Our previous journal lab has no path handling. Its chosen sectors are constants in the program, not user-supplied pathnames. This is intentional: storage durability and namespace resolution are separate lessons.

## 4. Follow an example file update

Suppose the filesystem already has `/notes/ledger.txt` containing 100 bytes. The user appends 20 bytes.

A filesystem might need to change some or all of the following: data blocks, allocation records, file length, timestamps and directory metadata. A completed sector write does not prove that **all** of those records now describe one consistent file.

The exact safe update order depends on the filesystem. FAT16 allocation tables and directory entries have different dependencies from a copy-on-write tree-based filesystem. Using one generic order for every filesystem would be incorrect.

For a transaction-sensitive Notes application, the document service should also check that the file has not changed unexpectedly since it was opened. This is a **working-copy conflict check**, not a device durability check.

## 5. What does deletion mean?

Removing a directory entry is not necessarily the same as immediately erasing every byte previously stored for that file. Some filesystems can keep an unlinked file alive while it remains open. Other storage must wait for an explicit reclamation phase.

Likewise, a successful unlink is not secure erasure. Copies might exist in snapshots, caches, backups or unused flash storage. Security-sensitive deletion requires a separate, carefully qualified policy.

## 6. Walk through a real Kernel implementation

Read the header comments and examples in these sources:

1. [VFS namespace and descriptions](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c)
2. [RAM filesystem and owned page storage](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c)
3. [Process-owned file services](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md)
4. [FAT16 file lifecycle](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FAT16_FILE_LIFECYCLE.md)

The process-file guide is especially useful: a user program cannot safely pass a Kernel-internal pointer directly into the VFS. A checked system-call adapter validates user memory and derives the calling task's authority from the actual execution session.

## 7. Practice: design a Notes directory

Draw a directory tree that holds two students' study notes and a shared course handbook. Decide which folders each person may read, write or delete. Then answer:

- What happens if a student opens a file and the filename is later removed?
- Which layer should reject a request to read `../../private`?
- Which part needs a flush: the text buffers, the directory metadata, or possibly both?
- What additional records would be needed to recover a rename interrupted halfway through?

You do not need to write a filesystem driver yet. The purpose of this exercise is to establish the namespace and authority rules before adding storage mutation code.

## 8. Continue learning

The next chapter traces the actual Umicom Kernel stack from a checked user request to VFS, FAT16 and VirtIO. You will see which pieces are already implemented in the research kernel and which durability guarantees are deliberately not claimed.

[Next: Follow storage and filesystems through Umicom Kernel](../06-umicom/136-follow-kernel-filesystems-and-storage.md).
