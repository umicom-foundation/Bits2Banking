<!--
Umicom Bits2Banking
File: content/simple-steps/c.md

PURPOSE:
Explain a small C program that adds two numbers and prints the result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Show the total in C

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two apples and one more make three. Find `2 + 1` in the code. That's the part that adds the apples.

```c
#include <stdio.h>

int main(void)
{
    printf("%d\n", 2 + 1);
    return 0;
}
```

1. `#include <stdio.h>` lets the program use `printf`, which writes text to the screen.
2. `main` is where the program starts. The curly braces hold its instructions.
3. C adds `2 + 1`. `printf` puts the answer where you see `%d`. `\n` starts a new line.
4. `return 0;` tells the computer that the program finished successfully.

The program shows **3**. Try changing the first number from `2` to `4`. What should it show now? Count four apples and one more to check.

## Run it if you have GCC

Save the code as `apples.c`. In PowerShell, go to that folder. Run these commands one at a time. The first makes the program. The second runs it.

```powershell
gcc apples.c -o apples.exe
.\apples.exe
```

After you change a number, save the file and run both commands again. The answer with `4 + 1` is **5**.

## Copy to WhatsApp

```text
In C, find 2 + 1 inside printf. The program shows 3. Change 2 to 4. What should it show now?
```

[All simple steps](index.md) · [Go further with C](../lessons/learning-c/index.md)
