# A Java port and a fake repository

[Course contents](index.md) · [Previous: A service boundary before an API call](01-a-service-boundary-before-an-api-call.md) · [Next: Timeouts, retries and control totals](03-timeouts-retries-and-control-totals.md)

## Practise without a licensed server

A port is a small interface expressing what the application needs. An adapter implements it for a particular system. A fake implementation lets us learn the contract without contacting a real server. This program contains no vendor classes and no credentials.

Save the following as TradeLookupLesson.java in your practice directory. The record here is a simple Java class, not a claim about the vendor trade object.

```java
public final class TradeLookupLesson {
    static final class TradeSummary {
        final long id;
        final String currency;
        TradeSummary(long id, String currency) {
            this.id = id;
            this.currency = currency;
        }
    }

    interface TradeRepository {
        TradeSummary findById(long id);
    }

    static final class PracticeRepository implements TradeRepository {
        public TradeSummary findById(long id) {
            return id == 42 ? new TradeSummary(42, "GBP") : null;
        }
    }

    public static void main(String[] args) {
        TradeRepository repository = new PracticeRepository();
        TradeSummary trade = repository.findById(42);
        if (trade == null) {
            System.out.println("Trade not found");
            return;
        }
        System.out.println(trade.id + " " + trade.currency);
    }
}
```

The interface names one operation. PracticeRepository provides its teaching behaviour. main asks through the interface, so replacing the adapter does not require rewriting the display code. null explicitly means not found in this tiny contract; a production contract should distinguish absence from transport or permission failure.

With a JDK installed, optional commands are javac TradeLookupLesson.java and java TradeLookupLesson. Expected output is 42 GBP. No Calypso installation is needed for this fake repository.

## Exercise

Change the lookup argument to 43. Predict the output. Then explain why the adapter should not turn a permission error into Trade not found.

## Explained answer

The fake returns null, so the program prints Trade not found. A permission error means the caller is not allowed to determine or retrieve the result, not that the trade does not exist. An explicit failure contract is necessary for correct audit and troubleshooting. A real adapter must map documented SDK behaviour, not guess from this exercise.

## Continue learning

[Course contents](index.md) · [Previous: A service boundary before an API call](01-a-service-boundary-before-an-api-call.md) · [Next: Timeouts, retries and control totals](03-timeouts-retries-and-control-totals.md)

[Browser edition](../../../courses/introduction-to-calypso-api-development/lessons/02-a-java-port-and-a-fake-repository.html)

## Read the related Umicom source

[Source and context](../sources-and-licensing.md). Follow the source and licensing notes before using vendor APIs.
