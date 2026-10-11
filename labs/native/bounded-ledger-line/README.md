# Parse fictional ledger changes from bounded bytes

A network packet or file buffer is not automatically a C string. This project reads an exact number of bytes, rejects malformed input and only publishes a complete result after validation.

The teaching format is `ACCOUNT:SIGNED_PENCE`. For example, `1001:+2500` represents a fictional change of 2,500 pence to training account 1001. It is **not** a general CSV parser, ISO 20022 message, or real financial protocol.

## Windows build

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\bounded-ledger-line" -B ".\output\learning-build\bounded-ledger-line" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\bounded-ledger-line" --parallel 2
ctest --test-dir ".\output\learning-build\bounded-ledger-line" --output-on-failure
```

The unit test covers the limits of `uint32_t` and `int64_t`, malformed separators and embedded zero bytes. The deterministic mutation test checks 20,000 inputs with no external fuzzing tools. A failed parse must not change the caller's existing record.

Try replacing `1001:+2500` in `main.c` with `1001:2500`. Run the demo again: it must return an error because the sign is required. Restore the example when finished.

[Read Lesson 69](../../../content/lessons/03-native-code/69-bounded-byte-slices.md).
