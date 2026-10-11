# Learning roadmap

Bits to Banking begins with understanding a computer and progresses towards developing software, operating systems, financial applications and reusable Umicom components. Each part has practical exercises. You can revisit an earlier chapter whenever the next topic introduces an unfamiliar concept.

## 1. Computers and digital information

You will explore the parts of a computer, binary numbers, logic gates, memory, storage and the processor's instruction cycle. You will learn how a high-level command eventually becomes an instruction understood by a CPU.

Begin with [Inside a computer](lessons/01-computers/01-inside-a-computer.md) and [Bits and logic](lessons/01-computers/02-bits-and-logic.md).

## 2. Assembly and C23

You will compare the same operation in C and Assembly, learn about registers, the stack, function-call conventions, pointers, memory ownership and runtime errors. You will build a small note-taking model and test how it behaves when inputs are too long.

Start with [From C to Assembly](lessons/03-native-code/35-assembly-and-processor-contracts.md) and [Writing safer C](lessons/03-native-code/36-safer-c-programming.md).

## 3. How a program is built

You will use GCC and Clang to compile source files, a linker to combine object files, CMake to describe build targets, Ninja to run a build and CTest to test the result. Later lessons introduce static and shared libraries, build profiles, cross-compilation, package managers and third-party dependencies.

Read [Building with CMake and Ninja](lessons/05-engineering/37-cmake-and-build-systems.md) and [Libraries and package management](lessons/05-engineering/38-package-managers-and-c-libraries.md).

## 4. How websites are delivered

You will follow an HTTP request from a browser through a socket to a C program. Build a website, start the Umicom native learning-site server, inspect responses and learn how the server prevents requests from escaping the selected directory. The source lives in Umicom Framework.

Continue with [Build and examine a web server in C](lessons/05-engineering/39-build-a-c-web-server.md), then [inspect HTTP line endings in C and Assembly](lessons/05-engineering/42-http-and-assembly.md).

## 5. How a kernel starts

You will understand what changes when a C program cannot rely on an operating system. Read the original Umicom Kernel boot path: RISC-V reset, Assembly entry, stack setup, C23 kernel entry, UART messages, interrupts, memory and address translation. Run the kernel under QEMU before studying more advanced services.

Read [Boot and inspect Umicom Kernel](lessons/06-umicom/40-boot-umicom-kernel.md).

## 6. Additional programming languages

Continue into modern C++, Java, Rust, Zig, Go and other compiled languages, together with Python, PowerShell, Bash, PHP, HTML, CSS and JavaScript. The lessons examine compilation, memory management and suitable use cases rather than treating every language as interchangeable.

Explore the [compiled-language landscape](lessons/05-engineering/41-other-compiled-languages.md).

## 7. Build with Umicom

Use the actual [Umicom Framework](https://github.com/umicom-foundation/umicom-framework), [Umicom Applications](https://github.com/umicom-foundation/umicom-applications), [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel) and [Umicom OS](https://github.com/umicom-foundation/umicom-os). Progress from a small reusable library to a window, menu, document, Data Server contract and tested application.

## 8. Finance, values and service

Explore software project management, accounting, account types, banking, treasury and trading systems. [Islam: Blueprint for Life](v001_islam_blueprint_for_life/index.md) remains available as a book on purpose, justice, fair trade, financial ethics and using knowledge responsibly.

**We Value Each Other and Together Everyone Achieves More.**

**Service to Many Leads to Greatness.**
