/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/java-path/ParallelReports.java
 *
 * PURPOSE:
 *   Run the referenced Learning Java exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;

public class ParallelReports {
    static int request(String site) throws InterruptedException {
        // The pause stands in for a blocking read. This lab uses no network.
        Thread.sleep(30);
        return switch (site) {
            case "North" -> 4;
            case "South" -> 3;
            default -> throw new IllegalArgumentException("Unknown site");
        };
    }

    public static void main(String[] args) {
        try (var executor = Executors.newVirtualThreadPerTaskExecutor()) {
            var north = executor.submit(() -> request("North"));
            var south = executor.submit(() -> request(args.length == 0 ? "South" : args[0]));
            // Read results in a fixed order. Completion order can differ.
            int total = north.get() + south.get();
            System.out.println("Total: " + total);
        } catch (InterruptedException error) {
            Thread.currentThread().interrupt();
            System.err.println("Interrupted while collecting reports.");
            System.exit(1);
        } catch (ExecutionException error) {
            System.err.println("Report failed: " + error.getCause().getMessage());
            System.exit(1);
        }
    }
}
