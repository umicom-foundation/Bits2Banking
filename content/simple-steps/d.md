<!--
Umicom Bits2Banking
File: content/simple-steps/d.md

PURPOSE:
Run the same coffee time calculation in D.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Convert brew time in D

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save the code as `coffee.d` in a practice folder.

   ```d
   import std.stdio;

   void main()
   {
       const int minutes = 4;
       writeln(minutes * 60, " seconds");
   }
   ```

   `import` makes `writeln` available. `main` starts the program. `minutes * 60` converts the time. `writeln` displays the number followed by its unit.

2. If you already have the LDC compiler, open PowerShell in that folder and type these commands one at a time.

   ```powershell
   ldc2 coffee.d -of=coffee-d.exe
   .\coffee-d.exe
   ```

3. Look for `240 seconds`. Change `4` to `3`, save, compile again, and confirm `180 seconds`.

[Compare with C](c.md) · [Full D course](../courses/learning-d/index.html) · [Guide to the D course](course-guides/learning-d.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```d
import std.stdio;

void main()
{
    writeln(2 + 1);
}
```

```powershell
ldc2 apples.d -of=apples.exe
.\apples.exe
```
-->
