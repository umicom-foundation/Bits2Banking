# One price in C, C++ and Java

[Course contents](index.md) · [Previous: Cashflows before formulas](01-cashflows-before-formulas.md) · [Next: Framework pricing and comparison evidence](03-framework-pricing-and-evidence.md)

## State the model before writing code

Complete the first lesson and the variables, functions and output lessons in the language you choose. You can read all three examples without installing three toolchains. A compiler translates source into an executable program; Java's compiler produces class files run by a Java runtime.

We now use continuous compounding: PV = amount * exp(-rate * years). The function exp(x) means e raised to x, where e is about 2.71828. You do not need to derive e to follow this example. Enter rate 0.05 for 5%, and 365 days for one year. Our simplified year fraction is days / 365.0; production contracts can specify different calendars and day-count conventions.

Choose a practice directory. Save each example under the exact filename shown. These are independent teaching programs that expose the arithmetic. Application pricing should call Framework rather than copying them into Bank or Trader.

## C: save as price.c

```c
#include <math.h>
#include <stdio.h>

int main(void)
{
    const double amount = 1050.0;
    const double rate = 0.05;
    const int days = 365;
    const double years = (double)days / 365.0;
    const double value = amount * exp(-rate * years);
    if (!isfinite(value)) return 1;
    printf("Present value: %.2f\n", value);
    return 0;
}
```

## C++: save as price.cpp

```cpp
#include <cmath>
#include <cstdio>

int main()
{
    const double amount = 1050.0;
    const double rate = 0.05;
    const int days = 365;
    const double years = static_cast<double>(days) / 365.0;
    const double value = amount * std::exp(-rate * years);
    if (!std::isfinite(value)) return 1;
    std::printf("Present value: %.2f\n", value);
    return 0;
}
```

## Java: save as Price.java

```java
import java.util.Locale;

public final class Price {
    public static void main(String[] args) {
        final double amount = 1050.0;
        final double rate = 0.05;
        final int days = 365;
        final double years = days / 365.0;
        final double value = amount * Math.exp(-rate * years);
        if (!Double.isFinite(value)) {
            throw new IllegalArgumentException("Non-finite price");
        }
        System.out.printf(Locale.ROOT, "Present value: %.2f%n", value);
    }
}
```

## Optional build and run

In PowerShell with the MSYS2 UCRT64 C/C++ tools available, run the matching pair of commands from your practice directory. Stop if compilation reports an error; an old executable is not evidence about new source. Java needs a JDK providing both javac and java.

```powershell
gcc -std=c23 -Wall -Wextra price.c -lm -o price.exe
.\price.exe
g++ -std=c++17 -Wall -Wextra price.cpp -o price-cpp.exe
.\price-cpp.exe
javac Price.java
java Price
```

If an older GCC does not recognise c23, consult its supported C-standard options; do not remove warnings to hide a source error. Each successful program should display approximately 998.79. That differs from 1,000 in lesson 1 because the compounding assumption changed. Two decimal places change presentation, not the internal value.

## Exercise

Set days to zero in all three examples. Explain the result before running. Then set rate to zero and restore days to 365.

## Explained answer

Both cases produce 1,050. At zero time or zero rate the exponent is zero and exp(0) = 1. The casts and decimal denominator keep the year fraction from being truncated by integer division. Rounding policy belongs at a declared financial boundary, not after every intermediate multiplication.

## Continue learning

[Course contents](index.md) · [Previous: Cashflows before formulas](01-cashflows-before-formulas.md) · [Next: Framework pricing and comparison evidence](03-framework-pricing-and-evidence.md)

[Browser edition](../../../courses/financial-instruments-pricing/lessons/02-one-price-three-languages.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/src/finance/quant/discount_curve.c). This public revision matches the source inspected for this lesson.
