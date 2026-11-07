# Write, compile and run a C program

Saving a C file does not run it. First save main.c.
Compile -> gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o hello.exe
Check -> $LASTEXITCODE
If it is 0, run -> .\hello.exe
If compilation failed, read the first error before trying to run an older executable.

[Full steps, explanations and recovery help](../lessons/09-build-your-first-c-program.md)
