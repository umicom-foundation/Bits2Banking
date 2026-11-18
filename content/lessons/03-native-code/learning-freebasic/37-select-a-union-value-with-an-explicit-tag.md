<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/37-select-a-union-value-with-an-explicit-tag.md

PURPOSE:
Select a union value with an explicit tag

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select a union value with an explicit tag

[Course contents](index.md)

## One slot, two possible meanings

Suppose an educational calculator stores either a whole number such as 42 or a fractional number such as 12.5. You could keep both fields in an ordinary record, but only one is meaningful at a time. A union lets the alternatives share storage. It does not remember which meaning you intended. This lesson adds a separate tag and checks that tag before reading the stored value.

1. Review records, enums, function arguments and the preceding layout lesson.
2. Open the complete tagged_number.bas example.
3. Predict what should happen when a caller asks for a fractional value from a record that contains a whole number.


## Name the alternatives

The example uses an explicit enumeration. Invalid is a deliberately unselected state. Whole and Fractional name the two supported alternatives. Explicit requires qualified names such as NumberKind.Whole, which makes the source easier to read when several enums have similarly named members. An enum organizes names; it does not prove that every integer received from a file or cast belongs to the declared set.

~~~basic
Enum NumberKind Explicit
    Invalid = 0
    Whole = 1
    Fractional = 2
End Enum
~~~


## Understand the overlapping payload

NumberPayload declares a LongInt view and a Double view of common storage. LongInt is the whole-number alternative; Double is the floating-point alternative. Writing one may replace the bytes visible through the other. This is storage sharing, not a conversion operation. The exercise never reads through the wrong view and does not depend on the bit pattern that such a read might expose.

~~~basic
Union NumberPayload
    wholeValue As LongInt
    fractionalValue As Double
End Union
~~~


## Keep the tag outside the overlap

TaggedNumber is an ordinary Type containing the tag and the union payload. The tag has its own storage, so writing a payload does not overwrite the selection. Its total record size may include alignment padding. Saving the raw record is therefore not a portable file format, even when two compilers happen to report the same size.

~~~basic
Type TaggedNumber
    kind As NumberKind
    payload As NumberPayload
End Type
~~~


## Construct a complete candidate

MakeWhole creates a local candidate, writes its whole-number payload, then sets the matching tag and returns the complete record. MakeFractional does the same for the other alternative. A caller should use these functions rather than changing the tag independently. The ordering is an ownership discipline for this single-threaded example; it is not an atomic publication protocol for concurrent readers.

~~~basic
Function MakeWhole(ByVal value As LongInt) As TaggedNumber
    Dim candidate As TaggedNumber
    candidate.payload.wholeValue = value
    candidate.kind = NumberKind.Whole
    Return candidate
End Function
~~~


## Check before reading

TryWhole first inspects the tag. If the value is not Whole, it returns False before reading the payload or writing the caller's result. A successful call copies the admitted member and returns True. TryFractional has the corresponding contract. The input record and output variables in the laboratory are separate; the example does not ask a read-only input reference to alias writable output.

~~~basic
Function TryWhole(ByRef value As Const TaggedNumber, ByRef result As LongInt) As Boolean
    If value.kind <> NumberKind.Whole Then Return False
    result = value.payload.wholeValue
    Return True
End Function
~~~


## Read the argument syntax

ByVal gives the constructor its own parameter value. ByRef makes an accessor refer to an existing caller object. Const on the input record prevents writes through that parameter. The result parameter is writable because a successful accessor publishes a value into it. Boolean describes the success/failure answer. Returning False is distinct from returning a numerical zero: zero may itself be a valid stored number.


## Trace preservation on a mismatch

The laboratory initializes the fractional output to −8.5, then asks for a fractional value from Whole(42). The call must fail and preserve −8.5. Next it stores Fractional(12.5) and successfully reads that value. A later whole-number request fails and leaves the previous whole result, 42, unchanged. These checks make the refusal contract visible instead of merely checking that the program did not crash.


| Stored selection | Requested accessor | Result | Previous output |
| --- | --- | --- | --- |
| Whole(42) | TryWhole | True; writes 42 | Replaced on success |
| Whole(42) | TryFractional | False | −8.5 preserved |
| Fractional(12.5) | TryFractional | True; writes 12.5 | Replaced on success |
| Fractional(12.5) | TryWhole | False | 42 preserved |


## Exercise an unknown tag deliberately

The test uses Cast(NumberKind, 99) to construct an unsupported tag. This deliberately bypasses the normal constructors. Both accessors must refuse it without reading either payload interpretation or changing the previous outputs. A cast changes the type of an expression; it is not evidence that the value satisfies an application rule. The Invalid state receives the same refusal treatment.


## Do not use a tag change as conversion

Changing only Whole to Fractional does not turn 42 into 42.0. It changes the stated meaning while leaving unrelated bytes in place. A real conversion should first read the admitted source member, check any required range or precision rule, calculate a value of the destination type, and construct a new tagged record. Similarly, the Double example is a numeric demonstration, not a prescription for representing money. Financial code needs an explicit decimal or fixed-point policy.


## Keep complex ownership out of this first union

The payload alternatives here are simple numeric values. They do not own strings, heap allocations, locks or open files. Adding an owning pointer would introduce another problem: which alternative must release which resource when the tag changes? You would need deliberate construction, replacement, copy and destruction rules. A smaller record is not automatically a safer record, and a union is not a substitute for an ownership design.


## Compile and run

Use the FreeBASIC fb dialect and keep warnings and runtime checks enabled. Run one command at a time and stop on an error. Check the exit code after the executable runs. Source review and a lesson-link check do not prove that a particular FreeBASIC compiler accepted or executed this example.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -w all -exx tagged_number.bas -x tagged_number_basic.exe
& .\tagged_number_basic.exe
$LASTEXITCODE
~~~


## Read the expected result

A successful execution prints the two lines below and exits zero. Each numbered End failure corresponds to a particular check in the complete source. If one fails, locate that line and inspect the tag, accessor and prior output; do not remove the check to make the demonstration print success.

~~~text
Umicom tagged-number checks passed.
Wrong and unknown tags preserved both output values.
~~~


## Compare the C and D examples carefully

The same laboratory includes tagged_number.c and tagged_number.d. They illustrate a similar selection protocol, but their native records are not declared to be ABI-compatible. Enumeration widths, alignment, calling conventions and language rules must be checked separately. For Umicom applications, prefer existing Framework C services and an explicit C boundary instead of passing a BASIC-owned record directly to an unrelated library.


## Build a portable protocol from values

A portable message should state a tag encoding and then encode the selected value according to a documented byte order and representation. A decoder first checks the tag, length and value constraints, then constructs the in-memory record. It must reject unsupported alternatives without reading beyond the input. Neither SizeOf nor copying the union bytes establishes those checks. Revisit the earlier portable-record lesson before attempting file interchange.


## Exercises and vocabulary checkpoint

Add a third supported alternative for a small unsigned count. Write its constructor and checked accessor, then add success, mismatch and unknown-tag tests. Explain why changing the payload without updating the tag is also invalid. Finally list the roles of Enum, Explicit, Union, Type, ByVal, ByRef, Const, Return, Cast and OrElse in the complete program. Distinguish language syntax from the user-defined names MakeWhole and TryWhole.


## Official references


- [FreeBASIC UNION](https://www.freebasic.net/wiki/KeyPgUnion)
- [FreeBASIC ENUM](https://www.freebasic.net/wiki/KeyPgEnum)


[Previous: Own worker threads and protect shared state](36-own-worker-threads-and-protect-shared-state.md)

[Next: Observe which conditional expression runs](38-observe-which-conditional-expression-runs.md)
