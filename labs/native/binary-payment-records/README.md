# Understand bytes by serialising a simulated payment

This lab represents a **fictional** instruction as 16 bytes. Nothing is transmitted to a bank, posted to a ledger or authorised. The C23 code checks the output capacity before writing, uses fixed-width integers and writes all multi-byte numbers in network (big-endian) order.

```text
Bytes 0–3     Payment ID (unsigned 32-bit)
Bytes 4–11    Amount in minor currency units (unsigned 64-bit)
Bytes 12–14   ISO-style three-letter currency code (ASCII, not zero-terminated)
Byte 15       Training status (1 pending, 2 reviewed)
```

For payment ID `27`, amount `125000` minor units (for example, GBP 1,250.00), currency `GBP`, status `1`, the expected bytes are:

```text
00 00 00 1B 00 00 00 00 00 01 E8 48 47 42 50 01
```

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\binary-payment-records" -B ".\output\learning-build\binary-payment-records" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\binary-payment-records" --parallel 2
ctest --test-dir ".\output\learning-build\binary-payment-records" --output-on-failure
& ".\output\learning-build\binary-payment-records\bits2banking-record-demo.exe"
```

## Linux

```bash
cmake -S labs/native/binary-payment-records -B /tmp/btb-payment-records -G Ninja
cmake --build /tmp/btb-payment-records
ctest --test-dir /tmp/btb-payment-records --output-on-failure
/tmp/btb-payment-records/bits2banking-record-demo
```

Try changing `125000U` in `main.c` to `7500U`; build and explain exactly which encoded bytes change. Then inspect `test_record.c`: how does it prove that a rejected request does not partially overwrite the buffer?

This is intentionally a transparent learning protocol, **not** a payment standard, regulatory interface or substitute for the real Umicom Framework financial messaging contracts.
