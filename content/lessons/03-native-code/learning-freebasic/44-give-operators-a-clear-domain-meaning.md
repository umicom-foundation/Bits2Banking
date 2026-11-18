<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/44-give-operators-a-clear-domain-meaning.md

PURPOSE:
Give operators a clear domain meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Give operators a clear domain meaning

[Course contents](index.md)

## An operator is a short way to request an operation

You have already used symbols and words such as +, And and Or. Their ordinary numeric meanings are built into the language. Operator overloading lets a program define selected operations for a user-defined type. It does not make every symbol sensible for every type. In this original exercise a FlagSet holds a collection of independent bit flags. Or means set union and And means intersection. Neither operation changes an input.

1. Review the earlier bit-mask lesson: 1, 2 and 4 select three different binary positions.
2. Open labs/languages/native-language-boundary/flag_operators.bas. Use the FreeBASIC fb dialect, not an older BASIC dialect.
3. Keep this exercise separate from permission enforcement. The names read, write and inspect are labels in a local example; no filesystem or application access is granted.


## Define the value before defining its syntax

Type introduces a record and End Type closes its declaration. The bits field has type ULong, a 32-bit unsigned integer in FreeBASIC. Each bit is either zero or one. An unsigned bit mask naturally represents a set because each position can indicate whether one member is present. The public field keeps the exercise short; it also means callers can construct unknown bit patterns directly. That is why admission of external data stays a separate function.

~~~basic
Type FlagSet
    bits As ULong
End Type
~~~


## Work out the expected answers on paper


| Expression meaning | Binary | Decimal |
| --- | --- | --- |
| Read flag | 001 | 1 |
| Write flag | 010 | 2 |
| Inspect flag | 100 | 4 |
| Read union inspect | 101 | 5 |
| That union intersect read | 001 | 1 |
| Read union read | 001 | 1 |


## Define the two global operations

For the two-operand operations used here, Operator begins a global definition outside the record. ByVal gives the function its own value copies. As FlagSet declares the returned type. Type<FlagSet>(...) constructs the result from its field value. End Operator ends the body. The field expression uses ordinary integer Or or And; the outer expression uses the overload because its operands are FlagSet values.

~~~basic
Operator Or(ByVal lhs As FlagSet, ByVal rhs As FlagSet) As FlagSet
    Return Type<FlagSet>(lhs.bits Or rhs.bits)
End Operator

Operator And(ByVal lhs As FlagSet, ByVal rhs As FlagSet) As FlagSet
    Return Type<FlagSet>(lhs.bits And rhs.bits)
End Operator
~~~


## Trace one expression through the function

1. readFlag has bits equal to 1 and inspectFlag has bits equal to 4.
2. The expression readFlag Or inspectFlag selects the overload because both operands have type FlagSet.
3. The function copies the operands into lhs and rhs, evaluates the built-in integer operation 1 Or 4, and obtains 5.
4. It constructs a separate FlagSet whose bits field is 5 and returns it.
5. The caller stores that result in combined. readFlag and inspectFlag retain their original values.


## Why addition would be a misleading substitute

For different bits, 1 + 4 happens to equal 1 Or 4. But repeating a member reveals the difference: 1 + 1 is 2, while 1 Or 1 is 1. A union should not invent the write flag merely because the read flag was supplied twice. This is an example of a domain law: a rule the operation must preserve. Choose tests from those laws, rather than checking only one convenient pair of numbers.


## Validate raw values before trusting their meaning

The example defines only bits 1, 2 and 4. Its allowed mask is 7. Not allowed flips the 32 bit positions; raw And (Not allowed) isolates any bits outside the allowed set. If that expression is nonzero, TryAdmitFlags returns False before assigning destination.bits. ByRef means destination refers to the caller’s variable, so the order of that assignment matters. On success it publishes the accepted value.

~~~basic
Function TryAdmitFlags(ByVal raw As ULong, ByRef destination As FlagSet) As Boolean
    Dim allowed As ULong = 7
    If (raw And (Not allowed)) <> 0 Then Return False
    destination.bits = raw
    Return True
End Function
~~~


## Build the standalone language example

Install and select a FreeBASIC compiler using the earlier setup lesson. This source was authored and reviewed, but has not been compiled in the current mirror environment. Run the commands in PowerShell from the Bits2Banking checkout. Stop if compilation fails; do not run a stale executable.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
fbc -lang fb -exx -w all flag_operators.bas -x flag_operators.exe
.\flag_operators.exe
~~~


## Read the expected result

Require is a small test helper in the complete example. It prints a failure description and exits with a nonzero code if an expectation is false. The executable checks the union, intersection, repeated flag, unchanged operands, refusal of raw value 8, preservation of the old output, and acceptance of 7. No C ABI or installed Framework behavior is qualified by this standalone language exercise.

~~~text
Umicom BASIC flags: union 5, intersection 1, repeated flag 1.
Unknown input refused; operator syntax does not grant permission.
~~~


## Apply the idea at an Umicom boundary

A BASIC teaching client could use FlagSet to express local selections while presenting an explicit uint32_t mask to a reviewed C API. The shared C service must still validate known bits, combinations, authorization and lifetime. Do not pass the record’s raw bytes as a portable wire format: use the earlier serialization and ABI lessons. Do not hide file writes, network calls or expensive allocation inside a seemingly harmless Or operation.


## Distinguish nearby language concepts


| Concept | Question it answers |
| --- | --- |
| Procedure overloading | Which function declaration matches these argument types? |
| Operator overloading | Which declared operation represents this operator on this type? |
| Assignment | Which destination receives a value? It is not a union operation. |
| Input admission | Does this external bit pattern satisfy the published contract? |
| Authorization | May this caller perform the real operation now? |


## Practice and recovery

1. Change the repeated-flag expectation to 2. The example should fail because union is not addition. Restore the correct expectation afterward.
2. Try raw value 0. It represents an empty set and the current admission rule accepts it. A real API may impose a separate nonempty requirement.
3. Try raw value 9. Its low read bit is known, but its bit valued 8 is unknown; the whole raw value is refused.
4. If a compiler reports that an operator definition belongs outside the type, check the placement of the global binary definitions. Member assignment and conversion operators have different declaration rules.
5. If an operator unexpectedly mutates an operand, inspect parameter passing and side effects. This exercise deliberately uses value copies and fresh results.


## Language reference


- [FreeBASIC manual: Operator declaration and definition rules](https://www.freebasic.net/wiki/KeyPgOperator)


[Previous: Choose a rounding rule before conversion](43-choose-a-rounding-rule-before-conversion.md)

[Next: Select ranges and test every boundary](45-select-ranges-and-test-every-boundary.md)
