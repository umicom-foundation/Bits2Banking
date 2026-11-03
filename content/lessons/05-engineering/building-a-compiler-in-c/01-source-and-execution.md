# From source text to a result

A program is a written description of work. The text you edit is called **source code**. A processor cannot directly obey an arbitrary text file: another program must interpret it or translate it into instructions the processor understands. Umicom C begins with a deliberately small translation problem.

## Read the first program

```c
int main(void) {
    return 7 * 6;
}
```

1. `int` says that the result is an integer: a whole number. This prototype uses signed 32-bit values, from −2,147,483,648 to 2,147,483,647.
2. `main` names the one entry function accepted by this language. A function is a named piece of work. Other function definitions are not yet supported.
3. `(void)` says that this function takes no arguments. Arguments are values supplied by a caller.
4. The braces `{ }` enclose the function body.
5. `return` supplies its result. The star means multiplication, so `7 * 6` produces 42. The semicolon ends the statement.

The source file is data until a tool processes it. It does not become an executable simply because its name ends in `.uc`.

## Follow the actual path

`src/lexer.c` groups characters into tokens. A token is one meaningful item, such as the number 7 or the multiplication sign. `src/compiler.c` checks the order of those items and emits small instructions. `src/vm.c` validates and executes them. The hosted command-line tool in `tools/main.c` reads files and prints results; those file operations are separate from the runtime.

**Hosted** means that an existing operating system supplies facilities such as files and the console. **Freestanding** code cannot assume those facilities exist. The runtime is designed without file, network or allocation calls so that it can also be linked into a native Kernel program.

## Try the prepared example

After building Umicom C using `docs/first-program.md`, run these commands from its repository directory:

```text
./build/windows-ucrt64-debug/bin/umicom-c.exe check examples/arithmetic.uc
./build/windows-ucrt64-debug/bin/umicom-c.exe run examples/arithmetic.uc
```

`check` checks the language and instruction structure. `run` additionally executes the instructions. Read the actual example before predicting its result; a file may have changed since you last opened it. The commands must finish successfully before their output can be treated as evidence.

## Paper exercise

Replace `7 * 6` with `7 + 6`. Which stage must change its output, and what is the new result?

<details>

<summary>Explanation</summary>

The lexer recognises a plus token instead of a star. The compiler emits ADD instead of MULTIPLY. The runtime returns 13. The return statement and function wrapper remain the same. This is a change in program behaviour, not just presentation.

</details>

If a command is not found, check its complete path and whether the build produced the executable. If compilation fails, keep the diagnostic and inspect that source location. Do not continue as though an old executable represents the failed new source.

## Find the implementation

Open `umicom-c/examples/arithmetic.uc` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/01-source-and-execution.html) · [Learning sequence](../../../start/learning-sequence.md)
