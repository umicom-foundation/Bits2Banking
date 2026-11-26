<!--
Umicom Bits2Banking
File: content/simple-steps/java.md

PURPOSE:
Run the same coffee time calculation in Java.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Convert brew time in Java

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save this code as `Coffee.java`. Use the capital `C` so the file name matches the class name.

   ```java
   public class Coffee {
       public static void main(String[] args) {
           int minutes = 4;
           System.out.println(minutes * 60 + " seconds");
       }
   }
   ```

   `class Coffee` groups the instructions. Java starts at `main`. `int` holds the minutes as a whole number. `println` displays the result and starts a new line.

2. With the Java development kit installed (JDK 11 or newer), open PowerShell in that folder and run this command.

   ```powershell
   java Coffee.java
   ```

3. Check for `240 seconds`. Change `4` to `3`, save and run the same command again. The new result is `180 seconds`.

[Compare with C](c.md) · [Full Java course](../courses/learning-java/index.html) · [Guide to the Java course](course-guides/learning-java.md)

<!-- Earlier demonstration code is retained for comparison. The active steps use an everyday task and check its result.

```java
public class Apples {
    public static void main(String[] args) {
        System.out.println(2 + 1);
    }
}
```

```text
java Apples.java
```
-->
