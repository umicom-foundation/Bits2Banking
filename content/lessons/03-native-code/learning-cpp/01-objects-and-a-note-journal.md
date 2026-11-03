# Objects and a note journal

A program needs both information and operations on that information. An object brings those two things together. Read this lesson without installing a compiler.

## 1. Start with the existing example

Open [the Umicom note journal source](../../../labs/cpp-notes/notes.cpp). A source file is text written for a compiler, a tool that translates instructions into an executable program. This file uses C++, a separate language from C. Knowing one does not mean every rule is the same in the other.

 <svg viewbox="0 0 700 110" role="img" aria-label="The journal stores each accepted note in its own sequence." style="width:100%;max-width:700px"><title>The journal stores each accepted note in its own sequence.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">journal object</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Add a note</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">notes_ sequence</text></svg>

The journal stores each accepted note in its own sequence.

## 2. Read an object declaration

```text
NoteJournal journal;
journal.Add("Plan the Umicom task board");
```

`NoteJournal` names the kind of object. `journal` is this particular object. The semicolon ends the statement. The dot selects something belonging to the object. `Add` is a function, also called a method here. The parentheses contain the value sent to it. Double quotation marks surround text; they are not part of the stored note.

## 3. Understand the class

A `class` describes which data and operations objects have. `public:` makes the following operations available to callers. `private:` keeps the stored sequence behind those operations. This helps the class control changes; it is not encryption or a security boundary between hostile programs.

The field `std::vector<std::string> notes_;` is a resizable sequence of strings. A string owns a sequence of characters. `std::` identifies names from the C++ standard library. The angle brackets give the vector its element type. The trailing underscore is a naming convention, not special C++ syntax.

## 4. Follow a borrowed input

```text
void Add(const std::string& note) {
    if (!note.empty()) {
        notes_.push_back(note);
    }
}
```

`void` means there is no returned value. The ampersand makes `note` a reference to a string. `const` prevents this function from changing the string through that reference. `empty()` asks whether its length is zero. The exclamation mark means “not”. Braces group statements. `push_back` adds a copy to the vector; the journal does not keep a reference to the caller's string.

## 5. Trace and compare

1. Start with no notes.
2. Add `"Review a lesson"`: the vector now has one string.
3. Add `""`: the condition is false, so it still has one.
4. Add three spaces: the string is not empty, so this implementation accepts it.

Try the trace before checking each answer. Empty and whitespace-only input are different. A later product policy may reject both; do not assume this introductory lab already does.

In the C23 Kernel, structures and explicitly named functions provide related organization. Compare `UmicomUserContract` in `umicom-kernel/include/umicom/user/native_contract.h`. Reusable Umicom services remain C23; learning C++ does not change their implementation language.

## Words to keep

Object

A value with a type and a lifetime.

Method

A function associated with a class.

Reference

Another way to refer to an existing object; it does not create ownership by itself.

---

[Read this lesson in HTML](../../../courses/learning-cpp/lessons/01-objects-and-a-note-journal.html) · [Learning sequence](../../../start/learning-sequence.md)
