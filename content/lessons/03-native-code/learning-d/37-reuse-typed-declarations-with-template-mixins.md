<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/37-reuse-typed-declarations-with-template-mixins.md

PURPOSE:
Reuse typed declarations with template mixins

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Reuse typed declarations with template mixins

[Course contents](index.md)

## Start with a small duplication problem

Imagine two tools that count accepted requests. A preview tool permits three requests, while an export tool permits six. Each needs a current count, a remaining count and a function that refuses an addition exceeding its limit. Copying the same declarations into two structures makes it easy to correct one and forget the other. A D template mixin can describe that declaration pattern once and insert a typed instance into each receiving structure. This exercise owns only integers. It does not run jobs, allocate images or enforce a real service quota.

1. Open labs/languages/native-language-boundary/typed_counter_mixins.d. Locate BoundedCount, PreviewCount and ExportCount.
2. Read the two limits, 3 and 6, before looking at the method bodies.
3. Predict that creating one PreviewCount and one ExportCount produces two independent counters starting at zero.


## Separate a template from a runtime value

A template describes code parameterized by compile-time arguments. Compile time is when the compiler processes source to produce a program. Runtime is when that program executes. In BoundedCount(uint Limit), Limit is an unsigned 32-bit value supplied when the template is used. BoundedCount!3 selects a limit of three. The exclamation mark introduces the template argument; it is not the logical “not” operation in this context. This example uses a single argument, so parentheses are optional in that spelling. The compiler knows each limit when it creates the corresponding declarations.

~~~d
mixin template BoundedCount(uint Limit)
{
    static assert(Limit > 0U, "A counter needs a positive limit");
    private uint count_;
    // Methods follow in the complete source.
}

struct PreviewCount { mixin BoundedCount!3; }
struct ExportCount { mixin BoundedCount!6; }
~~~


## Understand what mixin adds to a structure

The mixin template declares a reusable group of declarations. A mixin statement selects it at a receiving scope. Here that scope is a struct, a value type whose instances contain their own fields. The field and methods become available through each receiving type. PreviewCount and ExportCount remain different types. Neither derives from the other, and there is no shared global counter. This is declaration reuse, not class inheritance, a runtime plug-in or a download-and-execute mechanism. Names introduced by a mixin can interact with names already in its receiving scope; keep the pattern small and its names deliberate.


| Spelling | Meaning in this exercise |
| --- | --- |
| mixin template | Declare a reusable typed group of declarations |
| uint Limit | Supply a compile-time unsigned integer parameter |
| static assert | Reject an invalid template configuration during compilation |
| mixin BoundedCount!3 | Insert the declarations configured for limit three |
| struct PreviewCount | Define a value type with independent instance state |


## Follow the bounded arithmetic

count_ starts at zero under normal default initialization. Every accepted operation must keep it no larger than Limit. To add amount safely, compare amount with Limit minus count_. If it is larger, return false before modifying the field. Otherwise add it and return true. Subtraction is safe under this maintained invariant, which means a condition expected to stay true. Checking after addition would be too late if the addition overflowed. The final underscore in count_ is a naming convention for backing storage, not a special language operation.

~~~d
bool tryAdd(uint amount) @safe pure nothrow @nogc
{
    if (amount > Limit - count_) return false;
    count_ += amount;
    return true;
}
~~~


## Read safety attributes without promising too much

The attributes describe enforceable language restrictions on these small methods. @safe excludes operations the language classifies as unsafe in that context. pure restricts access to unrelated mutable state; it does not mean a method cannot change its own instance. nothrow prevents throwing D exceptions through that function’s interface. @nogc prevents operations requiring the D garbage collector from that function. None of these makes the counter atomic, thread-safe, persistent or a security boundary. The complete client uses std.stdio for printing and is built with the normal D runtime; it is not advertised as a BetterC executable.


| Method | State effect | Result |
| --- | --- | --- |
| value() const | Reads count_ | Current count |
| remaining() const | Reads count_ and Limit | Unused capacity |
| tryAdd(amount) | Changes count_ only on acceptance | true or false |


## Keep encapsulation and initialization assumptions explicit

private marks the field as implementation storage, but D privacy is module-based rather than a promise that no code elsewhere in this source module can access it. The example’s module deliberately changes the count only through tryAdd. If code bypasses that rule and sets count_ above Limit, the arithmetic assumption no longer holds. Do not initialize raw memory as if it were a valid counter, use unsafe casts or treat arbitrary file bytes as an instance. The static assertion checks the chosen positive limit, while the runtime branch checks each requested addition. These are different stages of validation.


## Trace independent instances and a value copy

preview.tryAdd(2) succeeds for the limit-three counter. A second addition of two is refused and leaves the value at two. exportCount starts separately at zero and can accept six. An attempted addition of uint.max is refused because there is no remaining capacity. uint.max is the largest value representable by uint; it is useful for checking an extreme request. Finally auto copy = preview creates another instance with the current numeric field value. Adding one to copy reaches three while preview stays two. This independent copying follows from this pointer-free value representation. A structure containing a slice or pointer may still share the referenced storage after copying.


| Operation | Accepted? | Relevant value afterward |
| --- | --- | --- |
| preview.tryAdd(2) | Yes | preview = 2 |
| preview.tryAdd(2) again | No | preview = 2 |
| exportCount.tryAdd(6) | Yes | exportCount = 6 |
| exportCount.tryAdd(uint.max) | No | exportCount = 6 |
| copy = preview; copy.tryAdd(1) | Yes | copy = 3; preview = 2 |


## Compile with checks, then run normal branches

Use a PowerShell terminal with the DMD compiler available. The -unittest option includes the unittest block, and -checkaction=context requests contextual failure reporting. The normal main function also checks acceptance and state through ordinary if branches and nonzero return codes. That keeps the demonstration’s observations visible even apart from unit assertions. The commands below assume the shown checkout path. Run separately and stop if compilation fails; do not execute an older binary as proof that the changed source works.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
dmd -unittest -checkaction=context typed_counter_mixins.d -of=typed-counter-mixins.exe
.\typed-counter-mixins.exe
~~~


## Compare the observations

Expect the three lines below. If dmd is not recognized, return to the compiler setup lesson and check the current terminal’s tool path. If a template error mentions the positive limit assertion, inspect the argument following the exclamation mark. If declarations conflict, check whether the receiving struct already has a field or method with the same name. Do not suppress a failed check merely to obtain output. These are D teaching sources requiring their own compiler and runtime qualification; Framework C tests do not establish that qualification.

~~~text
preview=2 remaining=1
export=6 remaining=0
copy=3; preview stays 2
~~~


## Connect mixins to reflection and Framework use

Reflection inspects information about code or types. A template mixin supplies declarations; reflection can subsequently inspect the receiving type. For example, a compile-time hasMember query can ask whether PreviewCount has a method named tryAdd. That query does not prove the method enforces the correct budget. Behavioral checks still matter. A D tool could use typed patterns and reflection to generate reviewed bindings or inspect project metadata. Reusable production behavior in Umicom remains Framework-owned C23/Assembly. A D-facing wrapper should call a documented C interface with explicit layouts and ownership instead of assuming a mixed-in D structure is automatically ABI-compatible.

~~~d
static assert(__traits(hasMember, PreviewCount, "tryAdd"));
static assert(__traits(hasMember, ExportCount, "remaining"));
~~~


## Distinguish typed mixins from string mixins

D also has string mixins, which interpret a compile-time string as source code. That is a different mechanism from this typed declaration template. This lesson builds no source string and accepts no text from a model, file or network to become executable code. Prefer a typed reusable function or template when it expresses the requirement clearly. Code generation can reduce repetitive declarations, but it also needs readable diagnostics, bounded generated output and independent review of the resulting contract. It does not automatically improve runtime speed or memory use.


## Practice with changed limits and refused inputs

Change one dimension of the exercise at a time so a failure has a clear meaning. A limit change is a compile-time configuration change; changing the count is a runtime operation. Record the compiler version and exact source when comparing results. This small counter is intentionally not synchronized, so it is unsuitable as a shared multi-threaded request limiter without a separately designed synchronization owner.

1. Create a third struct using BoundedCount!1. Predict acceptance for add one, then refusal for another one.
2. Try BoundedCount!0 in a separate exercise file and expect the compile-time assertion to reject it. Do not replace the working example to hide that diagnostic.
3. Add zero to a valid counter and predict that it succeeds while leaving the value unchanged.
4. Add the two hasMember assertions and explain why their success proves names exist, not that their implementations are correct.
5. Explain why the output methods can be const while tryAdd cannot be const.


## Language reference


- [D template mixins](https://dlang.org/spec/template-mixin.html)
- [D compile-time traits](https://dlang.org/spec/traits.html)


[Previous: Separate modules, visible names and linked code](36-separate-modules-names-and-linked-code.md)

[Next: Follow nested static-array copies](38-follow-nested-static-array-copies.md)
