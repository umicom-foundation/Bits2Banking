# Laboratory — Build a C23 library and examine the linker map

A library lets several applications reuse the same functions without copying their implementation. This exercise builds a small fictional ledger calculation as a static library, links a command-line application against it, tests the interface, and examines why the linker included the library's object file.

## 1. Configure and build on Windows

Open PowerShell and run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\static-library-map" `
    -B ".\output\learning-build\static-library-map" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\static-library-map" --parallel 2
ctest --test-dir ".\output\learning-build\static-library-map" --output-on-failure
```

Two tests should pass. One calls the public library functions, including failure paths. The other runs an application that prints a fictional amount of **GBP 504.00**.

## 2. Run the application

```powershell
& ".\output\learning-build\static-library-map\btb-ledger-demo.exe"
```

Expected:

```text
Learning fund total (fictional): GBP 504.00
```

The values are whole pence. No real funds or payments are processed.

## 3. Find the library archive

```powershell
Get-ChildItem ".\output\learning-build\static-library-map" `
    -File -Include "*.a", "*.lib" -Recurse
```

With GCC, look for `libbtb_ledger.a`. Its contents come from `src/ledger.c`, while `src/main.c` is compiled separately into the application.

Inspect the static archive using the Framework's native command:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& ".\build\umicom-education\bin\umicom-education.exe" archive `
    --file "C:\umicom\Umicom-Bits2Banking\output\learning-build\static-library-map\libbtb_ledger.a"
```

The tool should report `Format: ar` and at least one object member. The precise `.o` or `.obj` name varies by compiler.

## 4. Read the linker map

The GNU/Clang link step generates:

`output/learning-build/static-library-map/btb-ledger-demo.map`

View it in your editor or search for the library name:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Select-String -Path ".\output\learning-build\static-library-map\btb-ledger-demo.map" `
    -Pattern "btb_ledger"
```

The linker map shows why the linker extracted an object file from the archive. Look for `BtbLedgerTotalPence` or `BtbLedgerFormatPence`.

You may also inspect the archive's symbol table with your toolchain's `nm` command:

```powershell
& "C:\msys64\ucrt64\bin\nm.exe" `
    ".\output\learning-build\static-library-map\libbtb_ledger.a"
```

`BtbLedgerTotalPence` and `BtbLedgerFormatPence` are public function names. `AddChecked` is declared `static`, so it has internal linkage and is not a public API. A linker may still list a local `AddChecked` symbol inside the object; **internal linkage is not the same as hiding all debugging names**.

## 5. Install into a private directory

```powershell
cmake --install ".\output\learning-build\static-library-map" `
    --prefix "C:\umicom\Umicom-Bits2Banking\output\learning-install\static-library-map"
```

Inspect `bin`, `lib` and `include/btb` under that private install path. Installation does not write into Windows system directories.

## 6. Change one detail

Add a fourth fictional amount to `src/main.c`, rebuild and run the tests. The demo's expected total will change, so the demo-output test should fail until you deliberately update its expected result. This is useful: an automated test should detect a change in observable behaviour.

For the underlying concepts, read [Static archives](../../../content/lessons/05-engineering/77-understand-static-archives.md) and [Symbol visibility and link maps](../../../content/lessons/05-engineering/78-symbol-visibility-and-linker-map.md).
