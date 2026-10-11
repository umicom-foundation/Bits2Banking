# Physical page-frame ownership in C23

A kernel must know which physical memory pages are available, which belong to the kernel or a process, and which are reserved for firmware or another purpose. This programme models a *physical frame allocator* that manages a fictional inventory of 128 frames, each 4096 bytes long. It never reads or writes actual physical RAM.

The first eight frames are reserved. When the application requests its first frame, the allocator returns the address of frame 8, not frame 0:

```text
First available frame: 0x80008000
Reserved frames: 8
Owned frames: 1
```

A frame address is not a C pointer to usable physical RAM. It is an identifier of a page-sized range in the teaching model. Releasing a reserved frame, freeing the same frame twice, or allocating beyond capacity is refused.

## Build and test

From the Bits2Banking repository root, in Windows PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\physical-frame-pool" `
  -B ".\output\learning-build\physical-frame-pool" `
  -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\physical-frame-pool" --parallel 2
ctest --test-dir ".\output\learning-build\physical-frame-pool" --output-on-failure
```

**Try it:** Change the first reserved count in `BtbFramePoolInit` from eight to ten. Predict the first returned address, then rebuild and check. The expected value should move by 8192 bytes.

The real Umicom Kernel manages physical memory using architecture and platform information. Read its [Physical Memory](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PHYSICAL_MEMORY.md) guide and compare the model with `kernel/physical_memory.c`. Do not copy this educational allocator into production kernel source: it has neither locking nor firmware discovery, NUMA policy or real page ownership integration.
