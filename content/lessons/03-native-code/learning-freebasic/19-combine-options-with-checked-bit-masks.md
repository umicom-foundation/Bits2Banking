<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/19-combine-options-with-checked-bit-masks.md

PURPOSE:
Combine options with checked bit masks

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Combine options with checked bit masks

[Course contents](index.md)
A program often needs several independent yes-or-no settings: reading enabled, writing enabled and audit logging enabled, for example. A bit mask stores those choices in separate bits of one integer. This lesson uses FreeBASIC to combine, inspect and change such options while preserving the previous result when an unsupported bit appears. These are teaching settings, not an operating-system security mechanism.


## 1. Read a small binary number

Binary uses the digits zero and one. In three positions, the place values from right to left are 1, 2 and 4. Therefore 101 means 4 plus 1, or decimal 5. Each position can represent an independent setting. The name mask describes an integer whose set bits identify the positions you want to inspect or change. It is still an ordinary integer; the meaning of each bit comes from the program contract.

~~~freebasic
Const As ULong ReadOption = 1
Const As ULong WriteOption = 2
Const As ULong AuditOption = 4
Const As ULong KnownOptions = ReadOption Or WriteOption Or AuditOption
~~~

Const gives a value a name that cannot be reassigned. As ULong chooses FreeBASIC’s unsigned 32-bit integer type. Only three low bits are used in this example; the remaining bits must be zero. Do not assume that a type called Integer has the same width on every target. Using an explicit width makes masks and future data formats easier to review.


## 2. Learn the four bitwise operations

Or sets a result bit when either input has that bit set. And keeps a result bit only when both inputs have it set. Xor sets a result bit when the inputs differ at that position, which makes it useful for toggling. Not complements all bits in the operand’s integer width. It does not mean just the low three visible positions. That is why the example validates the result against its declared known-bit contract.

~~~freebasic
Dim As ULong options = ReadOption Or AuditOption
Print Bin(options, 3)       ' 101
Print Bin(options And ReadOption, 3)  ' 001
Print Bin(options Xor AuditOption, 3) ' 001
~~~

Bin formats an integer as binary text; its second argument requests a minimum number of digits. The quotes beginning comments are apostrophes, not string delimiters. Notice the distinction between bitwise And/Or and the short-circuit logical AndAlso/OrElse used in earlier lessons. A bitwise expression combines every bit. A short-circuit logical expression chooses whether a later Boolean operand needs evaluation.


## 3. Test for all requested bits

~~~freebasic
Function HasAll(ByVal flags As ULong, ByVal required As ULong) As Boolean
    Return (flags And required) = required
End Function
~~~

ByVal passes a value into the function, so this calculation does not change the caller’s flags. The And operation removes all bits that were not requested. Equality then checks whether every requested bit survived. Parentheses make the intended grouping explicit. Asking for ReadOption Or AuditOption succeeds only when both are present. Testing whether any bit is present would instead compare (flags And requested) with zero.

There is an important empty case: HasAll(flags, 0) returns True because there are no required bits missing. This is called vacuous truth. It is mathematically consistent, but a security decision that accidentally constructs an empty requirement could become too permissive. The example tests the case and explains it rather than hiding it. Real authorization needs an explicit policy and trusted identity checks, not only an integer mask.


## 4. Validate before changing a result

TrySetOptions accepts a current mask, a requested mask and a Boolean that chooses enabling or disabling. It refuses any bit outside KnownOptions in either input. The check combines both inputs with Or, then intersects with Not KnownOptions. A nonzero result reveals an unknown bit. On refusal, the output supplied ByRef is left unchanged. On success, a local candidate is assigned to that output.

~~~freebasic
If ((current Or requested) And Not KnownOptions) <> 0 Then Return False
Dim candidate As ULong
If enabled Then
    candidate = current Or requested
Else
    candidate = current And Not requested
End If
result = candidate
Return True
~~~

This is the body of the function in checked_flags.bas. Enabling uses Or so an already enabled bit remains enabled. Disabling clears the requested positions with And Not. Toggling with Xor is different: applying it twice restores the original value. A button labeled Enable should not silently toggle a setting off when pressed twice.


## 5. Compile the complete exercise

1. Use the FreeBASIC setup from the first lesson and open the native-language-boundary lab directory. The complete checked_flags.bas file includes the declarations, functions and checks omitted from short fragments.
2. Run the commands below separately. -lang fb selects the intended FreeBASIC dialect, -exx enables runtime checks and -g includes debugging information.
3. Expect Read plus audit: 101, then Only audit: 100, followed by Checked flag examples passed. The program exits with status one if a Require check fails.
4. Inspect the tests for an unknown requested bit, an invalid current mask, an empty change and toggling twice. Explain why each protects a different part of the contract.
5. If fbc is unavailable, return to the setup lesson. Reading the source is useful but is not compiler validation; do not describe an unexecuted example as passed.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -exx -g checked_flags.bas -x checked_flags.exe
.\checked_flags.exe
~~~


## 6. Reuse the idea across a native boundary

A C API can expose a documented unsigned integer mask, and BASIC can supply or inspect it when the width and calling convention match. The two sides must agree on every defined bit and how unknown bits are handled. Do not send a FreeBASIC Boolean object or an Enum representation across a boundary merely because it looks similar in source. Follow the exact header contract and the earlier interoperability lesson.

For Umicom applications, masks can describe optional capabilities, selected diagnostic categories or small UI choices. Configuration is not proof that a capability works. A bit labeled GPU available must come from a verified discovery path if the application uses it to choose a backend. Keep reusable behavior in Framework and treat a BASIC program as a caller or teaching tool, rather than creating a separate competing implementation of the same service.


## 7. Practice and check your understanding

1. Add an ExportOption with value 8 to a private learning copy, then deliberately forget to add it to KnownOptions. Confirm that the old admission rule refuses it. Update the rule deliberately and retest.
2. Start with options equal to 7. Disable WriteOption and predict the answer before running: decimal 5, binary 101.
3. Explain why the decimal values 1, 2 and 4 are independent one-bit choices, but 3 is a combination of the first two.
4. Explain the difference between enabling, disabling and toggling an already set bit.
5. Use a sentinel output value when testing refusal. Check the returned Boolean before treating that sentinel as a new result.


## Three visible bits

| Decimal | Binary | Meaning |
| --- | --- | --- |
| 0 | 000 | No options |
| 1 | 001 | Read |
| 2 | 010 | Write |
| 4 | 100 | Audit |
| 5 | 101 | Read and audit |
| 7 | 111 | All declared options |

## Further reading

- [FreeBASIC manual: operators](https://www.freebasic.net/wiki/CatPgOp)

[Previous: Distinguish comments, strings and language boundaries](18-comments-and-language-boundaries.md)

[Next: Name fixed rules with Const](20-name-fixed-rules-with-const.md)
