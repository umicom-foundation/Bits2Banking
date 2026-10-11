# Writing safer C: memory, ownership and checks

C gives a developer precise control over data layout, memory and operating-system interfaces. That control is useful when building a framework or kernel, but it also means that the programmer must define what memory an operation may read and write.

In this lesson, you will build a small Notes record, reject oversized input without damaging existing text and prove its behaviour with tests.

## 1. Know what an array can hold

```c
char title[8];
```

This declaration reserves eight bytes. When the text is a normal C string, the final byte must normally contain `\0`, the null terminator. The array can therefore hold at most seven one-byte characters plus the terminator.

Writing eight characters and then a terminator beyond the array's boundary is an out-of-bounds write. It may corrupt unrelated data or crash the program. There is no automatic capacity expansion for an ordinary fixed C array.

A **buffer** is a region of memory holding data. Its **capacity** is the available storage, while its **length** describes the number of meaningful bytes. A safe interface does not treat these quantities as interchangeable.

## 2. Declare the Notes record

Open [`labs/native/safe-notes/notes.h`](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/safe-notes/notes.h).

```c
#define UMICOM_NOTE_CAPACITY 128U

typedef struct UmicomNote {
    char bytes[UMICOM_NOTE_CAPACITY];
    size_t length;
} UmicomNote;
```

The `UmicomNote` owns 128 bytes of storage and records the length separately. The record is owned by the code that creates it; a function receiving `UmicomNote *` borrows access temporarily.

The type `size_t` represents object sizes and array positions. It is an unsigned integer type large enough for the size of any individual object that your implementation supports.

## 3. Return an explicit result

The public function returns a named status instead of silently discarding an oversized note.

```c
typedef enum UmicomNoteStatus {
    UMICOM_NOTE_OK = 0,
    UMICOM_NOTE_INVALID_INPUT = 1,
    UMICOM_NOTE_TOO_LONG = 2
} UmicomNoteStatus;

UmicomNoteStatus UmicomNoteSet(UmicomNote *note,
                              const char *text,
                              size_t length);
```

Three questions make the contract clear. First, who owns the memory? The caller owns both `note` and `text`. Second, how much data can be copied? Only `length` bytes, and only when space remains for `\0`. Third, what happens if the input is not valid? The old note remains unchanged.

## 4. Read the implementation

The implementation is in `labs/native/safe-notes/notes.c`:

```c
UmicomNoteStatus UmicomNoteSet(UmicomNote *note,
                              const char *text,
                              size_t length)
{
    if (note == NULL || text == NULL)
        return UMICOM_NOTE_INVALID_INPUT;
    if (length >= sizeof(note->bytes))
        return UMICOM_NOTE_TOO_LONG;

    memmove(note->bytes, text, length);
    note->bytes[length] = '\0';
    note->length = length;
    return UMICOM_NOTE_OK;
}
```

The function checks both pointers before dereferencing them. It checks the length *before* modifying the destination. This gives **failure-atomic behaviour**: when a check fails, it returns without changing the record.

`memmove` is used so an edit referring to overlapping bytes within the same record can be copied safely. For non-overlapping buffers, `memcpy` is also possible, but the contract must forbid overlap if you choose it.

The caller still has responsibilities. It must pass a readable `text` buffer with at least `length` bytes. The function can check the value of a pointer, but ordinary C cannot reliably prove that every address supplied by a caller points to readable memory.

## 5. Build the complete example

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\safe-notes" -B ".\build\safe-notes" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\build\safe-notes" --parallel 2
ctest --test-dir ".\build\safe-notes" --output-on-failure
& ".\build\safe-notes\bits-notes.exe"
```

The program prints:

```text
Note (32 bytes): Plan the Umicom Framework lesson
```

The CTest test checks ordinary input, empty input, invalid pointers and an oversized buffer. It also checks that the original note survives a refused update. A test is not only a successful printout; it is executable evidence of a rule the program promises to honour.

## 6. Try a failure deliberately

In `main.c`, change `text` to a sentence longer than 127 bytes. Rebuild and run. The function should refuse the input; it should not cut the sentence silently to fit.

Look at `test_notes.c`. It fills a buffer larger than `UMICOM_NOTE_CAPACITY` and verifies that the earlier note remains unchanged. This is more reliable than checking that one particular machine happens not to crash.

## 7. Understand stack, heap and lifetime

The note in our `main` function is a local variable. Its storage normally belongs to the function's automatic storage duration; it ceases to exist when that function returns. You must not return a pointer to that local note for another function to use later.

Heap allocation permits dynamically sized storage whose lifetime you control, commonly using `malloc` and `free`. A successful allocation must eventually be released by its owner. A pointer must not be used after its allocation is freed.

For this small Notes record, a fixed local value is simpler. The Framework will introduce dynamic allocation when a real requirement justifies it, such as a collection of documents of variable length.

## 8. Check arithmetic and integer types

`size_t` is unsigned. Expressions such as `capacity - length` can wrap if `length > capacity`. Check the relationship first:

```c
if (length > capacity) return UMICOM_NOTE_TOO_LONG;
size_t remaining = capacity - length;
```

Avoid using a floating-point `double` to represent an exact cash amount in banking examples. Use integer minor units or an explicit decimal type with documented scale and rounding rules. A numeric value is safe only when both its representation and permitted range match the problem.

## 9. Build with strict diagnostics

GCC and Clang can report suspicious conversions, shadowed names and unused variables:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow `
    -I ".\labs\native\safe-notes" `
    ".\labs\native\safe-notes\notes.c" `
    ".\labs\native\safe-notes\main.c" `
    -o ".\build\safe-notes-manual.exe"
```

Warnings are not a proof that the program is safe, and a warning-free build is not a substitute for boundary tests. Sanitizers, static analysis, fuzzing and code review provide additional evidence; availability varies by platform and compiler.

## 10. Apply the lesson to Umicom Framework

A reusable Umicom component should document whether the caller or Framework owns returned memory; whether an input pointer can outlive a call; the capacity of output storage; which thread may change state; and the exact meaning of success and failure.

The same rules apply to a text editor, a bank-account model, a trading position and the Umicom Kernel. A successful software design makes unsafe assumptions visible rather than relying on other developers to guess them.

Continue with [CMake and build systems](../05-engineering/37-cmake-and-build-systems.md) and the [native webserver exercise](../05-engineering/39-build-a-c-web-server.md).
