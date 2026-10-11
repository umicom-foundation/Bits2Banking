# Other compiled languages: C++, Rust, Zig, Go and Java

C and Assembly are useful foundations because they reveal how instructions, memory and operating-system interfaces fit together. They are not the only ways to build efficient software. Different languages offer different methods for controlling memory, sharing code and running applications.

A useful comparison starts with a real task: a Notes application must store a title, find a note and save it safely. The same task can be expressed in several languages, but each language has its own execution model and failure rules.

## 1. What does "compiled" mean?

A compiler translates source code into another representation. Sometimes that representation is native machine code. Sometimes it is an intermediate form run or further compiled by a virtual machine.

- **C, C++, Rust, Zig and Go** commonly produce native executables for a selected operating system and processor architecture.
- **Java** usually compiles source into JVM bytecode. The Java Virtual Machine can interpret or just-in-time compile bytecode while the program runs.
- **C#** commonly compiles into intermediate language consumed by .NET, which may use just-in-time or ahead-of-time compilation.
- **Python and PHP** commonly execute through managed language runtimes; they also have compilation steps and alternative implementations, so calling them simply “not compiled” is misleading.

The source language alone does not tell you the speed of a finished program. Algorithms, allocations, I/O, compiler settings, data locality and the runtime all matter.

## 2. Compare memory and interoperability

| Language | Memory/resource model | Typical role in Umicom learning |
|---|---|---|
| C23 | Explicit ownership, pointers and manual resource management | Framework core, kernel code, native APIs and reusable modules |
| C++ | RAII, destructors, templates and standard containers | Adapter layers and specialist libraries with a controlled C boundary |
| Rust | Ownership and borrowing checked by the compiler; controlled unsafe operations | Alternative native modules and safe interoperability experiments |
| Zig | Explicit allocators, compile-time facilities and direct C interoperability | Experimental native utilities and cross-compilation lessons |
| Go | Garbage-collected runtime and built-in concurrency facilities | Supporting network tools or independently deployed services |
| Java | JVM, garbage collection, exceptions and mature enterprise libraries | Financial-system connectors and Calypso interoperability |
| C# | Managed .NET runtime and extensive application frameworks | Managed integrations and comparative application exercises |
| Fortran / Ada | Strong history in numerical/scientific or safety-sensitive software | Optional specialised computation and language-design study |

These are useful tendencies, not absolute rules. A project can use a different runtime or compilation mode when justified.

## 3. Keep Umicom's ABI stable

Umicom Framework has a C-first design and a stable C ABI at cross-module binary boundaries. This allows a C++ library to use classes internally while exposing a small C-compatible function table. Managed-language components can use a supported foreign-function interface or communicate over an explicit service protocol.

A C++ exception should not escape through a C ABI. A pointer must not cross a boundary without a documented lifetime. A Java object reference is not a normal C object pointer. The adapter translates representations and takes responsibility for errors at that boundary.

## 4. An exercise to compare languages

Take the C Notes lab in `labs/native/safe-notes`. Its essential rules are that a note has a bounded capacity, an invalid update is rejected and a failed edit preserves the previous content. Reimplement those rules in another language, using that language's preferred data types and resource-management facilities.

Do not stop when the program prints one successful note. Test an empty title, a very long title and a rejected update. Compare how each language handles errors, allocations and ownership.

## 5. Choose a language for a problem

For a program talking to a processor or a kernel, a small amount of C and Assembly may expose the necessary hardware control. For a GUI adapter that already provides a C++ SDK, C++ can avoid unnecessary reimplementation. For a financial connector built around a Java SDK, Java may be the correct boundary. For website content, HTML and CSS are not alternatives to C: they solve different parts of a system.

Read the [C++ introduction](../03-native-code/10-cpp.md), [Java introduction](../03-native-code/11-java.md) and the [Umicom integration architecture](../06-umicom/23-introducing-umicom.md) before building cross-language adapters.
