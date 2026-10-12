# 145. Connect Two Storage Providers to One VFS

The Notes programme writes files in RAM. Our educational website also has
reference documents that should not be modified during a lesson. Instead of
creating a second pathname parser and descriptor system, we can connect a
**read-only provider** to the same VFS.

The second laboratory demonstrates that architecture using a small library of
immutable text documents. The application opens both `/notes` and `/library`
through the same public functions.

## 1. Compare the two mounts

| Operation | `/notes/PLAN.TXT` | `/library/COURSES.TXT` |
| --- | --- | --- |
| Open for reading | Allowed | Allowed |
| Read bytes | Allowed | Allowed |
| Open for writing | Allowed | Refused |
| Remove a name | Administratively controlled | Refused |
| Provider memory | Mutable file array | Immutable literal text |

The VFS itself does not contain special cases for the names `PLAN.TXT` or
`COURSES.TXT`. It selects a provider by mount prefix and calls its functions.
This is the central benefit of an interface: storage implementations can
differ without changing each application's file operations.

## 2. See how the callback table works

The reference provider returns this set of operations:

```c
return (BtbVfsProviderOps){
    .open = ReferenceOpen,
    .read = ReferenceRead,
    .write = NULL,
    .unlink = NULL,
    .release = ReferenceRelease
};
```

`NULL` means the provider has not supplied an implementation for that
operation. The VFS checks for the missing write operation and returns
`BTB_VFS_READ_ONLY` instead of calling a nonexistent function.

This is different from pretending the provider implements writes but silently
discards the data. A refused operation gives the caller a reliable result.

Read the full [reference provider implementation](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/vfs-provider-composition/reference_provider.c).
It owns two sample files and tracks open references. It does not own the VFS's
descriptor tables.

## 3. Understand reuse at build time

The first laboratory produces a static library called `btb_vfs`.
The second project's CMake configuration includes:

```cmake
add_subdirectory(
  "${CMAKE_CURRENT_SOURCE_DIR}/../vfs-descriptors"
  "${CMAKE_CURRENT_BINARY_DIR}/vfs-core")
```

The VFS source is compiled into its own library and linked into the new
application. No second copy of the VFS algorithms is maintained in the
reference-provider folder. This principle is important when a programme
becomes larger: fixes to descriptor checks should benefit every provider.

## 4. Build and run the composed application

Open PowerShell:

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

Expected output:

```text
Library: Computing, C23, Assembly, Umicom Kernel.
```

The tests also check that another client cannot use an existing descriptor,
that the reference provider refuses writes and unlinking, and that the VFS
refuses to unmount a provider while it still has an open-file description.

## 5. A failed close must remain observable

A provider can temporarily refuse its final `release` operation. In the
`test_composition.c` source, a test provider simulates one such refusal.
The VFS does **not** invalidate the descriptor or unmount the provider in
response. The next explicit close retries the release and succeeds.

The alternative would be dangerous: destroying the only token before
releasing its storage could make the remaining cleanup obligation unreachable.

That principle also appears in the actual Umicom Kernel storage subsystem,
where a failed device reset can require the driver to retain its DMA-owned
memory until it has evidence that the device can no longer access it.

## 6. Extend the reference library

Open `reference_provider.c`. Add a third entry, `SAFETY.TXT`, with the text
`Check every return status.` and update `BTB_REFERENCE_FILES` in
`reference_provider.h` from two to three. Add a test that reads the exact
bytes through `/library/SAFETY.TXT` and refuses a write request.

The complete programme should still build, and its existing tests should
continue to pass. Do not add another VFS implementation to solve this task;
only the provider's document table needs to change.

The next chapter moves from the classroom model to the real Umicom Kernel
code that inspired these ownership boundaries.
