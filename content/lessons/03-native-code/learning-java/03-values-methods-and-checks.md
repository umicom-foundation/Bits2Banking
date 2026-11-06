# Values, methods and checks

[Course contents](index.md) · [Previous: Decimal values and checks](02-decimal-values-and-checks.md)

## What a method does

Complete the two earlier Java lessons first. A method is a named operation belonging to a class. An argument is a value supplied to it. A return value is the result given back. This lesson uses whole minor units: 250 means 250 cents in this exercise, not an unspecified amount in any currency.

Save the following complete program as `BalanceCheck.java` in a practice folder. A public class's name must match its filename.

```java
public class BalanceCheck {
    static long remaining(long available, long payment) {
        if (available < 0 || payment < 0 || payment > available) {
            throw new IllegalArgumentException("Invalid practice payment");
        }
        return available - payment;
    }

    public static void main(String[] args) {
        long result = remaining(1000, 250);
        if (result != 750) {
            throw new IllegalStateException("Unexpected balance");
        }
        System.out.println(result);
    }
}
```

After installing a Java Development Kit as described in the earlier course, run `javac BalanceCheck.java`, then `java BalanceCheck`. `javac` compiles source into a class file; `java` runs the named class. Expect `750`. If `javac` is not found, check the JDK installation and terminal path rather than renaming the program.

`long` stores a signed whole number. `||` means either condition is true. `throw` stops the normal path and reports an exceptional condition. This example intentionally leaves that exception uncaught so its failure is visible. A production interface would handle it and present an appropriate message without losing the user's work.

## Exercise and answer

Change only the payment argument to 1000: expect 0. Change it to 1001: expect the invalid-payment exception, not a negative balance. The explicit result check runs without enabling Java's optional `assert` mechanism.

Compare the real `LedgerDemo.java` with this exercise. Its decimal-value lesson addresses a different representation. Never mix an amount, a currency and a scale by assumption. This is arithmetic practice, not an implemented bank transfer: it has no accounts, approval, durable ledger or concurrency control. Shared financial operations remain responsibilities of Umicom Framework, even when a Java integration client is used.

[Review the prerequisite course](../../../courses/learning-c/index.html).


## Source and further reading

[Read the related Umicom example](../../../labs/java-ledger/LedgerDemo.java). Path: `content/labs/java-ledger/LedgerDemo.java`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://dev.java/learn/). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../../courses/learning-java/lessons/03-values-methods-and-checks.html).

[Course contents](index.md) · [Previous: Decimal values and checks](02-decimal-values-and-checks.md)

Sammy Hegab · Umicom Foundation · Original learning material.
