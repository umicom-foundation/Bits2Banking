<!--
Umicom Bits2Banking
File: content/simple-steps/java.md

PURPOSE:
Introduce the Java program entry and output line around one small sum.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Show the total in Java

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Look for `2 + 1` in the middle. This is where Java adds the apples.

```java
public class Apples {
    public static void main(String[] args) {
        System.out.println(2 + 1);
    }
}
```

1. `class Apples` names the group that holds our instructions. That's why the file name starts with `Apples` too.
2. `main` tells Java where to start. Keep this starting line as written for now.
3. `System.out.println(2 + 1);` adds the numbers and shows the answer. Each closing brace `}` closes a group of instructions.

The program shows **3**. Change `2` to `4`. What do you expect to see?

## Run it if you have the Java developer tools

Use JDK 11 or newer. Save the code as `Apples.java` with a capital `A`. Open a terminal in that folder and run this command.

```text
java Apples.java
```

After you change a number, save the file and run the command again. The answer with `4 + 1` is **5**.

## Copy to WhatsApp

```text
Look for 2 + 1 inside System.out.println in the Java example. It shows 3. Change 2 to 4. What will you see now?
```

[All simple steps](index.md) · [Go further with Java](../courses/learning-java/index.html)
