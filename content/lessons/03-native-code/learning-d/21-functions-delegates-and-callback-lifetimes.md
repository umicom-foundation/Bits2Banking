<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/21-functions-delegates-and-callback-lifetimes.md

PURPOSE:
Distinguish function pointers, delegates and C callbacks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish function pointers, delegates and C callbacks

[Course contents](index.md)

## Before you begin

Draw one box for a function address and another for a captured local variable. Predict what must survive if the callback runs after the caller returns.
A callback is a function supplied for another operation to call later. Two callable values can look similar at the call site but carry different data. A function pointer identifies callable code. A D delegate also carries a context, which may refer to an object or captured local values. That distinction matters when connecting to C.

~~~d
import std.stdio : writeln;

int twice(int value) { return value * 2; }

void main() {
    int function(int) plain = &twice;
    int offset = 3;
    int delegate(int) addOffset = (int value) => value + offset;
    assert(plain(4) == 8);
    assert(addOffset(4) == 7);
    offset = 5;
    assert(addOffset(4) == 9);
    writeln("Function and delegate checks passed");
}
~~~

1. Save callbacks.d in your D practice folder. The function twice is declared outside main and does not refer to main's local variables.
2. Compile with dmd -g -checkaction=context callbacks.d, then run .\callbacks.exe after compilation succeeds. With LDC or GDC, use that compiler's documented equivalent debug/check options.
3. Trace plain(4): it calls twice and returns 8.
4. Trace addOffset(4) before and after assigning 5 to offset. The captured context supplies the current offset.
5. Explain why the delegate is more than the address of twice. Do not cast the delegate to a C function pointer to make an incompatible declaration compile.

The type int function(int) describes one integer parameter and one integer result. & takes the address of twice. The type int delegate(int) includes a context. The arrow expression creates a callable expression body. assert checks the expected result; production validation must still handle invalid inputs independently of checks that a release configuration might remove.


## Use an explicit C boundary

C libraries commonly accept a callback function plus a void* context. An adapter can place reviewed state in a separately owned object and pass its address as context. The callback needs the exact C linkage, parameter widths, return convention and thread requirements from the native header. Those details cannot be inferred from this standalone D function-pointer example.

If a callback runs only during the call, its context must outlive that call. If the service retains it, the context must remain alive until unregister, cancellation and worker completion have actually succeeded. A pointer stored only in a foreign library may not keep a D garbage-collected object rooted. Use a reviewed rooting or native-owned-context design and release it exactly once at the documented retirement boundary.

Do not let a D exception unwind through a C frame whose contract does not support it. Convert expected failures into the native API's status representation. nothrow is a declared effect constraint, not permission to ignore failed operations. For asynchronous Framework integration, retain ownership in Framework and keep D's adapter thin.


## Exercise

Draw three boxes: the native callback registration, its code address and its context object. Mark who owns each one and the exact event after which the context can be released. If the answer is only 'after pressing Cancel', the lifetime design is incomplete. This lesson does not implement a new Framework registration API or claim BetterC compatibility for std.stdio and capturing closures.


## Further reading

- [D function and delegate declarations](https://dlang.org/spec/function.html)
- [D interfaces to C](https://dlang.org/spec/interfaceToC.html)

## Continue practice

[Previous: Navigate D keywords and language concepts](20-keyword-and-concept-map.md) · [Next: Use scope guards to make cleanup paths visible](22-scope-guards-and-native-cleanup.md)
