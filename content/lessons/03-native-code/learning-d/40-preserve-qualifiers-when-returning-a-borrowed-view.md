<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/40-preserve-qualifiers-when-returning-a-borrowed-view.md

PURPOSE:
Preserve qualifiers when returning a borrowed view

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Preserve qualifiers when returning a borrowed view

[Course contents](index.md)

## A small function with an important promise

This lesson returns the first few bytes of an existing array without allocating another byte buffer. The caller may supply writable data, a read-only view, or immutable data. The returned view should preserve that permission. You will use D’s inout type constructor, then follow the backing storage through concrete mutations and compile-time checks. This builds on the earlier lesson about read-only views and copies. It is a language design exercise, not a new Framework binary interface or an implementation of a model loader.


## Separate the array from its view

The example begins with three bytes stored in a local static array. Ubyte means an unsigned eight-bit integer. The [3] gives the array a fixed length. The empty brackets in owner[] form a slice over those elements. A slice describes a region of existing array storage. Copying that descriptor does not copy the elements. Here every view is used inside the same scope as owner, so the backing array remains alive.

~~~d
ubyte[3] owner = [1, 2, 3];
auto mutableView = prefixView(owner[], 2);
~~~


## Read the function signature slowly

Prefix means the beginning of a sequence. Wanted is the requested number of bytes. The function uses the smaller of wanted and the available length, then returns the half-open slice beginning at zero and ending just before count. Size_t is the unsigned type used for sizes on the target platform. The conditional expression chooses one of two values. No element is created or copied by the return expression.

~~~d
inout(ubyte)[] prefixView(inout(ubyte)[] source, size_t wanted)
    @safe pure nothrow @nogc
{
    const count = wanted < source.length ? wanted : source.length;
    return source[0 .. count];
}
~~~


## What inout connects

Inout is a qualifier wildcard connecting the input element type to the returned element type. For this one-parameter function, writable input yields a writable view, const input yields a const view, and immutable input yields an immutable view. It avoids writing three bodies with the same slicing logic. It does not mean console input/output, an output parameter, a mutable reference parameter, or a permission to remove a qualifier. The ordinary out and ref parameter forms taught earlier are different constructs.


## Predict the three result types


| Input expression type | Returned view type | May this view write an element? |
| --- | --- | --- |
| ubyte[] | ubyte[] | Yes, while the backing storage is valid. |
| const(ubyte)[] | const(ubyte)[] | No. |
| immutable(ubyte)[] | immutable(ubyte)[] | No; the underlying data is immutable. |


## First observe a mutable alias

The first returned view selects two elements of owner. Assigning seven through mutableView[0] therefore changes owner[0] to seven. There is still only one original byte array. If you expected owner to remain one, you were thinking of an independent copy. This function intentionally returns a borrowed view; a separate copy would need a different operation and an explicit storage owner.

~~~d
auto mutableView = prefixView(owner[], 2);
mutableView[0] = 7;
assert(owner[0] == 7 && mutableView.length == 2);
~~~


## Next observe a const alias

ReadOnly is a view of the same owner array with element writes disallowed through that view. Requesting 99 bytes is clamped to the available three. The program then changes owner[0] to eight through its original mutable access. ReadView observes eight. Const limits this access path; it has not made an independent snapshot. This distinction matters when a preview, parser or model job borrows a buffer while another owner may still change it.

~~~d
const(ubyte)[] readOnly = owner[];
auto readView = prefixView(readOnly, 99);
owner[0] = 8;
assert(readView[0] == 8 && readView.length == 3);
~~~


## Finally observe immutable input

The frozen array is initialized separately with three, four and five. Its immutable elements cannot later be changed. PrefixView preserves that qualifier in its result. The mutable owner used earlier is a different object; changing it has no effect on frozen. Do not cast a mutable alias to immutable merely to make a signature match. Establish the real storage contract rather than concealing an alias that can still write.

~~~d
immutable ubyte[3] frozen = [3, 4, 5];
auto frozenView = prefixView(frozen[], 2);
assert(frozenView[0] == 3 && frozenView.length == 2);
~~~


## Trace values and lengths together


| View at the final observation | Backing storage | Length | First value |
| --- | --- | --- | --- |
| mutableView | owner | 2 | 8 |
| readView | owner | 3 | 8 |
| frozenView | frozen | 2 | 3 |
| prefixView(owner[], 0) | owner, empty view | 0 | No element may be indexed. |


## Use compile-time reflection as a check

Typeof asks for the type of an expression. The is expression compares it with an expected type here. Static assert asks the compiler to reject the source if that condition is false. These checks verify the inferred interface without needing a runtime type-inspection service. The __traits(compiles, expression) query asks whether an expression would compile. The program uses it to confirm that writing through readView and frozenView is refused.

~~~d
static assert(is(typeof(mutableView) == ubyte[]));
static assert(is(typeof(readView) == const(ubyte)[]));
static assert(!__traits(compiles, readView[0] = 1));
~~~


## Understand what the function attributes do not claim

The attributes constrain the function: @safe enables the language’s checked safety rules, pure constrains effects, nothrow forbids ordinary thrown exceptions, and @nogc forbids GC allocation in this function. These are not a claim that the complete executable never allocates, that it cannot fail, or that it is safe under arbitrary foreign-code behavior. The console program still uses normal D runtime support and std.stdio. It is not built with BetterC. Keep the scope of each promise clear when explaining a function to another developer.


## A view does not extend lifetime by itself

The supplied function returns a slice of caller-provided storage. Its safe use depends on that storage remaining alive and on the wider language and caller lifetime rules. The example retains the local arrays for all observations and does not return their slices from main. Do not generalize the exercise into returning pointers to dead stack objects, freeing a native buffer while views remain, or letting a callback retain temporary storage. At a C boundary, document ownership and validity duration explicitly; qualifiers alone cannot repair a broken lifetime.


## Run the source with the intended D compiler

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context -of=qualifier_preserving_views.exe qualifier_preserving_views.d
& .\qualifier_preserving_views.exe
~~~

1. Open the native-language-boundary lab folder in your Bits2Banking checkout.
2. Check that dmd names the D compiler rather than an unrelated alias. Use your installed compiler’s version command to record its identity.
3. Build qualifier_preserving_views.d with unit tests and checks enabled.
4. Stop on a compile failure; do not run a retained executable from an earlier source version.
5. Run the newly built program. Compare both values and lengths with the expected output.


## Expected observations and empty views

The unit tests also pass a zero-length input with a very large requested size. Clamping returns an empty view; there is no first element to read. This is why bounds reasoning should begin with lengths and ranges rather than assuming a nonempty pointer. A length-zero success is a legitimate empty selection, not necessarily a null result or an error.

~~~text
mutable=8 const=8 frozen=3
lengths=2,3,2
empty length=0
~~~


## Debug a qualifier mismatch without a cast

1. If the mutable result is unexpectedly const, inspect the type of the actual argument rather than only the original variable declaration.
2. If a write through readView compiles, inspect whether it was accidentally declared as a mutable slice or copied into a different mutable buffer.
3. If a static assert fails, print or inspect the compiler’s reported type and compare element qualification with descriptor qualification.
4. If an attribute is rejected, identify the operation that violates it. Do not remove every attribute just to obtain an executable.
5. If no D compiler is available, keep the source and mark compilation pending. Course discovery checks and native C tests cannot establish D compiler acceptance.


## Apply the idea to Framework API design

A reusable media or training API should distinguish writable ownership from read-only borrowing. D can express some qualifier relationships in one function signature. C interfaces can make the same design intention explicit through const-qualified pointers, separate mutable and read-only entry points, capacity parameters and documented lifetimes. The existing Framework image-view and training-reader services remain C-owned. This lesson is useful for reviewing their contracts; it does not require moving them into D or exposing a D slice descriptor through the C ABI.


## Practice and state the limits

The original example has been authored and reviewed against the language reference. D compilation and execution remain unverified in the current mirror environment. There is no claim of a new Umicom C language feature, an installed SDK binding or whole-application allocation freedom.

1. Request one, two, three and four bytes from the three-byte owner and predict each returned length.
2. Change an element through mutableView and explain which other views observe it.
3. Create an independent copy using the separate copy operation from the earlier lesson, then explain why that copy differs from a const alias.
4. Try the refused write only inside __traits(compiles, ...) and observe the compile-time Boolean instead of adding invalid active source.
5. Describe a scenario in which const data access is useful but does not provide a stable snapshot.


## Official references


- [D type qualifiers and inout](https://dlang.org/spec/const3.html#inout)
- [D function attributes and parameter contracts](https://dlang.org/spec/function.html)
- [D compile-time traits](https://dlang.org/spec/traits.html)


[Previous: Separate text bytes, code points and display](39-separate-text-bytes-code-points-and-display.md)

[Next: Inspect layout without serializing padding](41-inspect-layout-without-serializing-padding.md)
