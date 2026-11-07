# Framework Command Arguments Lab

A build button must translate a developer's request into a precise program and a list of arguments. This module follows that translation through Umicom Framework, using a small C exercise to examine spaces, quotation marks, empty arguments and rejected edits.

## Prepare the exercise

A terminal is a window that accepts typed commands. A compiler translates C source into an executable program. CMake describes the build, Ninja carries out the build steps, and CTest runs the checks registered by that build. An SDK supplies the headers and compiled libraries that a program uses.

Reading requires no installation. For the practical work, use a C23 compiler, CMake 3.26 or newer, Ninja, and a matching Umicom Framework SDK that exports the developer component and the exact-span command parser. Use the same architecture and compiler family as the SDK.

1. Find the Bits2Banking checkout and open its **labs/framework/command-arguments** folder.
2. Open PowerShell on Windows or Bash on Linux.
3. Run one command at a time. Stop and read the message if a command fails.
4. Replace the example paths with the locations you chose for the checkout and SDK.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\command-arguments"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-command-arguments.exe"
~~~

~~~bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/command-arguments
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-command-arguments
~~~

If CMake cannot find UmicomFramework, check the SDK prefix. If the compiler cannot find the parser declaration, or the linker cannot find its symbol, select one SDK containing the new header and its matching library. Do not combine files from different SDK installations. This exercise prints a plan; it does not start a compiler or execute text entered by a user.

For a longer introduction to functions and strings, see [Learning C](../../../content/courses/learning-c/index.html). The concepts needed for this exercise are explained below.

## Expected output

```text
Program: compiler
Argument 1: [-c]
Argument 2: [source file.c]
Argument 3: []
Rejected edit left the previous plan unchanged.
```

## Files and responsibilities

- **main.c** inspects a literal command and checks that a rejected edit leaves the previous result intact.
- **CMakeLists.txt** finds the installed developer SDK, links its existing implementation and registers the example with CTest.
- **[Learning Build Systems](../../../content/courses/learning-build-systems/index.html)** explains each concept and provides the source walkthrough.

The example performs no process launch and does not require an IDE or broker account. Its checks are intended for execution with a compatible SDK; reading the source alone is not a passing test.
