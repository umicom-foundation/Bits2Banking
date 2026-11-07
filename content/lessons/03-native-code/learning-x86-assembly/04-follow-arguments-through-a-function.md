<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-x86-assembly/04-follow-arguments-through-a-function.md

PURPOSE:
  Present "Follow arguments through an Assembly function" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow arguments through an Assembly function

A C function call and an Assembly function must agree on where arguments and results live. You will trace two small integers through the existing AddTwoAssembly example and learn how to separate a CPU instruction from the calling convention used by an operating system.

Source to open: `Umicom-Applications/framework/examples/learning/assembly/add_x86_64.S`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\examples\learning\assembly\add_x86_64.S'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/examples/learning/assembly/add_x86_64.S'
```

## Understand the idea

A register is a small storage location inside a processor. A calling convention is an agreement used by compiled functions: it specifies argument locations, result locations and which registers a function must preserve. The source selects the Windows register pair with a preprocessor condition and uses the System V pair for the other supported path. Both branches implement the same operation. The .S extension allows preprocessing before assembly; choosing a branch is part of the build configuration. Read add.h: this example accepts and returns uint32_t, an unsigned 32-bit integer. Its C reference uses unsigned addition, so results wrap modulo 2^32.

```text
C caller             Calling convention       Assembly       C caller
AddTwoAssembly(7,5) -> argument registers -> move and add -> result 12

Windows path: inspect ECX and EDX in the source.
Other supported path: inspect EDI and ESI.
Both paths return through EAX.
```

## Work through the lab

1. Find AddTwoAssembly and the conditional branch for Windows. Write down the two argument registers used by that branch and the result register. Repeat for the other branch.
2. Choose inputs 7 and 5. Copy 7 to the first argument register and 5 to the second in a paper trace. Follow the move and addition instructions in the selected branch; record the result after each instruction.
3. Repeat using the largest uint32_t value, 4294967295, and 1. Unsigned 32-bit addition returns 0. Trace the low 32 bits written to EAX. Do not silently change the C declaration to signed int; that would change the language contract for overflow.
4. Find the C declaration and caller beside this example using the file search in your editor. Check that both agree on the function name and parameter types. A matching name alone does not prove a matching binary interface.

## Expected result

Both supported branches should give the same uint32_t result for the same inputs, including unsigned wraparound. You should be able to explain why selecting the wrong calling convention can break a function even when its arithmetic instructions look correct.

## If the result differs

If a debugger later shows different values, first inspect the target architecture, argument types and selected preprocessor branch. A 64-bit operating system does not make every C integer 64 bits. Do not fix an interface mismatch by guessing registers until a single example happens to work.

## Explain it yourself

What three things would you compare before blaming the add instruction for a wrong result?

<details>
<summary>Worked explanation</summary>

Compare the C declaration and caller types, the build target and selected calling-convention branch, and the register contents on entry. Only after those agree should you inspect the instruction sequence and arithmetic boundaries.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-x86-assembly/lessons/04-follow-arguments-through-a-function.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-inspect-object-code.md) · [Course contents](index.md)

