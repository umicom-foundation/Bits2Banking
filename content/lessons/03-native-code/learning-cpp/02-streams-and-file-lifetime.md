# Streams and file lifetime

Saving a note moves information from memory to a file. A resource has to remain open long enough to use it, and be released when its owner finishes.

## 1. Inspect Save

Return to [notes.cpp](../../../labs/cpp-notes/notes.cpp) and find `Save`. Its `bool` result is either true or false. The parameter is a borrowed filename string. The `const` after the parameter list promises not to change the journal through this method; it does not promise that no external file changes.

```text
std::ofstream output(filename, std::ios::app);
if (!output) {
    return false;
}
```

An output file stream sends characters to a file. Constructing this object attempts to open the filename. `std::ios::app` requests append mode: existing content stays and writes go at the end. The condition checks the stream state after opening. A missing permission or unsuitable destination can make it fail.

 <svg viewbox="0 0 700 110" role="img" aria-label="A local stream owns access to a file while Save executes." style="width:100%;max-width:700px"><title>A local stream owns access to a file while Save executes.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">memory notes</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">file stream</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">notes.txt</text></svg>

A local stream owns access to a file while Save executes.

## 2. Read the loop

```text
for (const std::string& note : notes_) {
    output << note << '\n';
}
output.flush();
return output.good();
```

This range-based loop visits each stored string. The colon means “from this sequence”. Each iteration borrows the string without modifying it. Here `<<` sends text to the stream; it is not a comparison. `'\n'` is one newline character. `flush()` asks the stream to send buffered output onward. `good()` checks whether the stream has an error state.

## 3. Ownership at function exit

`output` is local to `Save`. Its destructor runs when the local object leaves scope, including ordinary early returns. A destructor is a cleanup function for an object. This pattern is often called resource acquisition is initialization: lifetime controls cleanup. It is useful but not magic. A device can still fail, and a successful stream flush is not a promise that data survives a power failure.

This small lab checks writes and flushing but does not explicitly check an error reported only during final close. It also does not replace a file atomically or coordinate two writers. Those are separate production requirements.

## 4. Predict repeated saves

1. The example adds two notes in memory.
2. Its first successful Save appends two lines.
3. Calling Save again on the same journal appends both lines again.
4. The vector is unchanged because Save does not clear it.

Expected answer: four newly appended lines after two successful saves, not two. Do not use a personal document as the output file while experimenting. `notes.txt` is relative to the process's current directory, which may differ from the source folder.

## 5. Connect the idea to Kernel C

In `umicom-kernel/kernel/console_shell.c`, `UmicomShellDescriptorClose` keeps a descriptor when closing fails. A descriptor is a service-owned identifier for an open file. The C implementation manages its lifetime explicitly. Both examples teach the same design question: who owns cleanup, and what happens when it fails?

Exercise: explain why “the method is const” and “the method does not write a file” are different claims. Answer: const limits changes through the journal object; Save deliberately changes external storage.

---

[Read this lesson in HTML](../../../courses/learning-cpp/lessons/02-streams-and-file-lifetime.html) · [Learning sequence](../../../start/learning-sequence.md)


## Continue learning

[Continue: Check a file operation](03-check-a-file-operation.md)
