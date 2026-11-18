<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/16-garbage-collection-and-memory-contracts.md

PURPOSE:
Understand D memory management and safety attributes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Understand D memory management and safety attributes

[Course contents](index.md)
Garbage collection reclaims some allocations after they are no longer reachable. It does not make unlimited allocation cheap or guarantee a pause duration. A leaked operating-system handle, a retained reference to a huge array and a C allocation never freed are different problems. Changing a language does not eliminate all three.

~~~d
int clampPercent(int value) @safe pure nothrow @nogc
{
    if (value < 0) return 0;
    if (value > 100) return 100;
    return value;
}
unittest
{
    assert(clampPercent(-1) == 0);
    assert(clampPercent(45) == 45);
    assert(clampPercent(101) == 100);
}
void main() {}
~~~

1. Save as memory_contract.d. Compile with dmd -w -unittest -g memory_contract.d and run it. Success produces no assertion failure.
2. Change one expected value deliberately and verify that the test catches it. Restore it.
3. Explain why this function needs no allocation: it reads one integer and returns one integer.
4. Keep the attributes and experiment with adding an operation that allocates through the garbage collector. Read the compiler’s rejection rather than deleting @nogc immediately.

@nogc restricts GC allocation; it does not mean no C malloc, no system calls, no blocking and no resource leak. nothrow restricts exception throwing, not all possible program faults. @safe restricts memory-unsafe operations in checked code. @system allows operations needing manual review. @trusted marks a programmer-reviewed boundary callable from safe code; it is an obligation, not a mechanism that verifies arbitrary pointer code.

pure constrains dependencies on mutable external state. scope can express a bounded lifetime context, and scope(exit) runs cleanup when a scope is left. A C allocation must be released by its matching allocator contract. Do not let a GC-managed reference disappear while a C service retains a raw pointer unless the binding explicitly keeps the storage alive.


## Apply to Umicom

Keep Framework buffer capacities, ownership and cancellation visible in a D binding. A native Media preview should have a maximum working set and release old frames promptly. Those properties require measurement and tests even when the wrapper is written in D. The lesson function is a small example, not proof of whole-application memory safety.


## Continue learning

[Previous: Choose a struct, class or interface](15-structs-classes-and-interfaces.md) · [Course contents](index.md) · [Next: Use templates and compile-time evaluation](17-templates-and-compile-time-work.md)
