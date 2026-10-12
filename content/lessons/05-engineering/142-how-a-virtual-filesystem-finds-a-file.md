# 142. How a Virtual Filesystem Finds a File

When you choose **Open** in a Notes application, you expect to find the right
document. You should not need to know whether the document is stored in RAM,
on a disk or in a read-only collection of teaching materials. A **virtual
filesystem (VFS)** gives applications a consistent way to request a file while
the operating system decides which storage implementation should respond.

In this chapter, we will build the first part of a VFS in C23. The application
will open `/notes/PROJECT.TXT`, read the text `Umicom Studio`, and close the
file. The same interface will later open a reference document belonging to a
different provider.

![A path is resolved to a mounted filesystem provider](../../assets/diagrams/vfs-path-to-provider.svg)

## 1. Follow the path

A **path** identifies a name within a filesystem. In our small laboratory,
`/notes/PROJECT.TXT` has three important parts: the leading `/` marks an
absolute path; `notes` selects a mount; `PROJECT.TXT` is the filename within
that mount. There are no subdirectories in this first model.

A **mount** connects a location in the VFS namespace to a provider. Consider:

| Mount | Provider | Example |
| --- | --- | --- |
| `/notes` | Writable in-memory Notes | `/notes/PROJECT.TXT` |
| `/library` | Read-only reference documents | `/library/COURSES.TXT` |

The VFS does not read file bytes itself. After validating the path, it calls a
provider's operations. This separation is important: changes to storage format
do not require every application to learn a different file API.

## 2. Understand the three owners

Our implementation has three distinct objects. The **VFS** owns the mount
records, descriptor tokens and open-file positions. The **provider** owns the
file's bytes and its own node identifiers. The **application** owns the buffer
into which it asks the VFS to copy data.

A provider supplies callbacks for `open`, `read`, optional `write`, optional
`unlink` and `release`. The VFS stores those functions in a
`BtbVfsProviderOps` structure, defined in the [VFS public header](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/vfs-descriptors/vfs.h).
The provider is selected once during `Open`; later reads use the retained
open-file description rather than searching the pathname again.

## 3. Build the example

Use PowerShell on Windows. The following commands configure a small CMake
project. CMake describes *what* to build; Ninja executes the compiler and
linker actions.

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
```

After a successful build, run:

```powershell
& ".\output\learning-build\vfs-descriptors\btb-vfs-demo.exe"
```

Expected result:

```text
Mounted /notes: Umicom Studio (13 bytes)
```

If the configuration fails, check the compiler path. If compilation fails,
read the first compiler diagnostic before changing anything. A successful
build is not the same as a successful test: the `ctest` step checks behaviour.

## 4. Read the C23 code

In [the complete example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/vfs-descriptors/main.c),
we begin with storage whose lifetime extends across the entire demonstration:

```c
BtbVfs vfs = {0};
BtbRamProvider notes = {0};
BtbVfsHandle handle = 0U;

BtbVfsInitialise(&vfs);
BtbRamFileCreate(&notes, "PROJECT.TXT", "Umicom Studio", 13U);
BtbVfsMount(&vfs, "/notes", 101U, BtbRamProviderOperations(), &notes);
```

`&vfs` means **the address of the `vfs` object**. The C functions receive this
address so they can operate on that object without copying all of its records.
The two `{0}` initialisers fill the storage with zero values before use.

The function `BtbVfsMount` registers the mount prefix and callbacks. The value
`101U` is the test's fictional namespace-owner identity. An actual kernel
must derive a process identity from a trusted execution context; it must not
trust an identity supplied by an untrusted application.

Next, the application calls:

```c
BtbVfsOpen(&vfs, 101U, "/notes/PROJECT.TXT", BTB_VFS_READ, &handle);
```

On success, `handle` contains an opaque *token*. Its numerical value is not a
RAM address. The application uses that token for reads and then closes it.
Always inspect the return status in application code. The complete programme
does so before using the handle; the excerpt above isolates each operation for
explanation.

## 5. A missing file is different from a bad path

The VFS refuses `notes/PROJECT.TXT` because it is not absolute. It refuses
`/notes/../SECRET.TXT` because the laboratory does not support traversal.
It returns **not found** for `/library/PROJECT.TXT` when there is no such
registered file. Treat these as different outcomes: an invalid request may need
a code correction, while a missing file may simply need a different name.

It also checks a complete path boundary. `/notes` must not accidentally match
`/notes-old`. A naïve prefix comparison could expose a different provider.

## 6. Try the next change

Open `labs/native/vfs-descriptors/main.c`. Change `PROJECT.TXT` to
`PLAN.TXT` in both the file-creation and open calls. Rebuild and run.
The output should remain the same because the filename has changed but its
contents have not. Then change only the `Open` path back to `PROJECT.TXT`.
The programme should report a failure rather than silently choosing another
file.

The next chapter explains why a successful `Open` creates a *descriptor* and
how its reading position changes over time.

**Further reading:** [Umicom Kernel VFS source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c).
