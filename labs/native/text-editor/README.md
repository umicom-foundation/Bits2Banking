# Build a small text editor in C

The project accepts line commands and edits a bounded text buffer. Begin with
[Building a Text Editor in C](../../../content/courses/building-a-text-editor/index.html);
[Safer C Programming](../../../content/courses/safer-c-programming/index.html)
explains its boundary and ownership checks.


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
5. Read the files under labs/native/text-editor. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
& ".\build\text-editor\btb-text-editor.exe"
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
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
./build/text-editor/btb-text-editor
~~~

## Understand the result
The editor prints its command summary and waits for input. Type append Hello, then show, then discard on separate lines. Expect TEXT: Hello. This is a bounded ASCII console lab with one-level undo, not a graphical production editor.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../../content/courses/learning-c/index.html). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## Try a complete editing session

Create a practice folder first; choose any accessible location. For example,
in PowerShell use `New-Item -ItemType Directory -Force "C:\umicom\practice"`.
Launch the editor, then type each command on a separate line:

~~~text
append ac
insert 1 b
show
erase 1 1
undo
show
save C:\umicom\practice\my-first-note.txt
quit
~~~

Both `show` commands should print `TEXT: abc`. Positions start at zero:
position 1 is the gap after the first character. Bash users can supply a
chosen Unix path, for example `save /tmp/my-first-note.txt`. The destination's
parent directory must already exist.

The path is the rest of the command: spaces are allowed and quotation marks
are not needed inside the editor. The terminal launches the editor; the
editor then reads its own commands. A shell command such as `mkdir` must be
run in a separate terminal or before launching this program.

## Files and behaviour

- `editor.h`: model and operation contracts.
- `editor.c`: insertion, erasure, one undo snapshot and new-file saving.
- `main.c`: command parsing and a caller-selected path.
- `test_editor.c`: model boundaries, overlapping input and failure preservation.
- `check_session.cmake`: real command input, saved bytes, existing-file refusal,
  numeric overflow and oversized-line recovery.

The buffer holds 1,024 ASCII bytes plus its terminating zero. Input strings
must be readable for the supplied length. The model supports newline and tab;
the line-oriented command interface inserts one command's text at a time.
Undo is available once after a successful edit. A no-op or rejected edit
retains the previous undo snapshot.

`save` creates a new file exclusively. It refuses an existing destination.
It does not implement overwrite, loading files, Unicode cursor movement or
a graphical interface. A failed write can leave a partial new file; inspect
it before retrying. A successful save checks the C stream operations but
does not promise power-loss durability.

`quit` refuses unsaved changes. `discard` explicitly ends the session and
reports that changes were unsaved. End-of-input also ends the session, with
the same warning when dirty. Any rejected command makes the final process
exit status nonzero even if later commands succeed.

The production editor and file ownership services remain in Umicom Framework.
This lab is an intentionally small model for learning and troubleshooting.

