# Build a read-only FAT16 inspector in C23

We will inspect an image without mounting it, modifying it or trusting its declared length.

## 1. Build the parser

From PowerShell in `C:\umicom\Umicom-Bits2Banking`, with MSYS2 UCRT64 installed:

```powershell
cmake -S .\labs\native\fat16-inspector -B .\output\learning-build\fat16-inspector -G Ninja -DCMAKE_C_COMPILER=C:\msys64\ucrt64\bin\gcc.exe
cmake --build .\output\learning-build\fat16-inspector --parallel 2
ctest --test-dir .\output\learning-build\fat16-inspector --output-on-failure
```

## 2. Read three functions

`BtbFat16Open()` checks the boot record and computes the volume layout. `BtbFat16RootNames()` reads short, 8.3 directory names, skipping deleted and long-filename records. `BtbFat16Follow()` walks one cluster chain while detecting loops and invalid links.

## 3. Explain a status result

The program reports `BTB_FAT_TRUNCATED` when its actual byte span is shorter than the volume claims; `BTB_FAT_UNSUPPORTED` when the computed cluster count does not classify as FAT16; and `BTB_FAT_CHAIN` for an invalid or cyclic allocation chain. None of these failures authorises repairing a disk.

## 4. Change and retest

In the fixture builder in `test_fat16.c`, change the first file's name from `NOTES   TXT` to `REPORT  TXT`. Update its assertion, build again, and explain how the root directory and the file's data clusters serve different purposes.

## 5. Limitations

This is a **small learning inspector**: it does not validate every FAT16 specification constraint, resolve long filenames, compare multiple FAT copies, mount a device, or fully verify file sizes and directory trees. Never point it at confidential data or mistake a successful inspection for filesystem integrity certification.
