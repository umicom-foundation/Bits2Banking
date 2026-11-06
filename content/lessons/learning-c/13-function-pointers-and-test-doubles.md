# Pass a function to separate policy from mechanism

The native contract reader needs answers, but its host tests do not need a real processor trap.

## 1. Recall an ordinary function call

A function takes input, does work and returns a result. When you write `ReadValue(3)`, the name identifies the code to run. A **function pointer** lets a caller provide which compatible function should run. It is a typed reference to callable code, not a place to store an arbitrary data address.

```text
typedef UmicomU64 (*UmicomUserInvoke)(
    UmicomU64 number, UmicomU64 first,
    UmicomU64 second, UmicomU64 third);
```

Read from the name: `UmicomUserInvoke` describes a pointer to a function taking four unsigned 64-bit values and returning one. The parentheses around `*UmicomUserInvoke` are important. Without them, the declaration would describe a different type.

## 2. Use the actual reader

```text
UmicomUserContract contract;
UmicomUserContractStatus status =
    UmicomUserContractDiscover(UmicomProgramSystemCall, &contract);
```

The function name supplies the ECALL bridge. `&contract` supplies the address where a successful answer will be written. The status is a named enum value: a small vocabulary of results such as OK, UNAVAILABLE or INCOMPATIBLE. Read fields only after the status is OK.

## 3. Replace only the boundary in a host test

In `tests/native_contract/contract_tests.c`, the test supplies `Invoke` instead. That function checks the requested operation number, selector order and zero reserved arguments, then returns a prepared answer. It never executes ECALL. The production reader still runs unchanged, including its version and size checks.

 <svg viewbox="0 0 700 110" role="img" aria-label="A test substitutes the boundary, not the logic whose behavior it is checking." style="width:100%;max-width:700px"><title>A test substitutes the boundary, not the logic whose behavior it is checking.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Same discovery function</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Chosen call bridge</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Real trap or observed reply</text></svg>

A test substitutes the boundary, not the logic whose behavior it is checking.

## 4. Learn what each test can prove

A host test can show that a legacy reply is refused before feature bits are interpreted, that future compatible minor versions are accepted, and that errors preserve output. It cannot show that RISC-V saves registers correctly or that the loader initialized a user stack. The separate guest test covers those connections.

## 5. Keep ownership explicit

The supplied function must remain callable for the duration of discovery. The reader does not save it for later. A missing function pointer is rejected before a call. None of this makes an invalid arbitrary pointer safe: the caller must supply a real function with the declared signature.

## Exercise

The first version reply is 1, which the older monitor uses for UNKNOWN_CALL. Why must the reader stop before interpreting a feature reply?

<details>

<summary>Answer</summary>

Feature bit 1 also has a valid meaning. Without checking the version first, a legacy error could be mistaken for service support. The test expects exactly one call and unchanged output in this case.

</details>

You have now connected C structures, pointers, callbacks and error handling to a working Umicom native-program boundary. Return to [Learning RISC-V Assembly](../../courses/learning-riscv-assembly/index.html) to see what the real bridge does.

[Next: Storage duration and freestanding code](14-storage-duration-and-freestanding-code.md)

## Read the source

Open [umicom-kernel/programs/support/native_contract.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/programs/support/native_contract.c) to compare the explanation with the current source. Repository contents can change; use the commit shown by GitHub when recording your observations.

[Words explained](../../courses/learning-c/glossary.html) · [Practical lab guide](../../courses/learning-c/practical-guide.html) · [Connected learning routes](../../courses/learning-paths.html)

---

[Read this lesson in HTML](../../courses/learning-c/lessons/13-function-pointers-and-test-doubles.html) · [Learning sequence](../../start/learning-sequence.md)

## Continue this module

Further study: systems programming · Lesson 2 of 7.

[Previous: Connect borrowed memory to bounded system input](11-bounded-spans-and-rejection.md) · [Next: Storage duration and freestanding code](14-storage-duration-and-freestanding-code.md)
