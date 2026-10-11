# A bounded Notes record in C23

The note belongs to its caller and holds at most 127 bytes of text plus a final null byte. An input that does not fit returns `UMICOM_NOTE_TOO_LONG` without changing the old note. The same model could later back a Notes panel in Umicom Framework.

## Windows (PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\safe-notes" -B ".\build\safe-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\build\safe-notes" --parallel 2
ctest --test-dir ".\build\safe-notes" --output-on-failure
& ".\build\safe-notes\bits-notes.exe"
```

## Linux

```bash
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/native/safe-notes -B build/safe-notes -G Ninja
cmake --build build/safe-notes --parallel 2
ctest --test-dir build/safe-notes --output-on-failure
./build/safe-notes/bits-notes
```

Expected output:

```text
Note (32 bytes): Plan the Umicom Framework lesson
```

Try increasing the note length beyond the limit. Confirm the test still proves the old note remains intact.
