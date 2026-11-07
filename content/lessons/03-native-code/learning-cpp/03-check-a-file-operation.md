# Check a file operation

[Course contents](index.md) · [Previous: Streams and file lifetime](02-streams-and-file-lifetime.md)

## The result matters

Complete the two note-journal lessons first. A file stream is a C++ object that sends bytes to or reads bytes from a file. Creating a stream does not guarantee that the file can be opened. A missing parent directory, an invalid name or insufficient permission can prevent it.

Open `content/labs/cpp-notes/notes.cpp`. Locate `NoteJournal::Save`. The `::` notation identifies a member belonging to the class. `const` after the parameter list promises not to change the journal through that member function. It does not promise that the filesystem remains unchanged: saving is explicitly an external effect.

## Follow each step

```text
Open output stream -> did opening succeed?
  no: return false
  yes: write every note -> flush -> inspect stream state
```

The implementation uses `std::ios::app`. This means append, not replace: a second successful save appends the notes again. That is current example behaviour, not an automatic deduplication service. `flush()` requests delivery of buffered stream data; it is not a guarantee that a sudden power loss cannot lose data. `good()` checks stream state after that request.

## Run in a practice folder

After installing the compiler described in the first lesson, copy only the example into your own folder. In its terminal, run:

```text
g++ -std=c++17 -Wall -Wextra notes.cpp -o notes-demo
```

On Windows PowerShell run `./notes-demo.exe`; on Linux run `./notes-demo`. Inspect `notes.txt`. Run again and compare the line count. Expect the same two notes to be appended again. Do not point this exercise at an important document.

## Exercise and answer

In your practice copy, change the filename to `missing-folder/notes.txt` while that directory does not exist. Expect a failure message and a nonzero process exit code. The stream will not create the missing parent directory. Restore the original path afterward.

Explain why the caller checks the Boolean returned by `Save`: otherwise the interface could announce success despite a failed write. In Umicom applications, a thin interface should receive the shared persistence service's result and preserve the unsaved draft on failure. This small C++ example illustrates result handling; it does not replace Framework's persistence implementation or establish crash-safe storage.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](../../../labs/cpp-notes/notes.cpp). Path: `content/labs/cpp-notes/notes.cpp`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://isocpp.org/get-started). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-cpp/lessons/03-check-a-file-operation.html).

[Course contents](index.md) · [Previous: Streams and file lifetime](02-streams-and-file-lifetime.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next: Understand append and repeated saves](04-understand-append-and-repeated-save.md)
