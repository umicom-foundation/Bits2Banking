# 57. Read an object file and follow the linker

A compiler does not normally turn every source file directly into a finished application. It first creates an **object file** containing machine code, data and information about symbols. A **linker** combines the object files, resolves symbol references and produces an executable or library.

The Assembly-functions lab provides a manageable case: `main.c` declares `AddTwoAssembly`, while `add_x86_64.S` defines it. Neither source file is sufficient on its own to make the final application work.

## 1. Compile and inspect the build folder

Build the [Assembly-functions laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/assembly-functions) first. CMake will create a Ninja build directory. Inside it, Ninja maintains generated rules and CMake stores the chosen compiler, assembler, include paths and target settings.

On Windows, set the UCRT64 path and configure:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\assembly-functions" `
    -B ".\output\learning-build\assembly-functions" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\assembly-functions" --parallel 2
```

Locate the object files:

```powershell
Get-ChildItem ".\output\learning-build\assembly-functions" -Recurse -File |
    Where-Object { $_.Extension -in '.obj', '.o' } |
    Select-Object FullName
```

You should find an object for the C source and another for the Assembly source. Their names and directory layout are controlled by the build system, so inspect the actual output rather than guessing a path.

## 2. Inspect object-file symbols

A **symbol** names a function or data object. A definition provides a symbol's implementation. A reference means another object will need to provide it. On Windows UCRT64, GNU binutils provides `nm` and `objdump`:

```powershell
& "C:\msys64\ucrt64\bin\nm.exe" --help
& "C:\msys64\ucrt64\bin\objdump.exe" --help
```

Run `nm` on the Assembly object found in the previous step. Look for `AddTwoAssembly`. A `T` symbol usually indicates a definition in a code section, while `U` indicates an unresolved external reference. Exact letter meanings depend on the file format and tool.

The C object should reference the function. The Assembly object should define it. The linker then connects the two.

## 3. Read disassembly without editing executable bytes

The `objdump -d` command disassembles the code in an object file. It translates machine instructions back into readable instruction mnemonics where possible.

On x86-64, look for the instructions `mov`, `add` and `ret`. The displayed syntax depends on the tool's settings. Compiler optimisation may also change what you see in the C-generated functions, so do not assume the source and the disassembly always have a one-to-one line relationship.

**Object formats:** Windows typically uses PE/COFF, while Linux and the current RISC-V Kernel lesson use ELF. Their headers and relocation mechanisms differ, even when both platforms run processors from the x86-64 family.

## 4. Create and correct one linker error

Change only the C declaration to `AddTwoAssemblyDifferent`. Leave the Assembly source untouched. Run the build again and read the linker diagnostic. Restore the correct declaration and rebuild.

This demonstrates why a compiler can accept an `extern` declaration even when no implementation is available, and why the linker must still verify that the executable's references can be satisfied.

## 5. Continue learning

Explain the difference between a source file, object file, static library and executable. Identify one symbol definition and one symbol reference in the lab. Which tools produced the intermediate object files? Which tool connected them into a runnable application?

Now open [Umicom Framework's CMake project](https://github.com/umicom-foundation/umicom-framework/blob/main/CMakeLists.txt). Its targets use the same fundamental compilation and linking ideas, although the Framework contains many more modules, libraries and tests.
