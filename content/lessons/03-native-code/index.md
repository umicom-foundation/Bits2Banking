# Assembly, C, C++ and Java

Understand the relationship between source code, machine instructions and runtimes.

- [8. Assembly: instructions the processor can execute](08-assembly.md)
- [9. C: write a native note-saving program](09-c.md)
- [10. C++: objects, libraries and resource ownership](10-cpp.md)
- [11. Java: programs, objects and exact monetary values](11-java.md)

[Explore the practical source files](../../labs/index.md)

## Continue with low-level systems programming

- [35. Assembly and processor calling conventions](35-assembly-and-processor-contracts.md) — trace registers and call a native Assembly function from C.
- [36. Writing safer C23](36-safer-c-programming.md) — use explicit memory ownership, bounds, error checking and small tests.

- [53. Call an Assembly function from C23](53-call-assembly-from-c.md) — use a real machine-level calling convention and test 100 boundary pairs.
- [55. Write a safe binary record in C23](55-write-a-safe-binary-record-in-c.md) — implement a checked, fixed-width wire format without structure casts.

## Memory ownership and checked numbers

- [58. Who owns this memory?](58-memory-ownership-in-c23.md) — build an owned Notes store, copy input text and release allocations safely.
- [59. Checked arithmetic and fictional accounts](59-checked-arithmetic-and-money.md) — use exact pence and reject overflow before changing two training account balances.
- [60. Find defects with tests and sanitizers](60-debugging-undefined-behaviour.md) — use compiler warnings, CTest, ASan and UBSan on supported toolchains.
## Testing C23 programs under failure

- [64. Make allocations fail on purpose](64-test-allocation-failures.md)
- [65. Parse incoming bytes without assuming a string](65-parse-bounded-http-bytes.md)
