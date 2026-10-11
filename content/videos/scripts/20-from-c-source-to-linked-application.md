# Episode 20 — From C23 source to a linked application

**Duration:** Approximately 15–19 minutes, including live compilation and review.

**Companion reading:** [Lesson 72](../../lessons/05-engineering/72-source-to-machine-code.md) and [Lesson 73](../../lessons/05-engineering/73-link-one-c-library.md).

**Working example:** `labs/native/course-catalogue-library/` in Bits2Banking.

## 00:00–01:30 — Introduce the problem

**On screen:** Show the folder containing `catalogue.h`, `catalogue.c`, `main.c` and `test_catalogue.c`. Then show an application window or terminal displaying three course modules.

**Narration:**

"Imagine we are building part of the Bits2Banking educational platform. We need one catalogue that knows which learning modules exist and how many lessons each contains. We will use it in a small application and in an automated test. We do not want to copy the catalogue implementation into both programmes. Instead, we will put it into a library and ask the linker to connect the pieces.

A C compiler is only one step in that process. In this video we will follow an individual C source file through preprocessing, Assembly generation, object compilation and linking. At the end, we will build the complete application and test that it behaves as expected."

## 01:30–03:30 — What the header provides

**On screen:** Highlight the declaration of `BtbCatalogueInit` in `catalogue.h`, then its definition in `catalogue.c`.

**Narration:**

"A declaration describes an interface. The compiler learns the name of a function, the type of its arguments and the type of the value it returns. The implementation lives elsewhere. Look at the header: it declares `BtbCatalogueInit`. Now open `catalogue.c`. Here is the function body that actually clears the catalogue to a known state.

When `main.c` includes `catalogue.h`, it knows how to call the function. But it has not yet received the compiled implementation. That is why linking exists. The linker will later find the definition and connect the caller to it.

This separation is also important in Umicom Framework. Applications use Framework interfaces, but they should not copy the Framework implementation into their own source directories."

## 03:30–05:30 — Preprocess the file

**On screen:** Run the `gcc -std=c23 -E` command from Lesson 72. Open `output/compiler-lab/main.i`.

**Narration:**

"The first stage is preprocessing. A directive such as `#include` tells the preprocessor to make declarations from another header available to this translation unit. The resulting `.i` file is still C code. It is not yet instructions for the CPU.

Notice how much larger the preprocessed file becomes. Standard headers may introduce many declarations. This is normal. The compiler receives the preprocessed translation unit and checks whether names, types and expressions form valid C source.

If a header declares a function incorrectly, the problem can appear before the linker has a chance to run. When debugging a build, it helps to know which stage reported the error."

## 05:30–07:30 — Produce Assembly and object code

**On screen:** Run the `-S` command and examine the generated `.s`; then run `-c` and show `main.o`.

**Narration:**

"The compiler turns C operations into target-machine instructions. Here we ask GCC to stop after producing Assembly, using `-S`. You do not need to understand every register in the output today. Look for function calls, branches and movements of values. Those instructions depend on the processor target and ABI selected by the compiler.

Next, `-c` asks for an object file. Unlike a final executable, an object file can contain references that are still unresolved. This is intentional: `main.o` may call `BtbCatalogueInit` even though the machine code for that function is in another object file.

On Windows with GCC UCRT64, the object normally uses COFF. On Linux, it normally uses ELF. We will inspect those formats in the next episode."

## 07:30–10:30 — Let CMake define the relationships

**On screen:** Open `CMakeLists.txt` and highlight `add_library`, `add_executable` and `target_link_libraries`. Configure and build with Ninja.

**Narration:**

"A project with many source files needs a reliable build description. Here is `add_library`. It compiles `catalogue.c` into an archive. Here is `add_executable`, which defines the demonstration application. And here is `target_link_libraries`: this is the connection we were missing when we compiled a client by itself.

CMake generates a build graph. Ninja uses that graph to compile the files and link in the right order. If we change `catalogue.c`, Ninja rebuilds the affected library and the programmes that depend on it, without compiling unrelated files.

The example also builds a test executable. The same library serves the application and the test. That is the benefit of having one implementation and several clients."

## 10:30–13:00 — Demonstrate a linker error and its correction

**On screen:** Open the intentionally unlinked file `examples/undefined_reference.c`. Run the manual command shown in the laboratory README; capture the unresolved symbol. Then return to the working CMake build.

**Narration:**

"In this file, the declaration exists, but we deliberately do not link `catalogue.c`. The compiler accepts the function call and the linker reports that it cannot find `BtbCatalogueInit`.

That diagnostic is useful. It tells us not to search for a syntax error in `main.c`. The interface compiled; the missing part is a machine-code definition at link time.

The fix is to link the library. We do not paste a second implementation into the application. A professional project protects this separation so that improvements in the library benefit every client."

## 13:00–16:00 — Test and reflect

**On screen:** Run CTest; show two passing checks and output `Total lessons: 21`. Draw the pipeline from source to linker.

**Narration:**

"The example now reports four computing lessons, nine C and Assembly lessons and eight banking lessons. The total is 21. Our tests check both correct output and situations such as duplicate module names, oversized titles and integer overflow.

The compiler checks the source. The linker connects the implementation. The tests check the behaviour. Each answers a different question, so none replaces the others.

This is the same pattern we will meet throughout Umicom: well-defined interfaces, shared services, explicit build dependencies and tests that explain what successful behaviour looks like."

**Practical task:** Add a fourth course module, predict the new lesson count and rebuild. Then restore the original example so the expected-output test passes again.

**Website reference:** The full source and test instructions are available in Bits2Banking Lessons 72 and 73.
