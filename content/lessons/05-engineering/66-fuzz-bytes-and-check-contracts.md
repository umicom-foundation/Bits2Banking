# 66. Reproduce parser failures with deterministic tests

A program may pass every example we wrote by hand and still fail when it receives an unexpected sequence of bytes. We can improve our confidence by trying many different inputs automatically, including malformed requests that nobody would intentionally send from a browser.

This chapter uses the [bounded HTTP request-line laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-byte-parser) to compare **unit tests**, **seeded adversarial tests** and **coverage-guided fuzzing**.

## 1. A unit test checks one known case

A unit test has a chosen input and an expected result. For example, `GET /lessons/ HTTP/1.1` should parse successfully, whereas a path with `../` should be refused. The unit-test executable performs such checks and reports a failure if any result differs from the expected behaviour.

Unit tests are valuable because they are understandable: each case names a problem that the implementation must handle.

## 2. A deterministic generator creates more inputs

Open `labs/native/http-byte-parser/fuzz_request_line.c`. The file includes a function named `NextRandom`, which updates a 32-bit unsigned integer and produces another value. The starting value is fixed, so every ordinary test run generates the same sequence.

Each trial makes a byte buffer of a bounded size and asks the parser to read it. A second variation starts with a real request line and changes one byte.

```c
(void)LLVMFuzzerTestOneInput(input, length);
```

This function verifies a **property**: if the parser rejects the input, the caller's output must remain unchanged. If it accepts an input, the method, path and version must satisfy the documented contract.

The default test exercises 5,000 arbitrary buffers and 5,000 mutated request lines. Its purpose is to make failures reproducible. It does **not** prove that 10,000 inputs cover all possible inputs.

## 3. Run the tests with CTest

From PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\http-byte-parser" `
    -B ".\output\learning-build\http-byte-parser" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\http-byte-parser" --parallel 2
ctest --test-dir ".\output\learning-build\http-byte-parser" --output-on-failure
```

You should see two passing tests. Run the seeded test again:

```powershell
ctest --test-dir ".\output\learning-build\http-byte-parser" `
    -R "http_seeded_fuzz" -V
```

Because the starting seed is fixed, the same test sequence is repeated. This makes a new failure easier to reproduce in a debugger.

## 4. Understand sanitizers

A **sanitizer** is compiler-assisted instrumentation that checks for certain runtime mistakes. AddressSanitizer can detect many invalid memory accesses and use-after-free errors. UndefinedBehaviorSanitizer can report several undefined operations such as signed integer overflow.

On Linux with Clang installed, configure a separate instrumented build:

```bash
cmake -S labs/native/http-byte-parser \
  -B output/learning-build/http-byte-parser-sanitized -G Ninja \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_C_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer' \
  -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'
cmake --build output/learning-build/http-byte-parser-sanitized --parallel 2
ctest --test-dir output/learning-build/http-byte-parser-sanitized --output-on-failure
```

On Windows, sanitizer support depends on the selected compiler and runtime. First run the supplied GCC/CTest configuration; use an instrumented toolchain only after verifying that its compiler and libraries support the chosen sanitizer flags.

A passing sanitizer run does **not** prove that a program contains no security defects. It means the instrumented execution did not detect the classes of problems the tool was configured to check.

## 5. What coverage-guided fuzzing adds

Coverage-guided fuzzers use feedback about which branches ran to decide which inputs to mutate next. The laboratory exports `LLVMFuzzerTestOneInput`, the entry point expected by LLVM's libFuzzer, so the same parser is suitable for a later dedicated fuzzing setup. The default CMake targets do **not** download libFuzzer or claim that coverage-guided fuzzing has run.

## 6. Change one assertion

In `test_request_line.c`, add a malformed request containing an embedded newline before the final `\r\n`. Predict whether the parser should accept it. Then run the tests again.

For a more demanding exercise, add a new accepted method to the parser. Update the method documentation, implementation and both unit and seeded-input properties. This shows why a public interface, its tests and its documentation should be changed together.

**Check your understanding:** What makes a seeded test reproducible? Why does a fuzzer need a property to check? How is a sanitizer different from a compiler warning? When is it reasonable to report that a program is *tested*, and when would claiming it is *proven secure* go too far?

Continue with the [Umicom Framework web-server interfaces](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/web) and the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel) to see how bounded memory and input contracts matter at system boundaries.
