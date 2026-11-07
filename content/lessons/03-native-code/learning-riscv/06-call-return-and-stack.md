<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-riscv/06-call-return-and-stack.md

PURPOSE:
Explain the lesson: Follow a function call and its saved return address.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a function call and its saved return address

## Setup recap
This is a source-reading and paper lab. You need the existing Assembly functions example. A function call transfers execution to another operation and provides a way to return. A calling convention assigns responsibilities to the caller and callee.

## Follow the return address
The return address identifies where execution should continue after a function. A leaf function makes no further calls. A function that calls another function must preserve any information it still needs after that nested call, including its own return path.

~~~text
caller -> helper -> nested helper
          needs its original return address after nested helper returns
~~~

## Source exercise
1. Open add_riscv64.S.
2. Find the exported symbol and the return instruction.
3. Check whether the function calls another function.
4. Identify the argument registers it consumes.
5. Identify the register holding the returned value.
6. Read the accompanying C declaration and compare types.

Do not invent a stack frame when the source does not need one. Conversely, do not assume a leaf function remains safe after inserting another call.

## Understand the stack
A stack is a memory region used for temporary call-related storage. Its pointer identifies the current position according to the platform convention. Allocating a frame, storing values, restoring them and releasing the frame must agree. Alignment is part of the convention too.

## Practical reasoning task
Draw two return addresses for a caller that invokes a helper which invokes another helper. Mark which value must survive each call. Explain why a single overwritten return-address register cannot represent both return paths at once.

## Connect to Umicom C
A compiler's generated calls must follow the same convention as the libraries they call. A program may assemble successfully and still fail if parameters, saved registers or stack alignment disagree.

## Limits and recovery
Consult the selected target ABI before writing a real call frame. Processor architecture alone does not specify every operating-system ABI detail. A crash on return should prompt inspection of saved state, not only the arithmetic result.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/assembly-functions/add_riscv64.S). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-branches-and-counted-loops.md)


[Next: Read an instruction contract](07-read-an-instruction-contract.md)
