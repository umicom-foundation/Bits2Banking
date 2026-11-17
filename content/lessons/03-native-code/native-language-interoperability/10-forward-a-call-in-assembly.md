<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/10-forward-a-call-in-assembly.md

PURPOSE:
Teach connect assembly to the same c function.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Connect assembly to the same C function

[Course contents](index.md) · [Previous](09-call-c-from-nim.md) · [Next](11-test-errors-and-ownership.md)

## Scope of this experiment
Assembly names processor instructions directly. It is specific to the processor and object format. This lab covers GNU-style assembly on Windows x64 and Linux x86-64. It deliberately rejects other targets during preprocessing. It is not a bootloader or a faster implementation of the counting rule.

## Follow the call
1. Open forward.S and main.c. The capital S tells the GNU toolchain to preprocess the assembly source.
2. Find the global BtbAssemblyActivityNext symbol. The C caller declares the same function.
3. Observe the single jump to BtbActivityNext. A tail jump reuses the original return address. No new stack frame or return address is created.
4. On Windows x64 the first integer argument arrives in ECX; on Linux x86-64 it arrives in EDI. The wrapper changes neither register. The two called functions use the same ABI on each platform.
5. The C function returns its integer result in EAX and returns directly to the original caller.

## Build and compare
Use the SDK prefix from lesson 1:

~~~powershell
cmake -S labs/native/assembly-activity -B build/assembly-activity -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_ASM_COMPILER=gcc "-DCMAKE_PREFIX_PATH=C:/umicom/installed/framework"
cmake --build build/assembly-activity --parallel 2
ctest --test-dir build/assembly-activity --output-on-failure --no-tests=error
~~~

The C driver checks INT_MIN, -1, 0, 41, 999, 1000 and INT_MAX against explicit answers and the direct C call. This tests both rejected extremes and valid transitions. The lab does not benchmark performance.

## Exercise and recovery
Would replacing jmp with call and leaving the rest unchanged work? No: call adds another return address and requires a valid return path and ABI-compliant stack handling. This particular wrapper needs none of those changes because it forwards the original call unchanged.

If the assembler reports an unsupported target, use the C-only client or provide a separately reviewed implementation for that target. Do not remove the guard to claim portability. The GNU stack-note section on Linux marks the object as not requesting an executable stack; Windows uses a different object format.

## Read the complete source

[labs/native/assembly-activity/forward.S](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/assembly-activity/forward.S)
