<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/07-link-a-constant.md

PURPOSE:
Inspect a native function body and call the matching COFF object from C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect and link native x64 output

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

The first recipe has a known answer before execution. Umicom C can evaluate that closed calculation and emit an x64 function that returns 255. Native output uses machine instructions for a named target.

1. On your x64 development machine, emit just the function body to a new file. Read it with Format-Hex. Expect **B8 FF 00 00 00 C3**. The B8 instruction loads 255 into EAX using four little-endian bytes. C3 returns to the caller.

   ~~~powershell
   $Source = Join-Path $Lab 'brew-time.uc'
   $Raw = Join-Path $Practice 'brew-time-x64.bin'
   & $Uc emit-constant-x64 $Source $Raw
   Format-Hex -LiteralPath $Raw
   ~~~

2. Emit the Windows x64 COFF object. Inspect its file header and symbol table using the UCRT64 toolchain. Look for the x86-64 architecture and the symbol **umc_constant_return**.

   ~~~powershell
   $Obj = Join-Path $Practice 'brew-time-x64.obj'
   & $Uc emit-constant-x64-coff $Source $Obj
   & 'C:\msys64\ucrt64\bin\objdump.exe' -f -t $Obj
   ~~~

3. Open [the C caller](../../../labs/native/umicom-c-brew-time/brew-time-return-caller.c). It declares the function and checks the answer. Link it against the object and launch only the executable you just built. Expect **Native return: 255 seconds.**

   ~~~powershell
   $Caller = Join-Path $Lab 'brew-time-return-caller.c'
   $App = Join-Path $Practice 'brew-time-native.exe'
   & 'C:\msys64\ucrt64\bin\gcc.exe' -std=c23 $Caller $Obj -o $App
   if ($LASTEXITCODE -eq 0) { & $App }
   ~~~

If emission or object inspection reports an error, stop before linking. Use fresh output names when repeating the exercise. Select tools that use the object's architecture and format. The raw bytes are practice data. Native code inside a full operating system uses its own executable format and loading rules.

[Previous step — Classify two language regions](06-classify-source.md) · [Next step — Call the compiler and runtime from C23](08-embed-and-test.md)
