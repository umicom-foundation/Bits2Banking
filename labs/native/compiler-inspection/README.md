# Compiler inspection lab

<!-- The explicit trace mode extends the existing execution choice. The previous wording is retained for engineering review.
This hosted C23 program embeds Umicom C. It compiles a literal source expression, checks its structure, prints its resource requirements and executes only when `--run` is supplied. Compiler and runtime behavior remain in the shared Umicom C libraries.
-->
This hosted C23 program embeds Umicom C. It compiles a literal source expression, checks its structure and prints its resource requirements. Execution is explicit: `--run` prints the result, while `--trace` also describes each arithmetic step. Compiler and runtime behaviour remain in Umicom C.

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


## Observe the shared runtime trace

After building the lab, run:

```powershell
& ".\build\compiler-inspection\compiler-inspection.exe" --trace
```

The seven rows should show top values 2, 3, 4, 12, 14, -14 and -14, with depths 1, 2, 3, 2, 1, 1 and 1. The final row is RETURN; the arithmetic answer is not a completed program before that instruction runs. The lab owns a trace array and reads only entries below the returned count. It neither copies the runtime evaluator nor adds callbacks to it.

The exact-output CTest case checks all seven rows. Rebuild Umicom C from source containing trace.h before configuring this lab; an older SDK or checkout cannot provide the new API. Trace data contains integer intermediates, so treat saved observations with the same care as the input. This is an arithmetic execution trace, not a live debugger, breakpoint facility or native stack inspector.

Continue with [observing the runtime trace](../../../content/courses/building-a-compiler-in-c/lessons/31-observe-an-execution-trace.html).

## Inspect and trace integer comparisons

Rebuild against Umicom C source containing the comparison extension, then select it explicitly:

```powershell
& ".\build\compiler-inspection\compiler-inspection.exe" --comparison
& ".\build\compiler-inspection\compiler-inspection.exe" --comparison --run
& ".\build\compiler-inspection\compiler-inspection.exe" --comparison --trace
```

The selected source is `int main(void) { return 2 + 3 < 2 * 3; }`. Inspection should report eight instructions, a peak of three temporary values and eighty encoded bytes. The run should return 1. Its trace should show top values 2, 3, 5, 2, 3, 6, 1 and 1. The LESS operation consumes the two completed arithmetic values; RETURN completes the program afterwards.

Comparisons produce 0 or 1, both valid results. They do not introduce variables, branches or logical short-circuiting. The encoder selects format 2 when a comparison occurs and preserves format 1 for the original arithmetic example. A successful inspection does not execute either operand. Keep the existing arithmetic checks when extending the exercise: they protect the old interface and demonstrate compatibility.

If the comparison source is rejected, check the configured `UMICOM_C_SOURCE` path and its revision. A matching header alone does not establish which library was linked. These expected observations require an actual build and run on your toolchain. Continue with [comparison tokens](../../../content/courses/building-a-compiler-in-c/lessons/39-recognise-comparison-tokens.html).
