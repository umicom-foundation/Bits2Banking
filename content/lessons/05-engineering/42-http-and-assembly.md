# 42. Understanding HTTP bytes with C and Assembly

A browser sends an HTTP message as a sequence of bytes. Before a C web server can interpret headers, it must locate the end of each line. In HTTP/1.1, a header line ends with two bytes: carriage return (`CR`, value 13) and line feed (`LF`, value 10). This pair is often written as `\r\n` in a C string.

## 1. Read a request as bytes

```text
G  E  T     /     H  T  T  P  /  1  .  1  CR LF
71 69 84 32 47 32 72 84 84 80 47 49 46 49  13 10
```

The numbers are decimal byte values. Searching for CRLF does not require a complete HTTP parser. It requires only an address and a length. The length matters because a received buffer may contain zeros and may not end in the null character expected by ordinary C string functions.

## 2. Start with the C implementation

Open `labs/native/http-header-scanner/scanner.c`. The implementation examines each adjacent byte pair. When the buffer contains fewer than two bytes, the answer is false. It never reads beyond the provided length.

```c
int BitsHttpContainsCrlfC(const unsigned char *bytes, size_t count)
{
    if (bytes == NULL || count < 2U) return 0;
    for (size_t i = 0U; i < count - 1U; ++i) {
        if (bytes[i] == 13U && bytes[i + 1U] == 10U) return 1;
    }
    return 0;
}
```

Here `size_t` represents the buffer length. The final legal first position is `count - 2`; the loop stops before `count - 1`, so `bytes[i + 1]` remains within the array.

## 3. Compare the Assembly implementations

The same source directory contains two Assembly files. On x86-64, [`scan_x86_64.S`](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/http-header-scanner/scan_x86_64.S) reads the pointer and count from either the Windows or System V argument registers. On RISC-V64, [`scan_riscv64.S`](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/http-header-scanner/scan_riscv64.S) uses `a0` and `a1`.

Neither helper allocates memory or makes an operating-system call. Both check the count, inspect adjacent bytes, advance one position and return 1 when the pair is found. The C implementation remains the reference result.

## 4. Compile and check the real code

In Windows PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-header-scanner" -B ".\build\http-header-scanner" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\http-header-scanner" --parallel 2
ctest --test-dir ".\build\http-header-scanner" --output-on-failure
& ".\build\http-header-scanner\bits-http-scan.exe"
```

The sample reports that C found a CRLF ending. With Assembly enabled on a supported target, it also reports whether the Assembly helper agrees. If a test fails, inspect the first disagreement before changing the code.

## 5. Continue from scanning to serving

Finding CRLF is only one very small operation in HTTP. The [native web-server lesson](39-build-a-c-web-server.md) follows the entire request through method parsing, a file-root check, a response header and streamed bytes. The server remains in C because network APIs, input checking and error paths are easier to review across platforms. An Assembly scanner is optional; using it without measurements would not establish a speed benefit.

### Try it yourself

1. Find the two bytes `13, 10` in the test cases.
2. Add a case where `13` is the final byte. It must not match.
3. Build once with Assembly and once with `-DBITS_HTTP_ENABLE_ASSEMBLY=OFF`.
4. Identify the argument registers and result register for your target.
5. Explain why treating an HTTP request as a null-terminated string could lose data.

Next, study [how the Umicom Kernel boots](../06-umicom/40-boot-umicom-kernel.md). That source uses freestanding Assembly to prepare execution before entering C23.
