<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/01-plan-a-small-editor.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Plan a small editor with a testable model

[Course contents](index.md) · [Next: Insert and erase text without losing the tail](02-insert-and-erase-text.md)

## The project
You will build a small console text editor. It accepts commands to insert text, erase bytes, undo the most recent edit and save to a path you choose. It is a manageable first project, not a complete replacement for Umicom Studio.

The implementation has three parts:
~~~text
terminal command -> main.c -> editor.c -> text and undo state
                                 |
                                 +-> explicit save path
test_editor.c calls the model directly
check_session.cmake exercises the command-line program
~~~

## Setup recap
Follow [the course setup](index.md) to install the compiler and build tools. Open labs/native/text-editor in the Bits2Banking repository. Keep a separate practice folder for saved documents. You can use a plain text editor and PowerShell or Bash.

A model is the data and behaviour independent of its screen. A frontend accepts user input and presents results. Keeping them separate makes it possible to test editing without clicking a window.

## Define the first useful scope
1. Use a buffer of at most 1024 content bytes.
2. Accept printable ASCII, tab and newline in the model.
3. Count edit positions from zero in bytes.
4. Reject invalid input before changing text.
5. Keep one previous state for undo.
6. Save only to an explicit new filename.
7. Refuse to silently quit with unsaved changes.

This project does not yet open existing documents, provide a graphical cursor, edit general Unicode or offer unlimited undo. Those are later steps with their own contracts.

## Read the state
BtbEditor contains text, length, previous, previous_length, can_undo and dirty. Initialise it with:
~~~c
BtbEditor editor = {0};
~~~
This gives an empty string, zero lengths and false flags. The extra byte after the capacity holds the string's zero terminator.

## Build the smallest vertical slice
A vertical slice connects input, model and visible output. Run the editor and enter:
~~~text
append Hello
show
discard
~~~
Expect OK after append and TEXT: Hello after show. discard ends the session without saving. The final unsaved-changes notice is a reminder that this session did not create a saved document.

## Exercise
Before adding a toolbar or a theme, write three observable requirements. Example answers: inserting at the end appends bytes; an invalid position leaves text unchanged; saving cannot replace an existing file.

## Connect to Framework
The application architecture follows the same separation: Umicom Framework owns reusable document behaviour and Studio supplies the interface. Read Framework's document headers after understanding this compact model. Do not copy the teaching editor into application code in place of Framework.

## Troubleshooting
If a typed command seems ineffective, use show to inspect the model's current text. An ERROR result means the command was refused. Check spelling, spaces and the zero-based position before changing the implementation.

## Source map
Read `labs/native/text-editor/editor.h` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Insert and erase text without losing the tail](02-insert-and-erase-text.md)
