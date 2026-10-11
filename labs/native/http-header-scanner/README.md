# Inspect an HTTP header in C and Assembly

HTTP uses CRLF byte pairs (13, 10) to end header lines. This laboratory reads a borrowed byte array and searches for one such pair. It never starts a socket or exposes a network service; the corresponding C23 native web-server workshop handles actual HTTP requests.

## Build on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-header-scanner" -B ".\build\http-header-scanner" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\http-header-scanner" --parallel 2
ctest --test-dir ".\build\http-header-scanner" --output-on-failure
& ".\build\http-header-scanner\bits-http-scan.exe"
```

On a supported x86-64 compiler, the Assembly helper uses the operating system's calling convention: Windows uses RCX and RDX; System V uses RDI and RSI. RISC-V64 ELF uses A0 and A1. Both implementations return 1 when a CRLF pair is present and zero otherwise.

To study portable C first, configure with `-DBITS_HTTP_ENABLE_ASSEMBLY=OFF`. Run the same tests. Other architectures use the C path automatically.

The native example is educational. A production HTTP parser must also validate request grammar, size limits, methods, Host, encodings, file roots and more. Compare the Framework's real native educational preview implementation in `framework/src/education/site_preview.c` after studying this scanner.
