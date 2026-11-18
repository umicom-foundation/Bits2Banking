<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/22-scope-guards-and-native-cleanup.md

PURPOSE:
Use scope guards to make cleanup paths visible

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use scope guards to make cleanup paths visible

[Course contents](index.md)
A function can leave a block by reaching its end, returning early or throwing an exception. When native storage belongs to that block, forgetting one exit path can leak it. D scope guards register actions for leaving a scope. They make cleanup visible next to resource acquisition, but still require the correct release function and a valid ownership contract.

~~~d
import core.stdc.stdlib : malloc, free;
import std.stdio : writeln;

bool inspectBuffer(bool refuse) {
    void* storage = malloc(16);
    if (storage is null) return false;
    scope(exit) free(storage);
    if (refuse) return false;
    ubyte* bytes = cast(ubyte*) storage;
    bytes[0] = 42;
    return bytes[0] == 42;
}

void main() {
    assert(inspectBuffer(false));
    assert(!inspectBuffer(true));
    writeln("Both exit paths exercised");
}
~~~

1. Save cleanup.d, compile it with your D compiler's debug checks, and run only after compilation succeeds.
2. Follow the allocation failure path: there is no owned allocation, so the function returns before registering a guard.
3. Follow refuse=true: the early return triggers scope(exit), which frees the allocation.
4. Follow refuse=false: the function reads its initialized byte and the same guard releases storage before the function leaves.
5. Draw an ownership table with one acquisition and one release for each successful allocation. There is no pointer returned to the caller.

malloc and free come from the C runtime through D declarations; they are not D keywords. is null checks pointer identity against absence. cast changes the pointer type but does not prove the allocation is large enough. This exercise uses a fixed 16-byte allocation and touches only its first byte. The pointer operations are deliberately low-level; do not mark the whole function @trusted just to silence a safety diagnostic without auditing its boundary.


## Understand the three guard conditions

Returning false is an ordinary return, not an exception. It triggers scope(exit) and does not automatically trigger scope(failure). A nonzero C status is also just a value. Therefore use explicit status handling for Framework failures; do not expect scope(failure) to notice them. Abrupt process termination cannot be treated as a normal cleanup path.

A void release such as free cannot fail. Some native Framework checked releases can return BUSY or an I/O error and retain ownership. A scope guard that discards that status could destroy the context too early or lose the only pointer needed for recovery. For such an API, design an explicit owner whose lifetime survives a refused release; a neat-looking scope guard is not a substitute.


## Connect to native development

The corresponding C practice is one clearly defined cleanup path with ownership flags or staged acquisition. Umicom production services remain C23/Assembly first. D can teach useful lifetime structure without requiring the Framework to adopt D's runtime or hiding native failures behind a language wrapper. These examples are authored and require D compilation on the intended platform.


## Scope-guard conditions

| Guard | When it runs | Typical use |
| --- | --- | --- |
| scope(exit) | Whenever control leaves this scope through ordinary scope unwinding | Release a locally owned resource |
| scope(success) | When leaving without exception unwinding | A success-path bookkeeping action |
| scope(failure) | When leaving because of exception unwinding | Rollback work tied to an exception |

## Further reading

- [D scope guard statements](https://dlang.org/spec/statement.html#scope-guard-statement)
- [D memory safety](https://dlang.org/spec/memory-safe-d.html)

## Continue practice

[Previous: Distinguish function pointers, delegates and C callbacks](21-functions-delegates-and-callback-lifetimes.md)

[Next: Inspect types and check conversions without guessing](23-type-inspection-and-checked-casts.md)
