<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/26-follow-construction-and-destruction.md

PURPOSE:
Follow construction and destruction through a scope

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Follow construction and destruction through a scope

[Course contents](index.md)

## What this exercise makes visible

A variable has a lifetime: an interval during which its value exists and may be used. Earlier lessons used Scope to limit where a name can be written. Here you will observe what happens when a user-defined value starts and ends its lifetime. The example prints creation and destruction events and counts how many values are currently live. It deliberately owns no file, heap buffer or Framework handle, so you can study the order without risking a double release.

A constructor is a special method used when an instance of a type is initialized. A destructor is its lifetime-ending counterpart. This lesson uses a default constructor with no arguments and ordinary local instances. It does not cover every rule for global storage, dynamic allocation, inherited objects or abnormal process termination. Read the official type and constructor reference alongside the exercise rather than treating a three-object trace as a complete resource-management implementation.


## 1. Read the small type declaration

~~~basic
Type LifetimeProbe
    identifier As Integer
    Declare Constructor()
    Declare Destructor()
End Type
~~~

Type begins the definition of a record-like user-defined value; End Type closes it. identifier is a field stored in each instance. Declare announces methods whose bodies appear later. Constructor and Destructor name those special lifetime methods. Parentheses contain their parameter lists; these lists are empty. There are no pointers in this type. Every instance receives its own integer identifier so a printed event can be associated with a particular creation.


## 2. Keep observation counters separate from owned values

The complete source declares three shared integers: createdCount, destroyedCount and liveCount. They are bookkeeping for this single-threaded demonstration. The constructor increments createdCount and liveCount, then assigns the new identifier through This.identifier. This identifies the instance whose method is running. The destructor increments destroyedCount and decrements liveCount. A counter is an observation, not a proof that an arbitrary operating-system resource was released correctly.

Imagine three visitors arriving and leaving a room. Counting arrivals and departures can tell you whether anyone should remain, but it does not describe what each visitor owns. Likewise, matching construction and destruction counts in this exercise says nothing about the correctness of a future pointer's allocator. Keep that boundary clear when you adapt the idea to a C library.


## 3. Trace the outer and inner variables

~~~basic
Function Exercise() As Integer
    Dim outerProbe As LifetimeProbe
    Scope
        Dim innerProbe As LifetimeProbe
    End Scope
    ' The outer value is still alive here.
    Return 0
End Function
~~~

The outer variable is declared in the function body. The inner variable is declared inside a nested Scope. Read the program downward and draw two horizontal lifetime bars on paper: the outer bar spans the nested scope; the inner bar ends at End Scope. The complete source checks liveCount after each transition. Return 0 exits the function with a success result. The caller checks the final counters only after Exercise has returned.


## 4. Trace the ordinary early-return path

LeaveEarly declares a third probe in a separate function called while the outer probe is alive. It returns normally from that function. The demonstration expects the local probe's destruction before the caller inspects its counters again. Do not replace this Return with process termination just to imitate an error. Ending the entire process is a different event from leaving a procedure, and this laboratory does not promise orderly cleanup after a crash or forced termination.

The expected event order is create 1, create 2, destroy 2, create 3, destroy 3, destroy 1. The live counts follow 1, 2, 1, 2, 1, 0. The precise spacing produced by Print for integers may differ from the compact notation here. Check the identities and counts, not a decorative alignment. The final message reports three created, three destroyed and none live. A failed internal comparison makes the program exit with a nonzero status.


## 5. Build the original file

1. Open PowerShell and use the FreeBASIC installation from the first lesson. Run fbc -version and record the version. If fbc is not recognized, repair the toolchain path before continuing.
2. Change to the language laboratory folder shown below. Read lifetime_probe.bas before compiling it; it contains both the observed methods and the checks.
3. Compile in the fb dialect with warnings enabled. Stop if compilation fails. The command produces a new executable in the laboratory folder.
4. Run the executable and compare the six event identities with your paper trace. A final success message is an observation from your compiler and machine, not an assumed result.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
fbc -version
fbc -lang fb -w all lifetime_probe.bas -x lifetime_probe.exe
& .\lifetime_probe.exe
$LASTEXITCODE
~~~


## 6. Why a destructor alone does not make a safe owner

A future wrapper might contain a pointer returned by a Framework create function. Releasing that pointer in a destructor seems convenient, but consider what happens if the wrapper is copied: two values might now contain the same owned pointer. Releasing both would be invalid. This example avoids that problem by owning only an integer. Before writing a real wrapper, specify whether copies are forbidden, share ownership deliberately, or duplicate the underlying resource. A copy constructor and assignment behavior require their own design and tests.

Match allocation and release functions. Memory allocated by a C library may need that library's own destroy function; it must not be handed arbitrarily to a BASIC deallocator. Also account for borrowed handles, callback retention and failure during creation. A wrapper must not destroy a borrowed object. The reusable ownership rules and operations belong in Framework, while a language binding should adapt them without inventing a second resource model.


## 7. Make small, explainable changes

1. Add a fourth nested Scope with one local probe. Predict the new event order and adjust the expected counts in a practice copy.
2. Temporarily make LeaveEarly return a failure status after its local declaration. Observe the procedure exit and the outer caller's cleanup; explain why error reporting and object lifetime are separate concerns.
3. Remove your experimental changes and rebuild the original example before using it as a reference.
4. Do not add raw allocation merely to make the example look more advanced. First write an ownership table naming who creates, borrows, copies and destroys each future resource.


## Troubleshooting and present limits

An unknown keyword or mismatched End statement usually means the source or dialect differs from the example; inspect the first diagnostic rather than adding random declarations. An unexpected extra event can come from an added temporary or copy. An event-order failure should be investigated against the exact compiler version and complete source. These BASIC files are authored teaching examples; no FreeBASIC execution is claimed by the native C checks in this repository. The program's counter model is not thread-safe and is not a production resource tracker.


## Names introduced here

| Name | Role in the example |
| --- | --- |
| Type / End Type | Describe the instance and its methods |
| Declare Constructor / Constructor | Announce and define initialization |
| Declare Destructor / Destructor | Announce and define lifetime-ending observation |
| This | Refer to the current instance |
| Dim Shared | Keep exercise counters visible to its procedures |
| Scope / End Scope | Create a nested local lifetime |
| Return | Leave an ordinary procedure and publish its result |

## Further reading

- [Original lifetime probe](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/lifetime_probe.bas)
- [FreeBASIC constructor reference](https://www.freebasic.net/wiki/KeyPgConstructor)
- [FreeBASIC language reference](https://www.freebasic.net/wiki/DocToc)

[Previous: Read file records and preserve errors](25-read-file-records-and-preserve-errors.md)

[Next: Select an overload by its arguments and preserve refused output](27-select-an-overload-by-its-arguments.md)
