# Build only what changed

## Separate configuration, compilation and testing

Configuration reads a project's build description and records how files depend on one another. Compilation translates source files into object files. Linking joins the required objects and libraries into a program. Testing runs checks against that result. These stages answer different questions; repeating every stage is not always necessary.

An incremental build reuses outputs whose inputs have not changed. CMake describes the dependency graph and generates the native build instructions. In the Windows UCRT64 preset, Ninja executes those instructions. You do not need to name each edited source file to request an ordinary incremental build.

~~~text
editor changes one .c file
          |
          v
its object file becomes out of date
          |
          v
programs using that object are linked again

shared header changes
          |
          v
all source files that depend on it may need compilation
~~~

## Reuse the same build folder

1. Configure the intended preset once after installing its required tools. Keep that build folder; it holds the dependency graph and previous outputs.
2. Edit and save the source file. Saving changes the input that the builder observes.
3. Run the build command for the same preset. Do not add --clean-first when you want to retain useful previous work.
4. Read the result. An unchanged build may say that there is no work to do. A changed shared header can correctly trigger many compiler jobs.
5. Reconfigure when changing a build option or dependency. CMake may also regenerate automatically when a tracked build description changes. Use a fresh build folder when changing to an incompatible compiler or architecture.

~~~powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --build --preset windows-ucrt64-all-debug --parallel 2
~~~

Run this after the matching preset has been configured, as described in the setup guide. The command requests the normal build. It does not delete outputs, name one module, or prove that tests passed. Stop if the command reports an error.

## Why one edit can still cause a large build

A shared type declaration can affect many applications. A compiler flag can change generated machine code. A new public Framework contract identity can invalidate consumers even when a copied file retained an old timestamp. These are real dependencies, not necessarily a broken incremental builder.

Changing a comment can also update a file timestamp. A conventional compiler build may compile that file again. Do not assume that every builder compares program meaning, or that ignoring comments is always harmless: preprocessing, generated input and source-location diagnostics also matter. Umicom does not claim a universal semantic-only compiler.

## Reuse test results only with evidence

Study [the automatic test driver](https://github.com/umicom-foundation/umicom-framework/blob/main/cmake/UmicomAutomaticTestsRun.cmake) and [the receipt API](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/testing/reuse.h). A receipt records evidence about a previous test result and the inputs associated with it. It is not permission to skip an arbitrary test just because its name passed yesterday.

An eligible unchanged passing result can be reused only when the driver has the required identity information. Failed tests remain candidates to run again. Missing or damaged evidence must not turn into a pass. If runtime library dependencies cannot be identified completely, the driver chooses a full run and records that reason. That conservative fallback can be slower, but it preserves coverage.

Runtime dependencies are libraries loaded when the program executes. On some Windows configurations, unresolved runtime imports prevent the driver from proving the complete dependency set. Do not remove those imports from the evidence merely to obtain a shorter test run.

<details>
<summary>Check your understanding</summary>
<p>Yesterday all tests passed. Today a shared Framework header changes. Is it safe to rerun only yesterday's failures?</p>
<p><strong>Answer:</strong> No. There were no failures, but the changed header may affect previously passing areas. Failed-test reruns help diagnose known failures; dependency-aware qualification must also account for changed inputs and newly affected tests.</p>
</details>

Read [the current automatic-build guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/guides/automatic-builds.html) before using its qualification commands. Keep an ordinary incremental build, targeted diagnosis, and full release qualification as distinct operations.

[Previous lesson](06-use-an-installed-sdk.md) · [Course contents](index.md) · [Next lesson](08-read-build-and-test-evidence.md)

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
