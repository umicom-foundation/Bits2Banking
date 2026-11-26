<!--
Umicom Bits2Banking
File: content/simple-steps/framework.md

PURPOSE:
Connect the coffee calculation to an authentic Framework status call.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use a shared tool in Umicom Framework

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Read this after [building your first C program](c.md). Look for the familiar minutes-to-seconds calculation.

   ```c
   #include <stdio.h>
   #include <umicom/base/status.h>

   int main(void)
   {
       // Convert the recipe time before printing it with its unit.
       const int minutes = 4;
       printf("%d seconds\n", minutes * 60);
       // Use the shared Framework text for a successful status.
       puts(umi_status_text(UMI_STATUS_OK));
       return 0;
   }
   ```

2. Follow `main` one line at a time. C prints `240 seconds`. The Framework header supplies `umi_status_text`. The call asks for the text that belongs to the success value, so the next line is `OK`.
3. Predict the result after changing the minutes to `3`. The first line changes to `180 seconds`. The second stays `OK` because the program asks for the same status text.
4. When you have installed the SDK, follow the [installed Framework SDK lab](../lessons/umicom-development/sdk-practical-lab.md). It walks through linking a C program to Framework and checking the result.

[Full Framework course](../courses/umicom-development/index.html) · [Guide to the Framework course](course-guides/umicom-development.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

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

```text
3
OK
```
-->
