# Execute instructions with checked arithmetic

A **virtual machine** is a program that carries out another instruction set. The current CVM is a small checked arithmetic interpreter. It is not a whole emulated computer and does not provide files, networking or arbitrary memory access.

## Follow the stack

A stack stores values in order. PUSH adds a value; an arithmetic operation takes its inputs from the top. For subtraction and division, the order matters: the most recently pushed input is the right-hand operand.

| Instruction | Stack afterwards, bottom to top |
| --- | --- |
| PUSH 9 | 9 |
| PUSH 4 | 9, 4 |
| SUBTRACT | 5 |
| RETURN | Result 5 is returned to the caller |

`umc_validate` first checks the entire instruction sequence. An ADD with only one value on the stack is invalid. A RETURN must be the final instruction and must have exactly one value available. Invalid instructions after an earlier RETURN are still rejected.

## Why arithmetic must be checked

A fixed-width number has a limited range. Adding 1 to the largest signed 32-bit value cannot produce a representable signed 32-bit answer. The runtime calculates addition, subtraction and multiplication in a wider signed 64-bit value, compares the result with the 32-bit limits, then narrows only when it fits.

Division needs its own rules. Division by zero is refused. Dividing the smallest signed value by −1 is also refused because the positive result is too large. Negating the smallest value has the same range problem. These checks occur before the dangerous narrow operation.

## Fuel is a work budget

**Fuel** is the maximum number of instructions the caller allows the interpreter to execute. PUSH 7, PUSH 6, MULTIPLY and RETURN require four units. With three units, execution must stop before RETURN and report `UMC_FUEL_EXHAUSTED`. Validation has a separate bounded cost; fuel does not count every operation performed by the C implementation.

`UmcResult` is written only on successful completion. On failure, its previous bytes remain unchanged. A caller must check the returned status rather than treating an old value as a new result. The Framework preview wrapper clears its displayed result before beginning another compile/execute attempt.

## Exercise

For PUSH 8, PUSH 2, DIVIDE, RETURN, predict the result and the minimum fuel. What changes if the second value is zero?

<details>

<summary>Explanation</summary>

The result is 4 and the minimum fuel is four. A zero divisor produces an arithmetic error and no new result. The instruction shape is valid in both cases: structural validation cannot prove that all arithmetic will succeed.

</details>

## Find the implementation

Open `umicom-c/src/vm.c` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/04-checked-execution.html) · [Learning sequence](../../../start/learning-sequence.md)
