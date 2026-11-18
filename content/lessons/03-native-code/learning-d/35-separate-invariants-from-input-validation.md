<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/35-separate-invariants-from-input-validation.md

PURPOSE:
Separate invariants from input validation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate invariants from input validation

[Course contents](index.md)

## What must always be true?

An invariant is a rule describing a valid object at its documented observation boundaries. Consider a request budget whose remaining count must be between zero and 1,024. D lets a struct declare an invariant for development-time contract checking. The program still needs explicit branches to refuse invalid external requests. This lesson compares those responsibilities instead of treating an assertion as user-input validation.


## Read the small value type

Open budget_invariant.d. RequestBudget is a struct, so it is a value type. It stores a private uint called remaining_. uint is D’s unsigned 32-bit integer type. Its default initialization is zero, which is valid for this design. The enum declaration introduces the compile-time maximum value 1,024. This is a manifest constant, not an enumeration of alternative states.

~~~d
struct RequestBudget
{
    private uint remaining_;
    enum uint maximum = 1024;
    invariant() { assert(remaining_ <= maximum); }
    @property uint remaining() const { return remaining_; }
    // Checked update methods follow in the complete source.
}
~~~


## Describe the invariant precisely

The invariant body asserts that the stored value does not exceed maximum. Nonnegativity follows from the unsigned type. With contract checks enabled, D uses invariants around relevant public member operations and other specified construction/destruction boundaries. It is not a background monitor that continuously watches every byte. Default struct initialization has its own rules; this type deliberately gives the default state a valid meaning. Consult the language specification for the precise boundary rules when designing more complex types.


## Inspect backing state inside the invariant

The invariant reads remaining_ directly. Do not call a public non-static member method from an invariant, directly or indirectly: that call can itself require invariant checking and create recursion. In particular, do not rewrite this invariant to call the public remaining getter simply because getters look harmless. An invariant should state the internal rule without mutating the object or invoking public behavior.


## Use a read-only property for callers

@property marks remaining as a property function. Calling code reads budget.remaining. The trailing const means this member function observes the object through a const view; it does not make every instance immutable. There is no setter in this example. Private in D primarily protects the module boundary, so other code in the same module can still be trusted with access according to D’s visibility rules. It is not a security barrier against malicious native memory access.


## Refuse invalid input explicitly

Try to consume four operations when only three remain. That is an ordinary refused request, not evidence that an already valid object was internally corrupted. tryConsume therefore returns false before changing the field. tryReset similarly checks its upper bound before assignment. These branches remain part of the program even if invariant and assertion checks are disabled by a build configuration.

~~~d
bool tryConsume(uint count)
{
    if (count > remaining_) return false;
    remaining_ -= count;
    return true;
}
~~~


## Compare the responsibilities


| Mechanism | Purpose | Response |
| --- | --- | --- |
| if (requested > maximum) | Admit or refuse an external request | Return false; preserve current state |
| invariant() with assert | Detect a broken internal rule during checked execution | Report a contract failure |
| @property remaining | Expose observation through a small interface | Return the current count |
| unittest | Exercise expected behavior and boundaries | Fail when an expectation is violated |


## Avoid side effects inside required assertions

The unittest block uses assertions to check its test operations. The normal main function performs required updates in ordinary if expressions, not inside assert. This distinction matters: a build can disable assertions, removing their expressions from execution. If the application depends on an assignment or function call hidden inside an assertion, disabling checks can change the program’s essential work. Assertions should verify application work, not be the only place that work happens.


## Compile with checks enabled

Use the D installation from the first lesson. The -unittest option includes the unittest block. -checkaction=context asks DMD to include useful context when checks fail. Do not add -release for this learning exercise. Run the two commands separately and stop on a build error. The compiler examples in this course require qualification in your installed D environment; a native C test result does not validate D source.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context budget_invariant.d -of=budget_invariant.exe
.\budget_invariant.exe
~~~


## Walk through the expected results

1. Default initialization starts at zero.
2. tryReset(5) succeeds, then tryConsume(2) leaves three.
3. tryConsume(4) and tryReset(1025) both return false and preserve three.
4. The unit tests also consume exactly the remaining amount, consume zero, and exercise the maximum allowed value.
5. The normal program prints Checked admission preserved 3; invariant documents 0..1024. It returns a nonzero code if ordinary admission behaves incorrectly.


## Do not confuse language checking with memory safety

The private field, getter and invariant make the design clearer, but do not make arbitrary foreign memory safe. D code that calls C still needs correct pointer lifetimes, sizes, alignment and ownership. A native Framework service should validate its own public inputs and return its own explicit status. A D wrapper can express additional contracts around that boundary, but it must not assume a D struct’s layout or invariant checks are understood by a C caller.


## Connect this to reflection

The earlier reflection lessons inspect field names, types and declared attributes at compile time. Reflection can help generate documentation or repetitive checks, but it does not infer an object’s intended invariant. The rule remaining <= maximum is a design decision. If metadata generates validation, inspect the generated logic and test the boundary values just as you would handwritten code. A reflected field list is not proof that an update preserves a cross-field rule.


## Practice

1. Explain why zero is a valid default state for this struct.
2. Write down the state before and after a refused request. It must be unchanged.
3. Describe what is lost when contract checking is disabled and what explicit admission still protects.
4. Explain why an invariant must not call the public getter.
5. Identify one operation in an application that must occur outside an assertion because the application needs it even in a release configuration.


## Official references


- [D struct invariants](https://dlang.org/spec/struct.html#struct-invariants)
- [D property functions](https://dlang.org/spec/function.html#property-functions)
- [D contract programming](https://dlang.org/spec/contracts.html)


[Previous: Distinguish lazy evaluation from caching](34-distinguish-lazy-evaluation-from-caching.md)

[Next: Separate modules, visible names and linked code](36-separate-modules-names-and-linked-code.md)
