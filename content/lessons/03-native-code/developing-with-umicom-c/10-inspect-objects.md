<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/10-inspect-objects.md

PURPOSE:
Teach explicit roots and bounded collection in a host C program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect objects before collecting them

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

A host application can keep a bounded set of objects. A root is an explicit starting object. The collector follows the links from the roots and frees the remaining objects. This example is a C program using the Umicom C managed heap library.

1. Open [the graph example](../../../labs/native/umicom-c-brew-time/brew-time-heap.c). Draw three boxes called recipe, brew time and draft. Draw an arrow from the recipe to the brew time. Circle the recipe as the only root. Decide which boxes a walk from the root can reach.
2. Build the library and compile the host example. Run the commands separately and stop on an error.

   ~~~powershell
   cmake --build $UcBuild --target umicom_c_managed_heap --parallel 2
   $Managed = Join-Path $UcBuild 'libumicom_c_managed_heap.a'
   $Includes = Join-Path $UcSource 'include'
   $HeapDemo = Join-Path $Lab 'brew-time-heap.c'
   $HeapApp = Join-Path $Practice 'brew-time-heap.exe'
   & 'C:\msys64\ucrt64\bin\gcc.exe' -std=c23 "-I$Includes" $HeapDemo $Managed -o $HeapApp
   if ($LASTEXITCODE -eq 0) { & $HeapApp }
   ~~~

   Before collection, the program reports two reachable objects and one collectable object. After collection, it reports one reclaimed object and a time of four minutes. Its checks also refuse the old draft handle.

3. Compare the calls in the source. Inspection reports reachability without changing the graph. Collection reclaims the draft. Reading the saved time still works because the root retained it through a link.
4. In a copy, make both the recipe and draft roots by passing a two-element handle array to inspection. Predict the new reachable count before you run it. Review which checks also need to change if you decide to collect with that same array.

The arena remains the same fixed size after a collection. The caller still owns that storage. The collector follows its recorded handle edges, and the caller tracks operating-system resources separately.

[Previous step — Display a number and a Boolean](09-print-and-return.md) · [Workshop contents](index.md)
