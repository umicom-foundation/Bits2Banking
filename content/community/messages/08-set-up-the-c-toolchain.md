# Set up the Windows C toolchain

For the first C program we need GCC. Install tools in the MSYS2 UCRT64 terminal, then return to PowerShell.
Type -> $env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Check -> Get-Command gcc, cmake, ninja, ctest
Use your own MSYS2 location if it is different.

[Full steps, explanations and recovery help](../lessons/08-set-up-the-c-toolchain.md)
