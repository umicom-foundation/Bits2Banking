<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/34-swap-values-without-confusing-their-owners.md

PURPOSE:
Swap values without confusing their owners

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Swap values without confusing their owners

[Course contents](index.md)

## What you will observe

This exercise follows three different exchanges: two numbers, two pointers and two variable-length strings. All use the FreeBASIC Swap statement, but the meaning depends on what each variable stores. You will predict values before running, draw which storage a pointer names, and explain why exchanging two references does not copy their underlying objects. This is a small language lesson for understanding native application state. It does not implement a bank transaction, a thread-safe publication primitive or a Framework service.


## Start with two named boxes

A variable has a name, a type and stored state. Long is the integer type used in this exercise. Dim declares the variables, As selects their type, and the equals sign in each declaration supplies its starting value. Imagine first and second as two separate boxes. Initially the first contains six and the second contains forty-two.

~~~freebasic
Dim first As Long = 6
Dim second As Long = 42
Swap first, second
~~~


## Trace the scalar exchange


| Moment | first | second |
| --- | --- | --- |
| Before Swap | 6 | 42 |
| After Swap | 42 | 6 |


## Why two assignments are not an exchange

If you write first = second followed by second = first, the original first value is lost before the second assignment. Both boxes then contain forty-two. A manual exchange needs a temporary variable that remembers the old value. Swap expresses the exchange directly. Both variables in this lesson have the same type, so you can focus on where the values go without introducing conversion rules.

This three-line version is a separate explanation of an exchange. Do not append it to the supplied program unless you intend to exchange the values a second time. A source listing is an ordered sequence: adding a correct operation in the wrong place changes the result.

~~~freebasic
Dim savedFirst As Long = first
first = second
second = savedFirst
~~~


## Read the real checks

The program follows each operation with ordinary If checks. The comparison operator <> means “not equal”. OrElse evaluates its right condition only when its left condition is false. End with a nonzero number reports a failed exercise check to the invoking shell. These normal checks remain part of the program rather than relying only on assertions that a build option might remove.

~~~freebasic
If first <> 42 OrElse second <> 6 Then End 1
Print "values="; first; ","; second
~~~


## A pointer stores an address

A pointer identifies a storage location. Long Ptr is a pointer to a Long value. The @ operator obtains the address of an existing variable. In the next code, leftView initially names first and rightView initially names second. Both local integers stay alive for the entire exercise, so the pointers have valid backing storage. No heap allocation or deletion is involved.

~~~freebasic
Dim leftView As Long Ptr = @first
Dim rightView As Long Ptr = @second
Swap leftView, rightView
~~~


## Draw the pointer exchange separately


| Moment | leftView names | rightView names | first value | second value |
| --- | --- | --- | --- | --- |
| Before pointer Swap | first | second | 42 | 6 |
| After pointer Swap | second | first | 42 | 6 |
| After *leftView = 9 | second | first | 42 | 9 |


## Follow the star to the selected storage

The leading star in *leftView accesses the Long stored at the address held by leftView. After the pointer exchange, that address belongs to second. Therefore *leftView = 9 changes second to nine while first stays forty-two. The pointer exchange itself changed neither integer. A reference and its referent are different things: the reference chooses an object, while the referent is the object being chosen.

~~~freebasic
*leftView = 9
If first <> 42 OrElse second <> 9 OrElse *rightView <> 42 Then End 4
~~~


## Keep a lifetime table


| Object | Owner in this exercise | When it is used |
| --- | --- | --- |
| first and second | The main program scope | Throughout all pointer operations |
| leftView and rightView | The main program scope | They borrow addresses of those integers |
| The integer values | Stored in the two original variables | Changed by scalar assignment or dereference |
| A copied address | Still a reference, not new integer storage | It does not extend the original variable’s lifetime |


## Try a variable-length string exchange

String declares an ordinary variable-length FreeBASIC string. The supplied example exchanges two application-style labels, preview and export. The official Swap reference describes variable-length strings as exchanging their descriptors rather than reallocating and copying all characters merely for the exchange. Keep this runtime representation inside the language boundary; a FreeBASIC string descriptor is not a portable C string ABI.

~~~freebasic
Dim activeName As String = "preview"
Dim nextName As String = "export"
Swap activeName, nextName
Print "names=["; activeName; "] ["; nextName; "]"
~~~


## A descriptor is not the whole object

A descriptor is a small piece of information that tells the runtime where some data is and how it is represented. Exchanging descriptors can change which variable refers to which data. That does not mean every kind of object can be safely exchanged by copying bytes. A record may contain a pointer to itself, an external registration, a callback context or another invariant tied to its address. The supplied exercise deliberately uses simple scalars, valid local pointers and normal strings instead of pretending to solve those more complicated ownership problems.


## Do not turn Swap into a transaction claim

A transaction groups changes under a defined all-or-nothing contract. Swap is a language operation on its arguments. It does not coordinate concurrent threads, publish a file, update a database or roll back arbitrary earlier work. A real application that switches active models or media buffers still needs its Framework owner to validate readiness, coordinate readers and release the old resource at the correct time. The language exercise helps explain the references involved; it is not that resource manager.


## Run the supplied FreeBASIC program

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -lang fb -w all -exx swap_values.bas -x swap_values.exe
& .\swap_values.exe
~~~

1. Open PowerShell and enter the native-language-boundary lab folder in your Bits2Banking checkout.
2. Check that fbc resolves to the FreeBASIC compiler you intend to use. A similarly named shell alias is not a compiler identity.
3. Compile swap_values.bas with the fb dialect, warnings and runtime checks enabled.
4. Stop if compilation fails. Do not launch an old executable left by an earlier build.
5. Run the new executable and compare the four observations with the table below.


## Read the expected observations


| Printed label | Expected values |
| --- | --- |
| values= | 42, 6 |
| after pointer write= | 42, 9 |
| names= | [export] [preview] |
| same variable= | 42 |


## Understand the same-variable check

The final statement exchanges first with itself. Its value should remain forty-two. This is a small aliasing case: both argument positions identify the same variable. It is not permission to use side-effecting expressions or partially overlapping complex records without understanding their contract. Integer spacing in Print output may differ by runtime formatting; compare the values and the explicit string delimiters rather than assuming every space is significant.


## Troubleshoot by locating the wrong kind of value

1. If scalar values are wrong, check whether you accidentally performed a second exchange or replaced Swap with two destructive assignments.
2. If first changes when you expected second to change, redraw the pointer arrows after each pointer assignment and Swap.
3. If the compiler rejects a dereference, verify that the declaration uses Long Ptr rather than Long.
4. If a string seems truncated, check that you used String rather than a fixed-length field from the previous lesson. This exercise does not test fixed-field padding rules.
5. If fbc is unavailable, retain the source and record that subject-language compilation remains pending. A passing C test elsewhere cannot compile this BASIC program.


## Apply the idea to Umicom designs

An editor can keep a current document and a prepared candidate. A media job can keep an active frame and a ready next frame. In both cases, selecting a different handle is separate from copying pixels or text, and separate again from freeing storage. Before implementing such behavior, use the existing Framework ownership service and document who may retain each pointer. Do not replace a shared C service with a BASIC-specific version merely because a teaching statement looks convenient.


## Exercises and references

These examples are authored teaching code. FreeBASIC compilation and execution remain unverified in the current mirror environment. Keep a record of your compiler version and actual output when you qualify them.

1. Predict the scalar results when the starting values are negative six and forty-two.
2. Remove only the pointer Swap and predict which integer the write through leftView changes.
3. Exchange the string variables twice and explain why their labels return to the starting assignment.
4. Draw an example where two pointers both name first. Explain why changing through either pointer reaches the same storage.
5. Write one sentence distinguishing a value exchange, a pointer exchange and a transaction.


## Official language reference


- [FreeBASIC SWAP reference](https://www.freebasic.net/wiki/KeyPgSwap)
- [FreeBASIC maintained manual source for SWAP](https://github.com/freebasic/fbc/blob/master/doc/manual/cache/KeyPgSwap.wakka)


[Previous: Format fixed ASCII fields without losing data](33-format-fixed-ascii-fields-without-losing-data.md)

[Next: Measure records before sharing their bytes](35-measure-records-before-sharing-their-bytes.md)
