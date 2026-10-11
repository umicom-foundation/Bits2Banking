# 60. Find defects with compiler warnings, tests and sanitizers

A program can compile successfully and still be incorrect. A function may read beyond an array, keep using memory after it has been released, or calculate a number using invalid arithmetic. Understanding these problems is part of learning to write reliable C.

This lesson demonstrates how to build small programmes with warnings enabled, run automated tests and use diagnostic tools. We use the [Owned Notes laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/owned-notes) to keep the exercise connected to a useful application.

## 1. What compilation actually proves

When a compiler accepts a C source file, it has determined that it can translate the code into machine instructions under the selected language and toolchain rules. It has **not** proved that every future input is valid.

For example, if you create an array with room for ten bytes, reading byte number ten is outside the array. C indexes start at zero, so the valid positions are zero through nine. Such an out-of-bounds read has *undefined behaviour*: the C language does not guarantee a particular result.

The safest approach is to prevent the invalid read, not to rely on the program appearing to work.

## 2. Start with compiler warnings

The Notes laboratory enables these common warning groups when supported by GCC or Clang:

```text
-Wall -Wextra -Wpedantic -Wconversion -Wshadow
```

`-Wall` and `-Wextra` enable additional diagnostics. `-Wconversion` helps identify surprising conversions between number types. `-Wshadow` identifies declarations that hide earlier variables with the same name.

A warning is a reason to inspect the affected code. Not every warning indicates a defect, and not every defect generates a warning.

## 3. Learn the purpose of AddressSanitizer and UBSan

**AddressSanitizer (ASan)** instruments a programme to help detect memory errors such as certain out-of-bounds accesses and use-after-free defects. **UndefinedBehaviorSanitizer (UBSan)** instruments selected operations that can violate language rules.

These tools are particularly useful during development and testing. They add runtime overhead and must not be treated as proof that an application is secure or free of errors.

The following commands use Clang and Ninja on Linux, where a supported sanitizer runtime is available:

```bash
cmake -S labs/native/owned-notes \
  -B output/learning-build/owned-notes-sanitized \
  -G Ninja -DCMAKE_C_COMPILER=clang \
  -DBTB_ENABLE_SANITIZERS=ON

cmake --build output/learning-build/owned-notes-sanitized --parallel 2
ctest --test-dir output/learning-build/owned-notes-sanitized --output-on-failure
```

On Windows UCRT64, first run the ordinary GCC build shown in [Lesson 58](58-memory-ownership-in-c23.md). Sanitizer support varies by compiler and runtime installation; do not assume these Linux commands are supported unchanged on every Windows toolchain.

## 4. Test failures without deliberately corrupting memory

You can practise error handling without compiling unsafe examples. In `test_notes.c`, the following ordinary test requests an output buffer that is deliberately too small:

```c
char tinyTitle[] = "KEEP";
char tinyBody[] = "KEEP";
BtbNoteStatus status = BtbNoteStoreRead(store, id,
    tinyTitle, sizeof(tinyTitle), tinyBody, sizeof(tinyBody));
```

The expected result is `BTB_NOTE_CAPACITY_EXCEEDED`. The strings must remain `KEEP` because the function refuses to make a partial copy. This is an example of a *negative test*: it demonstrates correct behaviour when the request is invalid.

Negative tests are particularly important in document editors, parsers, HTTP servers and financial transaction workflows.

## 5. How to approach a failing test

Suppose `ctest` reports one failed test. Start with the exact test name and run it in verbose mode:

```powershell
ctest --test-dir ".\output\learning-build\owned-notes" `
    -R "^bits2banking\.owned_notes$" -V
```

Read the failed condition, source location and expected output. Investigate one failure at a time. Do not remove a failing assertion merely to make the test green. Confirm that a genuine correction addresses the cause, then run the complete suite again.

For a native crash, reproduce it with the same input in a debugger. Record the call stack, the values and the source revision. If the program accepts untrusted data, inspect the boundaries where sizes, counts and pointers are checked.

## 6. Your next exercise

Add a test that asks `BtbNoteStoreRead` for a nonexistent note ID. Check that the function returns `BTB_NOTE_NOT_FOUND`. Run the test suite normally, then use a sanitizer-enabled build on a supported host.

**Check your understanding:** What does a compiler warning mean? Why is a passing test not enough to prove a programme is free of defects? What does an out-of-bounds access mean? Why should a rejected request leave a caller's buffer unchanged?

### Continue with Umicom Framework

The production [Umicom Framework](https://github.com/umicom-foundation/umicom-framework) uses explicit allocation, status and lifetime contracts. Examine its [allocator interface](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/memory.h) and [status codes](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/status.h) for examples of separating a public interface from an implementation. 
