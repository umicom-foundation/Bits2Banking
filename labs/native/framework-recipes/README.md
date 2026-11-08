<!--
Umicom Bits2Banking
File: labs/native/framework-recipes/README.md

PURPOSE:
Teach immutable recipe inspection with an installed Framework SDK and honest evidence boundaries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect a source recipe through Framework

A recipe describes source files, the compiler identity and stages that should depend on each other. This exercise parses that description and creates task metadata. It does not compile the source, run tests described by the recipe, install an image or publish anything.

## Prepare and run

1. Install a matching Framework development SDK containing `umicom/build/recipe.h` and its developer library. Use the same compiler and architecture for the SDK and this consumer.
2. Run each command separately; stop on an unexpected error. The CTest command exercises the consumer, not the build stages described in JSON.
3. Repeat the last command with `owned` and `identity`. Use `refuse` with the adjacent `command-refused.json` file.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-recipes -B .\build\framework-recipes -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-recipes --parallel 2
ctest --test-dir .\build\framework-recipes --output-on-failure --no-tests=error
& .\build\framework-recipes\btb-framework-recipes.exe inspect C:/umicom/Umicom-Bits2Banking/labs/native/framework-recipes/recipe.json
```

The four checks inspect a recipe, keep a projected task registry after destroying its recipe, distinguish exact bytes after adding whitespace, and reject an executable command field. Each returns zero only when its stated assertions match. These are expected results, not a recorded qualification run.

## Read the claims carefully

`recipe.json` identifies the authored `main.c` bytes. Its compiler path and zero-filled manifest digest are illustrative unverified claims. No compiler or manifest is bundled or downloaded. Editing the source makes its stored claim stale; parsing will still succeed because inspection does not compare files. Capture the real bytes and review provenance separately before designing execution.

Build identifies the machine preparing tools, host the machine that runs the resulting tool or program, and target the machine for which that tool produces output. The triples in this example describe a cross-toolchain scenario. Parsing their spelling does not verify the compiler ABI.

## Ownership and recovery

`UmiBuildRecipeReadFile` reads an explicitly selected absolute regular file under a byte limit. It refuses the final symlink or device; trusted parent directories remain the caller’s responsibility. Borrowed entry pointers expire when the recipe is destroyed. `UmiBuildRecipeCreateTasks` returns an independent registry that the caller destroys separately.

If the SDK cannot be found, correct `CMAKE_PREFIX_PATH`. If a symbol is missing, compare installed headers and archives before changing the example. If parsing fails, preserve the exact input and report; correct missing keys, aliases or references without weakening the guard. A successful parse cannot establish source authenticity, reproducible output, a bootable OS or permission to execute.
