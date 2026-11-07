# Allocation outputs and lifetimes

Allocating storage means setting aside space for some data. Ownership tells us who is responsible for that space. Lifetime tells us when the data may still be used. This lab follows an existing Bits2Banking arena: a teaching allocator that hands out pieces of a caller-owned array and can return to an earlier checkpoint.

## Setup recap

Install GCC with C23 support, CMake and Ninja as explained in [terminal setup](terminal-lab.md). No Framework SDK is needed for this isolated C exercise. Copy `labs/native/arena-allocator` from your Bits2Banking checkout into a new practice folder, such as `C:\umicom-learning\arena-allocator` or `$HOME/umicom-learning/arena-allocator`. Open a terminal in that folder. Use `Get-Content arena.h` in PowerShell or `cat arena.h` in Bash to read the public functions.

PowerShell, copying into a new destination:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force 'C:\umicom-learning'
Copy-Item -Recurse 'C:\umicom\Umicom-Bits2Banking\labs\native\arena-allocator' 'C:\umicom-learning\arena-allocator'
Set-Location 'C:\umicom-learning\arena-allocator'
Get-Content arena.h
```

Bash, copying into a new destination:

```bash
mkdir -p "$HOME/umicom-learning"
cp -R "$HOME/umicom/Umicom-Bits2Banking/labs/native/arena-allocator" "$HOME/umicom-learning/arena-allocator"
cd "$HOME/umicom-learning/arena-allocator"
cat arena.h
```

Copy once; repeating the copy into an existing destination can create a nested folder. Stop on any command error.

## 1. Trace ownership

```text
main owns workspace[512]
    └── arena describes used and remaining space
          ├── title points into workspace
          └── body points into workspace
checkpoint → allocate report → print report → rewind checkpoint
```

`BtbArenaInitialise` receives the backing array. It does not obtain memory from an operating system. `BtbArenaAllocate` advances the used count after checking the request. `BtbArenaCheckpoint` records a position. `BtbArenaRewind` makes later allocations available for reuse.

After rewind, the array still exists, but its old allocations no longer belong to that report. Another allocation can overwrite them. Do not keep using `title` or `body` as report values after that point. Rewinding does not securely erase confidential data.

## 2. Receive the correct pointer type

The allocator's last argument is `void **`: the address of an actual `void *` variable. A safe call is:

```c
void *storage = NULL;
BtbArenaStatus result = BtbArenaAllocate(&arena, 32U, 1U, &storage);
```

Check `result` before converting the returned pointer value to the type needed by your program. In C, assigning that `void *` value to `char *` is permitted. Casting the address of a `char *` variable to `void **` is different: it would let the function write through an incompatible pointer-object type. A cast can hide a diagnostic without fixing the underlying rule.

The report example now uses `titleStorage` and `bodyStorage` of type `void *`, then assigns their values to character pointers. A disabled section retains the older casts with an explanation for code review. Study the active path when following the exercise.

## 3. Build and inspect the result

The commands are the same in PowerShell and Bash:

```text
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
```

CTest runs ownership checks and the report demonstration. To see the report output after a passing run, use `ctest --test-dir build -V -R '^bits2banking[.]arena[.]report$' --no-tests=error`. Look for the report's final `Bytes after review: 0`. The earlier byte count includes both terminating zero characters and depends on the text's encoded bytes; do not infer it from the number of letters on screen.

Open `test_arena.c`. It requests more storage than the arena contains and checks that both the output pointer and used count stay unchanged. It also checks alignment: a rule saying which addresses are valid for a particular stored type.

## 4. Practise a refusal

In your copy of `main.c`, reduce the workspace to eight bytes. Rebuild. The report should return an error rather than copy text outside its storage. Restore 512 bytes and rerun both checks. If an assertion fails, inspect the allocation result before investigating `strcpy`; the copy is valid only after enough space was successfully reserved.

This lab teaches memory ownership, not a replacement production allocator. Applications should use existing Framework services where available. Continue with [Framework functions in a lab](../umicom-development/37-use-a-framework-function-in-a-lab.md), or return to [Learning C](index.md).

## Exercise and explanation

Does rewinding an arena securely erase the old report?

No. Rewind releases the allocation for reuse. Existing bytes can remain until overwritten; old report pointers must no longer be used as valid report allocations.

[Previous lesson](19-length-capacity-and-terminators.md) · [Course contents](index.md)

[Next: Follow a rejected function call](21-follow-a-rejected-call.md)

