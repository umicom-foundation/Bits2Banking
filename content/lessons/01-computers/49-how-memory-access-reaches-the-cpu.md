# 49. How memory access reaches the CPU

When a program opens a document or calculates a bank balance, the processor must obtain instructions and data. Not all data is equally close to the CPU. Registers hold a small amount of information inside the processor; caches keep recently or nearby used information; main memory holds a much larger working set. Storage retains files when the computer is switched off.

Understanding these layers helps explain why two programs that calculate the same answer can take different amounts of time.

## 1. Registers, cache, RAM and storage

A **register** is a small location built into the CPU. Machine instructions work with registers directly. **Cache memory** is a smaller, faster memory that helps the processor avoid repeated trips to RAM. **RAM** holds code and data used by running processes. **Storage**, such as an SSD, retains applications, documents and databases.

```text
              CPU
    ┌───────────────────┐
    │ Registers         │  machine instructions use these
    │ L1 / L2 cache     │  often nearby to a CPU core
    └────────┬──────────┘
             │
         Shared cache      may exist; processor dependent
             │
         Main memory       larger working set
             │
         SSD or disk       persistent files
```

The diagram is simplified. Cache levels, policies and sizes depend on the processor. A CPU can spend time waiting for data even when its arithmetic instructions are fast.

## 2. What is a cache line?

Processors often transfer a contiguous block of memory into cache rather than fetching one byte at a time. This block is a **cache line**. A commonly encountered size is 64 bytes, but software must not assume every processor has that size.

Imagine an array with eight numbers stored next to each other. When the first number is read, nearby numbers may already be available to the CPU. Repeatedly reading addresses far apart can make it harder to reuse data already in cache.

This is one reason data layout and iteration order can matter, even when every value and the final answer remain unchanged.

## 3. Build a small experiment in C23

Open the [complete cache-memory experiment](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/cache-memory). The program contains an array treated as a table of rows and columns.

One loop reads values row by row. Another reads column by column. Both visit every element and must produce the same sum.

Open PowerShell in `C:\umicom\Umicom-Bits2Banking` and run:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\cache-memory" `
    -B ".\output\learning-build\cache-memory" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cache-memory" --parallel 2
ctest --test-dir ".\output\learning-build\cache-memory" --output-on-failure
& ".\output\learning-build\cache-memory\umicom-cache-memory.exe"
```

If a command fails, read the first error before continuing. CMake prepares build instructions, Ninja compiles and CTest runs a check.

The two checksums must match. Times may differ because of cache behaviour, compiler optimisations, the operating system and other activity. This experiment is an illustration, **not a measurement of your processor's cache size**.

## 4. Connect this to Umicom

Umicom Framework uses arrays, structures, queues and buffers in its runtime and application services. Developers should first make those structures correct, bounded and easy to understand. Profiling should identify a genuine performance bottleneck before an implementation is optimised.

Umicom Kernel manages memory mappings and access permissions. CPU caches accelerate access to the corresponding physical memory. Virtual memory and CPU cache are different mechanisms. Read the [Umicom Kernel source](https://github.com/umicom-foundation/umicom-kernel) and the [virtual-memory guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/VIRTUAL_MEMORY.md) to see how memory management develops from the early boot stages.

## 5. Your exercise

Find the two nested loops in `main.c` and explain which variable changes fastest in each. Predict whether the totals should match, then run the program. Record the checksums and timing on your computer. Change the array dimensions within a manageable memory size, rebuild and repeat.

The lesson is complete when you can explain why the checksums agree, how read order changes locality and why a single timing result does not prove a hardware property.

[Continue with compilers and build systems](../05-engineering/18-build-and-tests.md).
