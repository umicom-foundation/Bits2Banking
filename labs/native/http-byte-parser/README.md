# Read HTTP request bytes without assuming they are strings

A client can send an incomplete message, a zero byte or a request with extra data. This laboratory works with an explicit buffer pointer and byte count. It accepts only GET/HEAD, HTTP/1.0 or 1.1 and a restricted ASCII path. It does not open a network socket, decode escapes, parse headers, serve files or claim to be a production HTTP parser.

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-byte-parser" -B ".\output\learning-build\http-byte-parser" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\http-byte-parser" --parallel 2
ctest --test-dir ".\output\learning-build\http-byte-parser" --output-on-failure
& ".\output\learning-build\http-byte-parser\bits2banking-http-parser.exe"
```

## Linux

```bash
cmake -S labs/native/http-byte-parser -B output/learning-build/http-byte-parser -G Ninja
cmake --build output/learning-build/http-byte-parser --parallel 2
ctest --test-dir output/learning-build/http-byte-parser --output-on-failure
./output/learning-build/http-byte-parser/bits2banking-http-parser
```

The CTest suite should report two passing cases. The seeded test sends 10,000 malformed or mutated inputs through the parser with consistent results. Unlike coverage-guided fuzzing, this deterministic run does not prove that every code path was explored. Read [Lesson 65](../../../content/lessons/03-native-code/65-parse-bounded-http-bytes.md) and [Lesson 66](../../../content/lessons/05-engineering/66-fuzz-bytes-and-check-contracts.md), then compare the bounded teaching contract with the [Umicom Framework web interfaces](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/web).
