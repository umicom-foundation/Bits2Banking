<!--
Umicom Bits2Banking
File: content/simple-steps/basic.md

PURPOSE:
Run the same coffee time calculation in FreeBASIC.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Convert brew time in FreeBASIC

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save these two lines as `coffee.bas` in a practice folder.

   ```basic
   Dim minutes As Integer = 4
   Print minutes * 60
   ```

   `Dim` creates a named whole number. `Print` evaluates the expression and displays its result. The result is in seconds.

2. With FreeBASIC installed, open PowerShell in that folder and type the two lines separately.

   ```powershell
   fbc coffee.bas -x coffee-basic.exe
   .\coffee-basic.exe
   ```

3. Check that the result is `240`. Change `4` to `3`, save and repeat the two commands. The new result is `180`. FreeBASIC may pad the number with a space.

[Compare with C](c.md) · [Full FreeBASIC course](../courses/learning-freebasic/index.html) · [Guide to the FreeBASIC course](course-guides/learning-freebasic.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```basic
Print 2 + 1
```

```powershell
fbc apples.bas
.\apples.exe
```
-->
