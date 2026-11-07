# Install Kotlin and run a first program

Kotlin is a programming language. A source file is a text file containing instructions written in that language. In this lesson a compiler translates those instructions into a form that the Java runtime can execute. The result will be one line of text in a terminal.

You need no previous Kotlin or Java experience. You need permission to install software, an internet connection for the downloads, and a folder in which you can save files. Reading this lesson needs only a browser. A terminal is a window for entering commands; the shell interprets those commands. The examples below use PowerShell on Windows and bash on Linux.

## Setup recap: Prepare the tools

1. Install a supported Java Development Kit (JDK), such as an OpenJDK distribution from its official distributor. A JDK contains the Java runtime and development tools. Follow its installer instructions for your operating system.
2. Follow the [Kotlin command-line compiler installation guide](https://kotlinlang.org/docs/command-line.html). On Windows, extract the compiler archive into a folder you choose, for example `C:\Tools\kotlin`, and add its `bin` directory to your user PATH. PATH is the list of directories searched for commands. Use the guide's Linux instructions on Linux.
3. Open a **new** PowerShell or bash window after changing PATH. Enter `java -version`, followed by `kotlinc -version`. Both should print version information. The numbers depend on the packages installed.
4. If either command is unrecognised, locate that installation and correct PATH before continuing. Installing a compiler does not automatically update an already-open terminal.

For more practice with commands and folders, see [Open a terminal](../../08-system-administration/03-open-powershell-or-linux-terminal.md). You can return here without completing another course.

## 2. Create a practice folder and source file

Choose an empty folder so that these commands do not overwrite existing work. On Windows:

```powershell
New-Item -ItemType Directory -Path 'C:\umicom-learning\kotlin-first'
Set-Location 'C:\umicom-learning\kotlin-first'
@'
fun main() {
    println("Welcome to Umicom learning.")
}
'@ | Set-Content -Encoding utf8 Main.kt
Get-Content Main.kt
```

`New-Item` creates a folder. `Set-Location` makes it the current folder. The single-quoted here-string, from `@'` to `'@`, holds several lines of literal text. `Set-Content` writes that text to a file; it replaces a file if one already exists. `Get-Content` displays what was saved.

On Linux, use this equivalent in bash:

```bash
mkdir -p "$HOME/umicom-learning/kotlin-first"
cd "$HOME/umicom-learning/kotlin-first"
cat > Main.kt <<'EOF'
fun main() {
    println("Welcome to Umicom learning.")
}
EOF
cat Main.kt
```

`mkdir -p` creates the folder and any missing parents. `cd` changes folder. The quoted `EOF` delimiter keeps the text literal, and `>` writes it to the named file. These are terminal commands; they are not Kotlin statements.

## 3. Understand every line

- `fun` starts a function declaration. A function is a named group of instructions.
- `main` is the entry point: the runtime begins this program there.
- `()` is the parameter list. It is empty because this function accepts no arguments.
- `{` and `}` enclose the function body.
- `println` prints a value and ends the line. Text between double quotes is a string.

The flow is **Main.kt → Kotlin compiler → main.jar → Java runtime → terminal text**. A JAR is an archive containing compiled classes and, with the option below, the Kotlin runtime libraries used by this example.

## 4. Compile, then run

These commands work in either shell:

```text
kotlinc Main.kt -include-runtime -d main.jar
java -jar main.jar
```

`-d` names the output archive. `-include-runtime` includes Kotlin's runtime; you still need Java installed. Run the second command only after compilation succeeds. Expected program output:

```text
Welcome to Umicom learning.
```

In PowerShell, inspect `$LASTEXITCODE` immediately after a native command; in bash use `echo $?`. Zero normally means successful completion. If compilation fails, an older JAR can still exist: running it would run an older program.

## Practice and worked answer

Change the sentence to `My first Kotlin program.` Save, compile again, then run again. The output should change to that sentence. If it does not, check the current folder and compilation result. Editing a source file does not change the previously compiled archive.

## Continue with real source

The next lesson uses [Progress.kt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/kotlin-first-program/Progress.kt), an Umicom learning example. Its calculation is deliberately small. Later mobile clients can call reusable Framework services rather than embedding production rules in every screen.

[Course contents](index.md) · [Next: values, functions and checks](02-values-functions-and-checks.md)
