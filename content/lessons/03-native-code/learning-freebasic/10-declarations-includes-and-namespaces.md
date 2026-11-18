<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/10-declarations-includes-and-namespaces.md

PURPOSE:
Separate declarations, implementations and namespaces

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate declarations, implementations and namespaces

[Course contents](index.md)
A declaration tells a compiler what a symbol looks like. A definition supplies storage or implementation. A header-style .bi file can share declarations across source files. An include directive inserts source during preprocessing; it does not dynamically load a library when the program runs.

~~~basic
' progress.bi
#ifndef LESSON_PROGRESS_BI
#define LESSON_PROGRESS_BI
Namespace Lesson
    Declare Function IsComplete(ByVal done As Long, ByVal total As Long) As Long
End Namespace
#endif
~~~

~~~basic
' progress.bas
#include once "progress.bi"
Namespace Lesson
    Function IsComplete(ByVal done As Long, ByVal total As Long) As Long
        Return IIf(total > 0 AndAlso done = total, 1, 0)
    End Function
End Namespace
~~~

~~~basic
' main.bas
#include once "progress.bi"
Print Lesson.IsComplete(8, 8)
~~~

1. Save the three named files in one empty practice folder.
2. Compile together with fbc -lang fb -w all main.bas progress.bas -x modules.exe.
3. Run .\modules.exe and expect 1.
4. Temporarily omit progress.bas from compilation. Observe that a declaration alone does not provide the function definition needed at link time. Restore the command.

Namespace groups names so Lesson.IsComplete can coexist with similarly named functions elsewhere. Using can make names visible without qualification, but too many imported names create ambiguity. The #ifndef/#define/#endif guard prevents repeated declarations in one compilation; #include once is also useful. Neither prevents linking two separate definitions of the same exported symbol.

Preprocessor #if chooses source based on compile-time conditions. It differs from a runtime If. #macro and #define can substitute source text, which may obscure types and evaluation. Prefer a typed Function when that expresses the operation clearly. Read the expanded intent before using macros at a C boundary.


## Check

Change the return type in only one declaration and explain why every translation unit must agree. Link success alone is not a complete type check across independently compiled foreign-language modules.


## Continue learning

[Previous: Follow pointers and allocation lifetimes](09-pointers-and-allocation-lifetimes.md) · [Course contents](index.md) · [Next: Test errors and define record contracts](11-tests-errors-and-record-contracts.md)
