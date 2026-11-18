<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/29-expose-state-through-a-read-only-property.md

PURPOSE:
Expose state through a read-only property

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Expose state through a read-only property

[Course contents](index.md)

## Start with a small rule

A request budget is a count of how many operations are still allowed in a small exercise. We allow values from zero through 1,024. Consuming work must reduce the count without making it wrap around to a very large number. Resetting the count must refuse a value above the limit. This lesson introduces Property, Private and Public while keeping those rules visible. It is a teaching value object, not an implementation of billing, security or a production queue.


## Separate stored data from an interface

A field is a value stored inside a Type. A method is a procedure associated with that Type. An interface is the set of operations a caller is allowed to use. If a caller can assign any value directly to the stored count, the Type cannot reliably maintain its own limit. We therefore keep remaining_ private and expose a getter named Remaining. A getter retrieves a value. A setter assigns one through a procedure. This example deliberately declares only the getter.


## Read the declaration

Type starts the record-like definition and End Type closes it. Private: applies to following member declarations until another visibility label. Public: exposes the operations that follow. UInteger is an unsigned integer type: it represents nonnegative values, but its size is target-dependent. It is not a portable on-disk format. Declare announces a procedure whose body appears later. Constructor initializes a new object. The two Function declarations return Boolean results so callers can distinguish accepted and refused operations.

~~~freebasic
Type RequestBudget
Private:
    remaining_ As UInteger
Public:
    Declare Constructor()
    Declare Property Remaining() As UInteger
    Declare Function TryReset(ByVal requested As UInteger) As Boolean
    Declare Function TryConsume(ByVal count As UInteger) As Boolean
End Type
~~~


## A property looks like a field access

The expression budget.Remaining calls the getter even though it looks like reading a field. Inside the getter, Return sends back the stored count. Reading this property performs no mutation or I/O. Keep getters like this predictable: hiding expensive work or surprising side effects behind a field-like expression makes a program harder to understand.

~~~freebasic
Property RequestBudget.Remaining() As UInteger
    Return remaining_
End Property
~~~


## Why the update is an explicit method

A setter can be useful, but an assignment-looking operation does not naturally show a Boolean refusal result. Here we use TryReset and TryConsume to make failure visible. TryReset checks the requested value before assigning it. TryConsume checks whether the requested count exceeds what remains before subtracting. Returning False leaves the old state intact. Returning True means the complete update was accepted.

~~~freebasic
Function RequestBudget.TryConsume(ByVal count As UInteger) As Boolean
    If count > remaining_ Then Return False
    remaining_ -= count
    Return True
End Function
~~~


## Understand unsigned subtraction

Unsigned types cannot represent a negative result. Subtracting a larger count without checking can wrap according to the integer representation rather than producing a useful negative budget. Checking first is clearer than subtracting and trying to detect the problem afterwards. In our example, consuming four when three remain returns False and preserves three. Consuming exactly three succeeds and leaves zero. Consuming zero succeeds without changing the count. These are explicit choices in the contract.


## Compile the complete example

Use the FreeBASIC setup from the first course lesson. Open a terminal in the native-language-boundary lab directory. The -lang fb option selects the modern FreeBASIC dialect. -exx enables extra runtime error checking for this learning run. -x names the output executable. Execute each command separately and stop after a compiler error; an older executable with the same name is not proof that the new source compiled.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -exx read_only_properties.bas -x read_only_properties.exe
.\read_only_properties.exe
~~~


## Follow the state by hand


| Operation | Result | Remaining |
| --- | --- | --- |
| Construct budget | Initialized | 0 |
| TryReset(5) | True | 5 |
| TryConsume(2) | True | 3 |
| TryConsume(4) | False | 3 |
| TryReset(1025) | False | 3 |
| TryConsume(3) | True | 0 |
| TryConsume(0) | True | 0 |


## Check the expected outcome

The complete file checks each result and terminates with exit code one if an expectation is wrong. A successful run prints: Read-only property: refused updates preserved 3; exact consumption reached 0. The final End 0 reports normal completion. These are expected results for you to verify with your installed compiler; reading the example alone is not runtime evidence.


## Try a deliberate compiler refusal

The final source comment shows budget.Remaining = 7. If you copy the file to your own experiment and uncomment that assignment, the Type has no setter for it and compilation should refuse the operation. Restore the comment before continuing. This teaches the difference between a readable public property and a freely writable public field. Do not remove Private or expose remaining_ merely to silence the error; use the checked method.


## Validate text before converting it

These methods take already typed unsigned values. They do not parse user input, and a Property does not validate arbitrary text. Use the earlier strict-number lesson before converting terminal or file text into UInteger. Reject negative spelling, overflow and extra characters under an explicit input policy. Do not assume that changing a signed value to unsigned preserves the meaning you intended.


## Use the idea at a native application boundary

A BASIC teaching tool could display a Framework-owned job budget through a read-only getter and call a C function to request an update. Keep the real state and validation in the shared native service when integrating with Umicom applications. A BASIC Type with methods is not automatically a C struct with the same layout. Use the earlier C interoperability lesson for explicit linkage, fixed-width fields where required, ownership and return-status handling.


## Practice

1. Predict the result of TryReset(1024), then TryConsume(1024). Both succeed and the final count is zero.
2. Explain why TryReset(1025) must check before assignment. Otherwise a refused request would leave invalid state behind.
3. Explain the roles of Private, Public, Property, Function, ByVal, Boolean and Return in this file.
4. Design a test that records Remaining before a refused request and compares it afterwards. Refusal must preserve the state, not just return False.


## Official language references


- [FreeBASIC Property reference](https://freebasic.net/wiki/KeyPgProperty)
- [FreeBASIC types as objects](https://www.freebasic.net/wiki/TutBeginnersGuideToTypesAsObjects)


[Previous: Guard a read with short-circuit operators](28-guard-a-read-with-short-circuit-operators.md)

[Next: Read fixed data records and reset the cursor](30-read-fixed-data-records-and-reset-the-cursor.md)
