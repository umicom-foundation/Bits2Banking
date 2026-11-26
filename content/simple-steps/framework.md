<!--
Umicom Bits2Banking
File: content/simple-steps/framework.md

PURPOSE:
Let readers see C and a real Framework service working together.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use a shared tool in Umicom Framework

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Draw two apples. Draw one more. How many can you count? Three.

This C program shows `3` and then `OK`. Umicom Framework is a set of shared tools for apps. Here we ask it for one short message.

```c
#include <stdio.h>
#include <umicom/base/status.h>

int main(void)
{
    /* C adds the numbers and shows the apple count. */
    int apples = 2 + 1;
    printf("%d\n", apples);

    /* Ask Framework for the same message other apps can use. */
    puts(umi_status_text(UMI_STATUS_OK));
    return 0;
}
```

1. The two `#include` lines let the program use the C and Framework tools shown here.
2. `main` is where the program starts. `int apples = 2 + 1;` saves the whole number `3` under the name `apples`.
3. `printf` puts the number where `%d` appears. `\n` starts the next line.
4. `UMI_STATUS_OK` is Framework's name for success. `umi_status_text` gives us the word `OK` and `puts` shows it on its own line.
5. `return 0;` tells the computer that the program finished normally.

```text
3
OK
```

**Try it on paper.** Change `2 + 1` to `4 + 1`. Which line changes? Point to the code that tells you why.

The number changes to `5`. The message stays `OK` because the program asks for the same Framework message. Count the apples yourself to check the answer.

Read along now. When you have the Umicom Framework tools installed and want to run a longer example, try the [Framework practice lab](../lessons/umicom-development/sdk-practical-lab.md).

## Copy to WhatsApp

```text
Bits2Banking • A shared tool
1. Draw two apples. Add one more.
2. Count them. C can do the same sum and show 3.
3. Ask Umicom Framework for the success message. It gives you OK.
Try one more sum. Start with four and add one. What number changes?
```

[Paper steps](paper.md) · [Learning in Simple Steps](index.md)
