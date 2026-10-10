# 4. From an idea to a working program

Before writing code, describe the problem in ordinary language. Suppose you want a note-taking application that remembers what you have written. What should happen when someone adds a note? What if they press Save without entering any text? Where will the note be stored so that it is available next time?

These questions are part of programming. The code is the final expression of the decisions you have made.

## Write an algorithm

An **algorithm** is a finite sequence of steps for solving a problem. A simple save-note algorithm might be:

1. Ask the user for a note.
2. Remove unwanted spaces at the beginning and end.
3. Reject the note if it is empty.
4. Save it in a file.
5. Tell the user whether the save succeeded.

We can express the same algorithm as **pseudocode**, which looks like programming but is designed to be read rather than executed:

```text
READ note
SET note TO trimmed note
IF note is empty THEN
    SHOW "Please enter a note"
ELSE
    SAVE note to the notes file
    SHOW "Note saved"
END IF
```

A **condition** chooses between alternatives. A **variable** holds a value such as `note`. A **function** is a named piece of work that can be used again, such as `SaveNote`. A **loop** repeats work, perhaps displaying every saved note. These concepts appear in almost every programming language in this guide.

## Data is part of the design

What information identifies a task on a Kanban board? A title alone may not be enough because two tasks can have the same title. A more useful task record has an identifier, title, status and optional due date:

| Field | Example | Why it exists |
| --- | --- | --- |
| `taskId` | `T-104` | Distinguishes this task from other tasks |
| `title` | `Add search to notes` | Explains the work |
| `status` | `in-progress` | Shows its current stage |
| `dueDate` | `2026-11-15` | Helps with planning when a deadline exists |

The **data type** describes what values are allowed. A title is text; a count is an integer; a due date is a date rather than an arbitrary number. A task identifier should stay the same even if the title changes.

## Test the reasoning before the program

Consider these inputs:

| Input | Expected behaviour |
| --- | --- |
| `Prepare monthly report` | Save the note |
| `   ` | Reject as empty |
| `Pay electricity bill` | Save the note |
| A file location without write permission | Report an error without claiming success |

A **test case** gives an input and an expected result. A program that works for one normal example may fail on a blank value, invalid date or missing file. Thinking about errors early is part of building dependable software.

## Try the algorithm yourself

On paper, design a command for moving a task from **To do** to **Done**. Include a check that the requested task exists and consider what should happen if it is already marked Done. Now explain why a task identifier is safer than searching by title alone.

You have already begun designing a real project: inputs, rules, state and failure behaviour. The next chapters turn these decisions into scripts.

**Next:** [Use PowerShell to work with files and folders](05-powershell.md).
