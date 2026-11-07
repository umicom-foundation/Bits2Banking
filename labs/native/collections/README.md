# Arrays, stacks, queues and searching

This is a small C teaching model. Production applications use the shared
Framework containers and services; the lab makes each operation visible so
that learners can trace it.

Start with [Learning Data Structures](../../../content/courses/learning-data-structures/index.html),
then [Learning Algorithms](../../../content/courses/learning-algorithms/index.html).
Both courses recap the required C concepts.

## Read the files in this order

1. `collections.h` defines values, results and the eight-element capacity.
2. `main.c` shows a caller appending, sorting and finding values.
3. `collections.c` implements each operation without heap allocation.
4. `test_collections.c` compares sorting with a frequency-count oracle and
   searching with a simple linear search. It also checks empty, full and
   wrapped queues. A test is a repeatable check, not proof of every possible use.


## Prepare a development environment
A compiler translates C source. CMake describes which files belong to a program. Ninja performs the build work. CTest runs registered checks. An editor changes the source text. You may use a plain text editor before learning an IDE.

### Windows with PowerShell
1. Install MSYS2 from [its official installation guide](https://www.msys2.org/). Use the UCRT64 environment described in [the environment guide](https://www.msys2.org/docs/environments/).
2. In the MSYS2 UCRT64 terminal, follow its update instructions, then install the C tools:
~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja git
~~~
3. Obtain the Bits2Banking repository. If it is already present, use that checkout; do not clone into it again. In the MSYS2 terminal, an example new location is:
~~~bash
mkdir -p /c/umicom
git clone https://github.com/umicom-foundation/Bits2Banking.git /c/umicom/Umicom-Bits2Banking
~~~
4. Open PowerShell and add the tools to that terminal's PATH. PATH is the list of directories searched for commands.
~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
~~~
5. Read the files under labs/native/collections. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/collections -B build/collections -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/collections --parallel 2
ctest --test-dir build/collections --output-on-failure --no-tests=error
& ".\build\collections\btb-collections.exe"
~~~

### Linux with Bash
1. Install Git, a C compiler with the required C23 mode, CMake 3.24 or newer, and Ninja using your distribution's documented package manager. Package names and compiler versions vary.
2. Clone into a new folder if needed:
~~~bash
mkdir -p "$HOME/umicom"
cd "$HOME/umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
cd Umicom-Bits2Banking
~~~
3. Check cc --version, cmake --version and ninja --version. If you choose a different compiler, configure a new build directory with -DCMAKE_C_COMPILER set to that compiler.
4. Run each command separately and stop on a failure. echo $? immediately afterwards displays the previous result.
~~~bash
cmake -S labs/native/collections -B build/collections -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/collections --parallel 2
ctest --test-dir build/collections --output-on-failure --no-tests=error
./build/collections/btb-collections
~~~

## Understand the result
The program prints 2 2 7 9 and then 7 is at index 2. The checks cover full and empty structures, queue wraparound, sorting and searching.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../../content/courses/learning-c/index.html). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## Contract and extension exercise

Initialise each container to zero. Do not change its internal count or head
outside the model. Output pointers must refer to writable objects of the
declared type and must not alias container storage. An error preserves the
output value. Binary search requires values sorted in ascending order.

The implementation is single-threaded and holds at most eight integers. Change
the example values, predict the order, then compare the actual output. Before
generalising to records or dynamic memory, specify ownership, allocation
failure and the meaning of comparison. Keep such reusable production behaviour
in Framework.

