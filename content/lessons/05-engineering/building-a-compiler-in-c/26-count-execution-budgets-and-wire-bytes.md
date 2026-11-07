<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/26-count-execution-budgets-and-wire-bytes.md

PURPOSE:
Count execution budgets and encoded bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Count execution budgets and encoded bytes

This module follows one small program from text to an inspectable instruction sequence. Each lesson defines its terms, shows a concrete operation and gives an exercise with an expected observation. Inspection describes the program; execution attempts its arithmetic. A compiler, an IDE and a teaching tool can all use the same library contracts.

A terminal is a window in which commands are typed. A compiler translates source text into instructions; CMake describes a build and Ninja carries out its steps. Install Git and the MSYS2 UCRT64 GCC, CMake and Ninja packages if these tools are not available. The [Learning Build Systems course](../../../courses/learning-build-systems/index.html) explains their roles in more depth.

1. Keep the Umicom C and Bits2Banking checkouts beside each other in a folder you choose. The examples use C:\umicom. Replace that location consistently if yours differs.
2. In the MSYS2 UCRT64 terminal, install the tools with the following command. Complete the package manager's normal update instructions first if it requests them.

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
```

3. Open PowerShell and build the small compiler. Run each line separately. If a command reports an error, stop and read it before continuing.

```powershell
Set-Location "C:\umicom\umicom-c"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-debug -DBUILD_TESTING=ON
cmake --build --preset windows-ucrt64-debug --parallel 2
ctest --preset windows-ucrt64-debug --output-on-failure --no-tests=error
& ".\build\windows-ucrt64-debug\bin\umicom-c.exe" inspect ".\examples\inspection.uc"
```

On Linux, install a C23-capable C compiler, CMake and Ninja with your distribution's package manager. From the umicom-c checkout use the native-debug preset:

```bash
cmake --preset native-debug -DBUILD_TESTING=ON
cmake --build --preset native-debug --parallel 2
ctest --preset native-debug --output-on-failure --no-tests=error
./build/native-debug/bin/umicom-c inspect ./examples/inspection.uc
```

The inspection example should report 7 instructions, a peak stack of 3 values, 3 constants, 3 arithmetic operations and 71 encoded bytes. These are expected results to check on your machine. The language currently supports one integer-returning main function with arithmetic; it does not compile the full C language. If inspect is an unknown command, check that the binary was rebuilt from source containing umc_inspect. Keep any previous logs when investigating a failure.


## An execution budget is a count

A budget limits how much work a caller permits. In the current Umicom C virtual machine, fuel counts instructions, including RETURN. The language has no branch or loop instructions, so a successful run executes each instruction once. Seven instructions therefore require a fuel allowance of seven.

1. Run the example with --max-steps 6. Expect fuel exhaustion before RETURN.
2. Run it with --max-steps 7. Expect -14 and seven executed instructions.
3. Remember that structural validation happens first. The fuel allowance does not skip validation or make malformed input acceptable.

Fuel is not a duration in milliseconds. A slow device can take more time for the same instruction count. If a future language adds loops, its execution-bound analysis will need a new design; the current straight-line count is not a general loop bound.

## Stored bytes have a separate unit

A byte is a unit of storage containing eight bits. The portable bytecode format uses an eight-byte header followed by nine bytes for each instruction. For seven instructions:

```text
encoded bytes = header + instructions * record size
              = 8 + 7 * 9
              = 71
```

The inspection report's bytecode_size uses this wire format. It is not sizeof(UmcInstruction). A C structure may contain padding and a machine-sized source offset. Encoding writes a defined byte layout so different hosts can exchange the same supported format.

## Exercise

Compile the example to a new filename, such as inspection-study.umcb, then inspect-bytecode that file. The report should match source inspection. Use a fresh output name for a second compilation: the CLI deliberately refuses to overwrite an existing output.

For a two-instruction program that pushes one value and returns it, calculate the encoded size before checking it. The answer is 26 bytes. For the maximum accepted 256 instructions, the size is 2,312 bytes. These bounded quantities keep size calculations simple and reviewable. They do not describe the memory used by the entire application, compiler or operating system.

## Read the source

[Open the example source](../../../../../umicom-c/include/umicom_c/umicom_c.h).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Distinguish structure from arithmetic safety](25-distinguish-structure-from-arithmetic-safety.md) · [Next: Embed the inspector in a C application](27-embed-the-inspector-in-a-c-application.md)
