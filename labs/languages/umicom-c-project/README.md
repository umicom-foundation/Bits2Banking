# A small programming-language project

Use the existing Umicom C compiler to follow source text through tokens,
instructions and execution. A **token** is a recognised piece of source, such as
a number or a plus sign. An **instruction** tells the virtual machine what to do.
The project introduces a small C-like language; it is not a complete C implementation.

1. Follow [Building a Compiler in C](../../../content/courses/building-a-compiler-in-c/index.html).
2. Prepare the separate Umicom C checkout using its
   [execution guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/execution-guide.md).
   Keep the compiler and its own tests together.
3. Predict the result of `answer.uc`: grouping makes 8 + 2 happen before multiplication.
4. Run the compiler commands shown in the course. Expect 30.
5. Compile `budget.uc` to a new file, disassemble it, then execute it with a
   four-instruction budget. Expect 42. A three-instruction budget must fail.
6. Write down a proposed language feature's syntax, meaning, invalid cases and
   tests before extending the compiler.

This folder supplies input programs, not another compiler implementation.
Compilation and execution use Umicom C. Shared application integration belongs
in Umicom Framework. An instruction budget is not a complete security sandbox.

