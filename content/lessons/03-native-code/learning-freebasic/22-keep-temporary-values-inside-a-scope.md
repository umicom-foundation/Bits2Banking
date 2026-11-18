<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/22-keep-temporary-values-inside-a-scope.md

PURPOSE:
Keep temporary values inside a scope

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep temporary values inside a scope

[Course contents](index.md)

## Build a small review calculation

You will calculate a reviewed-record total using an outer count and a temporary count. The program deliberately gives two variables the same name so you can see which one is being read. It then copies the useful result into a clearly named outer variable. This is a language exercise with small integers; it does not read a dataset, train a model or change a Framework service.

Complete the earlier lessons on variables, procedures, decisions and array lifetime first. Use the FreeBASIC compiler in its fb dialect. The complete source is scoped_values.bas in the native-language-boundary lab. The example is provided for compilation with your installed FreeBASIC toolchain; its execution is not claimed by the native C checks in the repository.


## Learn the rule before running the program

Scope opens an explicit local block and End Scope closes it. A local declared there is available from its declaration to the end of that block. A declaration can hide a same-named outer variable; this is called shadowing. Before that declaration, a use still refers to the visible outer name. After the block, the outer name is available again. Explicit Scope blocks belong to the fb and deprecated dialects, not qb or fblite. Consult the linked FreeBASIC manual for the precise language rule.


## Read the declarations

~~~basic
Dim As Integer selectedCount = 4
Dim As Integer reviewedTotal = 0

Scope
    Dim As Integer originalCount = selectedCount
    Dim As Integer selectedCount = 7
    reviewedTotal = originalCount + selectedCount
End Scope
~~~

There are two different objects named selectedCount in this fragment. The first holds four. originalCount captures that four before the second selectedCount is declared. The second declaration initializes a distinct temporary integer to seven. The assignment adds four and seven and stores eleven in reviewedTotal, which was declared outside the block. The arithmetic is intentionally small enough to avoid a distracting integer-range issue.

It is tempting to describe the inner declaration as changing selectedCount from four to seven. That description loses the distinction between two objects. In your notebook, give them temporary labels such as outer selectedCount and inner selectedCount. These labels are for your reasoning; they are not extra source-code names. Draw a box around the inner declarations and keep reviewedTotal outside the box.


## Compile and run the complete source

~~~powershell
Set-Location .\labs\languages\native-language-boundary
fbc -version
fbc -lang fb scoped_values.bas -x scoped_values.exe
.\scoped_values.exe
~~~

1. Open PowerShell in the Bits2Banking checkout. Change to labs/languages/native-language-boundary.
2. Run fbc -version to check that PowerShell can find the installed compiler. If it cannot, use its full executable path or configure that toolchain before continuing. Installing a C compiler alone does not install FreeBASIC.
3. Open scoped_values.bas and read the Require procedure. Each call checks an expected relationship and ends with a nonzero code if the relationship is false.
4. Compile with the fb dialect and run the resulting executable. Stop if compilation fails; do not run an older executable left from a previous attempt.

Expect the inner count to be seven, the outer count to be four, the reviewed total to be eleven and the final total to be fifteen. FreeBASIC numeric printing can include spacing around values; compare the numbers and labels rather than assuming an exact whitespace layout. The complete program ends with code zero after its assertions pass. If a Require check fails, read its message before changing the expected answer.


## Follow the second block

The second Scope block declares originalCount again. Its first declaration is no longer visible, so this is a new temporary. It captures the outer selectedCount, still four, and adds it to reviewedTotal. Eleven plus four gives fifteen. This gives a useful pattern for application code: keep a short calculation close to its use, then copy the intended result to an explicitly owned outer value.


## Compare declaration with assignment

1. Make a separate practice copy. Replace the inner declaration Dim As Integer selectedCount = 7 with the assignment selectedCount = 7.
2. Before compiling, predict which value the later outer-count check will see. An assignment updates the existing visible variable; it does not create the hidden temporary from the original example.
3. Compile the copy under a new executable name. Its existing assertion that the outer count remains four should fail. That failure is the intended observation.
4. Restore the declaration or give the temporary a distinct descriptive name. Do not merely change the assertion to hide the difference.

In production code, clear names often make review easier than intentional shadowing. You might choose requestedCount and temporaryCount. Learning the rule is useful because you will encounter shadowing in existing code, debugger displays and code reviews. It is not a recommendation to reuse names wherever the compiler permits it.


## Try an out-of-scope reference

1. In a new copy, add Print originalCount immediately after the first End Scope.
2. Compile the copy. With the explicit-declaration discipline used here, the inner originalCount is unavailable at that point. Read the compiler diagnostic and its source location.
3. Move the print into the block if you only need a temporary observation, or copy the intended value into a deliberately declared outer result.
4. Keep the original working file and compare the two versions. A compiler diagnostic is evidence about the source you compiled, not about an unrelated old executable.


## Separate visibility from resource lifetime

A name disappearing from source lookup is not a general instruction to wipe every byte associated with a calculation. This example uses only small integer locals. It does not establish what happens to a heap allocation, an open file, a model process or a native callback registration. For those resources, follow the API ownership contract and pair acquisition with the required release. The earlier pointer and callback lessons explain why a borrowed address must not outlive the object it refers to.

The distinction matters when a BASIC application calls a C service. Passing a pointer to a local for a synchronous call can be valid when the C contract only borrows it during that call. If the C service retains the pointer, the caller needs storage whose lifetime covers that retention and a clear release protocol. Putting the call inside Scope does not create that protocol. Do not add a pointer to this exercise merely to bypass a scope diagnostic.


## Compare with the bounded Umicom C compiler

The current Umicom C teaching compiler supports initialized declarations inside conditional bodies, removes their names after each body and reuses existing local slots. It deliberately refuses shadowing an already visible name and does not accept standalone nested blocks. Therefore the exact FreeBASIC exercise cannot be translated by replacing Scope with braces. A compatible Umicom C version must use distinct names and an admitted conditional body. These limits belong to that compiler implementation, not to the full C23 language.


## Check your understanding

1. Explain why the outer count remains four in the original program.
2. Identify the precise assignment that carries eleven outside the first block.
3. Predict the effect of changing the temporary seven to nine: the reviewed total should become thirteen and the final total seventeen. Update a practice copy and its intentionally related assertions together.
4. Explain why the assignment-only experiment fails the original outer-count assertion.
5. Give one example of a resource that needs an explicit lifetime contract beyond name visibility.


## Further reading

- [FreeBASIC Scope and End Scope reference](https://freebasic.net/wiki/KeyPgScope)
- [FreeBASIC variable scope reference](https://www.freebasic.net/wiki/ProPgVariableScope)
- [Complete scoped-values example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/scoped_values.bas)
- [Umicom C branch-local guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/branch-local-scope.md)

[Previous: Resize a bounded dynamic array and follow its lifetime](21-resize-a-bounded-dynamic-array.md)

[Next: Distinguish text from its stored bytes](23-distinguish-text-from-its-stored-bytes.md)
