# Read a FAT16 disk image with C23

Build in PowerShell from the Bits2Banking repository root:

```powershell
cmake -S .\labs\native\fat16-inspector -B .\output\learning-build\fat16-inspector -G Ninja -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe
cmake --build .\output\learning-build\fat16-inspector --parallel 2
ctest --test-dir .\output\learning-build\fat16-inspector --output-on-failure
```

The test writes a fictional 2.56 MiB image to its build/test working directory. Inspect that image using `btb-fat16-inspect.exe` in the build directory. The inspection tool is **read-only** and rejects files larger than 32 MiB.

Read `fat16.c` beside [Chapter 138](../../../content/lessons/05-engineering/138-build-a-read-only-fat16-inspector.md) and compare the conceptual differences with Umicom Kernel's bounded FAT16 implementation. This learning programme does not mount, repair or change a real disk.
