# Pascal console programs

Follow [Learning Pascal](../../../content/courses/learning-pascal/index.html).
It starts with a terminal, a source file and the meaning of compilation.


## Install and check the tools
1. Download Free Pascal for your operating system from [the official download page](https://www.freepascal.org/download.html). Follow the installation notes for that package.
2. Open PowerShell on Windows or a terminal on Linux. Type fpc -iV. Expect a compiler version. If the command is missing, locate the installed fpc executable and add its containing bin directory to PATH using the installation instructions. Do not guess another machine's installation path.
3. Obtain Bits2Banking in a folder you choose. With Git installed, a Windows example is:
~~~powershell
New-Item -ItemType Directory -Force "C:\umicom"
Set-Location "C:\umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
~~~
Skip cloning if your checkout already exists. The examples live in labs/languages/pascal-progress. Open hello.pas and progress.pas in a plain text editor.

## Compile without another build tool
Make a new practice directory and copy the two Pascal files there. Compile from that directory so object files do not appear beside your learning sources.
~~~powershell
fpc -Mobjfpc -Cr -Co hello.pas
.\hello.exe
fpc -Mobjfpc -Cr -Co progress.pas
.\progress.exe 2
$LASTEXITCODE
~~~
In Bash the compiler commands are identical; launch with ./hello and ./progress 2, then inspect echo $?. Stop if compilation fails. -Cr enables range checks and -Co enables overflow checks. These checks aid diagnosis; they do not prove all program behaviour correct.

Expect Welcome to Learning Pascal. from hello. progress 2 prints Remaining: 3 and three numbered practice lines.

## Build and check the complete lab
Install CMake 3.24 or newer and Ninja for your operating system. They organise the examples and process checks; Free Pascal remains the language compiler. From the Bits2Banking repository in PowerShell:
~~~powershell
cmake -S labs/languages/pascal-progress -B build/pascal-progress -G Ninja -DBUILD_TESTING=ON
cmake --build build/pascal-progress --parallel 2
ctest --test-dir build/pascal-progress --output-on-failure --no-tests=error
& ".\build\pascal-progress\progress.exe" 2
~~~
In Bash:
~~~bash
cmake -S labs/languages/pascal-progress -B build/pascal-progress -G Ninja -DBUILD_TESTING=ON
cmake --build build/pascal-progress --parallel 2
ctest --test-dir build/pascal-progress --output-on-failure --no-tests=error
./build/pascal-progress/progress 2
~~~
Run commands separately. CMake must find fpc on PATH. A failed configuration does not produce a usable build. A test failure needs investigation even when compilation succeeded.

## Reference and recovery
The [Free Pascal manuals](https://www.freepascal.org/docs.html) explain the compiler and language. The [Val documentation](https://www.freepascal.org/docs-html/rtl/system/val.html) defines conversion results and supported numeric formats. Our exercises use decimal counts. A rejected abc input is expected; an unexpected crash is not.

This course uses Pascal to teach Pascal concepts. Shared application engines remain in Umicom Framework. No Pascal runtime is being introduced into those applications.


## Explore the examples

1. Read `hello.pas`, compile it and compare the greeting with the source.
2. Read `progress.pas`. `Val` converts text to a number and reports where an
   invalid conversion failed. The program checks that report before using
   the resulting number.
3. Run with `2`: expect `Remaining: 3` and three numbered practice items.
4. Run with `5`: expect `Remaining: 0` and no practice-item lines.
5. Try `-1`, `6`, `abc` and no argument. Each should exit with status 1.
   Check `$LASTEXITCODE` in PowerShell or `echo $?` in Bash immediately.

Range and overflow checks are enabled for these examples. They help detect
particular mistakes; they do not prove the program correct. `Val` follows
Free Pascal's documented numeric syntax, not a custom decimal-only grammar.
The separate range check accepts only values from zero through five.

