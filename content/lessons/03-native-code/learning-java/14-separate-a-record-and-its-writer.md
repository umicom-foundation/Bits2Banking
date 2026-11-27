<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/14-separate-a-record-and-its-writer.md

PURPOSE:
  Teach separate a record and its writer with a small runnable example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

# Separate a record and its writer

Use a delivery record to keep a site and its box count together. Then put output behind a small interface so another writer can reuse the same reporting method.

Complete the previous lesson before trying this one. Use the same JDK and a writable practice folder.

## Try it

1. Save `DeliveryReport.java`. Find the two values declared in `Delivery`. The compact constructor checks their validity.
2. Read `LineWriter`. It says any writer must supply a `write` method that accepts a string.
3. Read `ConsoleWriter`. This class implements the interface and displays the line in the terminal.
4. Run the program and trace the call from `main` to `report` to `write`.

## Example files

### DeliveryReport.java

[Open DeliveryReport.java](../../../labs/java-path/DeliveryReport.java)

~~~java
public class DeliveryReport {
    record Delivery(String site, int boxes) {
        Delivery {
            // Validation belongs at the point where a delivery is created.
            if (site == null || site.isBlank() || boxes < 0) {
                throw new IllegalArgumentException("Invalid delivery");
            }
        }
    }

    interface LineWriter {
        void write(String line);
    }

    static final class ConsoleWriter implements LineWriter {
        public void write(String line) {
            System.out.println(line);
        }
    }

    static void report(Delivery delivery, LineWriter writer) {
        // The reporting method can use any writer that fulfils the contract.
        writer.write(delivery.site() + ": " + delivery.boxes());
    }

    public static void main(String[] args) {
        report(new Delivery("North", 4), new ConsoleWriter());
    }
}
~~~

## Run it

~~~text
javac DeliveryReport.java
java -cp . DeliveryReport
~~~

The program output to check is shown below.

~~~text
North: 4
~~~

## Read the result

`delivery.site()` and `delivery.boxes()` are accessors generated for the record components. A record fits a simple report value. A class with a separate interface fits a behaviour that could have several implementations. A C design can use a struct for data and an explicit callback for the reporting action.

## Practise

Change 4 to −1 in the delivery creation. The constructor should reject it. Restore the original value and confirm the valid report again.

## Fix a problem

If the compiler says a writer does not implement `write`, compare the method name, parameter type and access modifier with the interface.

## Reference

- [Classes, interfaces and records](https://dev.java/learn/language/oop/)

[Previous · Total an array with a method](13-total-an-array-with-a-method.md) · [Next · Group deliveries with collections](15-group-deliveries-with-collections.md)
