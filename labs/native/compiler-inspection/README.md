# Compiler inspection lab

This hosted C23 program embeds Umicom C. It compiles a literal source expression, checks its structure, prints its resource requirements and executes only when `--run` is supplied. Compiler and runtime behavior remain in the shared Umicom C libraries.

## What embedding means

Embedding a library means calling its functions from another program. The lab does this with Umicom C instead of starting its CLI. It owns a source string, an instruction array, a diagnostic and a result structure. The library borrows these objects during each call and does not retain their addresses.

1. Open labs/native/compiler-inspection/main.c.
2. Find source, a constant character array. sizeof(source) includes its terminating zero byte, so the compiler receives sizeof(source) - 1U as the text length.
3. Find program, an array with UMC_PROGRAM_LIMIT entries. count starts at zero.
4. Follow umc_compile. On failure the program prints the static diagnostic message and returns before reading any partial instruction output.
5. Follow umc_inspect. It fills info only after complete validation succeeds.
6. Follow the --run branch. Execution remains an explicit separate choice.

## Build just the lab

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/compiler-inspection -B build/compiler-inspection -G Ninja -DBUILD_TESTING=ON
cmake --build build/compiler-inspection --parallel 2
ctest --test-dir build/compiler-inspection --output-on-failure --no-tests=error
& ".\build\compiler-inspection\compiler-inspection.exe"
& ".\build\compiler-inspection\compiler-inspection.exe" --run
```

The first launch should report the resource counts and say that no program instructions were executed. The second should additionally report -14. The CMake project links UmicomC::Compiler and receives its Runtime dependency; it does not copy the lexer or evaluator into the lesson.

On Linux use the same cmake commands and launch ./build/compiler-inspection/compiler-inspection. If the compiler checkout is elsewhere, pass -DUMICOM_C_SOURCE followed by its absolute path when configuring. A missing checkout is a dependency-location error, not a source-language error.

## Extend the example

Change the source expression, rebuild and inspect it. Keep the error checks. Do not read info after a failed call or execute a partial compile result. Those ownership and status rules are the same ones an IDE integration needs.

## Files

- `main.c`: caller-owned buffers and explicit error handling.
- `CMakeLists.txt`: shared compiler linkage and two workflow checks.

See [the lesson](../../../content/courses/building-a-compiler-in-c/lessons/27-embed-the-inspector-in-a-c-application.html) for the full setup summary.
