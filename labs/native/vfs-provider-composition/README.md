# Compose two filesystem providers in C23

The previous laboratory implemented one VFS and a writable in-memory Notes
provider. This laboratory links that **same VFS library** and adds a different
provider for immutable reference documents. No descriptor table, pathname
router or handle decoder is copied here.

The VFS dispatches `/notes/PLAN.TXT` to the RAM provider and
`/library/COURSES.TXT` to the immutable reference provider. The latter has
`write = NULL` and `unlink = NULL` in its callback table, so attempts to open
it for writing or remove its files are refused.

## Build and run on Windows

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

Expected: **2/2 CTest cases pass**. The demo prints:

```text
Library: Computing, C23, Assembly, Umicom Kernel.
```

Read `reference_provider.c`, then follow its function pointers through
`BtbVfsOpen` and `BtbVfsRead`. It owns copied output but does not allocate or
persist file contents. Then inspect `test_composition.c`: a deliberately failing
provider release leaves the descriptor and mount alive until a successful retry.

## Develop the example

Add a third immutable document to `REFERENCE_FILES` and update
`BTB_REFERENCE_FILES`. Build, open and inspect that document through the VFS.
Attempt to write to it and confirm the request is rejected. Finally, try to
unmount `/library` while a descriptor is open; it must return `BTB_VFS_BUSY`.

This is a serial, hosted-C learning model. A production VFS needs robust
pathnames, concurrency control, user/kernel boundaries, resource budgets and
provider-specific guarantees. Umicom Kernel owns its real implementation;
this programme exists solely to teach the interfaces and lifetime rules.
