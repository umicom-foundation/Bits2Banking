# Install D and compile a first program

D is a programming language that can compile to a native executable. An executable is a file the operating system can start. This lesson creates a small text program without requiring an IDE. An IDE is an application that combines editing, building and debugging tools; understanding the commands first makes those tools easier to use.

## Setup recap

You need a Windows or Linux computer, permission to install a compiler, and a writable practice folder. No D or C knowledge is assumed. Download the reference compiler, DMD, from the [official D downloads page](https://dlang.org/download.html). Choose the installer or package for your operating system and follow its instructions, including any linker prerequisites it names. Open a fresh terminal and enter `dmd --version`. Continue only when it prints compiler information.

On Windows use PowerShell; on Linux use bash. A terminal displays input and output; a shell reads commands. For a longer explanation, use [Open a terminal](../../08-system-administration/03-open-powershell-or-linux-terminal.md). This course uses DMD command options; another D compiler may use different options.

## 1. Write the file

In PowerShell, choose a new folder:

```powershell
New-Item -ItemType Directory -Path 'C:\umicom-learning\d-first'
Set-Location 'C:\umicom-learning\d-first'
@'
import std.stdio : writeln;

void main() {
    writeln("Welcome to Umicom learning.");
}
'@ | Set-Content -Encoding utf8 hello.d
Get-Content hello.d
```

`New-Item` creates a directory and `Set-Location` enters it. The here-string contains literal source text. `Set-Content` saves the text, replacing an existing file of that name, so use a new practice folder. `Get-Content` displays the file for review.

In bash:

```bash
mkdir -p "$HOME/umicom-learning/d-first"
cd "$HOME/umicom-learning/d-first"
cat > hello.d <<'EOF'
import std.stdio : writeln;

void main() {
    writeln("Welcome to Umicom learning.");
}
EOF
cat hello.d
```

`cat` with the quoted delimiter reads literal lines into the file. `>` replaces that file's contents. Neither set of shell commands is part of the D program.

## 2. Read the program

`import std.stdio : writeln;` makes the named output function available from D's standard library. A library is a collection of reusable functionality. A semicolon ends this statement. `void main()` declares the entry function; `void` means it does not return a value. Braces enclose its body. `writeln` writes the quoted string and a newline.

The path through the tools is **hello.d → compiler and linker → executable → terminal output**. The linker combines compiled code with required library code or references.

## 3. Build and run

Windows PowerShell:

```powershell
dmd -g hello.d -of=hello.exe
$LASTEXITCODE
.\hello.exe
```

Linux bash:

```bash
dmd -g hello.d -of=hello
echo $?
./hello
```

`-g` requests debug information, useful for relating execution to source. `-of=` names the output. A zero compiler completion code means the command succeeded; run the executable only then. `./` or `.\` means the current folder. Expected program output is `Welcome to Umicom learning.` followed by a newline.

## 4. Diagnose a small error

Save a separate copy, remove the semicolon after `writeln(...)`, and compile that copy. Read the first diagnostic, restore the semicolon and compile again. A compiler can identify where it became unable to understand the text; the actual mistake can be just before that position. If the build fails, do not run an older executable and mistake its output for the new source.

If `dmd` cannot be found, correct the compiler's PATH entry and reopen the terminal. If compilation succeeds but linking fails, read the DMD installer documentation for the required platform linker and libraries. These are environment problems, not reasons to change the teaching program.

## Exercise and answer

Change the text to `My first D program.` Recompile and run. Only the sentence changes; the source still has one import, one entry function and one output call. Next, use a function with inputs and executable checks in [the progress example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-first-program/progress.d).

[Course contents](index.md) · [Next: contracts and unit tests](02-contracts-and-unit-tests.md)
