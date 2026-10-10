# 6. Bash: working in a Linux terminal

Bash is a command shell widely used on Linux and other Unix-like systems. It lets you navigate directories, start programs, connect their output and automate routine operations. Many Umicom build tools work on both Windows and Linux; the terminal commands differ even when the underlying CMake project is the same.

## Find where you are

Open a Linux terminal and enter:

```bash
pwd
ls -la
```

`pwd` prints your current working directory. `ls` lists files and folders; `-l` provides details and `-a` includes hidden entries. A hidden file in Unix-like systems often has a name beginning with a dot, such as `.gitignore`.

Create a practice directory and enter it:

```bash
mkdir -p "$HOME/UmicomLearning"
cd "$HOME/UmicomLearning"
```

`mkdir -p` creates the directory if necessary. Quoting a path with `"..."` matters when it contains spaces.

## Write and read a note

```bash
printf '%s\n' 'Build the Umicom task board' > notes.txt
cat notes.txt
```

The `>` operator directs a command's output into a file, **replacing** its previous contents if the file already exists. Use `>>` to append another line:

```bash
printf '%s\n' 'Review the project backlog' >> notes.txt
cat notes.txt
```

That distinction is important. Accidentally using `>` when you meant `>>` can erase earlier file contents.

## Copy, rename and remove practice files

Inside `UmicomLearning`, make a copy and give it a new name:

```bash
cp notes.txt notes-backup.txt
mv notes-backup.txt notes-copy.txt
ls -l
rm notes-copy.txt
```

`cp` copies a file, `mv` moves or renames it, and `rm` removes it. Here we remove only a known temporary copy. Avoid recursive deletion when working with valuable source files.

## Search and inspect

```bash
grep -n 'Umicom' notes.txt
wc -l notes.txt
```

`grep` searches for matching text; `-n` shows line numbers. `wc -l` counts newline characters, which often corresponds to line count in a normal text file.

## Exit codes and conditions

Programs normally return an **exit status**: `0` for success and a nonzero value for many failures. Bash uses that status to choose what to do next.

```bash
if test -f notes.txt; then
    printf '%s\n' 'The notes file exists'
else
    printf '%s\n' 'The notes file is missing'
fi
```

The word `fi` ends the `if` statement. `test -f` checks whether a regular file exists.

To see the exit status of the last command, enter:

```bash
printf '%s\n' "$?"
```

This reports the status of the immediately preceding `printf`, so it will usually be `0`. For a meaningful check, save a command's status before you run another command:

```bash
grep 'NotThere' notes.txt
status=$?
printf 'grep returned %s\n' "$status"
```

`grep` commonly returns `1` when no line matched. This is different from a command crashing: in scripts, you need to know which nonzero results are expected.

## Create a small shell script

Save the following as `check-tools.sh`:

```bash
#!/usr/bin/env bash

for tool in git python3 cmake; do
    if command -v "$tool" >/dev/null 2>&1; then
        printf '%s is installed\n' "$tool"
    else
        printf '%s is missing\n' "$tool"
    fi
done
```

Run it with:

```bash
bash ./check-tools.sh
```

You do not need to change file permissions when invoking the script explicitly with `bash`. Later you can learn the difference between execution permissions and running a script through its interpreter.

**Next:** [Write a note-taking program in Python](07-python.md).
