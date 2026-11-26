<!--
Umicom Bits2Banking
File: content/simple-steps/basic.md

PURPOSE:
Show the sum in FreeBASIC and name the dialect used in the example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Show the total in BASIC

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Start with two apples. Add one more. Here is how to ask **FreeBASIC**, one version of BASIC, to show the total.

```basic
Print 2 + 1
```

1. FreeBASIC works out `2 + 1`.
2. `Print` shows the answer on the screen.

The answer is **3**. Change `2` to `4`. What will the screen show now?

## Run it if you have FreeBASIC

Save the line as `apples.bas`. In PowerShell, go to that folder. Run these commands one at a time. The first makes the program. The second runs it.

```powershell
fbc apples.bas
.\apples.exe
```

FreeBASIC may put a little space next to the answer. After you change a number, save the file and run both commands again. The answer with `4 + 1` is **5**.

## Copy to WhatsApp

```text
In FreeBASIC, write Print 2 + 1. It shows 3. Change 2 to 4. What do you think it will show now?
```

[All simple steps](index.md) · [Go further with FreeBASIC](../lessons/03-native-code/learning-freebasic/index.md)
