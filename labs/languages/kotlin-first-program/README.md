# Kotlin progress and command-line input

This lab extends the existing progress function with a text-input boundary. It does not introduce a second progress rule. The Kotlin code is a language exercise; production shared services continue to belong to Umicom Framework.

## Prepare

Install a JDK, the Kotlin command-line compiler, CMake and Ninja. Open a new terminal and check `java -version`, `kotlinc -version`, `cmake --version` and `ninja --version`. The [first Kotlin lesson](../../../content/lessons/02-programming/learning-kotlin/01-tools-and-first-program.md) explains the tools and terminal steps.

Run from this lab's directory:

~~~powershell
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
java -cp build/progress-input.jar InputKt 4 1
~~~

These same commands work in bash. Stop at the first error. Successful execution prints `Remaining lessons: 3`. The folder may be anywhere you choose; change to it before running these commands.

## Understand the files

- Progress.kt retains the original range rule and its demonstration.
- Input.kt converts two command-line strings, then calls that rule.
- InputChecks.kt checks missing, malformed, out-of-range and valid arguments.
- CMakeLists.txt compiles a jar and registers each entry point separately.

There are several main functions, so these commands name the generated entry class with `-cp`; do not assume `java -jar` can choose one. Kotlin generates InputKt from Input.kt here because there is no package declaration or custom JVM class name.

## Try failures

Run `java -cp build/progress-input.jar InputKt 4 invalid`. Expect a usage message on standard error and exit status 2. In PowerShell inspect `$LASTEXITCODE`; in bash inspect `echo $?` immediately afterward. A zero result is valid progress, so failure is represented by a nullable result rather than the number zero.

If Kotlin is not found, correct its installation and PATH before configuring again. If a class cannot be found, check the jar path, spelling and successful build. The CTest checks are supplied for execution in your environment; source review alone does not establish their result.
