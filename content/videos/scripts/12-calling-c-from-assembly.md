# Episode 12 — How C calls Assembly functions

**Approximate duration:** 16–20 minutes  
**Related lesson:** [Call an Assembly function from C23](../../lessons/03-native-code/53-call-assembly-from-c.md)  
**Source code:** [Assembly functions laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/assembly-functions)

## 00:00–02:00 — A C function and a processor

**Narration:**

"When a C function is called, the processor does not see the original C source. It executes machine instructions that have been compiled from that source. The function needs to know where its inputs are, where to leave its answer and how to return to the caller. Those rules are part of an application binary interface, usually shortened to ABI.

"We will implement one function in Assembly and call it from C23. We will then compare its results with a normal C function. The example uses fictional reference numbers; no bank or trading operation is involved."

**On screen:** Open `main.c`, highlight the function declaration and show the Assembly-register diagram. Zoom in on the return type `uint32_t`.

## 02:00–05:00 — Define the function contract

**Narration:**

"Start with this declaration: `extern uint32_t AddTwoAssembly(uint32_t left, uint32_t right);`. It tells the compiler that another file supplies the function. We are not passing a pointer to a mutable account or asking the function to allocate memory. It receives two fixed-width unsigned values and returns one value."

**On screen:** Show `AddTwoC` immediately below the Assembly declaration. Point out that unsigned overflow has defined wraparound and compare it with signed overflow.

**Demonstration:** Draw the first two values in a simple register diagram. Write `27`, `15`, and the result `42`.

## 05:00–09:00 — Compare the calling conventions

**Narration:**

"On Windows x64, the first two integer values are placed in ECX and EDX. On Linux x86-64 using the System V ABI, the corresponding registers are EDI and ESI. Both platforms use EAX for this 32-bit return value. RISC-V64 uses a0 and a1 for the inputs and a0 for the return.

"Notice that sharing an instruction set does not necessarily mean sharing a calling convention. Windows and Linux are both using x86-64 here, but the argument registers are different."

**On screen:** Open `add_x86_64.S` and then `add_riscv64.S`. Highlight `movl`, `addl`, `addw`, and `ret`. Do not claim the RISC-V code has run on the current x86-64 computer.

## 09:00–13:00 — Build the real example

**Narration:**

"CMake reads the project description and selects the Assembly file appropriate to the target architecture. Ninja then compiles the C source, assembles the low-level source and links both object files into one executable."

**On screen:** Run the Windows PowerShell commands from the lesson, one at a time. Highlight the configure output, build output, and one passing CTest result.

**Demonstration:** Run the executable and show `C and Assembly agree on 100 value pairs.` Explain that the test includes values near the unsigned 32-bit limit.

## 13:00–16:30 — What the linker does

**Narration:**

"The compiler accepts the declaration of an external function. The assembler produces the definition. The linker connects them. If their symbol names do not match, the linker reports that the function cannot be found."

**On screen:** Temporarily change the function name only in the C declaration, build, show the link failure, then restore the name. Rebuild and run the test.

## 16:30–19:00 — From a function to a kernel

**Narration:**

"We have used Assembly inside an ordinary application, where the operating system has already started the process. The first instructions of an operating-system kernel have a different responsibility. They may need to prepare the stack and memory before entering C. Umicom Kernel gives us a real RISC-V example of this transition."

**On screen:** Open the [Umicom Kernel first-boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md) and identify `_start` and `UmiKernelMain()`.

**Closing:** "Use the linked lesson to repeat the commands and make one controlled change. Continue next with the first steps in Umicom Kernel. The written guide and source are available on the Bits2Banking website and GitHub."
