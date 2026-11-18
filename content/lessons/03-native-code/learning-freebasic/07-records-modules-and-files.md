<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/07-records-modules-and-files.md

PURPOSE:
Records, reusable modules and files

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Records, reusable modules and files

[Course contents](index.md)
A record groups related fields. FreeBASIC Type defines a user-defined record. A file stores bytes after a process exits; it is not a memory dump that another language can safely interpret by guessing. Begin with a simple text format and explicit validation.

~~~basic
Type LessonProgress
    completed As Long
    total As Long
End Type
Dim As LessonProgress progress = (2, 8)
Print progress.completed; " of "; progress.total
Dim As Integer handle = FreeFile
If Open("progress.txt" For Output As #handle) <> 0 Then
    Print "Cannot open progress.txt"
    End 1
End If
Print #handle, progress.completed
Print #handle, progress.total
Close #handle
~~~

1. Use an empty practice folder: opening For Output replaces the contents of an existing file. Save as records.bas, compile and run.
2. Open progress.txt in a text editor. It contains two numbers on separate lines, with formatting chosen by BASIC.
3. Change the current folder and observe that a relative filename names a different location. Application persistence should choose an explicit data location.
4. Make a copy of the program before extending it to read. Validate that total is positive and completed lies between zero and total before using the loaded data.

The dot selects a record field. FreeFile obtains an available BASIC file number; # marks that number in file operations. Open can fail, so the program checks its status before writing. Close releases the handle. A production writer must also handle write/close errors and interrupted updates. This introductory example is not a crash-safe settings store.

Put shared declarations in a .bi include file and use #include once to avoid repeating them in one translation unit. Put implementations in .bas files and compile/link those files together. Inclusion copies declarations into compilation; linking connects compiled definitions. Include guards do not excuse defining the same exported function twice.

Do not write a Type record’s raw memory as a portable format: padding, byte order and field representation may change. For Umicom applications, use Framework serialization and file replacement contracts through a reviewed C binding. Keep this exercise as a way to learn records and handles.


## Check

If Open fails, no Print # operation should run. If a loaded file says completed is 100 and total is 8, reject or explain the invalid record. A parser accepting two integers does not prove the values make sense.


## Continue learning

[Previous: Procedures, ByVal and ByRef](06-procedures-and-value-ownership.md) · [Course contents](index.md) · [Next: Call a small C service from FreeBASIC](08-a-reviewed-c-boundary.md)
