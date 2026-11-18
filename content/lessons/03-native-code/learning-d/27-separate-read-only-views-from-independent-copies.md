<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/27-separate-read-only-views-from-independent-copies.md

PURPOSE:
Separate read-only views from independent copies

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate read-only views from independent copies

[Course contents](index.md)
Read-only can describe how one part of a program accesses data without saying that the data can never change. D makes this distinction explicit with const and immutable. This lesson revisits slices with a concrete experiment: one mutable array, one read-only view, one mutable copy and one immutable copy. You will predict which values change, explain why, and connect the result to ownership at a native Framework boundary.


## 1. Draw the storage before reasoning about qualifiers

~~~d
int[] original = [6, 7];
const(int)[] view = original;
int[] independent = view.dup;
immutable(int)[] frozen = view.idup;
~~~

An array slice is a descriptor referring to a sequence of elements. Assigning original to view copies the descriptor and preserves the reference to the same two elements. It does not make another array of integers. The .dup property creates a new mutable array containing copies of the integer elements. .idup creates an independent immutable copy. This example uses the normal D runtime and its managed allocations.

~~~text
original descriptor ----+
                        +----> shared elements [6, 7]
view descriptor --------+

independent descriptor ------> separate elements [6, 7]
frozen descriptor -----------> separate immutable elements [6, 7]
~~~

An arrow means that a descriptor refers to storage. Two arrows reaching the same storage represent aliases. The boxes in this mental diagram are not actual pointers you should print or serialize. The representation is a teaching aid for understanding which writes affect which observations.


## 2. Change the original through its mutable alias

~~~d
original[0] = 8;
assert(view[0] == 8);
assert(independent[0] == 6 && frozen[0] == 6);
~~~

The assignment is legal because original provides mutable access. view immediately observes eight at index zero because it refers to the same elements. const prevents writing through view; it did not remove the original mutable alias. The independent copies still contain six because their integer elements occupy different storage.

This distinction is useful when designing a function that promises not to modify its input. A const parameter can express that promise for the callee’s view. It does not automatically promise that another thread or alias will leave the input unchanged throughout the call. Concurrency, synchronization and ownership still need explicit rules. Do not use const as a substitute for a lock or an immutable snapshot.


## 3. Modify the independent mutable copy

~~~d
independent[1] = 9;
assert(original[1] == 7 && frozen[1] == 7);
~~~

This changes only the mutable copy. The lab uses integer elements, so copying them creates independent values. Do not generalize that observation into a claim that .dup recursively clones every object graph. Arrays of references or aggregates containing pointers need a separate analysis of what was copied and what is still shared. Deep copying and immutable construction have their own type constraints.


## 4. Read the exact qualifier spelling

const(int)[] means a mutable slice descriptor whose elements are read-only through that view. The descriptor can be rebound to another suitable slice. That is different from declaring the entire descriptor and its reachable data through a const-qualified array type. Parentheses specify which type is qualified, so they are part of the contract rather than decoration.

~~~d
view = original[1 .. $];
assert(view.length == 1 && view[0] == 7);
~~~

The half-open range starts at index one and stops before $. In this indexing context, $ denotes the length of original. The new view therefore contains the final element only. Rebinding the descriptor does not edit that element. Its contents remain read-only through view.

D const and immutable are transitive through the qualified type: they apply through relevant indirections rather than merely marking one superficial integer field. immutable promises that the data cannot change through any legal alias after construction. A mutable array cannot generally be reinterpreted as immutable merely by adding a qualifier while keeping arbitrary mutable aliases alive. The explicit .idup in this exercise constructs an independent immutable copy.


## 5. Ask the compiler which writes are admitted

~~~d
static assert(!__traits(compiles, view[0] = 1));
static assert(!__traits(compiles, frozen[0] = 1));
~~~

__traits(compiles, expression) asks whether an expression is semantically accepted. The exclamation mark negates that answer, and static assert requires the result to be true during compilation. These lines check that writes through the two qualified views are rejected. They do not execute either assignment, and they do not turn a rejected write into a runtime exception.

Avoid casting away const or immutable to force a write. Such a cast can violate the actual storage contract and create undefined or invalid behavior. Choose a mutable copy when mutation is required, and keep the copied data’s ownership explicit. Compiler reflection is valuable for checking assumptions; it is not a license to bypass them.


## 6. Compile and run the complete example

1. Open labs/languages/native-language-boundary/readonly_views.d after completing the D setup lesson. Read the whole main function and its assertions.
2. Predict all four output arrays before compiling. Write the prediction beside the storage diagram on paper.
3. Run the DMD commands below without a release option that disables the exercise’s assertions. If the compiler is unavailable, finish the setup instead of treating a source review as a successful run.
4. Expect the original array [8, 7], the mutable copy [6, 9], the immutable copy [6, 7], and the rebound read-only view [7].
5. Compare every result with the diagram. A difference should be investigated at the assignment or copy boundary rather than explained away as garbage-collector behavior.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -g readonly_views.d -of=readonly_views.exe
.\readonly_views.exe
~~~

This file imports std.stdio for writeln and uses the normal D runtime. It is not a BetterC or freestanding Kernel example. DMD, LDC and GDC have different command-line switches; use the selected compiler’s documented equivalents. The sample needs independent D compilation and execution before any claim that it passed on a particular target.


## 7. Design a native boundary around lifetime, not just spelling

A C function receiving const int * promises not to write through that pointer in ordinary source use, but C const does not express all of D’s transitive type relationships. A D slice also carries a length and has a different representation from a lone C pointer. Pass the pointer, element count, integer width and lifetime using a documented C ABI. Never cast a D slice descriptor into an unrelated Framework structure.

If a native worker retains input after a call returns, a temporary read-only view is not sufficient ownership. Either keep the underlying allocation alive until the worker has finished or copy the input into a Framework-owned operation with an explicit release path. For short synchronous calls, document that the input is borrowed only for the call and must remain stable. The same distinction appears in the Framework training tape, which copies admitted target and selection arrays instead of retaining caller stack pointers.


## 8. Compare three fixed-value ideas

FreeBASIC Const in the companion lesson names a constant expression. Umicom C const int marks a local that source code cannot update after its runtime initializer. D const describes a read-only view, while immutable describes unchangeable data. These mechanisms can all help make intent visible, but their aliasing and evaluation rules differ. Treat a cross-language translation as a contract review, not a spelling replacement.


## 9. Practice deliberate changes

1. In a separate learning copy, replace independent = view.dup with independent = original. Predict which later assertion fails because the new slice aliases the original.
2. Restore .dup. Change original[1] before rebinding view and predict the final one-element view.
3. Add view[0] = 1 as an ordinary statement and compile. Observe the compile-time refusal, then remove it.
4. Create a second variable referring to frozen and explain why it still cannot legally mutate the immutable elements.
5. Describe what additional ownership rules would be needed if the elements were references to mutable objects rather than integers. Do not claim the current exercise tested that case.


## Which guarantee is present?

| Construct | Independent integer storage? | Can this view write elements? | May another mutable alias change observed data? |
| --- | --- | --- | --- |
| original | Original allocation | Yes | Yes, if aliases exist |
| view = original | No | No | Yes |
| view.dup | Yes for these integer elements | Yes | Only aliases to that new mutable copy |
| view.idup | Yes for these integer elements | No | No legal mutable alias to the immutable data |

## Further reading

- [D specification: const and immutable](https://dlang.org/spec/const3.html)
- [D specification: arrays](https://dlang.org/spec/arrays.html)
- [D specification: traits](https://dlang.org/spec/traits.html)

[Previous: Select code before the program runs](26-select-code-before-the-program-runs.md)

[Next: Look up records without confusing storage with learning](28-look-up-records-with-associative-arrays.md)
