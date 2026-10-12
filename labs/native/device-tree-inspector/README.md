# Device-tree inspection in C23

This standalone exercise reads a **synthetic** Flattened Device Tree (FDT) image. It checks its header, reservation terminator, structure tokens, property-name offsets, root address/size cells and one advertised `virtio,mmio` resource. It **never maps or reads hardware addresses**.

## Build on Windows (PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\device-tree-inspector" `
    -B ".\output\learning-build\device-tree-inspector" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\device-tree-inspector" --parallel 2
ctest --test-dir ".\output\learning-build\device-tree-inspector" --output-on-failure
& ".\output\learning-build\device-tree-inspector\btb-fdt-demo.exe"
```

The two tests cover the parser and its demonstration. Successful output identifies a `0x10001000` candidate spanning 4096 bytes; it does not establish a trustworthy driver capability. A real kernel must independently qualify the transport and permissions.

## Review the source

1. Open `fixture.c`; find the 40-byte FDT header, reservation terminator and big-endian properties.
2. Open `fdt.c`; follow `Read32`, `Span`, `BtbFdtInspect` and its final assignment to `outSummary`.
3. Open `test_fdt.c`; examine the malformed-header tests and 10,000 deterministic input mutations.
4. Modify the synthetic resource size in `fixture.c`, rebuild and predict the result. Keep the change within the declared fixture length.

This is intentionally a **bounded subset** of the FDT format. Its two-cell `reg` handling is sufficient for this lesson, but it is not a replacement for the full Umicom Kernel device-tree reader and bus-address translator.

[Read the lesson](../../../content/lessons/05-engineering/127-inspect-device-tree-in-c23.md).
