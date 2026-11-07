# Register and memory worksheet

Start with the sum of three uint64_t values: 2, 5 and 9. Give the array a symbolic address A; each element occupies eight bytes.

| Point | t0 | a1 | a0 |
| --- | --- | --- | --- |
| Before the loop | A | 3 | 0 |
| After the first iteration | A + 8 | 2 | 2 |
| After the second iteration | A + 16 | 1 | 7 |
| After the third iteration | A + 24 | 0 | 16 |

The final pointer is one element beyond the array. The loop stops before loading from that address.

Repeat the worksheet for count zero and a null pointer. The branch must reach the return before any load. A nonzero count with a null or invalid pointer violates the caller contract; this lab does not discover memory mappings.

For the nested call, draw the 16-byte stack frame. The saved s0 occupies bytes 0–7 and ra occupies bytes 8–15. Check that every store has a matching load and that the stack pointer returns to its original value.

For rotation, mark bit 63 and rotate left once. It becomes bit zero. Test zero, 64 and 65 as distances. Normalization uses the low six bits, so these correspond to zero, zero and one.

For parity, write the low bit observed at each step. XOR combines the observations into zero for an even number of set bits and one for an odd number. No parity bit identifies where a corruption occurred.

Connect this worksheet to Umicom Kernel by locating arch/riscv64/trap_entry.S. A trap saves much more state than this ordinary function call. List the additional saved registers before attempting to modify either implementation.
