<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/10-check-a-c-java-translation.md

PURPOSE:
  Translate initialized integer locals between C and Java and check the result with both compilers.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check a C and Java translation

A local variable belongs to one function or method. In this lab, a
translator preserves where two integer locals are initialized, when one
is reassigned and how the final value is returned. The sample uses fixed
practice values.

## Setup recap

Open a new writable directory. Put a build of `umicom-c` with the checked
function translator, a C23 compiler with a 32-bit `int`, and a JDK on your
command path. Run `umicom-c --version`, `gcc --version` and `javac -version`
before creating the fixture.

## 1. Translate the function in both directions

Save this file as `answer.c`. Predict the value of `net` immediately before
the return.

~~~c
int answer(void) {
    int net = 6;
    int fee = 3;
    net = (net + fee) * 5;
    return net - fee;
}
~~~

~~~powershell
umicom-c translate c-to-java answer.c UmicomAnswer.java
umicom-c translate java-to-c UmicomAnswer.java answer-roundtrip.c
~~~

Open the generated files. Check the initializers, reassignment and return
order. The reassignment makes `net` equal to 45, so the result should be
42. If a destination already exists, choose a fresh filename or directory.

## 2. Build and run both results

Save the Java entry point as `Fixture.java`.

~~~java
final class Fixture {
    public static void main(String[] args) {
        System.out.println(UmicomAnswer.answer());
    }
}
~~~

~~~powershell
javac UmicomAnswer.java Fixture.java
java -cp . Fixture
~~~

Save the C entry point as `fixture.c`.

~~~c
#include <stdio.h>
int answer(void);
int main(void) {
    printf("%d\n", answer());
    return 0;
}
~~~

~~~powershell
gcc -std=c23 -Wall -Wextra -Werror fixture.c answer-roundtrip.c -o c-check.exe
.\c-check.exe
~~~

On Linux, use `./c-check.exe` to run the same output filename. Each program
should write `42` on one line. Compare both results with your prediction.

## 3. Check the boundary

In a new source copy, initialize `net` to `2147483647` and reassign it with
`net = net + 1;`. Translate to an unused destination. Expect a diagnostic
and no destination file because the addition exceeds the shared signed
32-bit range. Keep this as a translation refusal exercise.

The profile supports decimal integer expressions, initialized locals,
simple assignments and a final return. Java objects, parameters, loops
and general project conversion need additional implementation. Try
different small values and repeat both compilation checks.

[Course contents](index.md) · [Previous lesson](09-test-the-runnable-jar.md)
