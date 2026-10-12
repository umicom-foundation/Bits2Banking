# Build a Virtual Filesystem in C23

The programme demonstrates a small virtual filesystem (VFS). A VFS takes a
path such as `/notes/PROJECT.TXT`, selects a mounted provider and returns a
**descriptor token**. The token belongs to one simulated client. Multiple
descriptors may share one **open-file description** and therefore one current
reading position.

The laboratory uses two C23 implementations: `vfs.c` owns path dispatch and
descriptor lifetimes; `ram_provider.c` owns the Notes bytes. Neither knows the
other's internal storage. The next laboratory links the same VFS library with
an independent, read-only provider.

## Build on Windows using MSYS2 UCRT64

Open PowerShell:

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

The expected result is **3/3 tests passed**. Run the programme:

```powershell
& ".\output\learning-build\vfs-descriptors\btb-vfs-demo.exe"
```

The programme prints `Mounted /notes: Umicom Studio (13 bytes)`.

## Explore the source

Read `vfs.h` first. Identify the opaque *meaning* of a 64-bit descriptor token,
then locate `BtbVfsOpen`, `BtbVfsDuplicate`, `BtbVfsRead` and `BtbVfsClose`.
Next inspect `ram_provider.c`: it owns file contents and counts references to
nodes. When a file is unlinked while open, the pathname becomes unavailable,
but the existing open description continues to hold its data.

Try modifying `main.c` to open the file for both reading and writing, then
write an additional word. Remember that the open-file position moves after a
successful read. Write to a new file using a new open operation if you want
the initial position to be zero.

## Design limits

- One-level paths only: `/mount/FILE.TXT`. No traversal or real directories.
- Four mounts, eight open-file descriptions and twelve descriptor tokens.
- Eight Notes files, each up to 256 bytes in the RAM provider.
- Caller-owned memory with no background threads or kernel mode.
- The client number is supplied by the test harness. A real kernel must derive
  a process identity from its scheduler/execution context.
- Namespace deletion is checked separately from descriptor read/write rights.
- The model is not a filesystem driver, a POSIX implementation or durable storage.

Relevant authoritative source:
[Umicom Kernel VFS](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c).
