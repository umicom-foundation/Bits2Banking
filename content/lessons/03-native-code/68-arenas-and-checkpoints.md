# 68. Build a bounded arena allocator in C23

A Notes application might create a temporary report containing hundreds of short strings. Calling the general-purpose allocator for every string is possible, but sometimes it is simpler to reserve a workspace and place the entire report inside it.

An **arena** manages one area of storage. It hands out non-overlapping ranges and can release a group of temporary allocations together. The programme still needs to know which component owns the original area.

## 1. Find the source files

Open [the Arena Allocator laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/arena-allocator). Its important files are `arena.h`, `arena.c`, `main.c` and `test_arena.c`. The header explains the contract; the C implementation performs the checks; the test probes failures.

The arena keeps three fields:

```c
typedef struct BtbArena {
    unsigned char *storage;
    size_t capacity;
    size_t used;
} BtbArena;
```

`storage` points to the memory that someone else owns. `capacity` is the number of bytes supplied. `used` is the number of bytes already reserved. At every valid moment, `used <= capacity`.

## 2. Understand alignment

A processor may expect an object such as a 64-bit integer to start at an address that meets an alignment requirement. For example, an 8-byte-aligned address is divisible by 8. The next free byte in an arena might not already be aligned.

The allocator therefore calculates a **padding** amount. If seven bytes have been used, the next 8-byte-aligned object may need one additional byte of padding, depending on the address of the storage.

```text
Storage start → [ seven bytes ][ padding ][ aligned object ][ remaining space ]
                                      ↑
                             returned address
```

The actual address matters: the first byte of the supplied buffer is not necessarily aligned to the type being requested. `BtbArenaAllocate` calculates alignment from the current address, not just from the offset.

## 3. Check before writing

Inspect this sequence in `arena.c`:

```c
size_t available = arena->capacity - arena->used;
if (padding > available || byteCount > available - padding)
    return BTB_ARENA_NO_SPACE;
```

The code validates `padding <= available` before evaluating `available - padding`. Otherwise an unsigned subtraction could wrap to a very large value and let an oversized allocation pass the check.

Only after checking all conditions does the function assign `*outMemory` and increase `arena->used`. This is a **failure-atomic operation**: a rejected request does not use any capacity and does not change the caller's existing pointer.

## 4. Build the laboratory

Open PowerShell at `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\arena-allocator" -B ".\output\learning-build\arena-allocator" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\arena-allocator" --parallel 2
ctest --test-dir ".\output\learning-build\arena-allocator" --output-on-failure
```

Two tests are registered. The first checks allocator contracts. The second runs a small Notes report and displays the temporary byte count. The exact number of bytes used depends on the strings and alignment.

## 5. Use a checkpoint

Before building the report, the example records the current `used` value. After printing the report, it rewinds to that checkpoint. No individual string is freed; the whole temporary section becomes available for reuse.

A rewind does **not** erase the old bytes, and the old addresses must not be used as live objects. Storing an arena pointer into a document that must survive a report refresh would be an ownership error.

An arena is helpful for temporary parse trees, report preparation, render frames and bounded scratch buffers. It is not automatically appropriate for documents that need independent lifetimes or long-term persistence.

## 6. Make a controlled change

Change `workspace[512]` in `main.c` to `workspace[16]`, rebuild and run the demonstration. The arena should reject an allocation rather than write beyond its bounds. Keep the unit test unchanged; it separately checks the failure path.

Restore the original capacity afterwards. Compare an arena with Umicom Framework's [`UmiAllocator`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/memory.h): one model divides a single known buffer, while the other allows a caller to supply general allocation callbacks.

Continue with [Lesson 69: Bounded byte slices](69-bounded-byte-slices.md).
