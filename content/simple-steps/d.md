<!--
Umicom Bits2Banking
File: content/simple-steps/d.md

PURPOSE:
Show how a short D program calculates and displays the same total.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Show the total in D

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Start with two apples and add one. `writeln` (say **write line**) shows the answer on the screen.

```d
import std.stdio;

void main()
{
    writeln(2 + 1);
}
```

1. `import std.stdio;` makes `writeln` available.
2. `main` is where the program starts. Its instruction goes between the curly braces.
3. `writeln(2 + 1);` adds the numbers, shows the answer and ends the line.

The program shows **3**. Change `2` to `4`. What will it show now?

## Run it if you have LDC

LDC is a tool that makes a program you can run from D code. Save the code as `apples.d`. In PowerShell, go to that folder and run these commands one at a time.

```powershell
ldc2 apples.d -of=apples.exe
.\apples.exe
```

After you change a number, save the file and run both commands again. The answer with `4 + 1` is **5**.

## Copy to WhatsApp

```text
D uses writeln(2 + 1); to show 3. Change 2 to 4. Can you guess the new answer before you run it?
```

[All simple steps](index.md) · [Go further with D](../lessons/03-native-code/learning-d/index.md)
