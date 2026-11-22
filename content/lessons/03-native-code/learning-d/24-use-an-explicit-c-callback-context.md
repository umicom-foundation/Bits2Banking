<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/24-use-an-explicit-c-callback-context.md

PURPOSE:
Use a C callback without capturing a D delegate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use a C callback without capturing a D delegate

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `callback_client.d` in `labs/languages/native-language-boundary` in the course checkout. Open the C boundary alongside the D client. Identify who supplies the context address and put both compilers in the same 64-bit toolchain environment before linking.
The earlier function-pointer lesson distinguished a function address from a delegate that also carries an environment. This exercise makes that distinction concrete. A small C routine calls a D function with an explicit context pointer. You will inspect the ABI declaration, follow two callback attempts, and explain why one accepted callback does not imply that only one callback ran.


## 1. Establish the ownership and thread contract

bounded_progress_visit validates up to 64 pairs of completed and total counts. It computes their percentages before invoking any callback. The visitor is synchronous and runs on the calling thread. It is never stored after the call returns. Input arrays, the context record and the accepted counter remain caller-owned. These facts make it valid to pass addresses of local values that stay alive throughout the call; the same design would be unsafe for an API that retained those addresses after main left its scope.


## 2. Build the C tests before the D client

1. Read the native-language-boundary README and complete the earlier C ABI lesson. Verify compiler architecture, object format and runtime compatibility.
2. Run the lab’s CMake configure/build/CTest commands. The arithmetic and callback C tests should pass. They check the C contract but do not compile D.
3. Open callback_client.d and compare every external parameter with boundary.h. int32_t in this teaching C interface corresponds to D int, which the example checks as four bytes.
4. Keep the callback as a module-level extern(C) function. Do not replace it with a capturing nested function or delegate and then force a cast to make the types appear compatible.


## 3. Read the complete client

~~~d
import std.stdio : writeln;
extern(C) {
    alias ProgressVisitor = int function(int, int, void*) nothrow @nogc;
    int bounded_progress_visit(const(int)* completed, const(int)* totals,
        int count, ProgressVisitor visitor, void* context, int* accepted) nothrow @nogc;
}
struct CallbackState { int calls; int stopAt; int[3] observed; }
extern(C) int onProgress(int index, int percent, void* context) nothrow @nogc
{
    if (context is null) return 99;
    auto state = cast(CallbackState*) context;
    if (index != state.calls || index < 0 || index >= 3) return 99;
    state.observed[index] = percent;
    ++state.calls;
    return index == state.stopAt ? 17 : 0;
}
int main()
{
    static assert(int.sizeof == 4);
    int[3] completed = [1, 2, 3], totals = [4, 4, 4];
    CallbackState state;
    state.stopAt = 1;
    int accepted = -1;
    int status = bounded_progress_visit(completed.ptr, totals.ptr, 3,
        &onProgress, &state, &accepted);
    if (status != 2 || accepted != 1 || state.calls != 2 ||
        state.observed[0] != 25 || state.observed[1] != 50) return 1;
    writeln("D callback checks passed: two attempted, one accepted");
    return 0;
}

~~~

The extern(C) block gives the declared function and function-pointer type the C linkage contract. The alias names that pointer type ProgressVisitor. Its arguments are two integers and an untyped pointer, and its result is an integer. nothrow states that it does not throw D exceptions; @nogc prevents operations requiring garbage-collected allocation. These attributes constrain code, but they do not prove that an arbitrary pointer is valid. The function still needs its documented context lifetime and bounds.

CallbackState is a D struct containing only fixed integers and a fixed three-element array. The C routine treats it as opaque and merely returns the same void pointer. The callback casts that address back to CallbackState*. This is a deliberate trusted boundary: the caller passed &state of exactly that type. The callback refuses a null pointer or an unexpected index before accessing the array. It records the percentage, increments the attempt count, and asks to stop at index one.


## 4. Keep runtime work outside the callback

The callback does not call writeln, allocate a class, capture a closure or throw an exception. The human-readable message is printed after the C function returns. In a real application you might append a bounded event to caller-owned storage and let another part of the program display it. Do not assume that @nogc means no allocation of any kind: an external C function can still allocate through its own allocator. Here the called C routine’s documented implementation performs no allocation.


## 5. Compile using matching object formats

~~~powershell
Set-Location labs/languages/native-language-boundary
cl /nologo /W4 /c boundary.c /Foboundary.obj
dmd --version
dmd -m64 callback_client.d boundary.obj -of=d-callback.exe
.\d-callback.exe
~~~

Run the commands separately from a compatible Microsoft C/DMD developer terminal on Windows. Stop if compilation fails. Do not pass the GNU boundary.o from the FreeBASIC exercise to this Microsoft-object example. On a supported Unix DMD target, compile boundary.c with the matching C compiler to boundary.o and link that object with dmd callback_client.d boundary.o -of=d-callback, then run ./d-callback. Consult your compiler’s target/runtime instructions when using a different D compiler.

Expect D callback checks passed: two attempted, one accepted and exit status zero. These are expected outcomes for this source, not a claim that a D compiler was available during the C test. If the linker cannot resolve bounded_progress_visit, rebuild the matching boundary object and inspect the declaration. Do not add arbitrary casts or disable checks to hide an ABI mismatch.


## 6. Trace early stopping precisely

For completed values one, two and three with totals four, the percentages are 25, 50 and 75. The first callback records 25 and returns zero. The second records 50 and returns 17. C stops, reports status two, and leaves accepted equal to one. The context records two attempts. The third callback never occurs. The recorded 50 remains a side effect even though that callback was not accepted.

This is why a visitor is not automatically a transaction. A transaction is a group of changes committed together or rolled back together. Validating all input before callbacks prevents a malformed later row from causing earlier callback effects, but it cannot undo arbitrary effects inside a callback. If an application needs all-or-nothing publication, collect a candidate result in its own storage and publish it only after successful completion.


## 7. Make controlled changes

1. Predict the values of status, accepted, calls and observed before running the reference source. Explain the distinction between row index and count.
2. In a separate copy, remove early stopping by setting stopAt to -1, and explicitly update the expected completion to status zero with three accepted and three attempted callbacks.
3. Make totals[2] zero and expect rejection before any callback runs. Explain why prevalidation is useful even though callback effects themselves are not transactional.
4. Try replacing &onProgress with a capturing delegate in a learning copy. A type error is useful feedback about the different representation. Restore the correct function pointer instead of forcing a cast.
5. Describe the lifetime protocol needed if a future API stores the callback: registration ownership, cancellation, draining outstanding calls and final release. None of those asynchronous guarantees should be inferred from this example.


## 8. Connect to Umicom Framework safely

A D client can remain thin by calling shared Framework services through public C headers and explicit wrappers. The wrapper should preserve UmiStatus, UTF-8 lengths, cancellation and release functions. Keep D classes, delegates, TypeInfo objects and runtime-owned descriptors on the D side unless a documented binding defines their representation and ownership. Compile-time reflection can help generate declarations, but generated code still needs ABI and lifetime tests.

The original bounded_progress function remains available, so simple clients do not need callbacks. Choose the smallest interface that fits the actual workflow. Synchronous iteration is useful for small bounded data; long-running work may need an asynchronous Framework service with explicit completion ownership. Do not emulate that by retaining pointers passed to this teaching function.


[Previous: Inspect types and check conversions without guessing](23-type-inspection-and-checked-casts.md)

[Next: Declare field metadata and inspect it at compile time](25-declare-and-inspect-field-metadata.md)
