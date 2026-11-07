# Discover the contract a native program needs

A native program and its kernel need an agreement about calls, data widths and limits. This agreement is an application binary interface, or ABI. A program must discover whether the running kernel supports what it needs before attempting those operations. This lab follows Umicom's existing discovery client and its refusal cases.

## Setup recap

Use a C23 host compiler, CMake, Ninja and an Umicom Kernel checkout. The [terminal setup guide](../../learning-c/terminal-lab.md) explains installation. The [memory-boundary lab](15-test-user-memory-boundaries.md) explains host tests. You do not need an emulator for this exercise. Test callbacks provide kernel replies so both valid and invalid responses can be examined safely.

## 1. Read the client, not just the test name

Open `programs/support/native_contract.c`. `UmicomUserContractDiscover` receives an invocation callback and an output structure. A callback is a function supplied by the caller; here it represents the path used to ask the kernel questions.

The client checks the version, available features, machine word width, byte order, page size, copy limit and call limit. Byte order describes how a multi-byte value is stored. A copy limit bounds how much data one call may transfer. A call budget limits repeated requests.

The function gathers replies into local values before publishing a complete output. This prevents a caller mistaking a partially filled contract for a usable one. Follow its early returns and identify which invalid condition each one handles.

## 2. Run selected discovery checks

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S 'C:/umicom/umicom-kernel/tests/native_contract' -B 'C:/umicom-learning/kernel-native-contract' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build 'C:/umicom-learning/kernel-native-contract' --parallel 2
ctest --test-dir 'C:/umicom-learning/kernel-native-contract' -R '^kernel\.native_contract\.(current|future-major|word-width|copy-zero|copy-too-large)$' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S "$HOME/umicom/umicom-kernel/tests/native_contract" -B "$HOME/umicom-learning/kernel-native-contract" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build "$HOME/umicom-learning/kernel-native-contract" --parallel 2
ctest --test-dir "$HOME/umicom-learning/kernel-native-contract" -R '^kernel\.native_contract\.(current|future-major|word-width|copy-zero|copy-too-large)$' --output-on-failure --no-tests=error
```

Five cases should be selected. `current` exercises an accepted contract. The other cases deliberately supply incompatible values. Success means the client recognises them and returns the expected refusal.

## 3. Separate availability from a program's requirements

Discovery tells a program what exists. `UmicomUserContractCheck`, in the same source file, compares those capabilities against the program's requirements. A valid kernel contract can still be insufficient for a particular program.

```text
kernel replies → validated contract
program requirements + validated contract → allow or refuse startup
```

Inspect `tests/native_contract/requirements_tests.c`. Find `missing-feature`, `copy-too-large` and `sum-overflow`. The first concerns a capability, the second a limit, and the third safe arithmetic. A version string alone cannot replace these checks.

## Exercise

Make a table with three columns: required feature, available feature, decision. Try a program needing two features when only one is advertised. Then try a program requesting a copy exactly at the limit and one byte above it. Write the expected decision before reading the corresponding test.

If discovery fails, retain the reason rather than guessing new constants. If a test executable is missing, build its configured host directory first. A host callback test validates the client against controlled replies; it does not establish that a real booted kernel returns those replies correctly. That needs the separate native qualification route.

Connect the result to [RISC-V object inspection](../../03-native-code/learning-riscv-assembly/05-inspect-a-riscv-object.md), where code becomes an object before linking. Return to [Umicom Kernel from Scratch](index.md) for the earlier boot and system-call lessons.

[Next: Publish a kernel contract only after validation](17-publish-a-contract-only-after-validation.md)
