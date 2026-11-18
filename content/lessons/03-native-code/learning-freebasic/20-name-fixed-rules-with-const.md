<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/20-name-fixed-rules-with-const.md

PURPOSE:
Name fixed rules with Const

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Name fixed rules with Const

[Course contents](index.md)
A program often contains numbers that represent a rule: six items in one box, a maximum of one hundred boxes, or a particular protocol version. Repeating those numbers in many expressions makes the rule difficult to review. A named constant gives a fixed value a meaningful name. In this lesson you will use FreeBASIC Const declarations, derive one constant from another, and keep runtime inputs separate from compile-time rules.


## 1. Distinguish a name, a type and a value

~~~freebasic
Const As Long UnitsPerBox = 6
Const As Long MaximumBoxes = 100
Const As Long MaximumUnits = UnitsPerBox * MaximumBoxes
~~~

Const introduces a named constant. As Long declares its numeric type. In the FreeBASIC dialect used here, Long is a signed 32-bit integer. UnitsPerBox is the identifier, the equals sign introduces its value, and 6 is an integer literal. MaximumUnits is another constant expression: the compiler can determine it from two already declared constants. Its value is six hundred.

The names are chosen to explain the units. A number of boxes and a number of individual items are both integers, but they mean different things. A meaningful name helps a reader notice when the wrong quantity is used. It does not make the compiler perform dimensional analysis; that would require a stronger type contract.


## 2. Keep changing input in a variable

~~~freebasic
Dim As Long boxes = 7
Dim As Long units = -1
~~~

Dim introduces variables. boxes can change while the program runs; UnitsPerBox is a constant. units starts with minus one so that an unchanged output is visible during debugging. These are ordinary in-memory values. A Const declaration does not read a settings file, follow a spreadsheet cell or change when another variable changes.

A FreeBASIC constant must use an admitted constant expression for its type and dialect. An ordinary user input or a runtime function call is not automatically such an expression. Do not use Const merely because you expect a value to stay unchanged after reading it. Runtime state and compile-time definitions need different designs.


## 3. Put the calculation behind a checked function

~~~freebasic
Function TryUnits(ByVal boxes As Long, ByRef units As Long) As Boolean
    If boxes < 0 OrElse boxes > MaximumBoxes Then Return False
    Dim As Long candidate = boxes * UnitsPerBox
    units = candidate
    Return True
End Function
~~~

The function receives boxes by value, so it gets an input copy. It receives units by reference, so it can publish a result into the caller’s variable. Boolean is the result type: True means the conversion was accepted and False means it was refused. The function checks both bounds before multiplication and before writing the caller’s output.

OrElse is the short-circuit logical OR operator. If boxes is already negative, the second comparison is unnecessary. This example would have no side effect in either comparison, but using explicit logical operators makes the intended boolean decision clear. The accepted range is zero through one hundred inclusive. Multiplying by six therefore stays within zero through six hundred, comfortably inside Long’s range.

candidate is a local temporary. Only after all checks succeed does the function assign candidate to units. A refused input leaves units unchanged. This is a useful boundary pattern for Umicom applications too: validate inputs, calculate in suitable types, and publish a result only when the whole operation is ready. Production services should use the shared Framework contract rather than copying this toy function into every application.


## 4. Run the complete example

1. Complete the compiler setup in the first FreeBASIC lesson. This exercise uses the fb dialect, not a promise of compatibility with every older BASIC dialect.
2. Open labs/languages/native-language-boundary/named_constants.bas. Read the declarations, function and top-level checks before compiling.
3. Run the commands below separately. If fbc is not recognized, return to the setup lesson and locate the compiler instead of changing the program to hide the missing tool.
4. Expect 42 accepted units and a declared upper bound of 600. The final message confirms that an out-of-range count did not replace the sentinel output.
5. Record the compiler version and command output. The example remains a source exercise until it has been compiled and executed with your chosen FreeBASIC installation.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -exx -w all named_constants.bas -x named_constants.exe
.\named_constants.exe
~~~

The -lang fb option selects the dialect. -exx enables the compiler’s extra runtime checking options, and -w all requests warnings. They help expose mistakes but do not prove every possible input or interaction is safe. The -x option names the executable. Keep the compiled output separate from the source file.


## 5. Observe a deliberate compile failure

1. Make a separate practice copy of named_constants.bas. Add UnitsPerBox = 8 after the declarations and try to compile it.
2. Expect rejection because the name denotes a constant. Remove the intentionally invalid assignment.
3. Change the constant declaration itself to eight, rebuild, and predict which expected-result check now fails. Seven boxes now contain fifty-six units, so the old expectation of forty-two must be reviewed.
4. Restore the original value. Try inputs zero, one hundred, minus one and one hundred and one, and predict acceptance and output preservation.
5. Explain why renaming the constant alone does not change its value, and why changing a declaration requires rebuilding the executable.


## 6. Avoid accidental global coupling

A named constant can still be used badly. If an unrelated screen uses MaximumBoxes as a maximum retry count just because both happen to be one hundred, changing the packaging rule unexpectedly changes the retry policy. Give unrelated concepts separate names and place them near the code or module that owns the rule. Share a constant only when the consumers genuinely share the same contract.

For a C ABI, a source-level constant name is not automatically an exported symbol. Another language may not be able to look it up in a library. Publish a documented enum, macro, query function or versioned structure as appropriate for the boundary. The existing C interoperability lessons explain why calling convention and integer width still need to match.


## 7. Compare with Umicom C and D carefully

Umicom C now supports initialized local const int and int const declarations. Their initializer may execute at runtime and read earlier locals, while later source updates are refused. That differs from the constant-expression role demonstrated by FreeBASIC Const here. Both can help express intent, but translating one word into the other is not a complete semantic translation.

D distinguishes const views from immutable data. A const view may observe changes made through another valid mutable alias, whereas an independent immutable copy cannot be legally modified after construction. Those aliasing rules do not apply to this simple FreeBASIC named integer constant in the same way. Learn the contract of each language before mixing interfaces.


## Review the vocabulary

| Term | Meaning here | Example |
| --- | --- | --- |
| Literal | A value written directly in source | 6 |
| Identifier | A name used by the language | UnitsPerBox |
| Type | Rules for representation and operations | Long |
| Constant expression | An expression admitted for a constant declaration | UnitsPerBox * MaximumBoxes |
| Runtime variable | Storage whose value can change during execution | boxes |
| Sentinel | A deliberately chosen value used to detect an unchanged result | units = 73 before a refusal test |
| Output publication | Writing the completed result into caller-owned storage | units = candidate |

## Further reading

- [FreeBASIC Const reference](https://www.freebasic.net/wiki/KeyPgConst)
- [FreeBASIC language reference](https://www.freebasic.net/wiki/DocToc)

[Previous: Combine options with checked bit masks](19-combine-options-with-checked-bit-masks.md)

[Next: Resize a bounded dynamic array and follow its lifetime](21-resize-a-bounded-dynamic-array.md)
