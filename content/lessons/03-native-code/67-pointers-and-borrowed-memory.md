# 67. Pointers, arrays and borrowed memory in C23

A Notes application keeps text, lists of documents and information about the active window. When several components need to read the same information, copying everything is often unnecessary. C provides a way to refer to existing storage: a **pointer**.

A pointer holds an address. It does not, by itself, tell us whether the address is valid, how many bytes can be accessed, or who is responsible for releasing the storage. These questions are part of the interface between functions.

## 1. Start with one object

Consider the number of saved notes:

```c
#include <stdio.h>

int main(void)
{
    unsigned savedNotes = 3U;
    unsigned *countAddress = &savedNotes;

    printf("Saved notes: %u\n", *countAddress);
    return 0;
}
```

`&savedNotes` means “the address of `savedNotes`”. The variable `countAddress` holds that address. `*countAddress` means “read the object at this address”. Because `countAddress` points to `savedNotes`, the programme prints `3`.

The expression `unsigned *countAddress` declares a pointer; `*countAddress` in the `printf` expression reads through it. The same symbol has a different role in the declaration and in the expression.

Try changing `savedNotes` to `8U`. Compile and run the programme again. It should print `8`. Both names refer to one stored number; we have not made a second number.

## 2. A pointer is not an array length

Imagine an API that receives a list of fictional account balances:

```c
#include <stddef.h>
#include <stdint.h>

uint64_t SumBalances(const uint32_t *values, size_t count)
{
    uint64_t total = 0U;
    for (size_t i = 0U; i < count; ++i)
        total += (uint64_t)values[i];
    return total;
}
```

This function accepts **two pieces of information**: the address of the first value and the number of elements. A pointer does not remember how many elements are in the array. The caller must supply the correct count.

The accumulator uses `uint64_t` because summing several `uint32_t` balances can exceed the range of a single `uint32_t`. With a sufficiently large count, even a 64-bit total could overflow; a production API would specify limits or use checked addition.

A pointer into a local array must not outlive that array. Do not store an array pointer in a long-running application when the array was created inside a function that has already returned.

## 3. Learn the difference between owning and borrowing

Suppose Umicom Notes has opened a document. The document store **owns** its text. A search function may **borrow** the text for the duration of one call; it must not free that text or keep the pointer after the document is closed.

```text
Document store (owner)
  └── allocated text buffer
          │
          ├── Search function (borrows during call)
          └── Preview function (borrows during call)
```

A borrowed pointer is safe only while its owner guarantees the object remains alive and unchanged in ways that would invalidate the pointer.

C has no automatic enforcement of ownership for arbitrary pointers. We establish the rules in interface contracts and confirm them with tests.

## 4. Understand `const`

A function parameter such as `const unsigned char *bytes` promises that the function will not modify the bytes **through that pointer**. It does not prove that another owner will not change them, and it does not make the memory immortal. The array must still remain valid while the function reads it.

For network requests and binary files, combine a byte pointer with an explicit length:

```c
int HasHeaderPrefix(const unsigned char *bytes, size_t count)
{
    return bytes != NULL && count >= 4U &&
           bytes[0] == 'G' && bytes[1] == 'E' &&
           bytes[2] == 'T' && bytes[3] == ' ';
}
```

The function checks `count >= 4U` **before** reading `bytes[3]`. Swapping that order can produce an out-of-bounds read.

## 5. Inspect a real Umicom contract

Open the public Framework header [`include/umicom/base/memory.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/memory.h). It defines an `UmiAllocator` containing allocation, reallocation and release callbacks.

The header shows how a caller supplies the allocation policy while the shared Framework defines the interface. It is also a good example of separating a public declaration from a C implementation.

Next open the [Arena Allocator laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/arena-allocator). It turns these ideas into a working Notes report.

## 6. Check your understanding

Explain why `char *name` is insufficient to check whether 20 bytes are available. Explain who owns the storage when a function receives `const char *text` but does not allocate or copy the text. Finally, explain why returning the address of a local variable creates a lifetime defect.

Continue with [Lesson 68: Arenas and checkpoints](68-arenas-and-checkpoints.md).

## Continue with a connected course

[A byte span is not a string](../../courses/umicom-kernel-from-scratch/lessons/02-bounded-input.html) — Apply bounds and lifetime ideas to Kernel input.

[Find prerequisites and other learning routes](../../start/systems-learning.md). Return to this chapter whenever the course refers to its concepts.
